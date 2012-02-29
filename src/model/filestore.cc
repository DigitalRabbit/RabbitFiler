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
 * \file    filestore.cc
 * \brief   digirabi::FileStore source file
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/29
 */

#include "model/filelist.h"

namespace digirabi {

/*! TreeView 上で表示される mName 列 Header */
const FileStore::gString FileStore::COLUMN_NAME = "名前";
/*! TreeView 上で表示される mSize 列 Header */
const FileStore::gString FileStore::COLUMN_SIZE = "サイズ";
/*! TreeView 上で表示される mType 列 Header */
const FileStore::gString FileStore::COLUMN_TYPE = "種類";
/*! TreeView 上で表示される mAccess 列 Header */
const FileStore::gString FileStore::COLUMN_ACCESS = "アクセス権";
/*! TreeView 上で表示される mUpdate 列 Header */
const FileStore::gString FileStore::COLUMN_UPDATE = "更新日時";
/*! TreeView 上で表示される mHolder 列 Header */
const FileStore::gString FileStore::COLUMN_HOLDER = "所有者";

/*!
 * ListStore instance を生成し、以下の初期化を行います。\n
 */
FileStore::FileStore()
{
    mrStore = Store::create( mRecord );
}

/*! <b>現在未使用</b> */
FileStore::~FileStore() {}

/*!
 * 渡された TreeView へと ListStore を設定し、\n
 * Store 内の Column を TreeView へと表示するように設定を行います。
 *
 * \param[in]   apTreeView  設定先 TreeView instance pointer
 */
void FileStore::attach( Gtk::TreeView* apTreeView )
{
    apTreeView->set_model( mrStore );

    /*! \todo vector なりを使って、巧くループさせる */
    apTreeView->append_column( "名前", mRecord.mName );
    apTreeView->append_column( "サイズ", mRecord.mSize );
    apTreeView->append_column( "種類", mRecord.mType );
    apTreeView->append_column( "アクセス権", mRecord.mAccess );
    apTreeView->append_column( "更新日時", mRecord.mUpdate );
    apTreeView->append_column( "所有者", mRecord.mHolder );

    return;
}

} // namespace digirabi

