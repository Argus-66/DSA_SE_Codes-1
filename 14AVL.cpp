#include <iostream>
#include <algorithm>
using namespace std;

struct Entry {
    string keyword;
    string meaning;
    Entry* left;
    Entry* right;
    int height;
    Entry(string k, string m) : keyword(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVLDictionary {
private:
    Entry* root;

    int getHeight(Entry* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(Entry* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Entry* rotateRight(Entry* y) {
        Entry* x = y->left;
        Entry* T = x->right;

        x->right = y;
        y->left = T;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Entry* rotateLeft(Entry* x) {
        Entry* y = x->right;
        Entry* T = y->left;

        y->left = x;
        x->right = T;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Entry* insertEntry(Entry* node, string keyword, string meaning) {
        if (node == nullptr) {
            return new Entry(keyword, meaning);
        }

        if (keyword < node->keyword) {
            node->left = insertEntry(node->left, keyword, meaning);
        } else if (keyword > node->keyword) {
            node->right = insertEntry(node->right, keyword, meaning);
        } else { // Update meaning if keyword already exists
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Left Left case
        if (balance > 1 && keyword < node->left->keyword) {
            return rotateRight(node);
        }

        // Left Right case
        if (balance > 1 && keyword > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right case
        if (balance < -1 && keyword > node->right->keyword) {
            return rotateLeft(node);
        }

        // Right Left case
        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Entry* minValueNode(Entry* node) {
        Entry* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Entry* deleteEntry(Entry* root, string keyword) {
        if (root == nullptr) {
            return root;
        }

        if (keyword < root->keyword) {
            root->left = deleteEntry(root->left, keyword);
        } else if (keyword > root->keyword) {
            root->right = deleteEntry(root->right, keyword);
        } else {
            if (root->left == nullptr || root->right == nullptr) {
                Entry* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Entry* temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->right = deleteEntry(root->right, temp->keyword);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        // Left Left case
        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
            return rotateRight(root);
        }

        // Left Right case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right case
        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
            return rotateLeft(root);
        }

        // Right Left case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorderTraversal(Entry* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        cout << node->keyword << ": " << node->meaning << endl;
        inorderTraversal(node->right);
    }

    void reverseInorderTraversal(Entry* node) {
        if (node == nullptr) {
            return;
        }
        reverseInorderTraversal(node->right);
        cout << node->keyword << ": " << node->meaning << endl;
        reverseInorderTraversal(node->left);
    }

    int searchComparisons(Entry* node, string keyword, int comparisons) {
        if (node == nullptr) {
            return comparisons;
        }

        if (node->keyword == keyword) {
            return comparisons + 1;
        } else if (keyword < node->keyword) {
            return searchComparisons(node->left, keyword, comparisons + 1);
        } else {
            return searchComparisons(node->right, keyword, comparisons + 1);
        }
    }

public:
    AVLDictionary() : root(nullptr) {}

    void addEntry(string keyword, string meaning) {
        root = insertEntry(root, keyword, meaning);
    }

    void deleteEntry(string keyword) {
        root = deleteEntry(root, keyword);
    }

    void updateEntry(string keyword, string newMeaning) {
        root = deleteEntry(root, keyword);
        root = insertEntry(root, keyword, newMeaning);
    }

    void displayAscending() {
        cout << "Dictionary entries in ascending order:" << endl;
        inorderTraversal(root);
    }

    void displayDescending() {
        cout << "Dictionary entries in descending order:" << endl;
        reverseInorderTraversal(root);
    }

    int maxComparisons(string keyword) {
        return searchComparisons(root, keyword, 0);
    }
};

int main() {
    AVLDictionary dictionary;

    dictionary.addEntry("apple", "A fruit");
    dictionary.addEntry("banana", "A fruit");
    dictionary.addEntry("carrot", "A vegetable");
    dictionary.addEntry("dog", "A mammal");

    dictionary.displayAscending();
    cout << endl;

    dictionary.deleteEntry("banana");

    dictionary.updateEntry("apple", "A delicious fruit");

    dictionary.displayDescending();
    cout << endl;

    cout << "Maximum comparisons for 'carrot': " << dictionary.maxComparisons("carrot") << endl;

    return 0;
}