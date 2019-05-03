#pragma once 

#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <typeinfo>
// struct default_pred{
//     bool operator()(){
//         return true; // dunno what exactly to do here ; if deafult is binary tree ,retrun true always ?
//     }
// };

//eg tree < int,vector<int>,my_pred> , where my_pred is a struct/class and has operator() overidden
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


template< typename T_datatype = int, typename T_container = vector<T_datatype>, typename T_predicate = less<T_datatype> >
class tree{

    private:
    int max_size;
    //int* ptr; //What is this for?? -- dunno just thought a random pointer might come in handy :p
    int size;
    T_container root;
    int left_(int);
    int right_(int);

    public:
    tree();
    ~tree();

    tree(int t_size);

    class Iterator{
        private:
        //T_datatype *it_ptr;
        typename T_container::iterator it_ptr; //changed the iterator to use the iterator of the container that we're using

        public:
        explicit Iterator(T_datatype *p = nullptr):it_ptr(T_container::iterator(p)){}
        explicit Iterator(typename T_container::iterator p):it_ptr(p){}

        bool operator==(const Iterator& rhs) const{
            return it_ptr==rhs.it_ptr;     // is_equal() should again be a generic function 
        }
        bool operator!=(const Iterator& rhs) const{
            return !(it_ptr==rhs.it_ptr);
        }

        T_datatype operator*() const{
            return *it_ptr; // works right ?
        }

        Iterator operator++(int){    // postfix ++ // edit : parameter has to be int always 
            Iterator temp(*this);
            ++*this;
            return temp;
        }

        Iterator operator++(){ 
            ++it_ptr;
            return *this;
        }

        Iterator operator--(int){    // postfix -- 
            Iterator temp(*this);
            --*this;
            return temp;
        }

        Iterator operator--(){ 
            --it_ptr;
            return *this;
        }
    
    };

    Iterator begin(){
        return Iterator(root.begin());  
    }

    Iterator end(){
        return Iterator(root.end());  
    }

    int  height();
    int  num_leaves();
    int  num_nodes(); //interior or all?  -- all nodes 
    void inorder();
    void preorder();
    void postorder();
    void insert(T_datatype element);
    void del(T_datatype element); // -pending
    Iterator find(T_datatype element); // returns position in container (-1 if otherwise)
    void children(T_datatype element); // makes more sense , a user would enter element directly to find its children
    
 
    //can add vector functions like empty resize and all those small small functions

};

#include "impl.cpp"