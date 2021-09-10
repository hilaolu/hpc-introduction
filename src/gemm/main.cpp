#include <iostream>
#include <fstream>

int a[1024][1024];
int b[1024][1024];
int c[1024][1024];

using namespace std;
int main(){
    std::fstream input("", std::ios_base::in);
    int n;
    cin>>n;
    int tmp;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin>>tmp;
            a[i][j]=tmp;
        }
    }
        
}