#include "intbst.h"

#include <iostream>
using namespace std;

int main() {
    
    IntBST bst;

    bst.insert(3);

    bst.remove(3);

    bst.printPreOrder();
    cout << endl;

    return 0;
}