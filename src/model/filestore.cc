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

#include <iostream>

#include <glibmm/fileutils.h>

#include <gtkmm/stock.h>

namespace digirabi {

/*!
 * ListStore instance を生成し、 FileRecord class の内容で列情報を初期化します。\n
 */
FileStore::FileStore()
{
    FUNC_LOG();

    mrStore = Gtk::ListStore::create( mRecord );
}

/*! <b>現在未使用</b> */
FileStore::~FileStore()
{
    FUNC_LOG();
}

/*!
 * 渡された TreeView へと ListStore を設定し、\n
 * Store 内の Column を TreeView へと表示するように設定を行います。\n
 * その際、以下の設定も同時に行います。\n
 *  \li  TreeView へメンバの ListStore を登録。
 *  \li  TreeView を親 View として設定。
 *  \li  TreeView へ Callback を登録( Activate event )。
 *  \li  TreeSelection を取得。
 *  \li  各列でのソートを可能にする。
 * また、 Path 情報から生成された File インスタンスと「名前」フィールドからなる File 用マップも同時に生成します。
 *
 * \param[in]   apTreeView  設定先 TreeView instance pointer
 */
void FileStore::attach( Gtk::TreeView* apTreeView )
{
    FUNC_LOG();

    apTreeView->set_model( mrStore );

    mpTreeView = apTreeView;
    mpTreeView->signal_row_activated().connect( sigc::mem_fun( *this, &FileStore::onRowActivated ) );

    /* ListStore に登録済みの列を TextView に登録し、ソートを可能にする。
     * ちなみに、取得した Record の内容は、以下の通り。
     *
     * record
     * ├ first     -> 列 Index
     * └ second    -> 列情報 std::pair インスタンスポインタ
     *    ├ first  -> 列ヘッダ文字列
     *    └ second -> 列定義 TreeModelColumn インスタンス
     */
    /*! \todo Record 登録は FileRecord にやらせたほうがいいか… */
    for( FileRecord::ColumnPair record : mRecord.mColumnMap )
    {
        ColumnInfo* info = record.second;
        int columnIndex = static_cast<int>( record.first );

        /*! \todo ここに関しては、このままここに書いておくのは望ましくない。 */
        if( record.first == FileRecord::ColumnIndex::NAME )
        {

            /* アイコン付き名前列を作って登録しておく */
            Gtk::TreeView::Column* viewCol = Gtk::manage( new Gtk::TreeViewColumn( info->getColumnName() ) );
            viewCol->set_sort_column( *( info->getCastPointer<ColumnInfo::StringColumn>() ) );
            viewCol->set_resizable( true );

            // アイコン列作成
            Gtk::CellRendererPixbuf* renPixbuf = Gtk::manage( new Gtk::CellRendererPixbuf() );
            viewCol->pack_start( *renPixbuf, false );
            viewCol->add_attribute( *renPixbuf, "pixbuf", static_cast<int>( FileRecord::ColumnIndex::ICON ) );

            // 名前列作成
            Gtk::CellRendererText* renText = Gtk::manage( new Gtk::CellRendererText() );
            viewCol->pack_start( *renText, false );
            viewCol->add_attribute( *renText, "text", columnIndex );

            mpTreeView->insert_column( *viewCol, columnIndex );
            mrStore->set_sort_func( static_cast<int>( FileRecord::ColumnIndex::NAME ), sigc::mem_fun( *this, &FileStore::onNameSort ) );
            continue;
        }
        else if( record.first == FileRecord::ColumnIndex::ICON )
        {
            continue;
        }

        mpTreeView->insert_column( info->getColumnName(), *( info->getCastPointer<ColumnInfo::StringColumn>() ), columnIndex );
        Gtk::TreeView::Column* pColumn = apTreeView->get_column( columnIndex );
        if( pColumn != nullptr )
        {
            pColumn->set_sort_column( *( info->getCastPointer<ColumnInfo::StringColumn>() ) );
            pColumn->set_resizable( true );
        }
    }

    /*! \todo 直接ホームフォルダではなく、初期設定値に従うように修正したい */
    moveDirectory( Glib::get_home_dir() );

    return;
}

/*!
 * リストの行がユーザー操作により決定された場合にコールされます。
 *
 * \note    「決定」とは、主に Enter キー押下、 マウスダブルクリックの事を指しています。
 *
 * \param[in]   aPath       決定時のリスト行 Path instance
 * \param[in]   aColumn     決定時のリスト列 TreeViewColumn instance pointer
 */
void FileStore::onRowActivated( const Gtk::TreeModel::Path& aPath, Gtk::TreeViewColumn* aColumn )
{
    FUNC_LOG();

    // Path オブジェクトから行情報を取得し、 File 別のランチャーを起動。
    Gtk::TreeModel::iterator iter = mrStore->get_iter( aPath );
    if( iter != nullptr )
    {
        Gtk::TreeModel::Row row = *iter;

        FileRecord::StringColumn* nameCol = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::NAME );
        std::map<GString, File>::iterator filePair = mFileMap.find( row[ *nameCol ] );
        File file = ( *filePair ).second;
        if( file.isDirectory() )
        {
            moveDirectory( file.getFilePath() );
        }
        else
        {
            file.launchApp();
        }
    }

