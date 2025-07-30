#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

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
        cout << left << setw(5) << id
             << left << setw(20) << description.substr(0, 18)
             << right << setw(12) << fixed << setprecision(2) << amount
             << "   " << left << setw(15) << category.substr(0, 13)
             << endl;
    }
};

class BSTNode
{
public:
    Transaction *transaction;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Transaction *t) : transaction(t), left(NULL), right(NULL) {}
};

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

    // Merge Sort by Amount (Recursive)
      void merge(vector<Transaction *> &arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Transaction *> L(n1);
        vector<Transaction *> R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (L[i]->amount <= R[j]->amount)
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    void mergeSort(vector<Transaction *> &arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    void displaySortedByAmount()
    {
        if (transactions.empty())
        {
            cout << "No transactions." << endl;
            return;
        }
        cout << "\n=== Display Sorted by Amount Only Income(Merge Sort) ===" << endl;
        vector<Transaction *> temp;
        for (Transaction *t : transactions)
        {
            if (t->amount >= 0)
            {
                temp.push_back(t);
            }
        }

        if (temp.empty())
        {
            return;
        }
        mergeSort(temp, 0, temp.size() - 1);

        // Display sorted amounts
        for (size_t i = 0; i < temp.size(); i++)
        {
            Transaction *t = temp[i];
            cout << "ID: " << t->id << " | " << t->description << " | $"
                 << fixed << setprecision(2) << t->amount << " | " << t->category << endl;
        }
        cout << "\n=== Display Sorted by Amount Only Expense (Merge Sort) ===" << endl;
        vector<Transaction *> temp1;
        for (Transaction *t : transactions)
        {
            if (t->amount < 0)
            {
                temp1.push_back(t);
            }
        }

        if (temp1.empty())
        {
            return;
        }
        mergeSort(temp1, 0, temp1.size() - 1);

        // Display sorted amounts
        for (size_t i = 0; i < temp1.size(); i++)
        {
            Transaction *t = temp1[i];
            cout << "ID: " << t->id << " | " << t->description << " | $"
                 << fixed << setprecision(2) << fabs(t->amount) << " | " << t->category << endl;
        }
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

        for (int i = 0; i < transactions.size(); ++i)
        {
            double amt = transactions[i]->amount;
            if (amt >= 0)
                totalIncome += amt;
            else
                totalExpense += amt;
        }

        double net = totalIncome + totalExpense;

        // Minimal color scheme
        string green = "\033[32m";
        string red = "\033[31m";
        string gray = "\033[90m";
        string reset = "\033[0m";

        string status = (net >= 0) ? "Within Budget" : "Over Budget";
        string statusColor = (net >= 0) ? green : red;

        cout << "\n";
        cout << gray << "  BUDGET SUMMARY" << reset << "\n\n";

        cout << "  Income      " << "$" << fixed << setprecision(2) << totalIncome << "\n";
        cout << "  Expenses    " << "$" << fixed << setprecision(2) << fabs(totalExpense) << "\n";
        cout << gray << "  ────────────────────────" << reset << "\n";

        cout << "  Balance     " << "$" << fixed << setprecision(2) << net << reset << "\n";
        cout << "  Status      " << statusColor << status << reset << "\n\n";
    }

    void displayAll()
    {
        if (transactions.empty())
        {
            cout << "No transactions recorded." << endl;
            return;
        }

        // Print table header
        cout << left << setw(5) << "ID"
             << left << setw(20) << "Description"
             << right << setw(12) << "Amount"
             << "   " << left << setw(15) << "Category"
             << endl;
        cout << string(54, '-') << endl;

        for (int i = 0; i < transactions.size(); ++i)
        {
            transactions[i]->display();
        }
    }

    // Destructor
    ~BudgetTracker()
    {
        for (int i = 0; i < transactions.size(); i++)
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

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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
    cout << "\nSample data loaded successfully!" << endl;

    int choice;
    while (true)
    {
        clearScreen();
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
            clearInput();
            continue;
        }

        clearScreen();
        switch (choice)
        {
        case 1:
        {
            string desc, category;
            double amount;

            cout << "=== Add New Transaction ===" << endl;
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
            cout << "\nTransaction added successfully!" << endl;
            break;
        }

        case 2:
        {
            string category;
            cout << "=== Search by Category ===" << endl;
            cout << "Enter category: ";
            clearInput();
            getline(cin, category);

            tracker.searchByCategory(category);
            break;
        }

        case 3:
            cout << "=== Display by Amount (BST Traversal) ===" << endl;
            tracker.displayByAmount();
            break;

        case 4:
            cout << "=== Display Sorted by Amount (Merge Sort) ===" << endl;
            tracker.displaySortedByAmount();
            break;

        case 5:
            cout << "=== All Transactions ===" << endl;
            tracker.displayAll();
            break;

        case 6:
            tracker.showBudgetSummary();
            break;

        case 7:
            clearScreen();
            cout << "=== Thank You for Using Budget Tracker! ===" << endl;
            cout << "Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice! Please select 1-7." << endl;
            break;
        }
    }

    return 0;
}
