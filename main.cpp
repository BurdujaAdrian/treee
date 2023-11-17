#include <iostream>
#include <climits>
#include <string>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* root, int value)
{
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

void printTree(Node* root, int spaces = 0)
{
    if (root != nullptr) {
        printTree(root->right, spaces + 4);
        cout << string(spaces, ' ') << root->data << endl;
        printTree(root->left, spaces + 4);
    }
}

Node* findMinValueNode(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        Node* temp = findMinValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

Node* lowestCommonAncestor(Node* root, int p, int q) {
    if (root == nullptr || root->data == p || root->data == q) {
        return root;
    }

    Node* leftLCA = lowestCommonAncestor(root->left, p, q);
    Node* rightLCA = lowestCommonAncestor(root->right, p, q);

    if (leftLCA != nullptr && rightLCA != nullptr) {
        return root;
    }

    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}

int height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return max(height(node->left), height(node->right)) + 1;
}

bool isBalanced(Node* root) {
    if (root == nullptr) {
        return true;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

int countLeafNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    // If the node is a leaf (both left and right children are null), return 1
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }

    // Recursively count leaf nodes in the left and right subtrees
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int main()
{Node* root = nullptr;string choice;

do
{
    int value;
    cout << "Enter a value to insert: ";
    cin >> value;
    if(value )
    root = insert(root, value);

    cout << "Binary Tree:" << endl;
    printTree(root);

    cout << "Do you want to insert another value? (y/n): ";
    cin >> choice;

} while (choice == "y" || choice == "Y");

int valueToDelete;
cout << "\nEnter a value to delete: ";
cin >> valueToDelete;

root = deleteNode(root, valueToDelete);

cout << "Binary Tree after deletion:" << endl;
printTree(root);

int p, q;
cout << "\nEnter values of two nodes to find their lowest common ancestor: ";
cin >> p >> q;

Node* lca = lowestCommonAncestor(root, p, q);

if (lca != nullptr)
    cout<< "Lowest Common Ancestor of " << p << " and " << q<< " is: " << lca->data << endl;
else
    cout << "Nodes not found in the tree." << endl;

cout<<"Do you want to see the number of leaf nodes? (y/n)";
cin>>choice;
if(choice == "y" || choice == "Y")
{int n = countLeafNodes(root);
cout<<"There are "<<n<<" leaf nodes";
}

cout<<"Do you want to see if the tree is balanced? (y/n)";
cin>>choice;
if(choice == "y" || choice == "Y")
{ if(isBalanced(root))cout<<"The tree is balanced.";
else cout<<"The tree is not balanced.";
}
    return 0;
}
