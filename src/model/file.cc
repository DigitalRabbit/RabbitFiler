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
 * \file    file.cc
 * \brief   digirabi::File source file
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/03/05
 */

#include "file.h"

#include <iostream>
#include <list>

#include <fcntl.h>

#include <giomm/appinfo.h>
#include <giomm/contenttype.h>

namespace digirabi {

/*! File attribute - Name */
const Glib::ustring File::FILE_NAME = G_FILE_ATTRIBUTE_STANDARD_NAME;
/*! File attribute - Size */
const Glib::ustring File::FILE_SIZE = G_FILE_ATTRIBUTE_STANDARD_SIZE;
/*! File attribute - Content type */
const Glib::ustring File::FILE_CONTENT_TYPE = G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE;

/*!
 * 引き渡されたファイルパスに対してファイル存在チェックを行い、\n
 * ファイルが存在していない場合は Excepsion を throw 、\n
 * ファイルが存在していた場合には FileInfo を取得して、 path をメンバへと設定します。
 *
 * \param[in]   aPath   このインスタンスが表すファイルの path
 *
 * \exception    std::invalid_argument  指定した path のファイルが存在しない
 */
File::File( const GString& aPath ) throw( std::invalid_argument )
    : mFilePath( aPath )
{
    if( mFilePath.empty() || !Glib::file_test( mFilePath, Glib::FILE_TEST_EXISTS ) )
    {
        GString what = "Unknown file or directory path.\nValue : " + mFilePath;
        throw std::invalid_argument( what );
    }

    RefGFile file = Gio::File::create_for_path( mFilePath );
    mFileInfo = file->query_info();

    return;
}

/*! <b>現在未使用</b> */
File::~File() {}

/*!
 * FileInfo から <b><i>&lt;standard::name&gt;</i></b> の属性を Glib::ustring で返却します。
 *
 * \return Glib::ustring    <b><i>&lt;standard::name&gt;</i></b> 属性値
 */
Glib::ustring File::getName()
{
    return ( mFileInfo->get_attribute_as_string( FILE_NAME ) );
}

/*!
 * FileInfo から <b><i>&lt;standard::size&gt;</i></b> の属性を Glib::ustring で返却します。
 *
 * \return Glib::ustring    <b><i>&lt;standard::size&gt;</i></b> 属性値
 */
Glib::ustring File::getSize()
{
    return ( mFileInfo->get_attribute_as_string( FILE_SIZE ) );
}

/*!
 * FileInfo から <b><i>&lt;standard::content_type&gt;</i></b> の属性を Glib::ustring で返却します。
 *
 * \return Glib::ustring    <b><i>&lt;standard::content_type&gt;</i></b> 属性値
 */
Glib::ustring File::getContentType()
{
    return ( mFileInfo->get_attribute_as_string( FILE_CONTENT_TYPE ) );
}

/*!
 * FileInfo から <b><i>&lt;standard::content_type&gt;</i></b> を取得し、\n
 * Content type の詳細( <i>human readable description</i> と言っている )を返却します。
 *
 * \return Glib::ustring    content type 詳細文字列 ( <i>human readable description</i> )
 */
Glib::ustring File::getContentTypeDescription()
{
    return ( Gio::content_type_get_description( mFileInfo->get_attribute_as_string( FILE_CONTENT_TYPE ) ) );
}

/*!
 * FileInfo から <b><i>&lt;unix::mode&gt;</i></b> を取得し mode の値を解析、\n
 * その後、アクセス権文字列を返却します。
 *
 * \note モードの解析には STAT の Man page に従って、以下のマスク値を使用しています。\n
 *       <table>
 *          <tr><th>Mask name</th><th>Value</th><th>Description</th></tr>
 *          <tr><td>S_IFM</td><td>0x0170000</td><td>ファイル種別を示すビット領域を表すビットマスク</td></tr>
 *          <tr><td>S_IFSOCK</td><td>0x0140000</td><td>ソケット</td></tr>
 *          <tr><td>S_IFLNK</td><td>0x0120000</td><td>シンボリック・リンク</td></tr>
 *          <tr><td>S_IFREG</td><td>0x0100000</td><td>通常のファイル</td></tr>
 *          <tr><td>S_IFBLK</td><td>0x0060000</td><td>ブロック・デバイス</td></tr>
 *          <tr><td>S_IFDIR</td><td>0x0040000</td><td>ディレクトリ</td></tr>
 *          <tr><td>S_IFCHR</td><td>0x0020000</td><td>キャラクター・デバイス</td></tr>
 *          <tr><td>S_IFIFO</td><td>0x0010000</td><td>FIFO</td></tr>
 *          <tr><td>S_ISUID</td><td>0x0004000</td><td>set-user-ID bit</td></tr>
 *          <tr><td>S_ISGID</td><td>0x0002000</td><td>set-group-ID bit</td></tr>
 *          <tr><td>S_ISVTX</td><td>0x0001000</td><td>スティッキー・ビット</td></tr>
 *          <tr><td>S_IRWXU</td><td>0x00700</td><td>ファイル所有者のアクセス許可用のビットマスク</td></tr>
 *          <tr><td>S_IRUSR</td><td>0x00400</td><td>所有者の読み込み許可</td></tr>
 *          <tr><td>S_IWUSR</td><td>0x00200</td><td>所有者の書き込み許可</td></tr>
 *          <tr><td>S_IXUSR</td><td>0x00100</td><td>所有者の実行許可</td></tr>
 *          <tr><td>S_IRWXG</td><td>0x00070</td><td>グループのアクセス許可用のビットマスク</td></tr>
 *          <tr><td>S_IRGRP</td><td>0x00040</td><td>グループの読み込み許可</td></tr>
 *          <tr><td>S_IWGRP</td><td>0x00020</td><td>グループの書き込み許可</td></tr>
 *          <tr><td>S_IXGRP</td><td>0x00010</td><td>グループの実行許可</td></tr>
 *          <tr><td>S_IRWXO</td><td>0x00007</td><td>他人 (others) のアクセス許可用のビットマスク</td></tr>
 *          <tr><td>S_IROTH</td><td>0x00004</td><td>他人の読み込み許可</td></tr>
 *          <tr><td>S_IWOTH</td><td>0x00002</td><td>他人の書き込み許可</td></tr>
 *          <tr><td>S_IXOTH</td><td>0x00001</td><td>他人の実行許可</td></tr>
 *       </table>
 *
 * \return Glib::ustring    アクセス権文字列
 */
Glib::ustring File::getAccessString()
{
    GString result;

    // mode を取得して、アクセス権関連でマスクする。
    guint32 mode = mFileInfo->get_attribute_uint32( "unix::mode" );

    // ファイルタイプを作成
    guint32 type = mode & S_IFMT;
    if( ( type & S_IFDIR ) != 0 )       result += "d";
    else if( ( type & S_IFREG ) != 0 )  result += "-";
    else if( ( type & S_IFLNK ) != 0 )  result += "l";
    else                                result += "-";

    // アクセス権限を作成
    guint32 access = mode & ( S_IRWXU | S_IRWXG | S_IRWXO );
    if( ( access & S_IRUSR ) != 0 ) result += "r";
    else                            result += "-";
    if( ( access & S_IWUSR ) != 0 ) result += "w";
    else                            result += "-";
    if( ( access & S_IXUSR ) != 0 ) result += "x";
    else                            result += "-";

    if( ( access & S_IRGRP ) != 0 ) result += "r";
    else                            result += "-";
    if( ( access & S_IWGRP ) != 0 ) result += "w";
    else                            result += "-";
    if( ( access & S_IXGRP ) != 0 ) result += "x";
    else                            result += "-";

    if( ( access & S_IROTH ) != 0 ) result += "r";
    else                            result += "-";
    if( ( access & S_IWOTH ) != 0 ) result += "w";
    else                            result += "-";
    if( ( access & S_IXOTH ) != 0 ) result += "x";
    else                            result += "-";

    return ( result );
}

/*!
 * ファイルに関連付けされたアプリケーションを起動します。
 *
 * \return  bool    起動可否
 * \retval  true    成功
 * \retval  false   失敗
 *
 * \todo nautilus 等で変更したアプリケーションを起動する方法を調査
 */
bool File::launchApp()
{
    GString contentType = mFileInfo->get_attribute_as_string( FILE_CONTENT_TYPE );
    Glib::RefPtr< Gio::AppInfo > info = Gio::AppInfo::get_default_for_type( contentType );

    return ( info->launch( Gio::File::create_for_path( mFilePath ) ) );
}

} // namespace digirabi

