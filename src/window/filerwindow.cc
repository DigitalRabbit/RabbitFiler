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
 * \file    filerwindow.cc
 * \brief   digirabi::FilerWindow source file
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/29
 */

#include "filerwindow.h"

namespace digirabi {

/*!
 * 各種 Widget instance を取得し、コールバック関数の登録を行っています。\n
 * 取得する Instance と 設定するコールバック関数は以下の通りです。
 * <table>
 *  <tr><th>Instance</th><th>Widget name</th><th>Menber</th><th>Callback function</th></tr>
 *  <tr align="center"><td>Gtk::Button</td><td>bt_create</td><td>yes</td><td>onCreateClicked</td></tr>
 *  <tr align="center"><td>Gtk::Button</td><td>bt_cancel</td><td>yes</td><td>onCancelClicked</td></tr>
 *  <tr align="center"><td>Gtk::FileChooserButton</td><td>fcb_project_dir</td><td>yes</td><td>onProjectDirSelected</td></tr>
 * </table>
 *
 * \param[in]   aCobject     基底クラス引渡し用 Object instance
 * \param[in]   aRefBuilder  GTK Builder instance
 */
FilerWindow::FilerWindow( BaseObjectType* aCobject, const Glib::RefPtr< Gtk::Builder >& aRefBuilder )
        : Gtk::Window( aCobject ), mrBuilder( aRefBuilder ), mpLeftView( nullptr )
{
    // Get the Glade-instantiated widget, and connect a signal handler.
    mrBuilder->get_widget( "tv_left", mpLeftView );
    mLeftStore.attach( mpLeftView );
//    mpLeftView->set_model( mrLeftStore );
//
//    mpLeftView->append_column( "名前", mLeftColumnRecord.mName );
//    mpLeftView->append_column( "サイズ", mLeftColumnRecord.mSize );
//    mpLeftView->append_column( "種類", mLeftColumnRecord.mType );
//    mpLeftView->append_column( "アクセス権", mLeftColumnRecord.mAccess );
//    mpLeftView->append_column( "更新日時", mLeftColumnRecord.mUpdateDate );
//    mpLeftView->append_column( "所有者", mLeftColumnRecord.mHolder );

    return;
}

/*! <b>現在未使用</b> */
FilerWindow::~FilerWindow() {}

} // namespace digirabi

