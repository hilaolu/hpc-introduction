#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cassert>
#include <f77blas.h>

#include "mpi.h"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

double a[10485760];
double b[10485760];
double c[10485760];
double ref[10485760];

void read_matrix(double* a,double* b,int n);
#define PROCESSORS_COUNT 12 
#define abs(a) (a>0?a:-a)
int main(int argc,char* argv[]){
    
    int short_edge;
    int last_edge;
    
    
    //multiply 
    int gemm_scale=atoi(argv[1]);
    int n=gemm_scale;
    
    int myid,source,numprocs;
    
    MPI_Status status;
    
    const int MATRIX_A_PARTS=1;
    const int MATRIX_B=2;
    const int MATRIX_C=3;
    const int MASTER=0;
    
    MPI_Init(nullptr,nullptr);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    
    int workers_count=numprocs-1;
    
    short_edge=n/workers_count;
    last_edge=n-short_edge*(workers_count-1);
    
    if(myid==0){
        read_matrix(a,b,gemm_scale);
        
        auto t1=high_resolution_clock::now();
        for(int dist=1;dist<numprocs;dist++){
            MPI_Send(b,n*n,MPI_DOUBLE,dist,MATRIX_B,MPI_COMM_WORLD);
            
            int id=dist-1;
            
            int start=short_edge*id;
            int end=start+short_edge;
            
            if(id==workers_count-1){
                end=start+last_edge;
            }
            
            MPI_Send(a+start*n,n*(end-start),MPI_DOUBLE,dist,MATRIX_A_PARTS,MPI_COMM_WORLD);
        }
        
        
        for(int dist=1;dist<numprocs;dist++){
            int id=dist-1;
            
            int start=short_edge*id;
            int end=start+short_edge;
            
            if(id==workers_count-1){
                end=start+last_edge;
            }
            
            MPI_Recv(c+start*n,n*(end-start),MPI_DOUBLE,dist,MATRIX_C,MPI_COMM_WORLD,&status);
        }
        
        
        auto t2=high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        cout<<ms_double.count()<<endl;
        //correctness checking
        /*{
            char ta = 'N';
            char tb = 'N';
            double alpha = 1;
            dgemm_(&ta, &tb,&n,&n,&n,&alpha,a,&n,b,&n,&beta,ref,&n);
            double beta = 0;
            
            for(int i=0;i<n*n;i++){
        	if(abs((ref[i]-c[i])/ref[i])>0.000001){
                    printf("%lf %lf %d\n",ref[i],c[i],i);
                    cin.get();
                }
            }
            
        }
        */
    }else{
        
        int id=myid-1;
        int start=short_edge*id;
        int end=start+short_edge;
        if(id==workers_count-1){
            end=start+last_edge;
        }
        
        MPI_Recv(b,n*n,MPI_DOUBLE,MASTER,MATRIX_B,MPI_COMM_WORLD,&status);
        
        //fix me
        MPI_Recv(a+start*n,n*(end-start),MPI_DOUBLE,MASTER,MATRIX_A_PARTS,MPI_COMM_WORLD,&status);
        
        //compute
        double tmp;
        double res;
        for(int i=start;i<end;i++){
            for(int k=0;k<n;k++){
                tmp=a[i*n+k];
                for(auto j=0;j<n;j++){
                    res=tmp*b[k*n+j];
                    c[i*n+j]+=res;
                }
            }
        }
        
        //return result
        MPI_Send(c+start*n,n*(end-start),MPI_DOUBLE,MASTER,MATRIX_C,MPI_COMM_WORLD);
        
    }
    
        
    MPI_Finalize();




    
        

    return 0;
    // cin.get();
}




void read_matrix(double* a,double* b,int n){
    std::fstream input("random.txt", std::ios_base::in);

    double tmp;
    //init a,b
    for(int i=0;i<n*n;++i){
        input>>tmp;
        a[i]=tmp;
        b[i]=tmp;
    }
    
}


                