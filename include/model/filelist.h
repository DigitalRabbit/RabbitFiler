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

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>

namespace digirabi {

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
public:
    /*! \brief 名前 Column */
    Gtk::TreeModelColumn< Glib::ustring >  mName;
    /*! \brief サイズ Column */
    Gtk::TreeModelColumn< unsigned long long >  mSize;
    /*! \brief 種類 Column */
    Gtk::TreeModelColumn< Glib::ustring >  mType;
    /*! \brief アクセス権 Column */
    Gtk::TreeModelColumn< Glib::ustring >  mAccess;
    /*! \brief 更新日時 Column */
    Gtk::TreeModelColumn< Glib::ustring >  mUpdate;
    /*! \brief 所有者 Column */
    Gtk::TreeModelColumn< Glib::ustring >  mHolder;

    /*! \brief コンストラクタ */
    FileRecord();
    /*! \brief デストラクタ */
    virtual ~FileRecord();

protected:

private:

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
public:
    /*! \brief 文字列 */
    typedef Glib::ustring   gString;
    /*! \brief ファイル用リストストア */
    typedef Gtk::ListStore  Store;

    /*! \brief mName 列名 */
    static const gString COLUMN_NAME;
    /*! \brief mSize 列名 */
    static const gString COLUMN_SIZE;
    /*! \brief mType 列名 */
    static const gString COLUMN_TYPE;
    /*! \brief mAccess 列名 */
    static const gString COLUMN_ACCESS;
    /*! \brief mUpdate 列名 */
    static const gString COLUMN_UPDATE;
    /*! \brief mHolder 列名 */
    static const gString COLUMN_HOLDER;

    /*! \brief コンストラクタ */
    FileStore();
    /*! \brief デストラクタ */
    virtual ~FileStore();

    /*! \brief ListStore 設定 */
    void attach( Gtk::TreeView* apTreetView );

protected:

private:
    /*! \brief ファイル一覧用 ListStore RefPtr */
    Glib::RefPtr< Store > mrStore;
    /*! \brief Column record */
    digirabi::FileRecord mRecord;

};

} // namespace digirabi

