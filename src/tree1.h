#pragma once

#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <typeinfo>

// using these as paramters to begin and end ; using a single generic Iterator now 
#define _pre_     1
#define _inorder_ 2
#define _post_    3



template<typename T_datatype>
struct node{
	T_datatype value;
	node<T_datatype>* left;
	node<T_datatype>* right;
};


template<typename T_datatype, typename T_predicate=less<T_datatype>>
class tree{
	private:
		node<T_datatype>* root;
		int  size;
		void delete_tree_ (node<T_datatype>* root);
		int  height_      (node<T_datatype>* ptr);
		int  num_leaves_  (node<T_datatype>* ptr);
	    int  num_nodes_   (node<T_datatype>* ptr); 
	    //all recursive functions have a private and a public declaration. 
	    //Cuz we need to pass a parameter but the public ones can't expect the user to pass root cuz the user doesnt have access to it
	public:
		tree();
		tree(node<T_datatype>*);
		tree(T_datatype val);
		~tree();

		class Iterator{

			private:
				vector<T_datatype> v;
				int index_v;  // your p 
				void inorder_(vector<T_datatype>& v, node<T_datatype>* subtree){
					if(subtree!=nullptr){
						inorder_(v,subtree->left);
						v.push_back(subtree->value);
						inorder_(v,subtree->right);
					}
				}

				void preorder_(vector<T_datatype>& v, node<T_datatype>* subtree){
					if(subtree!=nullptr){
						v.push_back(subtree->value);
						preorder_(v,subtree->left);
						preorder_(v,subtree->right);
					}
				}

				void postorder_(vector<T_datatype>& v, node<T_datatype>* subtree){
					if(subtree!=nullptr){
						postorder_(v,subtree->left);
						postorder_(v,subtree->right);
						v.push_back(subtree->value);
					}
				}	

			public:
				Iterator(){
					index_v = 0;
				}
				// variable parameter constructor 
				Iterator(node<T_datatype>*ptr, int param =1 , bool end =false){

					try{
						if(param == 1)
							preorder_(v,ptr);
						else if(param == 2)
							inorder_(v,ptr);
						else if(param == 3)
							postorder_(v,ptr);
						else{
							throw 0 ;
						}

					}	
					catch(int error_no){
						if(error_no == 0){
							cout <<"Recheck parameter passed to 'param' field of Iterator\n";
							cout <<"Legal values : _pre_ , _post_, _inorder_\n";
						}
						exit(0);
					}

					if(v.size()>0){
						if(end)
							index_v = v.size();
						else
							index_v= 0;
					}
					else
						index_v = -1;
				}

				bool operator==(const Iterator& rhs) const{   
		            return index_v==rhs.index_v;
		        }

		        bool operator!=(const Iterator& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return v[index_v]; //want to return the node or the value of the node? // again val is much safer
		        }

		        Iterator operator++(int){    // postfix ++ // edit : parameter has to be int always 
		            Iterator temp(*this);
		            ++*this;
		            return temp;
		        }

		        Iterator operator++(){ 
		            ++index_v;
		            return *this;
		        }

		        Iterator operator--(int){    // postfix -- 
		            Iterator temp(*this);
		            --*this;
		            return temp;
		        }

		        Iterator operator--(){ 
		            --index_v;
		            return *this;
		        }
		};
		// set what type of order you want here , by def preorder
		Iterator begin(int order = 1){
   			return Iterator(root,order);  
   		}
		Iterator end(int order = 1){
	    	return Iterator(root,order,true);
		}	        

		
		
		
		int   height();
		int   num_leaves();
	    int   num_nodes(); //interior or all?  -- all nodes 

	    void  insert   (T_datatype element);
	    void  erase    (T_datatype element); // -pending
	    int   find     (T_datatype element); // make this find use tree (bst like ordering) but it should also return iterators like normal find
	    void  children (T_datatype element); // makes more sense , a user would enter element directly to find its children
	    //we need to add a lot more functions like the ones offered by vector and all(whatever applies)
	    //we also need to implement reverse iterator --thats what I'll start with tomo
	    //we need to see if we should make this iterator random access
	    //we need to expose types and iterator traits (or try to. I'm sure he'll appreciate that)
};

#include "implementation.cpp"