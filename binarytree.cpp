#include <iostream>
using namespace std;

#define MAX 100

class Treenode
{
    public:
    int data;
    Treenode *left;
    Treenode *right;
    friend class Tree;
    Treenode()
    {
        left = NULL;
        right = NULL;
    }
};  

class Stack {
    public:
    int top;
    Treenode *data[MAX];

    Stack() {
        top = -1;
    }

    void push(Treenode *temp) {
        if (top >= MAX - 1) {
            cout << "Stack overflow!";
            return;
        }
        top++;
        data[top] = temp;
    }

    Treenode *pop(){
        if (top == -1) {
            cout << "Stack underflow!";
            return NULL;
        }
        Treenode *temp = data[top];
        top--;
        return temp;
    }

    int isEmpty(){
        if (top == -1)
            return 1;
        else    
            return 0;
    }

    friend class Tree;
};

class Tree
{
    Treenode *root;
    Stack stack;

public:
    //non recursive
    void create_nr();
    
    void inorder_nr();
    void preorder_nr();
    void postorder_nr();

    //recursive
    void inorder_r();
    void inorder_r(Treenode *);
    void preorder_r();
    void preorder_r(Treenode *);
    void postorder_r();
    void postorder_r(Treenode *);

    Tree()
    {
        root = NULL;
    }
};

void Tree::create_nr()
{
    if (!root)
    {
        root = new Treenode(); //Don't forget to allocate memory to root if root is NULL
        cout << "Enter value of root: ";
        cin >> root->data;
    }

    char choice; //Choice to a. add more nodes and b. Add node to left or right 

    do //(outer while)
    {
        Treenode *curr = new Treenode(); //New node to be added
        Treenode *temp = root; //Traversal node
        int flag = 0; //Stop inner while loop after new node is added
        cout << "Enter the data for the new node: ";
        cin >> curr->data;

        while (!flag) // While new node has not been added (inner while)
        {
            cout << "Is new node to the left or right of " << temp->data << "? (l/r): ";
            cin >> choice;

            if (choice == 'l') 
            {
                if (temp->left == NULL) //If there isn't already a node present in current position
                {
                    temp->left = curr;
                    flag = 1; // Break out of inner while loop
                }

                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL) //If there isn't already a node present in current position
                {
                    temp->right = curr;
                    flag = 1; // Break out of inner while loop
                }

                temp = temp->right;
            }
        }

        cout << "Do you want to continue? (y/n): ";
        cin >> choice;
    } while (choice == 'y');
}

void Tree::inorder_r() {
    cout << "INORDER" << endl;
    inorder_r(root);
}

void Tree::inorder_r(Treenode *temp) {
    if (temp) {
        inorder_r(temp->left);
        cout << "\t" << temp->data << endl;
        inorder_r(temp->right);
    }
}

void Tree::preorder_r() {
    cout << "PREORDER" << endl;
    preorder_r(root);
}

void Tree::preorder_r(Treenode *temp) {
    if (temp) {
        cout << "\t" << temp->data << endl;
        inorder_r(temp->left);
        inorder_r(temp->right);
    }
}

void Tree::postorder_r() {
    cout << "POSTORDER" << endl;
    postorder_r(root);
}

void Tree::postorder_r(Treenode *temp) {
    if (temp) {
        inorder_r(temp->left);
        inorder_r(temp->right);
        cout << "\t" << temp->data << endl;
    }
}

void Tree::inorder_nr() {
    cout << "INORDER NR" << endl;
    Treenode *temp = root; // assign root to temp
    while(1){ // while tree is not empty
        while (temp) { // while there exists a node in current position of tree
            stack.push(temp); // push the node into the stack
            temp = temp->left; // visit left of current position
        }

        if (stack.isEmpty()) { // tree has been fully traversed
            break;
        }
        // traversal is not over yet
        temp = stack.pop(); //pop the next node from stack into temp
        cout << "\t" << temp->data << endl; // display the popped node

        temp = temp->right; // visit right of current position
    }
}

void Tree::preorder_nr() {
    cout << "PREORDER NR" << endl;
    Treenode *temp = root; // assign root to temp
    while(1){ // while tree is not empty
        while (temp) { // while there exists a node in current position of tree
            cout << "\t" << temp->data << endl; // display the popped node
            stack.push(temp); // push the node into the stack
            temp = temp->left; // visit left of current position
        }

        if (stack.isEmpty()) { // tree has been fully traversed
            break;
        }
        // traversal is not over yet
        temp = stack.pop(); //pop the next node from stack into temp
        temp = temp->right; // visit right of current position
    }
}

void Tree::postorder_nr() {
    cout << "POSTORDER NR" << endl;
    Treenode *temp = root;

    while(1) { // while tree is not empty
        while(temp) { // while there exists a node in current position of tree
            stack.push(temp); // push the node into the stack
            temp = temp->left; // visit left of current position
        }

        if (stack.data[stack.top]->right == NULL) { // if there is no node to the right of parent
            temp = stack.pop(); // pop the next node from stack into temp (which is basically the parent)
            cout << "\t" << temp->data << endl; // display the popped node
        }       

        while(stack.isEmpty() == 0 && stack.data[stack.top]->right == temp) { // if current position is the right node which is yet to be visited
            temp = stack.pop(); // pop the next node from stack into temp
            cout << "\t" << temp->data << endl; // display the poppped node
        }

        if(stack.isEmpty()) { // tree has been fully traversed
            break;
        }

        temp = stack.data[stack.top]->right; // left of tree has been visited and there is a sibling node to the right. So set temp to the sibling node on the right
    }
}

int main() {

    Tree tree;

    tree.create_nr();
    cout << "RECURSIVE" << endl;
    tree.inorder_r();
    tree.preorder_r();
    tree.postorder_r();

    cout << "NON RECURSIVE" << endl;
    tree.inorder_nr();
    tree.preorder_nr();
    tree.postorder_nr();

    return 0;
}