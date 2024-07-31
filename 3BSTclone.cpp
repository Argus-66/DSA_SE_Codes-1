#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

void insertnode(Node* &root, int val)
{
    if (root == nullptr)
    {
        root = new Node(val);
        cout << "node inserted successfully\n";
    }
    else if (val >= root->data)
    {
        insertnode(root->right, val);
    }
    else
    {
        insertnode(root->left, val);
    }
}
void inorder(Node *root){
    if(root==nullptr) return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void preorder(Node *root){
    if(root==nullptr) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root){
    if(root==nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" "; 
}
Node *clone(Node *root)
{
    if (root == nullptr)
        return root;
    Node *newNode = new Node(root->data);
    newNode->left = clone(root->left);
    newNode->right = clone(root->right);
    return newNode;
}
int main()
{
    Node *root = nullptr;
    int choice, val;
    do
    {
        cout << "\nMENU\n";
        cout << "1 insert node\n";
        cout << "3 Inorder traversal\n";
        cout << "4 Preorder traversal\n";
        cout << "5 Postorder traversal\n";
        cout << "6. Clone tree\n";
        cout << "7 exit\n";
        cout << "enter choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "enter value to insert : ";
            cin >> val;
            insertnode(root, val);
            break;
        }
        case 3:
            cout << "Inorder Traversal: ";
            inorder(root);
            cout << endl;
            break;
        case 4:
            cout << "Preorder Traversal: ";
            preorder(root);
            cout << endl;
            break;
        case 5:
            cout << "Postorder Traversal: ";
            postorder(root);
            cout << endl;
            break;
        case 6:
        {
            Node *clonedRoot = clone(root);
            cout << "Cloned tree: ";
            inorder(clonedRoot);
            cout << endl;
            break;
        }
        default:
        {
            cout << "enter valid choice : ";
        }
        }

    } while (choice != 4);
    return 0;
}