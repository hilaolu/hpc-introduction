#ifndef Vector_H
#define Vector_H
#include "Move.hpp"
#include "Swap.hpp"

template <typename Object>
class Vector{
    public:
        explicit Vector(int initSize=0):theSize{initSize},
            theCapacity{initSize+SPARE_CAPACITY}{
                objects=new Object[theCapacity];
        }
        
        Vector(const Vector & rhs):theSize{rhs.theSize},
            theCapacity{rhs.theCapacity},objects{nullptr}{
            objects=new Object[theCapacity];
            for(int i=0;i<theSize;++i){
                objects[i]=rhs.objects[i];
            }
        }
        
        Vector & operator=(const Vector & rhs){
            Vector copy=rhs;
            swap(*this,copy);
            return *this;
        }
        
        ~Vector(){
            delete [] objects;
        }
        
        Vector(Vector && rhs):theSize{rhs.theSize},
            theCapacity{rhs.theCapacity},objects{rhs.objects}{
            rhs.objects=nullptr;
            rhs.theSize=0;
            rhs.theCapacity=0;
        }
        
        Vector & operator=(Vector && rhs){
            swap(theSize,rhs.theSize);
            swap(theCapacity,rhs.theCapacity);
            swap(objects,rhs.objects);
            return *this;
        }
        
        void resize(int newSize){
            if(newSize>theCapacity){
                reverse(newSize*2);
            }
            theSize=newSize;
        }
        
        void reverse(int newCapacity){
            if(newCapacity<theSize){
                return;
            }
            
            Object* newArray=new Object[newCapacity];
            for(int i=0;i<theSize;++i){
                newArray[i]=move(objects[i]);
            }
            
            theCapacity=newCapacity;
            swap(objects,newArray);
            delete [] newArray;
        }
        
        Object & operator[](int index){
            return objects[index];
        }
        
        Object* operator+(int addend){
            return objects+addend;
        }
            
        
        const Object & operator[](int index) const{
            return objects[index];
        }
        
        bool empty() const{
            return size()==0;
        }
        
        int size() const{
            return theSize;
        }
        
        int capacity() const{
            return theCapacity;
        }
        
        bool full() const{
            return theSize==theCapacity;
        }
        
        void push_back(const Object & x){
            if(theSize==theCapacity){
                reverse(2*theCapacity+1);
            }
            objects[theSize++]=x;
        }
            
        void push_back(const Object && x){
            if(theSize==theCapacity){
                reverse(2*theCapacity+1);
            }
            objects[theSize++]=move(x);
        }
        
        Object pop_back(){
            return objects[--theSize];
        }
        
        const Object & back() const{
            return objects[theSize-1];
        }
        
        typedef Object* iterator;
        typedef const Object* const_iterator;
        
        iterator begin(){
            return &objects[0];
        }
        
        const_iterator begin() const{
            return &objects[0];
        }
        
        iterator end(){
            return &objects[size()];
        }
        
        const_iterator end() const{
            return &objects[size()];
        }
        
        void clear(){
            theSize=0;
        }
        
        static const int SPARE_CAPACITY = 64;
        
    private:
        int theSize;
        int theCapacity;
        Object* objects;
        
};

#endif
