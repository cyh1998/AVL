#include <iostream>
#include <algorithm>
#include "avl.h"

int main(){
    int arr[] = {16,3,7,11,9,26,18,14,15};
    AVLTree<int> tree(arr,sizeof(arr)/sizeof(arr[0]));
    tree.traversal();
    cout << endl;
    tree.insert(8);
    tree.traversal();
    cout << endl;
    if(tree.search(14)){
        cout << "Found!" << endl;
    }else{
        cout << "Not Found!" << endl;
    }
    tree.delnode(11);
    tree.traversal();
    cout << endl;
    if(tree.search(11)){
        cout << "Found!" << endl;
    }else{
        cout << "Not Found!" << endl;
    }
    return 0;
}