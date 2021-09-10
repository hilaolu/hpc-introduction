#include "include/gemm.hpp"

void mul_gemm_plain(double* a,double* b,double* c,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                c[i*n+j]+=a[i*n+k]*b[k*n+j];
            }
        }
    }
}

void mul_gemm_opt_locality(double* a,double* b,double* c,int n){
    double tmp;
    for(int i=0;i<n;i++){
        for(int k=0;k<n;k++){
            tmp=a[i*n+k];
            for(int j=0;j<n;j++){
                c[i*n+j]+=tmp*b[k*n+j];
            }
        }
    }
}
