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

    // BST Operations with Recursion
    void addTransaction(const string &desc, double amt, const string &cat)
    {
        Transaction *t = new Transaction(nextId++, desc, amt, cat);
        transactions.push_back(t);
        root = insertRecursive(root, t);
        cout << "Transaction added with ID: " << t->id << endl;
    }

    BSTNode *insertRecursive(BSTNode *node, Transaction *t)
    {
        if (node == NULL)
        {
            return new BSTNode(t);
        }

        if (t->amount < node->transaction->amount)
        {
            node->left = insertRecursive(node->left, t);
        }
        else
        {
            node->right = insertRecursive(node->right, t);
        }

        return node;
    }

    // TODO: Loveless
    // Binary Search by category
    
        void searchByCategory(const string &category)
    {
        cout << "\n=== Searching for Category: " << category << " ===" << endl;

        bool found = false;
        searchCategoryInorder(root, category, found);

        if (!found)
        {
            cout << "No transactions found in category \"" << category << "\"." << endl;
        }
    }

    void searchCategoryInorder(BSTNode *node, const string &category, bool &found)
    {
        if (node != NULL)
        {
            searchCategoryInorder(node->left, category, found);

            if (node->transaction->category == category)
            {
                node->transaction->display();
                found = true;
            }

            searchCategoryInorder(node->right, category, found);
        }
    }


    // TODO: Roshan
    // Merge Sort by Amount (Recursive)
    void displaySortedByAmount()
    {
    }

    // Display using BST traversal (Recursion)
    void displayByAmount()
    {
        cout << "\n=== All Transactions by Amount (BST Traversal) ===" << endl;
        if (root == NULL)
        {
            cout << "No transactions found!" << endl;
            return;
        }
        inorderTraversal(root);
    }

    void inorderTraversal(BSTNode *node)
    {
        if (node != NULL)
        {
            inorderTraversal(node->left);
            node->transaction->display();
            inorderTraversal(node->right);
        }
    }

    void showBudgetSummary()
{
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    for (size_t i = 0; i < transactions.size(); ++i)
    {
        double amt = transactions[i]->amount;
        if (amt >= 0)
            totalIncome += amt;
        else
            totalExpense += amt;
    }

    double net = totalIncome + totalExpense;

    cout << "\n=== Budget Summary ===" << endl;
    cout << "Total Income  : $" <<  totalIncome << endl;
    cout << "Total Expense : $" <<  fabs(totalExpense) << endl;
    cout << "Net Balance   : $" << net << endl;
}

    void displayAll()
{
    cout << "\n=== All Transactions ===" << endl;
    if (transactions.empty())
    {
        cout << "No transactions recorded." << endl;
        return;
    }

    for (size_t i = 0; i < transactions.size(); ++i)
    {
        transactions[i]->display();
    }
}

    // Destructor
    ~BudgetTracker()
    {
        for (size_t i = 0; i < transactions.size(); i++)
        {
            delete transactions[i];
        }
        deleteBST(root);
    }

    void deleteBST(BSTNode *node)
    {
        if (node != NULL)
        {
            deleteBST(node->left);
            deleteBST(node->right);
            delete node;
        }
    }
};

void clearInput()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

int main()
{
    BudgetTracker tracker;

    // Add sample data
    cout << "=== Loading Sample Data ===" << endl;
    tracker.addTransaction("Salary", 3000.00, "Income");
    tracker.addTransaction("Groceries", -150.50, "Food");
    tracker.addTransaction("Gas", -45.00, "Transport");
    tracker.addTransaction("Freelance", 500.00, "Income");
    tracker.addTransaction("Rent", -1200.00, "Housing");
    
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
            string desc, category;
            double amount;

            cout << "Description: ";
            clearInput();
            getline(cin, desc);

            cout << "Amount (+ for income, - for expense): ";
            if (!(cin >> amount))
            {
                cout << "Invalid amount!" << endl;
                clearInput();
                break;
            }

            cout << "Category: ";
            clearInput();
            getline(cin, category);

            tracker.addTransaction(desc, amount, category);
            break;
        }

        case 2:
        {
            string category;
            cout << "Enter category: ";
            clearInput();
            getline(cin, category);
            tracker.searchByCategory(category);
            break;
        }

        case 3:
            tracker.displayByAmount();
            break;

        case 4:
            tracker.displaySortedByAmount();
            break;

        case 5:
            tracker.displayAll();
            break;

        case 6:
            tracker.showBudgetSummary();
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