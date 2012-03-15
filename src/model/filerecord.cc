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

#include <iostream>

namespace digirabi {

/*!
 * 自身にレコードの Column 情報を登録します。
 */
FileRecord::FileRecord()
{
    FUNC_LOG();

    // 各 Column の情報を作成
    mColumnMap.insert( ColumnPair( ColumnIndex::NAME  , new ColumnInfo( "名前",       new StringColumn() ) ) );
    mColumnMap.insert( ColumnPair( ColumnIndex::SIZE  , new ColumnInfo( "サイズ",     new StringColumn() ) ) );
    mColumnMap.insert( ColumnPair( ColumnIndex::TYPE  , new ColumnInfo( "種類",       new StringColumn() ) ) );
    mColumnMap.insert( ColumnPair( ColumnIndex::ACCESS, new ColumnInfo( "アクセス権", new StringColumn() ) ) );
    mColumnMap.insert( ColumnPair( ColumnIndex::UPDATE, new ColumnInfo( "更新日時",   new StringColumn() ) ) );
    mColumnMap.insert( ColumnPair( ColumnIndex::OWNER , new ColumnInfo( "所有者",     new StringColumn() ) ) );
    mColumnMap.insert( ColumnPair( ColumnIndex::ICON  , new ColumnInfo( "アイコン",   new IconColumn()   ) ) );

    // Record へ登録
    for( ColumnPair pair : mColumnMap )
    {
        ColumnInfo* column = pair.second;
        if( typeid( StringColumn ) == column->getTypeInfo() )
        {
            add( *( column->getCastPointer<StringColumn>() ) );
        }
        else if( typeid( IconColumn ) == column->getTypeInfo() )
        {
            add( *( column->getCastPointer<IconColumn>() ) );
        }
    }

    return;
}

/*!
 * 列インデックスマップ( FileRecord::mColumnMap )内に生成した StringColumn メモリ領域を delete します。
 */
FileRecord::~FileRecord()
{
    FUNC_LOG();

    for( ColumnPair pair : mColumnMap )
    {
        delete pair.second;
    }

    return;
}

} // namespace digirabi

