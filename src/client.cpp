#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string.h>
#include <typeinfo>
#include "tree.h"

int main(){
	tree<int,less<int>> a(5);
	a.insert(3);
	a.insert(7);
	a.insert(6);
	cout << a.height() << "\n";
	cout << a.num_leaves() << "\n";
	cout << a.num_nodes() << "\n";
	tree<int,less<int>>::iterator it;
	it = a.begin();
	// for(it=a.begin();it!=a.end();++it){
	// 	cout << *it << endl;
	// }
}