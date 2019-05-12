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
	cout << boolalpha;
	tree<int,less<int>> a(5); //if predicate is true for (val,key) then val is in the left subtree of key
	a.insert(3);
	a.insert(7);
	a.insert(6);
	cout << a.height() << " :Height\n";
	cout << a.num_leaves() << " :num_leaves\n";
	cout << a.num_nodes() << " :num_nodes\n";
	cout << "inorder\n";
	tree<int,less<int>>::iterator it;
	for(it=a.begin(_inorder_);it!=a.end(_inorder_);++it){
		cout << *it << endl;
	}
	// ukw isnt it better to have one .begin and .end ; and send parameter for which order of traversal
	// thats more at par with other stl libraries
	cout << "preorder\n";
	tree<int,less<int>>::iterator it1;
	for(it1=a.begin(_pre_);it1!=a.end(_pre_);++it1){
		cout << *it1 << endl;
	}

	cout << "postorder\n";
	tree<int,less<int>>::iterator it2;
	for(it2=a.begin(_post_);it2!=a.end(_post_);++it2){
		cout << *it2 << endl;
	}

	cout<<"find\n";
	tree<int,less<int>>::iterator res = a.find(5);
	if(res!=nullptr)
		cout << *res<<endl;
	else
		cout<<"not found\n";
	cout <<a.contains(0)<<endl;

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
	tree<int,less<int>>::iterator it4;
	for(it4=a.begin(_pre_);it4!=a.end(_pre_);++it4){
		cout <<*it4 << endl;
	}

	cout<<endl;

	tree<int,less<int>> a1(5); //if predicate is true for (val,key) then val is in the left subtree of key
	a1.insert(3);
	a1.insert(7);
	a1.insert(6);
	
	cout << "Equality: " << (a==a1) << endl;
	cout << "Inequality: " << (a!=a1) << endl;
	cout << "Lesser than or equal to: " << (a<=a1) << endl;
	cout << "Greater than or equal to: " << (a>=a1) << endl;
	cout << "Greater than: " << (a>a1) << endl;
	cout << "Lesser than: " << (a<a1) << endl;
	cout << "\n\n";

	cout << "reverse_iterator\n";
	tree<int,less<int>>::reverse_iterator rt;
	for(rt=a.rbegin();rt!=a.rend();++rt){
		cout << *rt << endl;
	}
	//rt= a.rbegin();
	//cout<<"here"<<rt[0]<<endl;
	//rt= a.begin();
	//cout<<"here"<<rt[0]<<endl;

	cout << boolalpha;
	cout << a.size() << endl;

	cout << "empty\n";
	cout << a.empty() << endl;
	cout << "cleared\n";
	a.clear();
	cout << "size\n";
	cout << boolalpha;
	cout << a.size() << endl;

	cout << "empty\n";
	cout << a.empty() << endl;

	/////////////////
	cout<<"\n\n\n\n";
	tree<int,less<int>> stl(5);
	stl.insert(3);
	stl.insert(6);
	stl.insert(4);
	stl.insert(7);
	
	tree<int,less<int>>::iterator x;
	x = stl.begin();
	cout << x[0]<<"\n";
	//x[0] = 1;
	//cout << x[0]<<"\n";

	tree<int,less<int>>:: iterator x2;
	x2=x;
	cout<<x2[0]<<"\n";

	disp(x,stl.end());

	tree<int,less<int>> stl2;
	stl2 = stl;  // operator= already working
	disp(stl2.begin(),stl2.end());
	disp(stl.begin(),stl.end());
	
	cout<<stl.front();

	cout<<"\n\nkey compare\n";
	tree<int,less<int>> test;
	tree<int>::key_compare comp = test.key_comp();
	cout<<comp(2,2);
	cout<<"\n\n\n";

	tree<int,less<int>>  y1; y1.insert(0);y1.insert(2);y1.insert(3); 
	tree<int,less<int>>  y2; y2.insert(6);y2.insert(7);y2.insert(9);
	disp(y1.begin(),y1.end());
	disp(y2.begin(),y2.end());
	y1.swap(y2);
	disp(y1.begin(),y1.end());
	disp(y2.begin(),y2.end());

	y1.merge(y2);
	disp(y1.begin(),y1.end());
	cout<<"\nExtract\n";
	tree<int,less<int>>  y3 = y1.extract(3);
	disp(y1.begin(),y1.end());
	disp(y3.begin(),y3.end());



	//find needs to be implemented STL like(returning iterators) and more efficient than a linear search
	// -- find runs faster than linear uses bsts property ; but no point in passing an iterator back 
/*
FROM VECTORS LIBRARY:
operator= // = is already working by default 
at		 //   tree.at() ?? like here again we have to specify order -- seems redundant  .. so instead : 
			  made iterator random access , no need of at , direct indexing possible via iterator	
front	 // done	
const iterator // ? all our iterators are constant , rvalue reference only 
empty		done
size		done
clear		done
operator==, !=, <= (if makes sense)		done
FROM SETS LIBRARY:
extract(maybe)//done
key_comp      // done
merge(maybe)  // done
swap(maybe)   // bad implementation --but done 
contains      // same as find . need to implement ? multiple functions with same action is bad right ?
*/




}