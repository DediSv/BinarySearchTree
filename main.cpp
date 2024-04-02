///Binary Search Tree
#include <iostream>
#include <vector>

using namespace std;

class Heap{ // Node
public:
    int data = NULL;
    Heap *left, *right;
};

Heap *Create(int n){ //Creating the first element
    Heap *node = new Heap;
    node->data = n;
    node->left = node->right = nullptr;
    return node;
}

Heap *Insert(Heap *root, int n) { // Pushing
    if (root == nullptr)
        root = Create(n);
    Heap *tmp = root;
    while (tmp != nullptr) {
        if (n <= tmp->data) {//<= cuz I decided to write numbers to the left side
            if (tmp->left == nullptr) {
                tmp->left = Create(n);
                return root;
            }
            tmp = tmp->left; //i++
        } else if (n > tmp->data) {
            if (tmp->right == nullptr) {
                tmp->right = Create(n);
                return root;
            }
            tmp = tmp->right;//i++
        }
    }
}

bool FindEl(Heap *root, int value){ //Finding element in heap thew recurs(we always need this func)
    if (root == nullptr) { //Vypis cesty s hledaním prvku rekurzivně (?)
        cout << "148";
        return false;
    }
    if (root->data == value) {
        cout << "\nFound.\n";
        return true;
    }
    else if (value < root->data) {
        cout << "\nGoing left\n";
        FindEl(root->left, value);
    }
    if (value > root->data) {
        cout << "\nGoing right\n";
        FindEl(root->right, value);
    }
}


Heap *FindElNere(Heap *root, int n){ //Find nerekurzivně!!
    Heap *node = root;
    while (node != nullptr) {
        if (node->data == n)
            return node;
        if (n < node->data) {
            if (node->left == nullptr)
                return nullptr;
            node = node->left;
        }
        else if(n > node->data) {
            if (node->right == nullptr)
                return nullptr;
            node = node->right;
        }
    }
}

void VypisCesty(Heap *root, int n){ //Writing down the way to element (B)
    if (root == nullptr) {  ///Improving of cod below
        cout << "Not found.\n";
        return;
    }
    cout << root->data << " ";
    if (root->data == n)
        cout << "\nFound.\n";
//        if (root->left == nullptr && root->right == nullptr) //It was improved
//        cout << "not found";
    if (n < root->data) VypisCesty(root->left,n);
    if (n > root->data) VypisCesty(root->right,n);
}

void Vypis(Heap* root){ //G
/*    if (root->left == nullptr && root->right == nullptr) {   //Doesnt work//
        cout << root->data << " ";
        return;
    }
    else */if (root == nullptr)
        return;
    Vypis(root->left);
    cout << root->data << " ";
    Vypis(root->right);
}

int PocetUzlu(Heap *root){ //C) Counting the amount of nodes from root REKURZ
    if (root == nullptr)
        return 0; //Tree is empty
    if (root->left == nullptr && root->right == nullptr)
        return 1; //Tree has only root
    return PocetUzlu(root->right) + PocetUzlu(root->left) + 1;
}

void Removing(Heap *&root, int value){ //DELETE
    if (root == nullptr)
        return;
    if (root->data == value){
        if (root->left == nullptr && root->right == nullptr) { //Basic case 1st(Node is a list)
            root = nullptr;
            return;
        }
        else if (root->right == nullptr){ //Je-li Node ma jenom levého syna
            Heap *tmp = root; //Saving the node to the temporary
            root = root->left;
            tmp = nullptr;
            return;
        }
        else if (root->left == nullptr){ //Je-li Node ma jenom pravého syna
            Heap *tmp = root; //Saving the node to the temporary
            root = root->right;
            tmp = nullptr;
            return;
        }
        else { //(Node má hodně synů)Bereme největšího syna z prvního levého elementa
            Heap *tmp = root;
            tmp = root->left;//One step to the left
            while (tmp->right != nullptr && tmp)//While going right-going.
                 tmp = tmp->right;
            root->data = tmp->data;
            Removing(root->left,tmp->data);//Deleting Node and controlling their sons
        }
    }
    else if (value < root->data){
        Removing(root->left, value);
    }
    else if (value > root->data){
        Removing(root->right, value);
    }
}

int main() {
    vector <int> input{5,15,3,7,6,2,8,12};
    Heap *root = Create(input[0]);
    for (int i = 1; i < input.size(); i++)
        Insert(root, input[i]);
    cout << "Setříděná posloupnost z heap:\n";
    Vypis(root);
    cout << "\nFinding Element:\n";
    bool node = FindElNere(root,12);
    cout << "\t" << node;
    cout << "\nNodes number:\n\t" << PocetUzlu(FindElNere(root,12)) << "\n";
    cout << "Vypis cesty:\n";
    VypisCesty(root,12);
    cout << "\nSearch Recursive(With directions):\n";
    int value;
    cin >> value;
    cout << FindEl(root,value);
    cout << "\nRemoving element:\n";
    Removing(root,6);
    Vypis(root);
    return 0;
}