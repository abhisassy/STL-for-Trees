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
	tree<int,less<int>>::iterator it;
	for(it=a.begin();it!=a.end();++it){
		cout << *it << endl;
	}

	cout << "preorder\n";
	tree<int,less<int>>::iterator_preorder it1;
	for(it1=a.begin_preorder();it1!=a.end_preorder();++it1){
		cout << *it1 << endl;
	}

	cout << "postorder\n";
	tree<int,less<int>>::iterator_postorder it2;
	for(it2=a.begin_postorder();it2!=a.end_postorder();++it2){
		cout << *it2 << endl;
	}
}