    return;
}

/*!
 * 表示中ディレクトリパスを変更し、ファイル一覧を再取得します。
 *
 * \param[in]   aDirPath    決定時のリスト行 Path instance
 * \return      bool        リスト取得結果
 * \retval      true        取得成功
 * \retval      false       取得失敗( 存在しないパスの場合も含む )
 */
bool FileStore::moveDirectory( const GString& aDirPath )
{
    FUNC_LOG();

    // パスチェック
    if( !Glib::file_test( aDirPath, Glib::FileTest::FILE_TEST_IS_DIR ) )
    {
        return ( false );
    }

    // 現リストを全て削除
    mrStore->clear();   // ListStore
    mFileMap.clear();   // File インスタンスマップ

    // Dir インスタンスを生成して、ファイル名称リストを生成
    Glib::Dir dir( aDirPath );
    std::list<std::string> entries( dir.begin(), dir.end() );

    /*! \todo ユーティリティを使ってファイル情報を全て取得する。 */
    try
    {
        FileRecord::StringColumn* nameCol   = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::NAME );
        FileRecord::StringColumn* sizeCol   = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::SIZE );
        FileRecord::StringColumn* typeCol   = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::TYPE );
        FileRecord::StringColumn* accessCol = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::ACCESS );
        FileRecord::StringColumn* updateCol = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::UPDATE );
        FileRecord::StringColumn* ownerCol  = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::OWNER );
        FileRecord::IconColumn*   iconCol   = mRecord.getModelColumn<FileRecord::IconColumn>( FileRecord::ColumnIndex::ICON );

        // 先頭にバック用の行を生成
        Gtk::TreeModel::Row row = *( mrStore->append() );
        // 「戻る」のストックアイコンを使用
        row[ *iconCol ] = mpTreeView->render_icon_pixbuf( Gtk::Stock::GO_BACK, Gtk::ICON_SIZE_MENU );
        row[ *nameCol ] = "..";
        mFileMap.insert( std::pair<GString, File>( "..", File( Glib::path_get_dirname( aDirPath ) ) ) );

        // モデルに行を追加するとビューの表示も同時に更新される
        for( std::string entry : entries )
        {
            // ファイルパスを生成して File インスタンスを生成
            File file( Glib::build_filename( aDirPath, entry ) );

            row = *( mrStore->append() );
            row[ *iconCol ] = file.getIcon();
            row[ *nameCol ] = file.getName();
            row[ *sizeCol ] = file.getSize();
            row[ *typeCol ] = file.getContentTypeDescription();
            row[ *accessCol ] = file.getAccessString();
            row[ *updateCol ] = file.getUpdateTime();
            row[ *ownerCol ] = file.getOwner();

            mFileMap.insert( std::pair<GString, File>( file.getName(), file ) );
        }
    }
    catch( std::invalid_argument& ex )
    {
        std::cerr << "Throwing exception!! : " << ex.what() << std::endl;

        dir.close();
        return ( false );
    }

    dir.close();
    return ( true );
}

int FileStore::onNameSort( const Gtk::TreeModel::iterator& aValueA, const Gtk::TreeModel::iterator& aValueB )
{
    // Iterator からファイル名を取得する。
    FileRecord::StringColumn* nameCol = mRecord.getModelColumn<FileRecord::StringColumn>( FileRecord::ColumnIndex::NAME );
    Gtk::TreeModel::Row rowA = *( aValueA );
    Gtk::TreeModel::Row rowB = *( aValueB );

    // 「..」は最上段
    if( rowA[ *nameCol ] == ".." )
    {
        return ( -1 );
    }
    else if( rowB[ *nameCol ] == ".." )
    {
        return ( 1 );
    }

    // File インスタンスを取得
    std::map<GString, File>::iterator filePair = mFileMap.find( rowA[ *nameCol ] );
    File fileA = ( *filePair ).second;

    filePair = mFileMap.find( rowB[ *nameCol ] );
    File fileB = ( *filePair ).second;

    // ディレクトリは優先
    if( fileA.isDirectory() && !fileB.isDirectory() )
    {
        return ( -1 );
    }
    else if( !fileA.isDirectory() && fileB.isDirectory() )
    {
        return ( 1 );
    }

    // ここまで来たら、文字列で比較をかける
    return ( fileA.getName().compare( fileB.getName() ) );
}

} // namespace digirabi

