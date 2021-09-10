#ifndef ChainList_H
#define ChainList_H
#include "Move.hpp"
#include "Swap.hpp"

template <typename Object>
class ChainList{
    
    private:
        struct Node{
            Object data;
            Node* prev;
            Node* next;
            
            Node(const Object & d=Object{},Node* p=nullptr,Node* n=nullptr):
                data{d},prev{p},next{n}{}
        };
        
    public:
        class const_iterator{
            public:
                const_iterator():current{nullptr}{
                }
                
                const Object & operator*() const{
                    return retrieve();
                }
                
                const_iterator & operator++(){
                    current=current->next;
                    return *this;
                }
                
                const_iterator operator++(int){
                    const_iterator old=*this;
                    ++(*this);
                    return old;
                }
                
                bool operator==(const const_iterator & rhs) const{
                    return current==rhs.current;
                }
                
                bool operator!=(const const_iterator & rhs) const{
                    return !(*this==rhs);
                }
                
            protected:
                Node* current;
                
                Object & retrieve() const{
                    return current->data;
                }
                
                const_iterator(Node* p):current{p}{
                }
                
                friend class ChainList<Object>;
                
        };
                    
        class iterator:public const_iterator{
            public:
                iterator(){
                }
                
                Object & operator*(){
                    return const_iterator::retrieve();
                }
                
                const Object & operator*() const{
                    return const_iterator::operator*();
                }
                
                iterator & operator++(){
                    this->current=this->current->next;
                    return *this;
                }
                
                iterator operator++(int){
                    iterator old=*this;
                    ++(*this);
                    return old;
                }
                
            protected:
                iterator(Node* p):const_iterator{p}{
                }
                
                friend class ChainList<Object>;
                    
        };
                
        
        
        
    public:
        ChainList(){
            init();
        };
        
        ~ChainList(){
            clear();
            delete head;
            delete tail;
        }
        
        ChainList(const ChainList & rhs){
            init();
            for(auto & x:rhs){
                push_back(x);
            }
        }
        
        ChainList(ChainList && rhs):theSize{rhs.theSize},head{rhs.head},tail{rhs.tail}{
            rhs.theSize=0;
            rhs.head=nullptr;
            rhs.tail=nullptr;
        }
        
        ChainList & operator=(const ChainList & rhs){
            ChainList copy=rhs;
            swap(*this,copy);
            return *this;
        }
        
        ChainList & operator=(ChainList && rhs){
            swap(theSize,rhs.theSize);
            swap(head,rhs.head);
            swap(tail,rhs.tail);
        }
        
        iterator begin(){
            return head->next;
        }
        
        const_iterator begin() const{
            return head->next;     
        }
        
        iterator end(){
            return tail;
        }
        
        const_iterator end() const{
            return tail;
        }
        
        int size() const{
            return theSize;
        }
        
        bool empty() const{
            return size()==0;
        }
        
        void clear(){
            while(!empty()){
                pop_front();
            }
        }
        
        Object & front(){
            return *begin();
        }
            
        const Object & front() const{
            return *begin();
        }
        
        Object & back(){
            return *--end();
        }
        
        const Object & back() const{
            return *--end();
        }
        
        void push_front(const Object & x){
            insert(begin(),x);
        }
        
        void push_front(const Object && x){
            insert(begin(),move(x));
        }
        
        void push_back(const Object & x){
            insert(end(),x);
        }
        
        void push_back(const Object && x){
            insert(end(),move(x));
        }
        
        void pop_front(){
            erase(begin());
        }
        
        void pop_back(){
            erase(--end());
        }
        
        iterator insert(iterator iter,const Object & x){
            Node* p=iter.current;
            ++theSize;
            return {
                p->prev=p->prev->next=new Node{x,p->prev,p}
            };
        }
        
        iterator insert(iterator iter,const Object && x){
            Node* p=iter.current;
            ++theSize;
            return {
                p->prev=p->prev->next=new Node{move(x),p->prev,p}
            };
        }
        
        iterator erase(iterator iter){
            Node* p=iter.current;
            iterator ret{p->next};
            p->prev->next=p->next;
            p->next->prev=p->prev;
            delete p;
            --theSize;
            return ret;
        }
        
        iterator erase(iterator from,iterator to){
            for(iterator iter=from;iter!=to;){
                iter=erase(iter);
            }
            
            return to;
        }
        
        void reverse(){
            for(auto iter=begin();iter!=end();){
                Node* p=iter.current;
                iter++;
                swap(p->prev,p->next);
            }           
            
            swap(head->prev,head->next);
            swap(tail->prev,tail->next);
            
            swap(head,tail);
            
        }
            
        
    private:
        int theSize;
        Node* head;
        Node* tail;
        
        void init(){
            theSize=0;
            head=new Node;
            tail=new Node;
            head->next=tail;
            tail->prev=head;
        }
        
};     

#endif