#ifndef lessThan_H
#define lessThan_H

template <typename Comparable>
inline bool lessThan( const Comparable a, const Comparable b ){
    return a < b;
}

#endif

#ifndef HeapSort_H
#define HeapSort_H
#include "Swap.hpp"

template <typename Comparable, typename Comparator>
void adjust(
    Comparable array[],
    int to_be_adjust,
    int end,
    Comparator cmp
){
    int left=to_be_adjust*2+1;
    int right=to_be_adjust*2+2;
    while( left <= end ){
        
        if( right > end ){
            if( cmp( array[to_be_adjust], array[left] ) ){
                swap( array[left], array[to_be_adjust] );
            }
            break;
        }
        
        if( cmp( array[left] , array[right] ) && cmp( array[to_be_adjust] , array[right] ) ){
            swap( array[right], array[to_be_adjust] );
            to_be_adjust = right;
        }else if( cmp( array[to_be_adjust], array[left] ) ){
            swap( array[to_be_adjust], array[left] );
            to_be_adjust = left;
        }else{
            break;
        }
        
        left=to_be_adjust*2+1;
        right=to_be_adjust*2+2;
    }
    
} 

template <typename Comparable>
void heapSort(
    Comparable array[], 
    int end,
    bool ( *cmp )( const Comparable a, const Comparable b ) = lessThan 
){
    for( int i = end / 2; i != -1; i-- ){
        adjust( array, i, end, cmp);
    }
    
    while( end != 0 ){
        swap( array[0], array[end] );
        end--;
        adjust( array, 0, end, cmp);
    }
}


#endif