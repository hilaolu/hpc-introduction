<template Comparable>
int binarySearch( const Comparable* & array, const Comparable & x ){
    int low = 0;
    int high = array.size() - 1;
    
    while( low <= high ){
        int mid = low + ( high - low ) / 2;
        
        if( array[mid] < x ){
            low = mid + 1;
        }else if( array[mid] > x ){
            high = mid - 1;
        }else{
            return mid;
        }
        
        return NOT_FOUND;
        
    }
}