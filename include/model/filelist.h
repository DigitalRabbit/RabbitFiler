/*-************************************************************
 *  ____            _        _   ____       _     _       _
 * |  _ \(_) __ _(_) |_ __ _| | |  _ \ __ _| |__ | |__ (_) |_
 * | | | | |/ _` | | __/ _` | | | |_) / _` | '_ \| '_ \| | __|
 * | |_| | | (_| | | |_ (_| | | |  _ < (_| | |_) | |_) | | |_
 * |____/|_|\__, |_|\__\__,_|_| |_| \_\__,_|_.__/|_.__/|_|\__|
 *          |___/
 **************************************************************
 * Copyright(C) 2012 Digital Rabbit All Rights Reserved.  *//*!
 *
 * \file    filelist.h
 *
 * \brief   ファイル一覧系 Class header file
 *
 * ファイル一覧を表示するために使用する Class を記述しているヘッダーファイルです。\n
 * ここに記述されているのは TreeModelColumnRecord, ListStore を簡便に使用するための Class 群です。
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/29
 */
#include "generic.h"
#include "model/file.h"

#include <map>
#include <stdexcept>
#include <typeinfo>
#include <iostream>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <gdkmm/pixbuf.h>

#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>

namespace digirabi {

class FileRecord;
class FileStore;

/*! \brief Column - Name ペア Class
 *
 * 各列の名称と Gtk::TreeModelColumn をまとめている Class です。\n
 * Gtk::TreeModelColumn は template class であるため、\n
 * void* として、ポインタを保管するようになっています。
 *
 * \note    void* の実体は、列に設定されている Gtk::TreeModelColumn<T> のポインタです。\n
 *          また、ここで設定した pointer 先のメモリ領域は、デストラクタで解放されます。
 *
 * \attention   ここで設定できる TreeModelColumn は、 typedef で定義されているものだけになります。
 */
class ColumnInfo
{
// ----- typedef -----
public:
    /*! \brief 文字列 */
    typedef Glib::ustring GString;
    /*! \brief ファイル一覧上の列種別( 文字列列 ) */
    typedef Gtk::TreeModelColumn<GString> StringColumn;
    /*! \brief ファイル一覧上の列種別( アイコン ) */
    typedef Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> IconColumn;

public:
    // コンストラクタ
    template<class TreeModel>
    ColumnInfo( GString aName, TreeModel* aColumn ) throw( std::invalid_argument )
            : mColumnName( aName ), mModelColumn( aColumn ), mInfo( typeid( *aColumn ) )
    {
        FUNC_LOG();

        if( mInfo != typeid( StringColumn ) && mInfo != typeid( IconColumn ) )
        {
            delete aColumn;
            throw std::invalid_argument( "Invalid TreeModelColumn pointer" );
        }
    }

    // デストラクタ
    ~ColumnInfo()
    {
        FUNC_LOG();

        if( mInfo == typeid( StringColumn ) )      delete static_cast<StringColumn*>( mModelColumn );
        else if( mInfo == typeid( IconColumn ) )   delete static_cast<IconColumn*>( mModelColumn );
    }

    // 列タイトル取得
    GString getColumnName()
    {
        return ( mColumnName );
    }

    // type_info 取得
    const std::type_info& getTypeInfo()
    {
        return ( mInfo );
    }

