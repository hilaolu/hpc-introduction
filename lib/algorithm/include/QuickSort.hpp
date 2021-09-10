#ifndef lessThan_H
#define lessThan_H

template < typename Comparable >
inline bool lessThan( const Comparable a, const Comparable b ){
    return a < b;
}

#endif

#ifndef QuickSort_H
#define QuickSort_H
#include "Swap.hpp"
#include "InsertSort.hpp"
#include <cstdlib>

template < typename Comparable_Ptr, typename Comparator >
void quickSort( 
    const Comparable_Ptr start,  
    const Comparable_Ptr end, 
    Comparator cmp
){
    const auto delta = end - start; 
    if( delta > 16 ){
        swap( *start, *( start + rand() % ( int )( end - start ) ) );
        auto judging = start + 1;
        auto less = start - 1;
        auto eq = start;
        auto criterion = *start;
        while( judging <= end ){
            if( cmp( criterion, *judging ) == cmp( *judging, criterion ) ){
                 ++eq;        
                 swap( *judging, *eq);
            }else if( cmp( *judging, criterion ) ){
                ++less;
                ++eq;
                *less = *judging;
                *judging = *eq;
                *eq = criterion;
            }
            ++judging;
        }
        ++eq;
        quickSort( start, less, cmp );
        quickSort( eq, end, cmp );

    }else{
        if( delta > 0 ){
            insertSort( start, end, cmp);
        }
    }
}

#endif