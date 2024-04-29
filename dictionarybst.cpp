#include <iostream>
using namespace std;
#define MAX 100

class Treenode
{
    string word;
    string meaning;
    Treenode *left;
    Treenode *right;
    friend class BST;

    Treenode()
    {
        left = NULL;
        right = NULL;
    }
};

class BST
{
    Treenode *root;

public:
    BST()
    {
        root = NULL;
    }

    void create();
    void inorder_r();
    void inorder_r(Treenode *);
    void search();
    void BFT();
    void copy();
    Treenode *copy(Treenode *);
    void mirror_r();
    void *mirror_r(Treenode *);
    void mirror_nr();
    void deleteNode();
};

class Queue
{
    Treenode *arr[MAX];
    int front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    void enqueue(Treenode *temp)
    {
        if (front == -1)
            front++;

        rear++;
        arr[rear] = temp;
    }

    Treenode *dequeue()
    {
        Treenode *temp = arr[front];
        front++;
        return temp;
    }

    bool isEmpty()
    {
        if (front == -1 || front > rear)
            return true;
        else
            return false;
    }
};

void BST::inorder_r()
{
    cout << "INORDER" << endl;
    inorder_r(root);
}

void BST::inorder_r(Treenode *temp)
{
    if (temp)
    {
        inorder_r(temp->left);
        cout << "\tWord: " << temp->word << "\tMeaning: " << temp->meaning << endl;
        inorder_r(temp->right);
    }
}

void BST::create()
{
    if (!root)
    {
        root = new Treenode();
        cout << "Enter the word for root node: ";
        cin >> root->word;
        cout << "Enter the meaning of the word: ";
        cin >> root->meaning;
    }

    char choice = 'y';
    do
    {
        Treenode *temp = root;
        Treenode *curr = new Treenode();
        cout << "Enter the word for the new node: ";
        cin >> curr->word;
        cout << "Enter the meaning of the word: ";
        cin >> curr->meaning;

        while (1)
        {
            if (curr->word < temp->word)
            {
                if (temp->left == NULL)
                {
                    temp->left = curr;
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                if (curr->word > temp->word)
                {
                    if (temp->right == NULL)
                    {
                        temp->right = curr;
                        break;
                    }
                    else
                    {
                        temp = temp->right;
                    }
                }
            }
        }

        cout << "Do you want to add more nodes? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    inorder_r();
}

void BST::search()
{
    Treenode *temp = root;
    if (temp)
    {
        string key;
        cout << "Enter the word to search: ";
        cin >> key;
        while (temp)
        {
            if (temp->word == key)
            {
                cout << "Word has been found! Meaning: " << temp->meaning << endl;
                break;
            }
            else if (key < temp->word)
                temp = temp->left;

            else
                temp = temp->right;
        }

        if (!temp)
        {
            cout << "Word could not be found" << endl;
        }
    }
    else
        cout << "Tree is empty!";
}

void BST::BFT()
{
    Queue q;
    Treenode *temp = root;
    if (!root)
        cout << "BST is empty!" << endl;
    else
    {
        q.enqueue(temp);
        while (!q.isEmpty())
        {
            temp = q.dequeue();
            cout << "\tWord: " << temp->word << "\tMeaning: " << temp->meaning << endl;

            if (temp->left != NULL)
            {
                q.enqueue(temp->left);
            }
            if (temp->right != NULL)
            {
                q.enqueue(temp->right);
            }
        }
    }
}

void BST::copy()
{
    BST copyTree;
    copyTree.root = copy(root);
    cout << "COPY" << endl;
    copyTree.inorder_r();
}

Treenode *BST::copy(Treenode *temp)
{
    Treenode *copynode = NULL;
    if (temp)
    {
        copynode = new Treenode;
        copynode->word = temp->word;
        copynode->meaning = temp->meaning;
        copynode->left = copy(temp->left);
        copynode->right = copy(temp->right);
    }

    return copynode;
}

void BST::mirror_r()
{
    cout << "MIRROR" << endl;
    if (root)
    {
        mirror_r(root);
        inorder_r();
    }
}

void *BST::mirror_r(Treenode *temp)
{
    if (!temp)
        return NULL;

    Treenode *t = temp->left;
    temp->left = temp->right;
    temp->right = t;

    mirror_r(temp->left);
    mirror_r(temp->right);
}

void BST::mirror_nr()
{
    if (!root)
    {
        cout << "BST is empty!" << endl;
        return;
    }

    Queue q;
    q.enqueue(root);

    while (!q.isEmpty())
    {
        Treenode *curr = q.dequeue();

        // swap children

        Treenode *temp = curr->left;
        curr->left = curr->right;
        curr->right = temp;

        if (!curr->left)
            q.enqueue(curr->left);

        if (!curr->right)
            q.enqueue(curr->right);
    }

    inorder_r();
}

void BST::deleteNode()
{
    if (!root)
    { // If BST is empty
        cout << "BST is empty!" << endl;
        return;
    }

    string word; // Word to search for
    cout << "Enter the word to delete: ";
    cin >> word;

    Treenode *temp = root;   // To search for the entered word in BST
    Treenode *parent = NULL; // Parent of the node for word found in BST
    Treenode *curr = NULL;

    while (temp && temp->word != word)
    {
        parent = temp; // This will stop at the position of parent of the node for word found in BST
        if (word < temp->word)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (temp == root) // Word is found at root
    {
        if (temp->left == NULL) // If node has no left child set root to right child
        {
            root = temp->right;
        }
        else if (temp->right == NULL) // If node has no right child set root to left child
        {
            root = temp->left;
        }
        else // Node has both children
        {
            Treenode *s = temp->right; // Pointer for inorder successor
            root = temp->right;        // Set root to right child of node

            while (s->left) // Finding the inorder successor
                s = s->left;

            s->left = temp->left; // Set left of inorder successor to left of root node
        }
    }
    else
    {
        if (!temp->left && !temp->right) // Word is found at leaf node
        {
            if (parent->left == temp)
                parent->left == NULL;
            else
                parent->right == NULL;
        }
        else if (!temp->left) // Word doesn't have a left child
        {
            if (parent->left == temp)
            {
                parent->left = temp->right;
            }
            else
            {
                parent->right = temp->right;
            }
        }
        else if (!temp->right) // Word doesn't have a right child
        {
            if (parent->left == temp)
            {
                parent->left = temp->left;
            }
            else
            {
                parent->right = temp->left;
            }
        }
        else {
            Treenode *s = temp->right;
            
            while(!s->left) {
                s = s->left;
            }
            
            s->left = temp->left;
            if (parent->left == temp)
                parent->left = temp->right;
            else 
                parent->right = temp->right;
        }
    }

    BFT();
}

int main()
{

    BST bst;
    bst.create();
    // bst.inorder_r();
    // bst.search();
    // bst.BFT();
    // bst.copy();
    // bst.mirror_r();
    // bst.inorder_r();
    bst.deleteNode();

    return 0;
}