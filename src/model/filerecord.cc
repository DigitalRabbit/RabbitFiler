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
    // 各 Column の情報を作成
    mColumnMap.insert( std::pair< int, ColumnInfo* >
            ( static_cast< int >( ColumnIndex::NAME   ), new ColumnInfo( "名前",       StringColumn() ) ) );
    mColumnMap.insert( std::pair< int, ColumnInfo* >
            ( static_cast< int >( ColumnIndex::SIZE   ), new ColumnInfo( "サイズ",     StringColumn() ) ) );
    mColumnMap.insert( std::pair< int, ColumnInfo* >
            ( static_cast< int >( ColumnIndex::TYPE   ), new ColumnInfo( "種類",       StringColumn() ) ) );
    mColumnMap.insert( std::pair< int, ColumnInfo* >
            ( static_cast< int >( ColumnIndex::ACCESS ), new ColumnInfo( "アクセス権", StringColumn() ) ) );
    mColumnMap.insert( std::pair< int, ColumnInfo* >
            ( static_cast< int >( ColumnIndex::UPDATE ), new ColumnInfo( "更新日時",   StringColumn() ) ) );
    mColumnMap.insert( std::pair< int, ColumnInfo* >
            ( static_cast< int >( ColumnIndex::HOLDER ), new ColumnInfo( "所有者",     StringColumn() ) ) );

    // Record へ登録
    for( std::pair< int, ColumnInfo* > record : mColumnMap )
    {
        add( ( *record.second ).second );
    }

    return;
}

/*!
 * 列インデックスマップ( FileRecord::mColumnMap )内に生成した StringColumn メモリ領域を delete します。
 */
FileRecord::~FileRecord()
{
    for( std::pair< int, ColumnInfo* > record : mColumnMap )
    {
        delete record.second;
    }

    return;
}

/*!
 * 引数を Index として列に定義されている Gtk::TreeModelColumn インスタンスを返却します。
 *
 * \param[in]   aIndex                      取得する Gtk::TreeModelColumn の列 Index
 * \return      FileRecord::StringColumn    列 Index の位置に指定されている Gtk::TreeModelColumn インスタンスポインタ
 *
 * \exception   std::invalid_argument   引数に不正な列 Index が渡された
 */
FileRecord::StringColumn FileRecord::getTreeModelColumn( ColumnIndex aIndex ) throw( std::invalid_argument )
{
    std::map< int, ColumnInfo* >::iterator iter = mColumnMap.find( static_cast< int >( aIndex ) );
    if( iter == mColumnMap.end() )
    {
        throw std::invalid_argument( "Unknown column index." );
    }

    return ( ( *( *iter ).second ).second );
}

} // namespace digirabi

