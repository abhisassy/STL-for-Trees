#pragma once 

#include <iostream>
using namespace std;

#include <vector>
#include <stack>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <math.h>

/*
template<typename T_conatiner, typename T_datatype>
void resize_(T_container cnt, T_datatype d, int size){
	cnt->resize(size,-1);
}
template<typename T_container>
void resize_(T_container cnt, string d, int size){
	cnt->resize(size,"-1");
}
*/


template< typename T_datatype, typename T_container, typename T_predicate>
tree<T_datatype, T_container, T_predicate>::tree():max_size(0),size(0){    
	cout << "Default constructor called\n";
	T_datatype *temp = new T_datatype();
	root.resize(1,*temp);
	delete temp;
	//T_datatype temp; 
	//resize_(root,temp,1);
}

template< typename T_datatype, typename T_container, typename T_predicate>
tree<T_datatype, T_container, T_predicate>::tree(int t_size):max_size(t_size),size(0){
	cout << "Parameterized constructor called\n";
	T_datatype *temp = new T_datatype();
	root.resize(t_size,*temp);
	delete temp;
	//resize_(root,temp,t_size);
}

template< typename T_datatype, typename T_container, typename T_predicate>
tree<T_datatype, T_container, T_predicate>::~tree(){
	cout << "Destructor called\n";
	//delete[] root;
}

template< typename T_datatype, typename T_container, typename T_predicate>
int tree<T_datatype, T_container, T_predicate>::height(){
//	return(size%2-1); //?? height of binary tree ranges from size-1 to log2(size) no? -- so assuming a full balanced tree h= size/2 +1 
//	return (size/2 + 1); // subject to change later maybe 
//size was wrongly calculated before
	return (ceil(log2(size))); 
//size is the length of container upto the last node entered. So log2 of that should be fine for all trees. Balanced or unbalanced.	
}

template< typename T_datatype, typename T_container, typename T_predicate>
int tree<T_datatype, T_container, T_predicate>::num_leaves(){
	int count=0;
	for(int i=0;i<size;i++){
		if(2*(i+1)<max_size){
			if(root[2*(i+1)]==-1 && root[2*(i+1)-1]==-1)
				count++;
		}
		else if(2*(i+1)-1<max_size){
			if(root[2*(i+1)-1]==-1)
				count++;
		}
		else count++;
	}
	return count;
}

template< typename T_datatype, typename T_container, typename T_predicate>
void tree<T_datatype, T_container, T_predicate>::insert(T_datatype element){
	int i=0;
	T_datatype *temp = new T_datatype();
	T_predicate fn=T_predicate();
	while(true){
		if(i>=max_size){
			root.resize(2*max_size,*temp);
			max_size=max_size*2;
		}
		if(root[i]==*temp){
			root[i]=element;
			if(size<i+1)
				size=i+1;
			return;
		}
		else if(fn(element,root[i])){
			i=2*(i+1)-1;
		}
		else
			i=2*(i+1);
	}
	delete temp;
}

template< typename T_datatype, typename T_container, typename T_predicate>
int tree<T_datatype, T_container, T_predicate>::left_(int i){
	if(2*(i+1)-1>=max_size)
		return -1;
	return (2*(i+1)-1);
}

template< typename T_datatype, typename T_container, typename T_predicate>
int tree<T_datatype, T_container, T_predicate>::right_(int i){
	if(2*(i+1)>=max_size)
		return -1;
	return (2*(i+1));
}

template< typename T_datatype, typename T_container, typename T_predicate>
void tree<T_datatype, T_container, T_predicate>::preorder(){
	T_datatype *temp = new T_datatype();
	stack<int> st;
	int l,r;
	int x;
	st.push(0);
	while(!st.empty()){
		x = st.top();
		st.pop();
		cout << root[x] << " ";
		l=left_(x);
		r=right_(x);
		if(r!=-1 && root[r]!=*temp)
			st.push(r);
		if(l!=-1 && root[l]!=*temp)
			st.push(l);
	}
	delete temp;
	cout << "\n";
	// T_datatype *temp = new T_datatype();
	// int i=0;
	// for(Iterator it=begin();i<size;++it,++i){    // this just failed to work for float , string no idea why   
	// 	if((*it)!=*temp)						// prob something wrong with our iterator
	// 		cout << *it << " ";
	// }
	// int count =0,i=0;
	
	// while(count < size){
		
	// 	if(root[i]!=*temp){
	// 		cout << root[i] << " ";
	// 		count++;
	// 	}
	// 	i++;
	// }
}

template< typename T_datatype, typename T_container, typename T_predicate>
void tree<T_datatype, T_container, T_predicate>::inorder(){
	stack<int> st; //your pushing only index so why make it generic --didnt realise I did that :P
	int i=0;
	//st.push(i);
	int l,r;
	T_datatype *temp = new T_datatype();
	while(!st.empty() || (i!=-1 && root[i]!=*temp)){
		while(i!=-1 && root[i]!=*temp){ //-1 when child beyond max_size
			st.push(i);
			i=left_(i);
		}
		i=st.top();
		cout << root[i] << " ";
		st.pop();
		i=right_(i);
	}
	cout << "\n";
	delete temp;
}

template< typename T_datatype, typename T_container, typename T_predicate>
void tree<T_datatype, T_container, T_predicate>::postorder(){
	stack<int> st;
	int i=0;
	//st.push(i);
	T_datatype *temp = new T_datatype();
	int l,r;
	do{
		while(i!=-1 && root[i]!=*temp){
			if(right_(i)!=-1 && root[right_(i)]!=*temp){
				st.push(right_(i));
			}
			st.push(i);
			i=left_(i);
		}
		i=st.top();
		st.pop();
		if(st.empty()){
			cout << root[i] << " ";
		}
		else{
			if((right_(i)!=-1 && root[right_(i)]!=*temp) && st.top()==right_(i)){
				//cout << st.top() <<" " << i << "\n";
				st.pop();
				st.push(i);
				i=right_(i);
			}
			else{
				cout << root[i] << " ";
				i=-1;
			}
		}
	}while(!st.empty());
	cout << "\n";
	delete temp;
}

template< typename T_datatype, typename T_container, typename T_predicate>
typename tree<T_datatype, T_container, T_predicate>::Iterator tree<T_datatype, T_container, T_predicate>::find(T_datatype element){
	//int count = 0,i=0;						// note : need to fix iterator and come back and reimplement or we could leave it like this  
	Iterator it=begin();
	for(;it!=end() && *it!=element;++it){}
	return it;
	// while(count < size){
	// 	if(root[i]!=*temp)
	// 		count++;
	// 	if(element == root[i])
	// 		return i;
	// 	i++;
	// }
	// return -1;
}

template< typename T_datatype, typename T_container, typename T_predicate>
void tree<T_datatype, T_container, T_predicate>::children(T_datatype element){
	int i=0;
	for(Iterator it=begin();i<size;++it,++i){
		if(*it==element)
			break;
	}
	if(i==size){
		cout <<"Element doesnt exist \n";
		return;
	}
			
	int l = left_(i), r = right_(i);
	T_datatype *temp = new T_datatype();
	if(l==-1 && root[l]!=*temp)
		cout <<"no left child\n";
	else
		cout <<"left: "<<root[l]<<"\n";
	if(r==-1 && root[r]!=*temp)
		cout <<"no right child\n";
	else
		cout <<"right: "<<root[r]<<"\n";	
}