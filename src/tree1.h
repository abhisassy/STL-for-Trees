#pragma once

#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <typeinfo>

template<typename T_datatype>
struct node{
	T_datatype value;
	node<T_datatype>* left;
	node<T_datatype>* right;
};

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


template<typename T_datatype, typename T_predicate=less<T_datatype>>
class tree{
	private:
		node<T_datatype>* root; //dont know why I got "invalid use of non-static data member 'root'" error
		void delete_tree_(node<T_datatype>* root);
		int height_(node<T_datatype>* ptr);
		int  num_leaves_(node<T_datatype>* ptr);
	    int  num_nodes_(node<T_datatype>* ptr); 
	    void inorder_(); //change to iterators only. function doesnt make sense
	    void preorder_();
	    void postorder_();
	    //all recursive functions have a private and a public declaration. 
	    //Cuz we need to pass a parameter but the public ones can't expect the user to pass root cuz the user doesnt have access to it
	public:
		tree();
		tree(node<T_datatype>*);
		tree(T_datatype val);
		~tree();

		class iterator{ //inorder
			node<T_datatype>* ptr_;
			vector<node<T_datatype>*> v;   //node or just value?

			public:
				void inorder_(vector<node<T_datatype>*>& v, node<T_datatype>* subtree){
					if(subtree!=nullptr){
						inorder_(v,subtree->left);
						v.push_back(subtree);
						inorder_(v,subtree->right);
					}
				}
				iterator(){
					ptr_=nullptr;
				}
		        iterator(node<T_datatype>*p){
		        	inorder_(v,p);
		        	// for(int i=0;i<v.size();++i){
		        	// 	cout << v[i]->value << "\n";
		        	// }
		        	if(v.size()>0)
		        		ptr_ = v[0];
		        	else
		        		ptr_ = nullptr;
		        }

		        bool operator==(const iterator& rhs) const{
		            return (isequal(ptr_->value,rhs.ptr_->value) && ptr_->left==rhs.ptr_->left && ptr_->right==rhs.ptr_->right);
		        }

		        bool operator!=(const iterator& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return ptr_->value; //want to return the node or the value of the node?
		        }

		        iterator operator++(int){    // postfix ++ // edit : parameter has to be int always 
		            iterator temp(*this);
		            ++*this;
		            return temp;
		        }

		        iterator operator++(){ 
		            ++ptr_;
		            return *this;
		        }

		        iterator operator--(int){    // postfix -- 
		            iterator temp(*this);
		            --*this;
		            return temp;
		        }

		        iterator operator--(){ 
		            --ptr_;
		            return *this;
		        }

		        friend class tree;
		};

		iterator begin(){
        	return iterator(root);  
	    }

	    iterator end(){
	    	iterator* temp=new iterator(root);
			node<T_datatype>** x=&(temp->v).front();
			int y = (temp->v).size();
			delete temp;
	        return iterator(*(x+y));  
	    }

		int height();
		int  num_leaves();
	    int  num_nodes(); //interior or all?  -- all nodes 
	    void inorder();
	    void preorder();
	    void postorder();
	    void insert(T_datatype element);
	    void erase(T_datatype element); // -pending
	    iterator find(T_datatype element); // returns position in container (-1 if otherwise)
	    void children(T_datatype element); // makes more sense , a user would enter element directly to find its children
};

#include "implementation.cpp"