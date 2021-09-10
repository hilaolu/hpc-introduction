#ifndef Stack_H
#define Stack_H

#include "Vector.hpp"

#define DEFAULT_SIZE 64
using namespace std;
template <typename Object>
class Stack{
    public:
        Stack(){
            objects=new Vector<Object>;
        }    
            
        ~Stack(){
            delete objects;
        }
        
        Stack(const Stack & rhs){
            objects=new Vector<Object>(*(rhs.objects));
        }
        
        Stack(const Stack && rhs){
            objects=rhs.objects;
            rhs.objects=nullptr;
        }
        
        Stack & operator=(const Stack & rhs){
            delete objects;
            objects=new Vector<Object>(*(rhs.objects));
            return *this;
        }
        
        Stack & operator=(const Stack && rhs){
            delete objects;
            objects=rhs.objects;
            rhs.objects=nullptr;
            return *this;
        }
        
        Object pop(){
            return objects->pop_back();
        }
        
        Object top(){
            return objects->top();
        }
        
        bool empty(){
            return objects->empty();
        }
        
        bool full(){
            return objects->full();
        }
        
        void push(Object object){
            objects->push_back(object);    
        }    
        
        void clear(){
            objects->clear();
        }
        
        int size(){
            return objects->size();
        }
                
        
    private:
        Vector<Object>* objects;
};
    
    

#endif