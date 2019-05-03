#include "tree.h"

int main(){
    cout <<" tree.h compiled \n\n";


    cout << "\nTest Case 1: \ndata type : int , container : vector , default predicate\n";

    tree<int,vector<int>> tree1(5);
    tree1.insert(6);
    tree1.insert(4);
    tree1.insert(5);
    tree1.insert(7);
    tree1.insert(8);
    tree1.insert(9);
    tree1.preorder();
    tree1.inorder();
    tree1.postorder();
    tree<int,vector<int>>::Iterator it=tree1.find(5);
    if(it!=tree1.end())
        cout <<"find : "<< *it << "\n";
    else
        cout << "Not found\n";
    it=tree1.find(16);
    if(it!=tree1.end())
        cout <<"find : "<< *it << "\n";
    else
        cout << "Not found\n";
    cout <<"children : ";tree1.children(6);

    cout << "\nTest Case 2: \ndata type : char , container : vector , default predicate\n";
    tree<char,vector<char>> tree2(5);
    tree2.insert('a');
    tree2.insert('b');
    tree2.insert('c');
    tree2.insert('d');
    tree2.insert('e');
    tree2.preorder();
    tree2.inorder();
    tree2.postorder();
    tree<char,vector<char>>::Iterator it2=tree2.find('d');
    if(it2!=tree2.end())
        cout <<"find : "<< *it2 << "\n";
    else
        cout << "Not found\n";
    it2=tree2.find('x');
    if(it2!=tree2.end())
        cout <<"find : "<< *it2 << "\n";
    else
        cout << "Not found\n";
    cout <<"children : ";tree2.children('a');

    cout << "\nTest Case 3: \ndata type : float , container : vector , default predicate\n";
    tree<float,vector<float>> tree3(5);
    tree3.insert(1.1);
    tree3.insert(2.2);
    tree3.insert(3.3);
    tree3.insert(4.4);
    tree3.insert(5.5);
    tree3.preorder();
    tree3.inorder();
    tree3.postorder();
    tree<float,vector<float>>::Iterator it3=tree3.find(2.2);
    if(it3!=tree3.end())
        cout <<"find : "<< *it3 << "\n";
    else
        cout << "Not found\n";
    it3=tree3.find(16.0);
    if(it3!=tree3.end())
        cout <<"find : "<< *it3 << "\n";
    else
        cout << "Not found\n";
    cout <<"children : ";tree3.children(1.1);

    cout << "\nTest Case 4: \ndata type : string , container : vector , default predicate\n";
    tree<string,vector<string>> tree4(5);
    tree4.insert("abc");
    tree4.insert("def");
    tree4.insert("hij");
    tree4.insert("yyy");
    tree4.insert("xxx");
    tree4.preorder();
    tree4.inorder();
    tree4.postorder();
    tree<string,vector<string>>::Iterator it4=tree4.find("abc");
    if(it4!=tree4.end())
        cout <<"find : "<< *it4 << "\n";
    else
        cout << "Not found\n";
    it4=tree4.find("dd");
    if(it4!=tree4.end())
        cout <<"find : "<< *it4 << "\n";
    else
        cout << "Not found\n";
    cout <<"children : ";tree4.children("abc");
    
    cout << "\nTest Case 5: \ndata type : double , container : vector , default predicate\n";
    tree<double,vector<double>> tree5(5);
    tree5.insert(1.23333);
    tree5.insert(3.4444444);
    tree5.insert(5.33232);
    tree5.insert(5.212);
    tree5.insert(1.23232);
    tree5.preorder();
    tree5.inorder();
    tree5.postorder();
    tree<double,vector<double>>::Iterator it5=tree5.find(1.23232);
    if(it5!=tree5.end())
        cout <<"find : "<< *it5 << "\n";
    else
        cout << "Not found\n";
    it5=tree5.find(1.2);
    if(it5!=tree5.end())
        cout <<"find : "<< *it5 << "\n";
    else
        cout << "Not found\n";
    cout <<"children : ";tree5.children(123);

    
    return 0; 
}