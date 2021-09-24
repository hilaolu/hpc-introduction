#include <iostream>
#include <fstream>
#include <chrono>
#include <f77blas.h>

#include "hpc/include/gemm.hpp"

double a[10485760];
double b[10485760];
double c[10485760];

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
int main(){
    std::fstream input("bin/random.txt", std::ios_base::in);
    int n;
    cin>>n;
    int tmp;
    //init a,b
    for(int i=0;i<n*n;++i){
        input>>tmp;
        a[i]=tmp;
        b[i]=tmp;
    }
    
    
    cout<<"init ok"<<endl;
    
    
    //multiply 
    
    for(int i=0;i<n*n;++i){
        c[i]=0;
    }
    
    
    char ta = 'N';
    char tb = 'N';
    double alpha = 1;
    double beta = 0;
    
    auto t1=high_resolution_clock::now();
    // dgemm_(&ta, &tb,&n,&n,&n,&alpha,a,&n,b,&n,&beta,c,&n);
    // mul_gemm_plain(a,b,c,n);
    mul_gemm_opt_locality(a,b,c,n);
    auto t2=high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    cout<<ms_double.count()<<endl;
    
    
    
    cin.get();
}