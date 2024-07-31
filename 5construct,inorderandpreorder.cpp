/*Create binary tree/binary search tree with n nodes, do following operation 
1. Insert a node         
2. construct a binary tree from inorder and preorder traversal  
3. Check whether two trees are equal.
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

void insertNode(Node *&root, int val)
{
    if (root == nullptr)
    {
        root = new Node(val);
        cout << "Node inserted successfully\n";
    }
    else if (val >= root->data)
        insertNode(root->right, val);
    else
        insertNode(root->left, val);
}

bool identical(Node *root1, Node *root2)
{
    if (root1 == nullptr && root2 == nullptr)
        return true;
    if (root1 == nullptr || root2 == nullptr)
        return false;
    return (root1->data == root2->data && identical(root1->left, root2->left) && identical(root1->right, root2->right));
}

Node *helper(vector<int> &preorder, vector<int> &inorder, unordered_map<int, int> &inorder_map, int instart, int inend, int &preindex)
{
    if (instart > inend)
        return nullptr;
    int rootval = preorder[preindex++];
    Node *root = new Node(rootval);
    int inindex = inorder_map[rootval];
    root->left = helper(preorder, inorder, inorder_map, instart, inindex - 1, preindex);
    root->right = helper(preorder, inorder, inorder_map, inindex + 1, inend, preindex);
    return root;
}

Node *createTree(vector<int> &preorder, vector<int> &inorder)
{
    unordered_map<int, int> inorder_map;
    for (int i = 0; i < inorder.size(); i++)
    {
        inorder_map[inorder[i]] = i;
    }
    int preindex = 0;
    return helper(preorder, inorder, inorder_map, 0, inorder.size() - 1, preindex);
}

void inordertraversal(Node *root)
{
    if (root == nullptr)
        return;
    inordertraversal(root->left);
    cout << root->data << " ";
    inordertraversal(root->right);
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
int main()
{
    Node *root = nullptr;
    Node *root2 = nullptr;
    int choice, val;
    vector<int> pre;
    vector<int> ino;
    do
    {
        cout << "\nMENU\n";
        cout << "1. Insert node\n";
        cout << "2. Construct tree from inorder and preorder traversal\n";
        cout << "3. Check trees equality\n";
        cout << "4. Exit\n";
        cout << "5 Inorder traversal\n";
        cout << "6 Preorder traversal\n";
        cout << "7 Postorder traversal\n";
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter value to insert: ";
            cin >> val;
            insertNode(root, val);
            break;
        }
        case 2:
        {
            cout << "Enter no. of nodes in the tree : ";
            int size;
            cin >> size;
            cout << "Enter inorder traversal: ";
            for (int i = 0; i < size; i++)
            {
                int num;
                cin >> num;
                ino.push_back(num);
            }
            cout << "Enter preorder traversal: ";
            for (int i = 0; i < size; i++)
            {
                int num;
                cin >> num;
                pre.push_back(num);
            }
            root2 = createTree(pre, ino);
            cout << "Tree constructed successfully.\n";
            cout << "Inorder traversal of constructed tree : ";
            inordertraversal(root2);
            break;
        }
        case 3:
        {
            if (identical(root, root2))
                cout << "Trees are identical.\n";
            else
                cout << "Trees are not identical.\n";
            break;
        }
        case 4:
        {
            cout << "Exiting...";
            break;
        }
        case 5:
            cout << "Inorder Traversal: ";
            inordertraversal(root);
            cout << endl;
            break;
        case 6:
            cout << "Preorder Traversal: ";
            preorder(root);
            cout << endl;
            break;
        case 7:
            cout << "Postorder Traversal: ";
            postorder(root);
            cout << endl;
            break;
        default:
        {
            cout << "Enter valid choice." << endl;
            break;
        }
        }
    } while (choice != 4);
    return 0;
}