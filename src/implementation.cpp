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
	size_of_tree=0;
	cout << "Default constructor\n";
}

template<typename T_datatype, typename T_predicate>
tree<T_datatype, T_predicate>::tree(node<T_datatype>* param):root(param){
	root=param;
	size_of_tree=1;
	cout << "Parameterized constructor\n";
}

template<typename T_datatype, typename T_predicate>
tree<T_datatype, T_predicate>::tree(T_datatype val){
	root=new node<T_datatype>;
	root->value  = val;
	root->left   = nullptr;
	root->right  = nullptr;
	root->parent = nullptr;
	size_of_tree=1;
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
	size_of_tree=0;
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
bool tree<T_datatype, T_predicate>::insert(T_datatype element){
	node<T_datatype>* ele=new node<T_datatype>;
	ele->value  = element;
	ele->left   = nullptr;
	ele->right  = nullptr;
	ele->parent = nullptr;
	T_predicate fn = T_predicate();
	node<T_datatype>* iter=root, *prev=nullptr;
	if(root==nullptr){
		root=ele;
		size_of_tree++;
		return true;
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
		else if(fn(iter->value,element)){
			if(iter->right==nullptr){
				iter->right=ele;
				ele->parent=iter;
				break;
			}
			else
				iter=iter->right;
		}
		else{
			return false;
		}
	}
	size_of_tree++;
	return true;
}

template<typename T_datatype, typename T_predicate>
typename tree<T_datatype, T_predicate>::iterator tree<T_datatype, T_predicate>::find(T_datatype element){

	tree<T_datatype, T_predicate>::iterator it = begin();
	while(it!=end()){
		if(*it == element)
			return it;
		++it;
	}

	return nullptr;

}

template<typename T_datatype, typename T_predicate>
bool tree<T_datatype, T_predicate>::contains(T_datatype element){

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
	size_of_tree--;
	return true;
}


template<typename T_datatype, typename T_predicate>
bool tree<T_datatype, T_predicate>::empty() const{
	if(root == nullptr && size_of_tree==0)
		return true;
	return false;
}

template<typename T_datatype, typename T_predicate>
size_t tree<T_datatype, T_predicate>::size() const{
	return size_of_tree;
}

template<typename T_datatype, typename T_predicate>
void tree<T_datatype, T_predicate>::clear(){
	delete_tree_(root);
	size_of_tree=0;
	root=nullptr; // for some reason delete_tree_ didnt set root to nullptr
}

template<typename T_datatype, typename T_predicate>
bool operator==(tree<T_datatype,T_predicate>& lhs, tree<T_datatype,T_predicate>& rhs){
	if(lhs.size_of_tree==rhs.size_of_tree){
		auto i=lhs.begin();
		auto j=rhs.begin();
		for(;i!=lhs.end()&&j!=rhs.end();++i,++j){
			if(*i!=*j)
				return false;
		}
		if(i==lhs.end() && j==rhs.end())
			return true;
		return false;
	}
	return false;
}

template<typename T_datatype, typename T_predicate>
bool operator!=(tree<T_datatype,T_predicate>& lhs, tree<T_datatype,T_predicate>& rhs){
	return !(lhs==rhs);
}

template<typename T_datatype, typename T_predicate>
bool operator<=(tree<T_datatype,T_predicate>& lhs, tree<T_datatype,T_predicate>& rhs){
	size_t s = lhs.size()<rhs.size()? lhs.size() : rhs.size();
	auto i=lhs.begin();
	auto j=rhs.begin();
	for(size_t x=0;x<s;++i,++j,++x){
		if(*i > *j)
			return false;
	}
	if(lhs.size() <= rhs.size() )
		return true;
	return false;
}

template<typename T_datatype, typename T_predicate>
bool operator>=(tree<T_datatype,T_predicate>& lhs, tree<T_datatype,T_predicate>& rhs){
	size_t s = lhs.size()<rhs.size()? lhs.size() : rhs.size();
	auto i=lhs.begin();
	auto j=rhs.begin();
	for(size_t x=0;x<s;++i,++j,++x){
		if(*i < *j)
			return false;
	}
	if(lhs.size() >= rhs.size() )
		return true;
	return false;
}

template<typename T_datatype, typename T_predicate>
bool operator>(tree<T_datatype,T_predicate>& lhs, tree<T_datatype,T_predicate>& rhs){
	return !(lhs<=rhs);
}

template<typename T_datatype, typename T_predicate>
bool operator<(tree<T_datatype,T_predicate>& lhs, tree<T_datatype,T_predicate>& rhs){
	return !(lhs>=rhs);
}


template<typename T_datatype, typename T_predicate>
T_datatype tree<T_datatype, T_predicate>::front(){
	return root->value;
}


template<typename T_datatype, typename T_predicate>
T_predicate tree<T_datatype, T_predicate>::key_comp(){
	key_compare temp;
	return temp;
}
template<typename T_datatype, typename T_predicate>
void tree<T_datatype, T_predicate>::swap(tree<T_datatype,T_predicate>& rhs){
	
	auto it1a = begin();   auto it1b = end();
	auto it2a = rhs.begin();   auto it2b = rhs.end();

	clear();
	rhs.clear();

	for(;it1a != it1b ;++it1a)
		rhs.insert(*it1a);
	
	for(;it2a != it2b ;++it2a)
		insert(*it2a);
	
	return;
}

template<typename T_datatype, typename T_predicate>
void tree<T_datatype, T_predicate>::merge(tree<T_datatype,T_predicate> &rhs){

	auto ita = rhs.begin();
	auto itb = rhs.end();

	for(;ita!=itb;++ita)
		insert(*ita);

}

template<typename T_datatype, typename T_predicate>
tree<T_datatype,T_predicate> tree<T_datatype, T_predicate>::extract(T_datatype element){

	erase(element);
	tree<T_datatype,T_predicate> new_tree(element);
	return new_tree;

}


