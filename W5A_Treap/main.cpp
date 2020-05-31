#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct TreapNode{
    unsigned int key, pri; // key, priority
    TreapNode *left, *right; // left and right children
    //TreapNode(unsigned int k, unsigned int p) : key(k), pri(p), left(nullptr), right(nullptr) {}
    TreapNode(){}
};

TreapNode* newNode(unsigned int k, unsigned int p) {
    TreapNode* node_ptr = new TreapNode;
    node_ptr->key = k; node_ptr->pri = p;
    node_ptr->left = node_ptr->right = nullptr;
    return node_ptr;
}

void getin(string fn);
void getin();
TreapNode* lrotate(TreapNode* node);
TreapNode* rrotate(TreapNode* node);
TreapNode* insertNode(TreapNode* root, unsigned int k, unsigned int p);
void findNode(TreapNode* node, unsigned int k);
TreapNode* deleteNode(TreapNode* node, unsigned int k);
void inorder(TreapNode* root);
void preorder(TreapNode* root);

int main()
{
    //getin("in.txt");
    getin();
    return 0;
}

void getin() {
    TreapNode* root = new TreapNode;
    root = nullptr; // null pointer
    string s;
    int m;
    unsigned int k, p;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> s;
        if (s.compare("insert") == 0){
            cin >> k >> p;
            root =  insertNode(root, k,p);
        } else if (s.compare("find") == 0) {
            cin >> k;
            findNode(root, k);
        } else if (s.compare("delete") == 0) {
            cin >> k;
            root = deleteNode(root, k);
        } else if (s.compare("print") == 0) {
            inorder(root);
            cout << endl;
            preorder(root);
            cout << endl;
        }
    }
}

void getin(string fn) {
    ifstream infile(fn);
    TreapNode* root = new TreapNode;
    root = nullptr; // null pointer
    string s;
    int m;
    unsigned int k, p;
    infile >> m;
    for (int i = 0; i < m; i++) {
        infile >> s;
        if (s.compare("insert") == 0){
            infile >> k >> p;
            root =  insertNode(root, k,p);
            //printNode(root);
            //inorder(root);
        } else if (s.compare("find") == 0) {
            infile >> k;
            findNode(root, k);
        } else if (s.compare("delete") == 0) {
            infile >> k;
            root = deleteNode(root, k);
        } else if (s.compare("print") == 0) {
            inorder(root);
            cout << endl;
            preorder(root);
            cout << endl;
        }
    }
    infile.close();
}

TreapNode* lrotate(TreapNode* x){
    TreapNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
TreapNode* rrotate(TreapNode* y){
    TreapNode* x = y->left;
    y->left = x-> right;
    x-> right = y;
    return x;
}

TreapNode* insertNode(TreapNode* node, unsigned int key, unsigned int pri) {
    if (node == nullptr) {      // when reach a left node
        return newNode(key,pri);    // create a new node
    }

    if (key == node->key) {
        // ignore duplicated keys
        return node;
    }

    if (key < node->key) {
        // move to the left child
        // then, update the pointer to the left child
        node->left = insertNode(node->left, key, pri);
        // right rotate if the left child has higher priority
        if (node->pri < node->left->pri) {
            node = rrotate(node);
        }
    } else { // key > node.key
        // move to the right child
        // then, update the pointer to the right child
        node->right = insertNode(node->right, key, pri);
        // left rotate if the right child has higher priority
        if (node->pri < node->right->pri) {
            node = lrotate(node);
        }
    }
    return node;
}

void findNode(TreapNode* node, unsigned int key) {
    if (node == nullptr) {cout << "no\n"; return;} // already reach a child of a left node but find nothing
    if (key == node->key) {cout << "yes\n"; return;} // find out!
    if (key < node->key) {findNode(node->left, key);}
    else {findNode(node->right, key);}
}

TreapNode* deleteNode(TreapNode* node, unsigned int key) {
    if (node == nullptr) { // the treap does not contain the key
        return nullptr;
    }
    if (key == node->key) { // the current node is the target node
        // the target node is a leaf node
        if ((node->left == nullptr)&&(node->right==nullptr)) {
            delete(node);
            return nullptr;
        }
        // the target node has a right child but no left child
        else if (node->left==nullptr) {
            node = lrotate(node);
        }
        // the target node has a left child but no right child
        else if (node->right==nullptr) {
            node = rrotate(node);
        }
        else {  // the target node has both left and right children
            // pull up the child with higher priority
            if (node->right->pri > node->left->pri) {
                node = lrotate(node);
            } else {
                node = rrotate(node);
            }
        }
        return deleteNode(node,key);
    }
    // search the target node recursively
    if (key < node->key) {
        node->left = deleteNode(node->left,key);
    } else {
        node->right = deleteNode(node->right,key);
    }
    return node;
}

void inorder(TreapNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << " " << root->key;
        inorder(root->right);
    }
}

void preorder(TreapNode* root) {
    if (root != nullptr) {
        cout << " " << root->key;
        preorder(root->left);
        preorder(root->right);
    }
}
