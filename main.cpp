#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Transaction class for data structure
class Transaction
{
public:
    int id;
    string description;
    double amount;
    string category;

    Transaction(int id, const string &desc, double amt, const string &cat)
        : id(id), description(desc), amount(amt), category(cat) {}

    void display() const
    {
        cout << "ID: " << id << " | " << description << " | $"
             << fixed << setprecision(2) << amount << " | " << category << endl;
    }
};

// BST Node for Binary Search Tree implementation
class BSTNode
{
public:
    Transaction *transaction;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Transaction *t) : transaction(t), left(NULL), right(NULL) {}
};

// Personal Budget Tracker System
class BudgetTracker
{
private:
    vector<Transaction *> transactions; // Array/Vector data structure
    BSTNode *root;                      // BST root
    int nextId;                         // Auto-increment ID
public:
    BudgetTracker() : root(NULL), nextId(1) {}
};

int main()
{
    BudgetTracker tracker;
    int choice;
    while (true)
    {
        cout << "\n=== Personal Budget Tracker ===" << endl;
        cout << "1. Add Transaction" << endl;
        cout << "2. Search by Category (BST)" << endl;
        cout << "3. Display by Amount (BST)" << endl;
        cout << "4. Display Sorted by Amount (Merge Sort)" << endl;
        cout << "5. Display All Transactions" << endl;
        cout << "6. Show Budget Summary" << endl;
        cout << "7. Exit" << endl;
        cout << "Choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input!" << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Add Transaction
            break;
        }

        case 2:
        {
            // Search by Category
            break;
        }

        case 3:
            // Display by Amount
            break;

        case 4:
            // Display Sorted by Amount
            break;

        case 5:
            // Display All Transactions
            break;

        case 6:
            // Show Budget Summary
            break;

        case 7:
            cout << "Thank you!" << endl;
            return 0;

        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
