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


//current iterator essentially stores the required traversal in a vector and iterates through that.
//It was damn hard cuz it threw random errors. So I got this to work. Might not be the most efficient

//not used by current iterator
/*template<typename type>      
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
}*/


template<typename T_datatype, typename T_predicate=less<T_datatype>>
class tree{
	private:
		node<T_datatype>* root;
		int size;
		void delete_tree_(node<T_datatype>* root);
		int height_(node<T_datatype>* ptr);
		int  num_leaves_(node<T_datatype>* ptr);
	    int  num_nodes_(node<T_datatype>* ptr); 
	    //all recursive functions have a private and a public declaration. 
	    //Cuz we need to pass a parameter but the public ones can't expect the user to pass root cuz the user doesnt have access to it
	public:
		using value_type = T_datatype;
		
		tree();
		tree(node<T_datatype>*);
		tree(T_datatype val);
		~tree();

		class iterator{

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
				using value_type = T_datatype;
				using iterator_category = bidirectional_iterator_tag;
				using pointer = void;
				using reference = void;
				using difference_type = void;

				iterator(){
					index_v = 0;
				}
				// variable parameter constructor 
				iterator(node<T_datatype>*ptr, int param =1 , int index=0){
					if(param == 1)
						preorder_(v,ptr);
					else if(param == 2)
						inorder_(v,ptr);
					else if(param == 3)
						postorder_(v,ptr);

					if(v.size()>0){
							index_v = index;
					}
					else
						index_v = -1;
				}

				bool operator==(const iterator& rhs) const{   
		            return index_v==rhs.index_v;
		        }

		        bool operator!=(const iterator& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return v[index_v]; //want to return the node or the value of the node? // again val is much safer
		        }

		        iterator operator++(int){    // postfix ++ // edit : parameter has to be int always 
		            iterator temp(*this);
		            ++*this;
		            return temp;
		        }

		        iterator operator++(){ 
		            ++index_v;
		            return *this;
		        }

		        iterator operator--(int){    // postfix -- 
		            iterator temp(*this);
		            --*this;
		            return temp;
		        }

		        iterator operator--(){ 
		            --index_v;
		            return *this;
		        }
		};

		class reverse_iterator{
			private:
				iterator itr;
			public:
				using value_type = T_datatype;
				using iterator_category = bidirectional_iterator_tag;
				using pointer = void;
				using reference = void;
				using difference_type = void;
				reverse_iterator(iterator x){
					itr=x;
				}

				reverse_iterator(){
					itr=nullptr;
				}

		        bool operator==(const reverse_iterator& rhs) const{
		            return itr==rhs.itr;
		        }

		        bool operator!=(const reverse_iterator& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return *itr; //want to return the node or the value of the node?
		        }

		        reverse_iterator operator++(int){    // postfix ++ // edit : parameter has to be int always 
		            reverse_iterator temp(*this);
		            ++*this;
		            return temp;
		        }

		        reverse_iterator operator++(){ 
		            --itr;
		            return *this;
		        }

		        reverse_iterator operator--(int){    // postfix -- 
		            reverse_iterator temp(*this);
		            --*this;
		            return temp;
		        }

		        reverse_iterator operator--(){ 
		            ++itr;
		            return *this;
		        }

		        friend class tree;
		};

		iterator begin(){
        	return iterator(root,2,0);  
	    }

	    iterator end(){
	    	return iterator(root,2,size);
	    }

	    iterator begin_preorder(){
        	return iterator(root,1,0);  
	    }

	    iterator end_preorder(){
	    	return iterator(root,1,size);
	    }

	    iterator begin_postorder(){
        	return iterator(root,3,0);  
	    }

	    iterator end_postorder(){
	    	return iterator(root,3,size);
	    }

	    reverse_iterator rbegin(){
	    	return reverse_iterator(--(end()));
	    }

	    reverse_iterator rend(){
	    	return reverse_iterator(--(begin()));
	    }

		int height();
		int  num_leaves();
	    int  num_nodes(); //interior or all?  -- all nodes 
	    // void inorder();
	    // void preorder();
	    // void postorder(); //implemented as iterators so no point of these?
	    void insert(T_datatype element);
	    void erase(T_datatype element); // -pending
	    iterator find(T_datatype element); // make this find use tree (bst like ordering) but it should also return iterators like normal find
	    void children(T_datatype element); // makes more sense , a user would enter element directly to find its children
	    //we need to add a lot more functions like the ones offered by vector and all(whatever applies)
	    //we also need to implement reverse iterator --thats what I'll start with tomo
	    //we need to see if we should make this iterator random access
	    //we need to expose types and iterator traits (or try to. I'm sure he'll appreciate that)
};

#include "implementation.cpp"