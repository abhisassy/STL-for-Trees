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
	tree<int,less<int>>::iterator it1;
	for(it1=a.begin_preorder();it1!=a.end_preorder();++it1){
		cout << *it1 << endl;
	}

	cout << "postorder\n";
	tree<int,less<int>>::iterator it2;
	for(it2=a.begin_postorder();it2!=a.end_postorder();++it2){
		cout << *it2 << endl;
	}
	cout<<"find\n";
	cout << a.find(0)<<endl;
	cout << a.find(3)<<endl;

	cout<<"children\n";
	const int* lchild = a.left(3);
	const int* rchild = a.right(5);
	if(lchild!=nullptr)
		cout <<*lchild <<endl;
	if(rchild!=nullptr)
		cout<<*rchild<<endl;

	cout<<"parent\n";
	const int* parent= a.parent(6);
	if(parent!=nullptr)
		cout<< *parent<<endl;



	cout<<"erase\n";
	cout << a.erase(5);
	tree<int,less<int>>::Iterator it4;
	for(it4=a.begin(_pre_);it4!=a.end(_pre_);++it4){
		cout <<*it4 << endl;
	}

	cout<<endl;
	cout << "reverse_iterator\n";
	tree<int,less<int>>::reverse_iterator rt;
	for(rt=a.rbegin();rt!=a.rend();++rt){
		cout << *rt << endl;
	}

	cout << typeid(std::iterator_traits<tree<int,less<int>>::iterator>::value_type).name() << endl;
	// typename tree<int,less<int>>::value_type abc=5;
	// cout << typeid(abc).name() << endl;
	// cout << abc << endl;

	// vector<int> abc;
	// abc.push_back(1);
	// abc.push_back(2);
	// abc.push_back(3);
	// abc.push_back(4);
	// abc.push_back(5);
	// vector<int>::reverse_iterator x=abc.rbegin();
	// ++x;
	// ++x;
	// --x;
	// cout << *x <<"hi";
	// for(x=abc.rbegin();x!=abc.rend();++x){
	// 	cout << *x << endl;
	// }
}
