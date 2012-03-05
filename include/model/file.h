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
 * \file    file.h
 *
 * \brief   ファイル系 Class header file
 *
 * ファイルを表す Class を記述しているヘッダーファイルです。\n
 * このクラスを使用することでファイル操作を行うことが簡単になります。
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/03/05
 */
#pragma once

#include <stdexcept>

#include <glibmm/refptr.h>

#include <giomm/file.h>
#include <giomm/fileinfo.h>

namespace digirabi {

/*! \brief ファイル Class
 *
 * Rabbit Filer の file / Directory を表す Class です。\n
 * ここで定義されている情報がファイルそのものを表すことになります。
 *
 * \author  Digital Rabbit
 * \since   2012/03/05
 */
class File
{
public:
// ----- value and function -----
    /*! \brief コンストラクタ */
    File( const Glib::ustring& aPath ) throw( std::invalid_argument );
    /*! \brief デストラクタ */
    ~File();

    /*! \brief ファイルサイズ取得 */
    Glib::ustring getFileSize();

protected:

private:
// ----- typedef and inner class -----
    /*! \brief このクラスで使用されるデフォルト文字列 */
    typedef Glib::ustring GString;
    /*! \brief GIO::File class 参照ポインタ */
    typedef Glib::RefPtr< Gio::File > RefGFile;
    /*! \brief GIO::FileInfo class 参照ポインタ */
    typedef Glib::RefPtr< Gio::FileInfo > RefGFileInfo;

// ----- value and function -----
    /*! \brief ファイルパス */
    const GString mFilePath;
    /*! \brief ファイル情報 */
    RefGFileInfo mFileInfo;

};

} // namespace digirabi

