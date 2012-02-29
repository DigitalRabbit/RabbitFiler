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
 * \file    filerwindow.h
 *
 * \brief   メイン Window Class header file
 *
 * アプリケーションのルート Window として機能する Class を記述しているヘッダーファイルです。
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/29
 */

#include "model/filelist.h"

#include <glibmm/refptr.h>

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>

namespace digirabi {

/*! \brief Rabbit Filer メイン Window
 *
 * Rabbit Filer のメインとなる Window Class です。\n
 * 各種 Widget の管理等 UI 制御を行います。
 *
 * \author  Digital Rabbit
 * \since   2012/02/29
 */
class FilerWindow : public Gtk::Window
{
public:
    /*! \brief コンストラクタ */
    FilerWindow( BaseObjectType* aCobject, const Glib::RefPtr< Gtk::Builder >& aRefBuilder );
    /*! \brief デストラクタ */
    virtual ~FilerWindow();

protected:

private:
    /*! \brief GTK+ Builder */
    Glib::RefPtr< Gtk::Builder > mrBuilder;

    /*! \brief 左 pain TreeView */
    Gtk::TreeView* mpLeftView;
    digirabi::FileStore mLeftStore;

    /*! \brief 右 Pain List store */
    Glib::RefPtr< Gtk::ListStore > mrRightStore;

};

} // namespace digirabi

