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
	cout << "\n\n\nCreating tree with elements 5, 3, 6, 7\n";
	tree<int,less<int>> a(5); //if predicate is true for (val,key) then val is in the left subtree of key
	a.insert(3);
	a.insert(6);
	a.insert(7);
	cout << a.insert(6) << " returned on trying to insert 6 again\n";
	cout << a.height() << " :Height\n";
	cout << a.num_leaves() << " :num_leaves\n";
	cout << "inorder: ";
	tree<int,less<int>>::iterator it;
	for(it=a.begin(_inorder_);it!=a.end(_inorder_);++it){
		cout << *it << " ";
	}
	cout << "\n";
	// ukw isnt it better to have one .begin and .end ; and send parameter for which order of traversal
	// thats more at par with other stl libraries
	cout << "preorder: ";
	tree<int,less<int>>::iterator it1;
	for(it1=a.begin(_preorder_);it1!=a.end(_preorder_);++it1){
		cout << *it1 << " ";
	}

	cout << "\npostorder: ";
	tree<int,less<int>>::iterator it2;
	for(it2=a.begin(_postorder_);it2!=a.end(_postorder_);++it2){
		cout << *it2 << " ";
	}

	cout<<"\nfind: ";
	tree<int,less<int>>::iterator res = a.find(5);
	if(res!=nullptr)
		cout << *res << " Successful"<<endl;
	else
		cout<<"not found\n";
	cout << "Contains 0? --> ";
	cout <<a.contains(0)<<endl;

	cout<<"children: ";
	const int* lchild = a.left(3);
	const int* rchild = a.right(5);
	if(lchild!=nullptr)
		cout <<*lchild <<" ";
	if(rchild!=nullptr)
		cout<<*rchild<<" ";

	cout<<"\nparent: ";
	const int* parent= a.parent(6);
	if(parent!=nullptr)
		cout<< *parent<<endl;



	cout<<"erase 7: ";
	cout << a.erase(7);
	tree<int,less<int>>::iterator it4;
	cout << "Preorder: ";
	for(it4=a.begin(_preorder_);it4!=a.end(_preorder_);++it4){
		cout <<*it4 << " ";
	}

	cout<<"\n\nCreating new tree, same as initial tree\n";

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

	cout << "reverse_iterator: ";
	tree<int,less<int>>::reverse_iterator rt;
	for(rt=a.rbegin();rt!=a.rend();++rt){
		cout << *rt << " ";
	}
	cout << "\n";

	cout << boolalpha << "Size: ";
	cout << a.size() << endl;

	cout << "empty? --> ";
	cout << a.empty() << endl;
	cout << "clearing the tree\n";
	a.clear();
	cout << "Size: ";
	cout << boolalpha;
	cout << a.size() << endl;

	cout << "empty? --> ";
	cout << a.empty() << endl;

	/////////////////
	cout<<"\n\n\n\n";
	cout << "New tree with 5,3,6,4,7\n";
	tree<int,less<int>> stl(5);
	stl.insert(3);
	stl.insert(6);
	stl.insert(4);
	stl.insert(7);
	
	tree<int,less<int>>::iterator x;
	cout << "[] operator to access element at 0th position ";
	x = stl.begin();
	cout << x[0]<<"\n";
	//x[0] = 1;
	//cout << x[0]<<"\n";

	tree<int,less<int>>:: iterator x2;
	x2=x;
	cout<<x2[0]<<"\n";
	cout << "Inorder: ";
	disp(x,stl.end());

	// tree<int,less<int>> stl2;
	// stl2 = stl;  // operator= already working
	// disp(stl2.begin(),stl2.end());
	// disp(stl.begin(),stl.end());
	
	// cout<<stl.front();

	cout<<"\n\nkey compare\nChecking if 2<3 after extracting predicate from tree class\n";
	tree<int,less<int>> test;
	tree<int>::key_compare comp = test.key_comp();
	cout<<comp(2,3);
	cout<<"\n\n\n";

	cout << "Creating two new trees, displaying them, swapping and displaying again";
	tree<int,less<int>>  y1; y1.insert(0);y1.insert(2);y1.insert(3); 
	tree<int,less<int>>  y2; y2.insert(6);y2.insert(7);y2.insert(9);
	cout << "t1: ";
	disp(y1.begin(),y1.end());
	cout << "t2: ";
	disp(y2.begin(),y2.end());
	y1.swap(y2);
	cout << "swapping..\n";
	cout << "t1: ";
	disp(y1.begin(),y1.end());
	cout << "t2: ";
	disp(y2.begin(),y2.end());

	cout << "Merging t1 and t2\n";
	y1.merge(y2);
	disp(y1.begin(),y1.end());
	cout<<"\nExtract and display both trees\n";
	tree<int,less<int>>&  y3 = y1.extract(3);
	disp(y1.begin(),y1.end());
	disp(y3.begin(),y3.end());


	tree<int,less<int>>  random; random.insert(0);random.insert(2);random.insert(3); 
	auto it_r = random.begin(_inorder_);
	cout <<"\n\nRANDOM ACCESS on tree with 0, 2, 3\n";
	cout <<*it_r ;
	cout <<" testing by accessing the third element from the first " <<*(it_r +2)<<endl;
	cout <<*it_r ;
	it_r++;
	auto it_2 = random.begin(_inorder_);
	cout<<"\ntesting - by subtracting iterator to second element and iterator to first element\n";
	cout<<it_r - it_2<<endl;

}