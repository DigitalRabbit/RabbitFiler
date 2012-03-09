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

#include <gtkmm/paned.h>

namespace digirabi {

/*!
 * 左右ペイン用の Gtk::TreeView を取得し、\n
 * リストストアとして digirabi::FileStore を attach しています。
 *
 * \param[in]   aCobject     基底クラス引渡し用 Object instance
 * \param[in]   aRefBuilder  GTK Builder instance
 */
FilerWindow::FilerWindow( BaseObjectType* aCobject, const Glib::RefPtr<Gtk::Builder>& aRefBuilder )
        : Gtk::Window( aCobject ), mrBuilder( aRefBuilder ), mpLeftView( nullptr )
{
    // Get the Glade-instantiated widget, and connect a signal handler.
    mrBuilder->get_widget( "tv_left", mpLeftView );
    mLeftStore.attach( mpLeftView );

    mrBuilder->get_widget( "tv_right", mpRightView );
    mRightStore.attach( mpRightView );

    return;
}

/*! <b>現在未使用</b> */
FilerWindow::~FilerWindow() {}

} // namespace digirabi

