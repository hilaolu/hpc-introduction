template <typename Intergal>
Intergal gcd( Intergal m, Interal n){
    Intergal rem;
    
    while( n != 0 ){
        rem = m % n;
        m = n;
        n = rem;
    }
    
    return m;
    
}