#include <iostream>
using namespace std;

class tbtnode
{
    int data;
    int rbit, lbit;
    tbtnode *rightc;
    tbtnode *leftc;
    friend class tbt;

public:
    tbtnode()
    {
        lbit = 0;
        rbit = 0;
    }
};

class tbt
{
    tbtnode *head;

public:
    void create();
    void preorder();
    void inorder();
    tbtnode *insuccr(tbtnode *temp);
    tbt();
};

tbt::tbt()
{
    head = new tbtnode;
    head->rbit = 1;
    head->leftc = head;
    head->rightc = head;
}

void tbt::create()
{
    tbtnode *root;
    char ch;
    root = new tbtnode;
    cout << "Enter data for root" << endl;
    cin >> root->data;
    root->leftc = head;
    root->rightc = head;
    head->leftc = root;
    head->lbit = 1;
    head->rightc = head;

    do
    {
        int flag = 0;
        tbtnode *curr, *temp;
        temp = root;
        curr = new tbtnode;
        cout << "Enter data: " << endl;
        cin >> curr->data;
        curr->rightc = temp;
        curr->leftc = head;

        while (flag == 0)
        {
            char choice;
            cout << "Enter data to l or r of " << temp->data << endl;
            cin >> choice;
            if (choice == 'l')
            {
                if (temp->lbit == 0)
                {
                    curr->rightc = temp;
                    curr->leftc = temp->leftc;
                    temp->leftc = curr;
                    temp->lbit = 1;
                    flag = 1;
                }
                else
                    temp = temp->leftc;
            }
            else if (choice == 'r')
            {
                if (temp->rbit == 0)
                {
                    curr->leftc = temp;
                    curr->rightc = temp->rightc;
                    temp->rightc = curr;
                    temp->rbit = 1;
                    flag = 1;
                }
                else
                    temp = temp->rightc;
            }
        }
        cout << "Do you want to add new node? (y or n)" << endl;
        cin >> ch;
    } while (ch == 'y');
}

void tbt::inorder()
{
    tbtnode *temp = head;
    while (1)
    {
        temp = insuccr(temp);
        if (temp == head)
        {
            break;
        }
        cout << temp->data << " " << endl;
    }
}

tbtnode *tbt::insuccr(tbtnode *temp)
{
    tbtnode *x;
    x = temp->rightc;
    if (temp->rbit == 1)
    {
        while (x->lbit == 1)
        {
            x = x->leftc;
        }
    }

    return x;
}

void tbt::preorder()
{
    tbtnode *temp = head->leftc;
    while (temp != head)
    {
        cout << temp->data << " " << endl;
        while (temp->lbit != 0)
        {
            temp = temp->leftc;
            cout << temp->data << " " << endl;
        }
        while (temp->rbit == 0)
        {
            temp = temp->rightc;
        }
        temp = temp->rightc;
    }
}

int main()
{
    tbt tree;
    int choice;
    do
    {
        cout << "1. Create Threaded Binary Tree" << endl;
        cout << "2. Display Preorder" << endl;
        cout << "3. Display Inorder" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            tree.create();
            break;
        case 2:
            tree.preorder();
            break;
        case 3:
            tree.inorder();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        }
    } while (choice != 4);
}