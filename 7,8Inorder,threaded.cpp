/*Create inorder threaded binary search tree and implement following operations
1. Insert a new node  2. Inorder and preorder traversal 
3. Convert given binary search tree into threaded binary search  tree. 
*/

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool isthreaded;

    Node(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
        isthreaded = false;
    }
};

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

void insertbst(TreeNode*& root, int val) {
    if (root == nullptr) {
        root = new TreeNode(val);
        return;
    }
    if (val >= root->data) {
        insertbst(root->right, val);
    }
    else {
        insertbst(root->left, val);
    }
}

void insert(Node*& root, int val) {
    Node* newNode = new Node(val);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    Node* curr = root;
    while (true) {
        if (val < curr->data) {
            if (curr->left == nullptr) {
                curr->left = newNode;
                newNode->right = curr;
                newNode->isthreaded = true;
                return;
            }
            curr = curr->left;
        }
        else {
            if (!curr->isthreaded || val < curr->right->data) {
                if (curr->right == nullptr || curr->right->isthreaded) {
                    newNode->right = curr->right;
                    curr->right = newNode;
                    curr->isthreaded = false;
                    newNode->isthreaded = true;
                    return;
                }
                curr = curr->right;
            }
            else {
                newNode->right = curr->right;
                curr->right = newNode;
                curr->isthreaded = false;
                newNode->isthreaded = true;
                return;
            }
        }
    }
}

void inorder(Node* root) {
    Node* curr = root;
    while (curr != nullptr) {
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        cout << curr->data << " ";
        if (curr->isthreaded) {
            curr = curr->right;
            if (curr == nullptr)
                break;
        }
        else {
            curr = curr->right;
            if (curr != nullptr)
                cout << curr->data << " ";
        }
    }
}

void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    if (!root->isthreaded) preorder(root->left);
    preorder(root->right);
}

Node* createTBT(TreeNode* root1) {
    if (root1 == nullptr)
        return nullptr;
    Node* root = new Node(root1->data);
    if (root1->left != nullptr) {
        Node* l = createTBT(root1->left);
        l->right = root;
        l->isthreaded = true;
    }
    if (root1->right != nullptr) {
        root->right = createTBT(root1->right);
    }
    return root;
}

int main() {
    Node* root = nullptr;
    TreeNode* root1 = nullptr;
    int choice, val, nodes;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert a new node\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Convert the binary search tree to threaded binary search tree\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the value to be inserted: ";
            cin >> val;
            insert(root, val);
            break;
        case 2:
            cout << "Inorder Traversal: ";
            inorder(root);
            cout << endl;
            break;
        case 3:
            cout << "Enter no. of nodes: ";
            cin >> nodes;
            cout << "Enter nodes for BST: ";
            for (int i = 0; i < nodes; i++) {
                cin >> val;
                insertbst(root1, val);
            }
            root = createTBT(root1);
            cout << "Binary search tree has been converted to threaded binary search tree.\n";
            cout << "Preorder Traversal : ";
            preorder(root);
            break;
        case 4:
            cout << "Exiting...\n";
            exit(0);
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}