    // ポインタキャスト
    template<class ColumnType>
    ColumnType* getCastPointer()
    {
        ColumnType* result = nullptr;
        if( typeid( ColumnType ) == getTypeInfo() )
        {
            result = static_cast<ColumnType*>( mModelColumn );
        }

        return ( result );
    }

private:
    // 名前
    GString mColumnName;
    // 列オブジェクトポインタ
    void* mModelColumn;
    // ポインタ型情報
    const std::type_info& mInfo;

};

/*! \brief ファイル表示 ColumnRecord
 *
 * Rabbit Filer の file / Directory 情報を表すレコード Class です。\n
 * ここで定義されている情報がファイル一覧で扱うファイル情報の全てになります。
 *
 * \author  Digital Rabbit
 * \since   2012/02/29
 */
class FileRecord : public Gtk::TreeModelColumnRecord
{
    friend class FileStore;

// ----- inner class and enum -----
public:
    /*! \brief 列 ID
     *
     * 各列の Index を表す class enum です。\n
     * ここで定義されている位置が、そのまま列の Index 値となります。
     */
    enum class ColumnIndex
    {
        NAME   = 0, /*!< 名前 */
        SIZE   = 1, /*!< サイズ */
        TYPE   = 2, /*!< 種類 */
        ACCESS = 3, /*!< アクセス権 */
        UPDATE = 4, /*!< 更新日時 */
        OWNER  = 5, /*!< 所有者 */
        ICON   = 6, /*!< ファイルアイコン */
    };

// ----- typedef -----
public:
    /*! \brief 文字列 */
    typedef Glib::ustring GString;

    /*! \brief ファイル一覧上の列種別( 文字列列 ) */
    typedef ColumnInfo::StringColumn StringColumn;
    /*! \brief ファイル一覧上の列種別( アイコン ) */
    typedef ColumnInfo::IconColumn IconColumn;

    /*! \brief インデックスと ColumnInfo のマップ */
    typedef std::map<ColumnIndex, ColumnInfo*> ColumnMap;
    /*! \brief インデックスと ColumnInfo のペア */
    typedef std::pair<ColumnIndex, ColumnInfo*> ColumnPair;

// ----- value and function -----
public:
    /*! \brief コンストラクタ */
    FileRecord();
    /*! \brief デストラクタ */
    ~FileRecord();

    /*! \brief TreeModelColumn 取得
     *
     * 引数を Index として列に定義されている Gtk::TreeModelColumn インスタンスを返却します。
     *
     * \param[in]   aIndex                      取得する Gtk::TreeModelColumn の列 Index
     * \return      FileRecord::StringColumn    列 Index の位置に指定されている Gtk::TreeModelColumn インスタンスポインタ
     * \retval      nullptr                     template の型が合わない
     *
     * \exception   std::invalid_argument   引数に不正な列 Index が渡された
     */
    template<class ColumnType>
    ColumnType* getModelColumn( ColumnIndex aIndex ) throw( std::invalid_argument )
    {
        ColumnMap::iterator iter = mColumnMap.find( aIndex );
        if( iter == mColumnMap.end() )
        {
            throw std::invalid_argument( "Unknown column index." );
        }

        return ( ( *iter ).second->getCastPointer<ColumnType>() );
    }

protected:

private:
    /*! \brief 列の index, 名前と種類のマップ */
    ColumnMap mColumnMap;

};

/*! \brief ファイル一覧 ListStore 管理
 *
 * ファイル一覧のデータを持つ ListStore を管理し、\n
 * 内部との情報変換 Adapter として機能します。
 *
 * \author  Digital Rabbit
 * \since   2012/02/29
 */
class FileStore
{
// ----- typedef -----
private:
    /*! \brief 文字列 */
    typedef Glib::ustring   GString;
    /*! \brief ファイル用リストストア */
    typedef Glib::RefPtr<Gtk::ListStore> RefStore;

// ----- value and function -----
public:
    /*! \brief コンストラクタ */
    FileStore();
    /*! \brief デストラクタ */
    ~FileStore();

    /*! \brief ListStore 設定 */
    void attach( Gtk::TreeView* apTreetView );

protected:

private:
    /*! \brief 接続先 TreeView ポインタ ( 解放不必要 ) */
    Gtk::TreeView* mpTreeView;
    /*! \brief ファイル一覧用 ListStore RefPtr */
    RefStore mrStore;
    /*! \brief Column record */
    FileRecord mRecord;
    /*! \brief Name - File instance map */
    std::map<GString, File> mFileMap;

    /*! \brief リスト行決定 */
    void onRowActivated( const Gtk::TreeModel::Path& aPath, Gtk::TreeViewColumn* aColumn );

};

} // namespace digirabi

