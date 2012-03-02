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
 * ここに記述されているのは TreeModelColumnRecord, ListStore を簡便に使用するための Class です。
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/29
 */

#include <map>
#include <stdexcept>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>

namespace digirabi {

class FileRecord;
class FileStore;

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

// ----- typedef and inner class -----
private:
    /*! \brief 文字列 */
    typedef Glib::ustring Gstring;

public:
    /*! \brief ファイル一覧上の列種別( 文字列列 ) */
    typedef Gtk::TreeModelColumn< Gstring > StringColumn;
    /*! \brief 名前と種別のペア */
    typedef std::pair< Gstring, StringColumn > ColumnInfo;

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
        HOLDER = 5, /*!< 所有者 */
    };

// ----- value and function -----
public:
    /*! \brief コンストラクタ */
    FileRecord();
    /*! \brief デストラクタ */
    ~FileRecord();

    /*! \brief TreeModelColumn 取得 */
    StringColumn getTreeModelColumn( ColumnIndex aIndex ) throw( std::invalid_argument );

protected:

private:
    /*! \brief 列の index, 名前と種類のマップ */
    std::map< int, ColumnInfo* > mColumnMap;

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
    typedef Glib::ustring   Gstring;
    /*! \brief ファイル用リストストア */
    typedef Glib::RefPtr< Gtk::ListStore > RefStore;

// ----- value and function -----
public:
    /*! \brief コンストラクタ */
    FileStore();
    /*! \brief デストラクタ */
    virtual ~FileStore();

    /*! \brief ListStore 設定 */
    void attach( Gtk::TreeView* apTreetView );

protected:

private:
    /*! \brief ファイル一覧用 ListStore RefPtr */
    RefStore mrStore;
    /*! \brief Column record */
    FileRecord mRecord;

};

} // namespace digirabi

