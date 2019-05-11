#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <typeinfo>
#include "tree1.h"

int main(){
	tree<int,less<int>> a(5); //if predicate is true for (val,key) then val is in the left subtree of key
	a.insert(3);
	a.insert(7);
	a.insert(6);
	cout << a.height() << " :Height\n";
	cout << a.num_leaves() << " :num_leaves\n";
	cout << a.num_nodes() << " :num_nodes\n";
	cout << "inorder\n";
	tree<int,less<int>>::Iterator it;
	for(it=a.begin(_inorder_);it!=a.end(_inorder_);++it){
		cout << *it << endl;
	}
	// ukw isnt it better to have one .begin and .end ; and send parameter for which order of traversal
	// thats more at par with other stl libraries
	cout << "preorder\n";
	tree<int,less<int>>::Iterator it1;
	for(it1=a.begin(_pre_);it1!=a.end(_pre_);++it1){
		cout << *it1 << endl;
	}

	cout << "postorder\n";
	tree<int,less<int>>::Iterator it2;
	for(it2=a.begin(_post_);it2!=a.end(_post_);++it2){
		cout << *it2 << endl;
	}
}