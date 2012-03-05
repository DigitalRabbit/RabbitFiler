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

namespace digirabi {

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
        GString what = "Unknown file or directory path.\nValue : " + aPath;
        throw std::invalid_argument( what );
    }

    RefGFile file = Gio::File::create_for_path( aPath );
    mFileInfo = file->query_info();
//    std::list< GString > infoList = info->list_attributes( "standard" );
//    Glib::ustring str;
//    for( Glib::ustring work : infoList )
//    {
//        str += work + ", ";
//    }
//
//    std::cout << "Attributes value : " << str << std::endl;
//    std::cout << "File content type : " << info->get_attribute_as_string( "standard::content-type" ) << std::endl;
    return;
}

/*! <b>現在未使用</b> */
File::~File() {}

/*!
 * FileInfo から <b><i>&lt;standard::size&gt;</i></b> の属性を Glib::ustring で返却します。
 *
 * \return Glib::ustring    <b><i>&lt;standard::size&gt;</i></b> 属性値
 */
Glib::ustring File::getFileSize()
{
    return ( mFileInfo->get_attribute_as_string( "standard::size" ) );
}

} // namespace digirabi

