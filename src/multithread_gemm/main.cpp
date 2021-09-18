#include "gemm.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cassert>

double a[1048576];
double b[1048576];
double c[1048576];

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
int n;
int short_edge;
int last_edge;

void* mul_gemm_plain(void* worker_id);
#define PROCESSORS_COUNT 12
int main(){
    std::fstream input("bin/random.txt", std::ios_base::in);
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
    
    short_edge=n/PROCESSORS_COUNT;
    last_edge=n-short_edge*(PROCESSORS_COUNT-1);
    
    auto t1=high_resolution_clock::now();
    pthread_t tid[PROCESSORS_COUNT];
    
    int worker_id[PROCESSORS_COUNT];
    for(int i=0;i<PROCESSORS_COUNT;++i){
        worker_id[i]=i;
    }
    
    for(int i=0;i<PROCESSORS_COUNT;++i){
        int error;
        error=pthread_create(&tid[i],NULL,mul_gemm_plain,&worker_id[i]);
        assert(error==0);
    }
    
    for(int i=0;i<PROCESSORS_COUNT;++i){
        pthread_join(tid[i],NULL);
    }

    
    auto t2=high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    cout<<ms_double.count()<<endl;
    
    cin.get();
}

void* mul_gemm_plain(void* worker_id){
    int id=*(int*)worker_id;
    int start=short_edge*id;
    int end=start+short_edge;
    if(id==PROCESSORS_COUNT-1){
        end=start+=last_edge;
    }
    // printf("%d %d\n",start,end);
    for(int i=start;i<end;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                c[i*n+j]+=a[i*n+k]*b[k*n+j];
            }
        }
    }
}