#include "Vector.hpp"
#include "Swap.hpp"
#ifndef cmp
#define cmp(a,b) (a<b)
#endif
template <typename Object>
class Heap{
    public:
        Heap(){
            objects=new Vector<Object>;
        }
        
        Heap(Vector<Object>* vector_ptr){
            objects=vector_ptr;
            for(int i=(objects->size())>>1;i!=-1;--i){
                adjustDown(i);
            }
        }
        
        ~Heap(){
            delete objects;
        }
        
        
        Object pop(){
            swap((*objects)[0],(*objects)[objects->size()-1]);
            auto ret=objects->pop_back();
            adjustDown(0);
            return ret;
        }
        
        Object top(){
            return (*objects)[0];
        }
        
        void push(Object x){
            objects->push_back(x);
            adjustUp(objects->size()-1);
        }
        
        void clear(){
            objects->clear();
        }
        
        bool empty(){
            return objects->empty();
        }
            
        
    private:
        void adjustUp(int to_be_adjust){
            int ancestor=to_be_adjust>>1;
            while(to_be_adjust!=0&&cmp((*objects)[ancestor],(*objects)[to_be_adjust])){
                swap((*objects)[to_be_adjust],(*objects)[ancestor]);
                to_be_adjust=ancestor;
                ancestor=to_be_adjust>>1;
            }
        }
        
        void adjustDown(int to_be_adjust){
            int left=(to_be_adjust<<1)+1;
            int right=left+1;
            int end=objects->size();
            while( left < end ){
                if( right >= end ){
                    if( cmp( (*objects)[to_be_adjust], (*objects)[left] ) ){
                        swap( (*objects)[left], (*objects)[to_be_adjust] );
                    }
                    break;
                }
                
                if( cmp((*objects)[left] , (*objects)[right]) && cmp( (*objects)[to_be_adjust] , (*objects)[right] ) ){
                    swap( (*objects)[right], (*objects)[to_be_adjust] );
                    to_be_adjust = right;
                }else if( cmp( (*objects)[to_be_adjust], (*objects)[left] ) ){
                    swap( (*objects)[to_be_adjust], (*objects)[left] );
                    to_be_adjust = left;
                }else{
                    break;
                }
                
                left=(to_be_adjust<<1)+1;
                right=left+1;
            }
        }
        Vector<Object>* objects;
};