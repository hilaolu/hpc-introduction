#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cassert>
#include <f77blas.h>

double a[10485760];
double b[10485760];
double c[10485760];
double ref[10485760];

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int n;
int short_edge;
int last_edge;

void* mul_gemm_plain(void* worker_id);
void mul_gemm_single();
void gemm_omp(double* A,double* B,double* C,int n);
#define PROCESSORS_COUNT 12 
#define abs(a) (a>0?a:-a)
int main(){
    std::fstream input("bin/random.txt", std::ios_base::in);
    
    int tmp;
    //init a,b
    for(int i=0;i<n*n;++i){
        input>>tmp;
        a[i]=tmp;
        b[i]=tmp;
    }
    
    
    cout<<"init ok"<<endl;
    
    
    //multiply 
    for(n=50;n<3000;n+=50){
        // n=3000;
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
        
        mul_gemm_single();

        // dgemm_(&ta, &tb,&n,&n,&n,&alpha,a,&n,b,&n,&beta,ref,&n);
        
        auto t2=high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        cout<<ms_double.count()<<endl;
    
        
        for(int i=0;i<n*n;i++){
    	if(abs((ref[i]-c[i])/ref[i])>0.000001){
                printf("%lf %lf %d\n",ref[i],c[i],i);
                cin.get();
            }
        }
    }

    
    cin.get();
}



void* mul_gemm_plain(void* worker_id){
    int id=*(int*)worker_id;
    int start=short_edge*id;
    int end=start+short_edge;
    if(id==PROCESSORS_COUNT-1){
        end=start+last_edge;
    }
    register double tmp;
    register double res;
    for(int i=start;i<end;i++){
        for(int k=0;k<n;k++){
            tmp=a[i*n+k];
            for(auto j=0;j<n;j++){
                res=tmp*b[k*n+j];
                c[i*n+j]+=res;
            }
        }
    }
    return nullptr;
}

void mul_gemm_single(){
    
    #pragma omp parallel 
    {
        double tmp;
        #pragma omp for
        for(int i=0;i<n;i++){
            for(int k=0;k<n;k++){
                tmp=a[i*n+k];
                for(int j=0;j<n;j++){
                    c[i*n+j]+=tmp*b[k*n+j];
                }
            }
        }
    }

}

                