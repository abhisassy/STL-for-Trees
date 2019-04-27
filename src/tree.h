#pragma once 

#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>

struct default_pred{
    bool operator()(){
        return true; // dunno what exactly to do here ; if deafult is binary tree ,retrun true always ?
    }
};

//eg tree < int,vector<int>,my_pred> , where my_pred is a struct/class and has operator() overidden

template< typename T_datatype = int, typename T_container = vector<T_datatype>, typename T_predicate= default_pred>
class tree{

    private:
    int  size;
    int* ptr;
    T_container root;

    public:
    tree(){
        cout << "default constructor called\n";
        
    }
    ~tree(){
        cout << "default destrcutor called\n";
        // any freeing mechanism ?
    }

    tree(int size){
        root.resize(size,0); // initally size is zero , so basiccaly initialzes entire root to 0
        this->size =size;    // also assuming resize works for all our containers the same way     
    }

    class Iterator{
        private:
        T_datatype *it_ptr;

        public:
        explicit Iterator(T_datatype *p = nullptr){  
            it_ptr = p;
        }

        bool operator==(const Iterator& rhs) const{
            return is_eqaul(*it_ptr,*rhs.it_ptr);     // is_equal() should again be a generic function 
        }
        bool operator!=(const Iterator& rhs) const{
            return !(*this == rhs);
        }

        T_datatype operator*() const{
            return *this; // works right ?
        }

        Iterator operator++(T_datatype){    // postfix ++
            Iterator temp(*this);
            ++*this;
            return temp;
        }

        Iterator operator++(){ 
            ++it_ptr;
            return it_ptr;
        }

        Iterator operator--(T_datatype){    // postfix -- 
            Iterator temp(*this);
            --*this;
            return temp;
        }

        Iterator operator--(){ 
            --it_ptr;
            return it_ptr;
        }
    
    };

    Iterator begin(){
        return Iterator(begin(root)); // makes sense right ? you return the pointer to the fist element i.e first elem in root 
        // conatiner is vector , root.begin() will have first elem
    }

    Iterator end(){
        return Iterator(end(root));  
    }

    int  depth();
    int  num_leaves();
    int  num_nodes();
    void inorder();
    void preorder();
    void postorder();
    void insert(T_datatype element);
    void del(T_datatype element);
    int  find(T_datatype element);
    void children(); // list children



};


template<typename ptr_t>
void disp(ptr_t first, ptr_t last){
	while(first != last){
		cout << *first << "\t";
		++first; 
	}
	cout << "\n";
}

template<typename type>      
bool isequal(type p1, type p2){   // two specializations needed only right ? for string and char*
    return p1==p2;
}

template<>
bool isequal(string p1, string p2){
    if(p1.compare(p2))  // returns 0 if same 
        return false;
    else
        return true;
}
template<>
bool isequal(char* p1, char* p2){
    if(strcmp(p1,p2))  // returns 0 if same 
        return false;
    else
        return true;
}