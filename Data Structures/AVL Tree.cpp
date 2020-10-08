/**
 * AVL tree is a self-balancing Binary Search Tree (BST)
 * where the difference between heights of left and right subtrees cannot be more than one for all nodes.
*/



class Node { 
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};  

int height(Node *N) { 
    if (N == NULL) return 0;  
    return N->height;  
}

Node* newNode(int key) {  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1;
    return(node);  
}  

Node *rightRotate(Node *y) {  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    x->right = y;  
    y->left = T2;  
  
    y->height = max(height(y->left), height(y->right)) + 1;  
    x->height = max(height(x->left), height(x->right)) + 1;  
  
    return x;  
}  

Node *leftRotate(Node *x) {  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    y->left = x;  
    x->right = T2;  
  
    x->height = max(height(x->left), height(x->right)) + 1;  
    y->height = max(height(y->left), height(y->right)) + 1;  
  
    return y;  
}  
  
int getBalance(Node *N) {  
    if (N == NULL) return 0;  
    return height(N->left) - height(N->right);  
}  

Node* insert(Node* node, int key) {  
    if (node == NULL) return(newNode(key));  
  
    if (key < node->key) node->left = insert(node->left, key);  
    else if (key > node->key) node->right = insert(node->right, key);  
    else return node;  
  
    node->height = 1 + max(height(node->left), height(node->right));  
  
    int balance = getBalance(node);  
  
    if (balance > 1 && key < node->left->key) return rightRotate(node);  
  
    if (balance < -1 && key > node->right->key) return leftRotate(node);  
  
    if (balance > 1 && key > node->left->key) {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    if (balance < -1 && key < node->right->key) {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    return node;  
}  