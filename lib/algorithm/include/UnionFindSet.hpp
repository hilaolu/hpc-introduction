#include "Vector.hpp"

template <typename Object>
class UnionFindSet{
    public:
        UnionFindSet(Object size){
            ++size;
            objects=new Vector<Object>(size);
            for(int i=0;i!=size;++i){
                (*objects)[i]=i;
            }
        }
        
        ~UnionFindSet(){
            delete objects;
        }
        
        void clear(){
            objects->clear();
        }
        
        void merge(Object x,Object y){
            (*objects)[find(x)]=(*objects)[find(y)];
        }
        
        Object find(Object x){
            if((*objects)[x]==x){
                return x;
            }
            
            return (*objects)[x]=find((*objects)[x]);
        }
        

    private:
        Vector<Object>* objects;
        
};