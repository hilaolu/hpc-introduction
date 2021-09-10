#ifndef lessThan_H
#define lessThan_H

template <typename Comparable>
inline bool lessThan(const Comparable a, const Comparable b){
    return a < b;
}

#endif

#ifndef InsertSort_H 
#define InsertSort_H 

template <typename Comparable_Ptr, typename Comparator>
void insertSort(
    const Comparable_Ptr start,
    const Comparable_Ptr end,
    Comparator cmp
){
    for(auto i = start; i <= end; ++i ){
        auto j = i - 1;
        auto current = *i;
        for( ; j >= start && cmp( current, *j ); --j ){
            *(j + 1) = *j;
        }
        *( j + 1 ) = current;
    }
}        


#endif
