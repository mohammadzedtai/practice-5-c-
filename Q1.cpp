#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class LibraryItem
{
private:
    string title;
    string author;
    string dueDate;

public:
    LibraryItem(string t = "", string a = "", string d = "")
        : title(t), author(a), dueDate(d) {}

    virtual ~LibraryItem() {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getDueDate() const { return dueDate; }

    void setTitle(string newTitle) { title = newTitle; }
    void setAuthor(string newAuthor) { author = newAuthor; }
    void setDueDate(string newDueDate) { dueDate = newDueDate; }

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;
};

class Book : public LibraryItem
{
private:
    string ISBN;

public:
    Book(string t, string a, string d, string isbn)
        : LibraryItem(t, a, d), ISBN(isbn) {}

    void checkOut() override
    {
        cout << "Book '" << getTitle() << "' checked out successfully!\n";
    }

    void returnItem() override
    {
        cout << "Book '" << getTitle() << "' returned successfully!\n";
    }

    void displayDetails() const override
    {
        cout << "\n[Book Details]\n";
        cout << "Title: " << getTitle() << "\nAuthor: " << getAuthor()
             << "\nDue Date: " << getDueDate()
             << "\nISBN: " << ISBN << "\n";
    }
};

class DVD : public LibraryItem
{
private:
    int duration;

public:
    DVD(string t, string a, string d, int dur)
        : LibraryItem(t, a, d), duration(dur)
    {
        if (dur <= 0)
            throw invalid_argument("Duration cannot be negative or zero!");
    }

    void checkOut() override
    {
        cout << "DVD '" << getTitle() << "' checked out successfully!\n";
    }

    void returnItem() override
    {
        cout << "DVD '" << getTitle() << "' returned successfully!\n";
    }

    void displayDetails() const override
    {
        cout << "\n[DVD Details]\n";
        cout << "Title: " << getTitle() << "\nDirector: " << getAuthor()
             << "\nDue Date: " << getDueDate()
             << "\nDuration: " << duration << " minutes\n";
    }
};

class Magazine : public LibraryItem
{
private:
    int issueNumber;

public:
    Magazine(string t, string a, string d, int issue)
        : LibraryItem(t, a, d), issueNumber(issue)
    {
        if (issue <= 0)
            throw invalid_argument("Issue number must be positive!");
    }

    void checkOut() override
    {
        cout << "Magazine '" << getTitle() << "' checked out successfully!\n";
    }

    void returnItem() override
    {
        cout << "Magazine '" << getTitle() << "' returned successfully!\n";
    }

    void displayDetails() const override
    {
        cout << "\n[Magazine Details]\n";
        cout << "Title: " << getTitle() << "\nEditor: " << getAuthor()
             << "\nDue Date: " << getDueDate()
             << "\nIssue Number: " << issueNumber << "\n";
    }
};

int main()
{
    vector<LibraryItem *> libraryItems;
    int choice;

    try
    {
        do
        {
            cout << "\n===== Library Management System =====\n";
            cout << "1. Add Book\n";
            cout << "2. Add DVD\n";
            cout << "3. Add Magazine\n";
            cout << "4. Display All Items\n";
            cout << "5. Check Out Item\n";
            cout << "6. Return Item\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
            {
                throw runtime_error("Invalid input! Please enter a number.");
            }

            if (choice == 1)
            {
                string title, author, dueDate, isbn;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter due date: ";
                getline(cin, dueDate);
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                libraryItems.push_back(new Book(title, author, dueDate, isbn));
                cout << "Book added successfully!\n";
            }
            else if (choice == 2)
            {
                string title, author, dueDate;
                int duration;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter director: ";
                getline(cin, author);
                cout << "Enter due date: ";
                getline(cin, dueDate);
                cout << "Enter duration (minutes): ";
                cin >> duration;
                libraryItems.push_back(new DVD(title, author, dueDate, duration));
                cout << "DVD added successfully!\n";
            }
            else if (choice == 3)
            {
                string title, author, dueDate;
                int issue;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter editor: ";
                getline(cin, author);
                cout << "Enter due date: ";
                getline(cin, dueDate);
                cout << "Enter issue number: ";
                cin >> issue;
                libraryItems.push_back(new Magazine(title, author, dueDate, issue));
                cout << "Magazine added successfully!\n";
            }
            else if (choice == 4)
            {
                cout << "\n--- Library Items ---\n";
                for (auto item : libraryItems)
                    item->displayDetails();
            }
            else if (choice == 5 || choice == 6)
            {
                string title;
                cout << "Enter title of item: ";
                cin.ignore();
                getline(cin, title);
                bool found = false;
                for (auto item : libraryItems)
                {
                    if (item->getTitle() == title)
                    {
                        found = true;
                        if (choice == 5)
                            item->checkOut();
                        else
                            item->returnItem();
                        break;
                    }
                }
                if (!found)
                    cout << "Item not found!\n";
            }
            else if (choice == 7)
            {
                cout << "Exiting system...\n";
            }
            else
            {
                cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 7);

        for (auto item : libraryItems)
            delete item;

        libraryItems.clear();
        cout << "All items deleted successfully!\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
