#ifndef LinearQueue_H
#define LinearQueue_H

using namespace std;

#define DEFALUT_SIZE 64

#include "Vector.hpp"
template <typename Object>
class LinearQueue{
    public:
        LinearQueue(int init_size=DEFALUT_SIZE){
            objects=new Vector<Object>;
            in=objects->begin();
            out=objects->end();
        }
        
        ~LinearQueue(){
            delete objects;
        }
        
        LinearQueue & operator=(LinearQueue & rhs)=delete;
        
        LinearQueue(LinearQueue & rhs)=delete;
        
        LinearQueue & operator=(LinearQueue && rhs)=delete;
        
        LinearQueue(LinearQueue && rhs)=delete;
            
        void push(Object x){
            *in=x;
            iter_self_increase(in);
        }
        
        Object pop(){
            iter_self_increase(out);
            return *out;    
        }
        
        bool full(){
            return in==out; 
        }
        
        bool empty(){
            auto tmp=out;
            iter_self_increase(out);
            return tmp==in; 
        }
        
        void iter_self_increase(Object* & iter){
            if(iter==objects->end()){
                iter=objects->begin();
                return;
            }
            ++iter;
        }
        
    private:
        
        Vector<Object>* objects;
        Object* in;
        Object* out;

};
#endif