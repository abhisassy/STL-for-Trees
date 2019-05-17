#pragma once

#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <typeinfo>

// using these as paramters to begin and end ; using a single generic iterator now 
#define _preorder_     1
#define _inorder_ 2
#define _postorder_    3

template<typename T_ptr>
void disp(T_ptr first, T_ptr last){
	while(first!=last){
		cout << *first<<" ";
		++first;
	}
	cout <<"\n";
}



template<typename T_datatype>
struct node{
	T_datatype value;
	node<T_datatype>* left;
	node<T_datatype>* right;
	node<T_datatype>* parent;
};


template<typename T_datatype, typename T_predicate=less<T_datatype>>
class tree{
	private:
		node<T_datatype>* root;
		int  size_of_tree;
		void delete_tree_ (node<T_datatype>* root);
		int  height_      (node<T_datatype>* ptr);
		int  num_leaves_  (node<T_datatype>* ptr);

		node<T_datatype>*  find_ (T_datatype element);

	    //all recursive functions have a private and a public declaration. 
	    //we need to pass a parameter but the public ones can't expect the user to pass root cuz the user doesnt have access to it
	public:
		
		using value_type  = T_datatype;
		using key_compare = T_predicate;

		tree();
		tree(node<T_datatype>*);
		tree(T_datatype val);
		~tree();
		tree(const tree<T_datatype, T_predicate>& rhs) = delete;
		tree<T_datatype, T_predicate>& operator=(const tree<T_datatype, T_predicate>& rhs) = delete;
		tree(tree<T_datatype, T_predicate>&& rhs) = delete;
		tree<T_datatype, T_predicate>& operator=(tree<T_datatype, T_predicate>&& rhs) = delete;

		class iterator{

			private:
				vector<T_datatype> v;
				int index_v;   
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

				using value_type        = T_datatype;
				using iterator_category = random_access_iterator_tag;
				using pointer           = void;
				using reference         = void;
				using difference_type   = void;
				
				iterator(){
					index_v = 0;
				}
				// variable parameter constructor 
				iterator(node<T_datatype>*ptr, int param =2 , bool end =false){
					if(v.size()!=0){
							if(end)
								index_v = v.size();
							else
								index_v= 0;
							return;
					}
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
							cout <<"Recheck parameter passed to 'param' field of iterator\n";
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

				bool operator==(const iterator& rhs) const{   
		            return index_v==rhs.index_v;
		        }

		        bool operator!=(const iterator& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return v[index_v]; 
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

				const T_datatype& operator[](int index) const{  // only rvalue usage
					try{
						if(index>=v.size())
							throw 0;
						return v[index];
					}
					catch(int error_no){
						cout <<"Index Out of Bounds. Execution Halted\n";
						exit(0);
					}	
				}

				iterator operator+(int n){
					iterator temp = *this;
					temp.index_v = index_v + n;
					return temp;
				}

				int operator-(const iterator& it2){
					return index_v - it2.index_v;
				}

		};
		// set what type of order you want here , by def inorder
		iterator begin(int order = 2){
   			return iterator(root,order);  
   		}
		iterator end(int order = 2){
	    	return iterator(root,order,true);
		}	        

		class reverse_iterator{
			
			private:
				iterator itr;
			public:
				using value_type        = T_datatype;
				using iterator_category = bidirectional_iterator_tag;
				using pointer           = void;
				using reference         = void;
				using difference_type   = void;
			
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
		            return *itr; 
		        }

		        reverse_iterator operator++(int){   
		            reverse_iterator temp(*this);
		            ++*this;
		            return temp;
		        }

		        reverse_iterator operator++(){ 
		            --itr;
		            return *this;
		        }

		        reverse_iterator operator--(int){    
		            reverse_iterator temp(*this);
		            --*this;
		            return temp;
		        }

		        reverse_iterator operator--(){ 
		            ++itr;
		            return *this;
		        }
				
		        
		};

		reverse_iterator rbegin(int order = 2){
	    	return reverse_iterator(--(end(order)));
	   	}

	    reverse_iterator rend(int order = 2){
	    	return reverse_iterator(--(begin(order)));
	    }

		
		
		
		int   height();
		int   num_leaves();//interior or all?  -- all nodes 
	    
		bool  contains(T_datatype element);
		bool  insert(T_datatype element);
	    bool  erase(T_datatype element); 
	    
		tree<T_datatype, T_predicate>::iterator find(T_datatype element);
		
		const T_datatype*  parent(T_datatype element);
		const T_datatype*  left(T_datatype element);
		const T_datatype*  right(T_datatype element);
		

		bool   empty() const;
	    size_t size ()  const;
	    void   clear();

		T_datatype&  front();
		T_predicate key_comp();
		
		void merge(tree<T_datatype,T_predicate>& rhs);
		void swap(tree<T_datatype,T_predicate>& rhs);
		
		tree<T_datatype,T_predicate>& extract(T_datatype element);

	    template<typename T_data, typename T_pred>
	    friend bool operator==(tree<T_data,T_pred>& lhs, tree<T_data,T_pred>& rhs);

	    template<typename T_data, typename T_pred>
	    friend bool operator!=(tree<T_data,T_pred>& lhs, tree<T_data,T_pred>& rhs);

	    template<typename T_data, typename T_pred>
	    friend bool operator<=(tree<T_data,T_pred>& lhs, tree<T_data,T_pred>& rhs);

	    template<typename T_data, typename T_pred>
	    friend bool operator>=(tree<T_data,T_pred>& lhs, tree<T_data,T_pred>& rhs);

	    template<typename T_data, typename T_pred>
	    friend bool operator>(tree<T_data,T_pred>& lhs, tree<T_data,T_pred>& rhs);

	    template<typename T_data, typename T_pred>
	    friend bool operator<(tree<T_data,T_pred>& lhs, tree<T_data,T_pred>& rhs);
				
};

#include "implementation.cpp"