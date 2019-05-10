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
	root->value=val;
	root->left=nullptr;
	root->right=nullptr;
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
	ele->value=element;
	ele->left=nullptr;
	ele->right=nullptr;
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
				break;
			}
			else
				iter=iter->left;
		}
		else{
			if(iter->right==nullptr){
				iter->right=ele;
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
