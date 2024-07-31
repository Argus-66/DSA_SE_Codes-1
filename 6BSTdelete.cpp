/*Create binary tree/binary search tree with n nodes, do following operation 
1. Insert a node         2. Delete a node from BST 
3. All traversals (recursive and iterative)
*/

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

void insertnode(Node *&root, int val)
{
    if (root == nullptr)
    {
        root = new Node(val);
        cout << "node inserted successfully\n";
    }
    else if (val >= root->data) insertnode(root->right, val);
    else insertnode(root->left, val);
}

void deletenode(Node* &root, int val){
    if(root == nullptr) return;
    if(val < root->data) deletenode(root->left, val);
    else if(val > root->data) deletenode(root->right, val);
    else{
        if(root->left == nullptr){
            Node *temp = root->right;
            delete root;
            root = temp;
        }
        else if(root->right == nullptr){
            Node *temp = root->left;
            delete root;
            root = temp;
        }
        else{
            Node *temp = root->right;
            while(temp->left != nullptr) temp = temp->left;
            root->data = temp->data;
            deletenode(root->right, temp->data);
        }
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

void preorderiter(Node *root){
    if(root==nullptr) return;
    Node* temp = root;
    stack<Node*> st;
    st.push(temp);
    while(!st.empty()){
        temp = st.top();
        st.pop();
        cout<<temp->data<<" ";
        if(temp->right!=nullptr) st.push(temp->right);
        if(temp->left!=nullptr) st.push(temp->left);
    }
}

void inorderiter(Node *root){
    if(root==nullptr) return;
    Node* temp = root;
    stack<Node *> st;
    while(temp!=nullptr || !st.empty()){
        while(temp!=nullptr){
            st.push(temp);
            temp = temp->left;
        }
        temp = st.top();
        st.pop();
        cout<<temp->data<<" ";
        temp = temp->right;
    }
}

void postorderiter(Node *root){
    if(root==nullptr) return;
    Node * temp = root;
    stack<Node *> st1;
    stack<Node *> st2;
    st1.push(temp);
    while(!st1.empty()){
        temp = st1.top();
        st1.pop();
        st2.push(temp);
        if(temp->left!=nullptr) st1.push(temp->left);
        if(temp->right!=nullptr) st1.push(temp->right);
    }
    while(!st2.empty()){
        temp = st2.top();
        cout<<temp->data<<" ";
        st2.pop();
    }
}

int main()
{
    Node *root = nullptr;
    int choice, val;
    do
    {
        cout << "\nMENU\n";
        cout << "1 Insert node\n";
        cout << "2 Delete node\n";
        cout << "3 Inorder traversal\n";
        cout << "4 Preorder traversal\n";
        cout << "5 Postorder traversal\n";
        cout << "6 Preorder traversal (iterative)\n";
        cout << "7 Inorder traversal (iterative)\n";
        cout << "8 Postorder traversal (iterative)\n";
        cout << "9 Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter value to insert : ";
            cin >> val;
            insertnode(root, val);
            break;
        }
        case 2:
            cout << "Enter value to delete: ";
            cin >> val;
            deletenode(root, val);
            cout << "Node deleted successfully\n";
            break;
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
            cout << "Preorder Traversal: ";
            preorderiter(root);
            cout << endl;
            break;
        case 7:
            cout << "Inorder Traversal: ";
            inorderiter(root);
            cout << endl;
            break;
        case 8:
            cout << "Postorder Traversal: ";
            postorderiter(root);
            cout << endl;
            break;
        case 9:
            cout<<"Exiting------"<<endl;
            break;
        default:
        {
            cout << "enter valid choice : ";
        }
        }
    } while (choice != 9);
    return 0;
}
