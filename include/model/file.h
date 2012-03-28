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

#include "generic.h"

#include <stdexcept>

#include <glibmm/refptr.h>

#include <gdkmm/pixbuf.h>

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
// ----- typedef and inner class -----
private:
    /*! \brief このクラスで使用されるデフォルト文字列 */
    typedef Glib::ustring GString;
    /*! \brief GIO::File class 参照ポインタ */
    typedef Glib::RefPtr<Gio::File> RefGFile;
    /*! \brief GIO::FileInfo class 参照ポインタ */
    typedef Glib::RefPtr<Gio::FileInfo> RefGFileInfo;

// ----- value and function -----
public:
    /*! \brief コンストラクタ */
    File( const Glib::ustring& aPath ) throw( std::invalid_argument );
    /*! \brief デストラクタ */
    virtual ~File();

    /*! \brief Name 取得 */
    Glib::ustring getName();
    /*! \brief Size 取得 */
    Glib::ustring getSize();
    /*! \brief Content type 取得 */
    Glib::ustring getContentType();
    /*! \brief Description ( Content type 詳細 ) 取得 */
    Glib::ustring getContentTypeDescription();
    /*! \brief アクセス権情報文字列取得 */
    Glib::ustring getAccessString();
    /*! \brief 更新日時文字列取得 */
    Glib::ustring getUpdateTime();
    /*! \brief 所有者文字列取得 */
    Glib::ustring getOwner();
    /*! \brief ファイルアイコン取得 */
    Glib::RefPtr<Gdk::Pixbuf> getIcon();

    /*! \brief ディレクトリ判定 */
    bool isDirectory();
    /*! \brief パス取得 */
    const Glib::ustring& getFilePath();

    /*! \brief 関連アプリ起動 */
    bool launchApp();

protected:

private:
    /*! \brief Attribute - Name */
    static const GString FILE_NAME;
    /*! \brief Attribute - Size */
    static const GString FILE_SIZE;
    /*! \brief Attribute - Content type */
    static const GString FILE_CONTENT_TYPE;
    /*! \brief Attribute - Update time */
    static const GString FILE_UPDATE_TIME;
    /*! \brief Attribute - Owner user */
    static const GString FILE_OWNER_USER;
    /*! \brief Attribute - Standard icon */
    static const GString FILE_STANDARD_ICON;

    /*! \brief ファイルパス */
    const GString mFilePath;
    /*! \brief ファイル情報 */
    RefGFileInfo mFileInfo;

};

} // namespace digirabi

