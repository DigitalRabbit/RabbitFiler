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
 * \file    main.cc
 * \brief   Entry point source file
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/28
 */
#include "filerwindow.h"

#include <iostream>

#include <glibmm/refptr.h>
#include <glibmm/ustring.h>

#include <gtkmm/main.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

/*! \brief エントリポイント
 *
 * Rabbit Filer のエントリポイントです。\n
 * Gtk::Builder で glade ファイルから window を生成、\n
 * GTK+ を使用してメインループへダイアログを引き渡しています。\n
 *
 * \note    読み込むファイルパス : <b><i>&lt;Glib::get_home_dir()/.rabbitfiler/res/filer.glade&gt;</i></b>
 *
 * \param[in]   argc    コマンドライン引数の数
 * \param[in]   argv    コマンドライン引数配列
 *
 * \return      int     プログラム終了状態
 * \retval      EXIT_SUCCESS    正常終了
 * \retval      EXIT_FAILURE    異常終了
 */
int main( int argc, char* argv[] )
{
    // Create Main roop instance.
    Gtk::Main kit( argc, argv );

    // Load the Glade file and instiate its widgets:
    Glib::RefPtr< Gtk::Builder > builder = Gtk::Builder::create();
    try
    {
        Glib::ustring filepath( Glib::get_home_dir() );
        filepath += "/.rabbitfiler/res/filer.glade";
        if( Glib::file_test( filepath, Glib::FILE_TEST_EXISTS | Glib::FILE_TEST_IS_REGULAR ) ) {
            builder->add_from_file( filepath );
        }
        else {
            std::cerr << "Resource file ( " << filepath << " ) is not found." << std::endl;
            return ( EXIT_FAILURE );
        }
    }
    catch( const Glib::FileError& ex )
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return ( EXIT_FAILURE );
    }
    catch( const Glib::MarkupError& ex )
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return ( EXIT_FAILURE );
    }
    catch( const Gtk::BuilderError& ex )
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return ( EXIT_FAILURE );
    }

    // Create window.
    digirabi::FilerWindow* pWindow = nullptr;
    builder->get_widget_derived( "wd_filer", pWindow );
    if( pWindow != nullptr )
    {
        // Run window.
        kit.run( *pWindow );
        delete pWindow;
    }

    return ( EXIT_SUCCESS );
}

