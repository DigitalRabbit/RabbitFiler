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
 * \file    filerecord.cc
 * \brief   digirabi::FileRecord source file
 *
 * \author  Digital Rabbit(digital.rabbit.jp@gmail.com)
 * \date    2012/02/29
 */

#include "filelist.h"

namespace digirabi {

/*!
 * 自身にレコードの Column 情報を登録します。
 */
FileRecord::FileRecord()
{
    /*! \todo ここで、設定に合わせた Column の調整ができるようにしておく。 */
    add( mName );
    add( mSize );
    add( mType );
    add( mAccess );
    add( mUpdate );
    add( mHolder );

    return;
}

/*! <b>現在未使用</b> */
FileRecord::~FileRecord() {}

} // namespace digirabi

