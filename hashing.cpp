#include <iostream>
#include <string>
#include <fstream>

#define MAX 20

using namespace std;

class Student
{
    int rollNo;
    string name;
    string grade;
    friend class Hash;

public:
    Student()
    {
        rollNo = -1;
        name = "None";
        grade = "None";
    }
};

class Hash
{
    Student table[MAX];

public:
    void linearProbe_wo();
    void linearProbe_w();
    void display();
    void writeToFile(string);
    void readFromFile(string);
};

void Hash::linearProbe_wo()
{
    bool flag, choice;
    do
    {
        int rollNo;
        string name;
        char grade;

        cout << "Enter roll number of student: ";
        cin >> rollNo;
        cout << "Enter name of student: ";
        cin >> name;
        cout << "Enter grade of student: ";
        cin >> grade;

        int loc = rollNo % MAX;

        if (table[loc].rollNo == -1)
        {
            table[loc].rollNo = rollNo;
            table[loc].name = name;
            table[loc].grade = grade;
            flag = true;
        }
        else
        {
            int i = (loc + 1) % MAX;
            while (i != loc)
            {
                if (table[i].rollNo == -1)
                {
                    table[i].rollNo = rollNo;
                    table[i].name = name;
                    table[i].grade = grade;
                    flag = true;
                    break;
                }
                i = (i + 1) % MAX;
            }
        }

        if (!flag)
        {
            cout << "Hash table is full!" << endl;
            return;
        }
        cout << "Do you want to add more students? (1/0): ";
        cin >> choice;

    } while (choice);

    display();
}

void Hash::display()
{
    cout << endl
         << "\tRoll\tName\tGrade" << endl;
    for (int i = 0; i < MAX; i++)
    {
        cout << "\t" << table[i].rollNo << "\t" << table[i].name << "\t" << table[i].grade << endl;
    }
}

void Hash::writeToFile(string filename)
{
    ofstream outFile(filename);

    if (!outFile)
    {
        cerr << "Unable to open file!" << endl;
        return;
    }

    for (int i = 0; i < MAX; i++)
    {
        if (table[i].rollNo != -1)
        {
            outFile << "\t" << table[i].rollNo << "\t" << table[i].name << "\t" << table[i].grade << endl;
        }
    }
}

void Hash::readFromFile(string filename)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error in opening file!" << endl;
        return;
    }

    for (int i = 0; i < MAX; i++)
    {
        inFile >> table[i].rollNo >> table[i].name >> table[i].grade;
    }
}

int main()
{

    Hash hash;

    hash.readFromFile("students.txt");
    hash.display();

    return 0;
}