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
 * アプリケーションのルート Window として機能する
 * Class を記述しているヘッダーファイルです。
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/29
 */

#include "generic.h"
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
// ----- typedef -----
private:
    /*! \brief GTK Builder ( 参照ポインタ ) */
    typedef Glib::RefPtr<Gtk::Builder> RefGtkBuilder;

// ----- value and function -----
public:
    /*! \brief コンストラクタ */
    FilerWindow( BaseObjectType* aCobject, const RefGtkBuilder& aRefBuilder );
    /*! \brief デストラクタ */
    virtual ~FilerWindow();

protected:

private:
    /*! \brief GTK+ Builder */
    RefGtkBuilder mrBuilder;

    /*! \brief 左 pain TreeView */
    Gtk::TreeView* mpLeftView;
    /*! \brief 左 pain ListStore */
    digirabi::FileStore mLeftStore;

    /*! \brief 右 pain TreeView */
    Gtk::TreeView* mpRightView;
    /*! \brief 右 pain ListStore */
    digirabi::FileStore mRightStore;

};

} // namespace digirabi

