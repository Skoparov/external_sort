#ifndef EXTERNAL_SORT_HPP
#define EXTERNAL_SORT_HPP

#include "details/split_sorter.hpp"
#include "details/merge_sorter.hpp"

namespace external_sort
{

template< typename T >
void external_sort( const std::string& file_path,
                    size_t avail_mem,
                    size_t merge_at_once,
                    size_t threads_num = std::thread::hardware_concurrency() - 1 )
{
    // if avail_mem < memory needed to merge 2 files + output buffer
    if( !avail_mem || avail_mem < 3 * sizeof( T ) ){
        throw std::invalid_argument( "Not enough memory to sort" );
    }

    if( merge_at_once < 2 ){
        throw std::invalid_argument( "Cannot merge less that two files" );
    }

    if( threads_num == 0 ){
        threads_num = 1;
    }

    std::string work_folder = common::get_folder_from_path( file_path );
    size_t files_num = split::split< T >( file_path, avail_mem, threads_num );


    merge::merge< T >( work_folder, files_num, merge_at_once, avail_mem, threads_num );
}

}// external_sort

#endif
