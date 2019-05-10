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
		tree();
		tree(node<T_datatype>*);
		tree(T_datatype val);
		~tree();

		class iterator{ //inorder
			int p;
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
					p=0;
				}
		        iterator(node<T_datatype>*ptr){
		        	inorder_(v,ptr);
		        	// for(int i=0;i<v.size();++i){
		        	// 	cout << v[i]->value << "hi\n";
		        	// }
		        	if(v.size()>0)
		        		p = 0;
		        	else
		        		p = -1;
		        }

		        iterator(node<T_datatype>*ptr,bool end){
		        	inorder_(v,ptr);
		        	// for(int i=0;i<v.size();++i){
		        	// 	cout << v[i]->value << "hi\n";
		        	// }
		        	if(v.size()>0)
		        		p = v.size();
		        	else
		        		p = -1;
		        }


		        bool operator==(const iterator& rhs) const{
		            return p==rhs.p;
		        }

		        bool operator!=(const iterator& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return v[p]->value; //want to return the node or the value of the node?
		        }

		        iterator operator++(int){    // postfix ++ // edit : parameter has to be int always 
		            iterator temp(*this);
		            ++*this;
		            return temp;
		        }

		        iterator operator++(){ 
		            ++p;
		            return *this;
		        }

		        iterator operator--(int){    // postfix -- 
		            iterator temp(*this);
		            --*this;
		            return temp;
		        }

		        iterator operator--(){ 
		            --p;
		            return *this;
		        }

		        friend class tree;
		};

		class iterator_preorder{ //preorder
			int p;
			vector<node<T_datatype>*> v;   //node or just value?

			public:
				void preorder_(vector<node<T_datatype>*>& v, node<T_datatype>* subtree){
					if(subtree!=nullptr){
						v.push_back(subtree);
						preorder_(v,subtree->left);
						preorder_(v,subtree->right);
					}
				}
				iterator_preorder(){
					p=0;
				}
		        iterator_preorder(node<T_datatype>*ptr){
		        	preorder_(v,ptr);
		        	// for(int i=0;i<v.size();++i){
		        	// 	cout << v[i]->value << "hi\n";
		        	// }
		        	if(v.size()>0)
		        		p = 0;
		        	else
		        		p = -1;
		        }

		        iterator_preorder(node<T_datatype>*ptr,bool end){
		        	preorder_(v,ptr);
		        	// for(int i=0;i<v.size();++i){
		        	// 	cout << v[i]->value << "hi\n";
		        	// }
		        	if(v.size()>0)
		        		p = v.size();
		        	else
		        		p = -1;
		        }


		        bool operator==(const iterator_preorder& rhs) const{
		            return p==rhs.p;
		        }

		        bool operator!=(const iterator_preorder& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return v[p]->value; //want to return the node or the value of the node?
		        }

		        iterator_preorder operator++(int){    // postfix ++ // edit : parameter has to be int always 
		            iterator_preorder temp(*this);
		            ++*this;
		            return temp;
		        }

		        iterator_preorder operator++(){ 
		            ++p;
		            return *this;
		        }

		        iterator_preorder operator--(int){    // postfix -- 
		            iterator_preorder temp(*this);
		            --*this;
		            return temp;
		        }

		        iterator_preorder operator--(){ 
		            --p;
		            return *this;
		        }

		        friend class tree;
		};

		class iterator_postorder{ //postorder
			int p;
			vector<node<T_datatype>*> v;   //node or just value?

			public:
				void postorder_(vector<node<T_datatype>*>& v, node<T_datatype>* subtree){
					if(subtree!=nullptr){
						postorder_(v,subtree->left);
						postorder_(v,subtree->right);
						v.push_back(subtree);
					}
				}
				iterator_postorder(){
					p=0;
				}
		        iterator_postorder(node<T_datatype>*ptr){
		        	postorder_(v,ptr);
		        	// for(int i=0;i<v.size();++i){
		        	// 	cout << v[i]->value << "hi\n";
		        	// }
		        	if(v.size()>0)
		        		p = 0;
		        	else
		        		p = -1;
		        }

		        iterator_postorder(node<T_datatype>*ptr,bool end){
		        	postorder_(v,ptr);
		        	// for(int i=0;i<v.size();++i){
		        	// 	cout << v[i]->value << "hi\n";
		        	// }
		        	if(v.size()>0)
		        		p = v.size();
		        	else
		        		p = -1;
		        }


		        bool operator==(const iterator_postorder& rhs) const{
		            return p==rhs.p;
		        }

		        bool operator!=(const iterator_postorder& rhs) const{
		            return !(*this==rhs);
		        }

		        T_datatype operator*() const{
		            return v[p]->value; //want to return the node or the value of the node?
		        }

		        iterator_postorder operator++(int){    // postfix ++ // edit : parameter has to be int always 
		            iterator_postorder temp(*this);
		            ++*this;
		            return temp;
		        }

		        iterator_postorder operator++(){ 
		            ++p;
		            return *this;
		        }

		        iterator_postorder operator--(int){    // postfix -- 
		            iterator_postorder temp(*this);
		            --*this;
		            return temp;
		        }

		        iterator_postorder operator--(){ 
		            --p;
		            return *this;
		        }

		        friend class tree;
		};

		iterator begin(){
        	return iterator(root);  
	    }

	    iterator end(){
	    	return iterator(root,true);
	    }

	    iterator_preorder begin_preorder(){
        	return iterator_preorder(root);  
	    }

	    iterator_preorder end_preorder(){
	    	return iterator_preorder(root,true);
	    }

	    iterator_postorder begin_postorder(){
        	return iterator_postorder(root);  
	    }

	    iterator_postorder end_postorder(){
	    	return iterator_postorder(root,true);
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