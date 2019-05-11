#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <typeinfo>
#include <math.h>

template<typename T_datatype, typename T_predicate>
tree<T_datatype, T_predicate>::tree():root(nullptr){
	root=nullptr;
	size=0;
	cout << "Default constructor\n";
}

template<typename T_datatype, typename T_predicate>
tree<T_datatype, T_predicate>::tree(node<T_datatype>* param):root(param){
	root=param;
	size=1;
	cout << "Parameterized constructor\n";
}

template<typename T_datatype, typename T_predicate>
tree<T_datatype, T_predicate>::tree(T_datatype val){
	root=new node<T_datatype>;
	root->value  = val;
	root->left   = nullptr;
	root->right  = nullptr;
	root->parent = nullptr;
	size=1;
	cout << "Parameterized constructor\n";	
}

template<typename T_datatype, typename T_predicate>
void tree<T_datatype, T_predicate>::delete_tree_(node<T_datatype>* root){
	if(root!=nullptr)
    {
        delete_tree_(root->left);
        delete_tree_(root->right);
        if(root->left!=nullptr)
            root->left=nullptr;
        if(root->right!=nullptr)
            root->right=nullptr;
        delete root;
        root=nullptr;
    }
}

template<typename T_datatype, typename T_predicate>
tree<T_datatype, T_predicate>::~tree(){
	cout << "Destructor\n";
	delete_tree_(root);
	size=0;
}

template<typename T_datatype, typename T_predicate>
int tree<T_datatype, T_predicate>::height_(node<T_datatype>* ptr){
	if(ptr==nullptr)
		return -1;

	return 1+max(height_(ptr->left),height_(ptr->right));
}

template<typename T_datatype, typename T_predicate>
int tree<T_datatype, T_predicate>::height(){
	return height_(root);
}

template<typename T_datatype, typename T_predicate>
int tree<T_datatype, T_predicate>::num_leaves_(node<T_datatype>* ptr){
	if(ptr==nullptr)
		return 0;
	if(ptr->left==nullptr && ptr->right==nullptr)
		return 1;
	return num_leaves_(ptr->left)+num_leaves_(ptr->right);
}

template<typename T_datatype, typename T_predicate>
int tree<T_datatype, T_predicate>::num_leaves(){
	return num_leaves_(root);
}

template<typename T_datatype, typename T_predicate>
int tree<T_datatype, T_predicate>::num_nodes_(node<T_datatype>* ptr){
	if(ptr==nullptr)
		return 0;
	return 1+num_nodes_(ptr->left)+num_nodes_(ptr->right);
}

template<typename T_datatype, typename T_predicate>
int tree<T_datatype, T_predicate>::num_nodes(){
	return num_nodes_(root);
}

template<typename T_datatype, typename T_predicate>
void tree<T_datatype, T_predicate>::insert(T_datatype element){
	node<T_datatype>* ele=new node<T_datatype>;
	ele->value  = element;
	ele->left   = nullptr;
	ele->right  = nullptr;
	ele->parent = nullptr;
	T_predicate fn = T_predicate();
	node<T_datatype>* iter=root, *prev=nullptr;
	if(root==nullptr){
		root=ele;
		size++;
		return;
	}
	while(true){
		if(fn(element,iter->value)){
			if(iter->left==nullptr){
				iter->left=ele;
				ele->parent=iter;
				break;
			}
			else
				iter=iter->left;
		}
		else{
			if(iter->right==nullptr){
				iter->right=ele;
				ele->parent=iter;
				break;
			}
			else if(iter->right->value==element || iter->value==element)
				break;
			else
				iter=iter->right;
		}
	}
	size++;
}


template<typename T_datatype, typename T_predicate>
bool tree<T_datatype, T_predicate>::find(T_datatype element){

	node<T_datatype>* iter = find_(element);
	if(iter == nullptr)
		return false;
	else 
		return true;

}
template<typename T_datatype, typename T_predicate>
node<T_datatype>*  tree<T_datatype, T_predicate>::find_(T_datatype element){
	node<T_datatype>* iter=root;
	
	T_predicate fn = T_predicate();
	
	while(true){
		if(iter == nullptr)
			return nullptr;
		if(iter->value == element)
			return iter;
		if(fn(element,iter->value)){
			iter = iter->left;
		}
		else
			iter = iter->right;
	}
}

template<typename T_datatype, typename T_predicate>
const T_datatype* tree<T_datatype, T_predicate>::parent(T_datatype element){
	
	node<T_datatype>* iter  = find_(element);
	
	if(iter == nullptr || iter->parent==nullptr)
		return nullptr;
	else	
		return &iter->parent->value;	
}

template<typename T_datatype, typename T_predicate>
const T_datatype* tree<T_datatype, T_predicate>::left(T_datatype element){
	
	node<T_datatype>* iter  = find_(element);
	
	if(iter == nullptr)
		return nullptr;
	if(iter->left!=nullptr)
		return &iter->left->value;
	else
		return nullptr;
	
}

template<typename T_datatype, typename T_predicate>
const T_datatype* tree<T_datatype, T_predicate>::right(T_datatype element){
	
	node<T_datatype>* iter  = find_(element);
	
	if(iter == nullptr)
		return nullptr;
	if(iter->right!=nullptr)
		return &iter->right->value;
	else
		return nullptr;
	
}
template<typename T_datatype, typename T_predicate>
bool tree<T_datatype, T_predicate>::erase(T_datatype element){

	node<T_datatype>* iter  = find_(element);
	if(iter == nullptr)
		return false;
	if(iter->left == nullptr && iter->right == nullptr)
		{
			if(iter->value == root->value)
				root = nullptr;
			else{
				const T_datatype *temp = left(iter->parent->value);
				if(temp!=nullptr  && *temp==iter->value)
					iter->parent->left=nullptr;
				else
					iter->parent->right=nullptr;
			}
			delete iter;
			iter = nullptr;
		}	
	
	else if(iter->left == nullptr){
		if(iter->value == root->value){
			root = root->right;
		}
		else{
			const T_datatype *temp = left(iter->parent->value);
			if(temp!=nullptr  && *temp==iter->value)
				iter->parent->left=iter->right;
			else
				iter->parent->right=iter->right;
		}
		delete iter;
		iter = nullptr;  
		
	}
	else if(iter->right == nullptr){
		if(iter->value == root->value){
			root = root->left;
		}
		else{
			const T_datatype *temp = left(iter->parent->value);
			if(temp!=nullptr  && *temp==iter->value)
				iter->parent->left=iter->left;
			else
				iter->parent->right=iter->left;
		}
		delete iter;
		iter = nullptr;  
		
		
	}
	else{
		
		node<T_datatype>* iter2 = iter;
		iter = iter->right;
		while(iter->left!=nullptr){
			iter = iter->left;
		}
		iter->parent->left=nullptr;
		iter2->value = iter->value;
		delete iter;
		iter = nullptr;  
	}
	size--;
	return true;
}