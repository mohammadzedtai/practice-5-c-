#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class LibraryItem
{
protected:
    string title;
    string creator;
    string dueDate;

public:
    LibraryItem(string t = "", string c = "", string d = "")
        : title(t), creator(c), dueDate(d) {}

    virtual ~LibraryItem() {}

    string getTitle() const { return title; }
    string getCreator() const { return creator; }
    string getDueDate() const { return dueDate; }

    void setTitle(const string &t) { title = t; }
    void setCreator(const string &c) { creator = c; }
    void setDueDate(const string &d) { dueDate = d; }

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void showDetails() const = 0;
};

class Book : public LibraryItem
{
private:
    string isbn;

public:
    Book(string t, string a, string d, string i)
        : LibraryItem(t, a, d), isbn(i) {}

    void checkOut() override
    {
        cout << " Book \"" << title << "\" issued successfully.\n";
    }

    void returnItem() override
    {
        cout << " Book \"" << title << "\" returned successfully.\n";
    }

    void showDetails() const override
    {
        cout << "\n Book Info:\n";
        cout << "Title: " << title
             << "\nAuthor: " << creator
             << "\nDue Date: " << dueDate
             << "\nISBN: " << isbn << "\n";
    }
};

class DVD : public LibraryItem
{
private:
    int duration;

public:
    DVD(string t, string dir, string d, int dur)
        : LibraryItem(t, dir, d), duration(dur)
    {
        if (dur <= 0)
            throw invalid_argument("Duration must be greater than 0.");
    }

    void checkOut() override
    {
        cout << " DVD \"" << title << "\" issued successfully.\n";
    }

    void returnItem() override
    {
        cout << " DVD \"" << title << "\" returned successfully.\n";
    }

    void showDetails() const override
    {
        cout << "\n DVD Info:\n";
        cout << "Title: " << title
             << "\nDirector: " << creator
             << "\nDue Date: " << dueDate
             << "\nDuration: " << duration << " mins\n";
    }
};

class Magazine : public LibraryItem
{
private:
    int issueNo;

public:
    Magazine(string t, string e, string d, int issue)
        : LibraryItem(t, e, d), issueNo(issue)
    {
        if (issue <= 0)
            throw invalid_argument("Issue number must be positive.");
    }

    void checkOut() override
    {
        cout << " Magazine \"" << title << "\" issued successfully.\n";
    }

    void returnItem() override
    {
        cout << " Magazine \"" << title << "\" returned successfully.\n";
    }

    void showDetails() const override
    {
        cout << "\n Magazine Info:\n";
        cout << "Title: " << title
             << "\nEditor: " << creator
             << "\nDue Date: " << dueDate
             << "\nIssue No: " << issueNo << "\n";
    }
};

void getLineInput(const string &label, string &input)
{
    cout << label;
    getline(cin, input);
}

int main()
{
    vector<LibraryItem *> items;
    int choice;

    cout << "\n====== Welcome to Library System ======\n";

    do
    {
        cout << "\n1. Add Book"
             << "\n2. Add DVD"
             << "\n3. Add Magazine"
             << "\n4. Show All Items"
             << "\n5. Check Out Item"
             << "\n6. Return Item"
             << "\n7. Exit"
             << "\n----------------------------------------\n"
             << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << " Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        cin.ignore();

        try
        {
            if (choice == 1)
            {
                string t, a, d, i;
                getLineInput("Enter book title: ", t);
                getLineInput("Enter author: ", a);
                getLineInput("Enter due date: ", d);
                getLineInput("Enter ISBN: ", i);
                items.push_back(new Book(t, a, d, i));
                cout << "Book added successfully.\n";
            }
            else if (choice == 2)
            {
                string t, dir, d;
                int dur;
                getLineInput("Enter DVD title: ", t);
                getLineInput("Enter director: ", dir);
                getLineInput("Enter due date: ", d);
                cout << "Enter duration (in minutes): ";
                cin >> dur;
                cin.ignore();
                items.push_back(new DVD(t, dir, d, dur));
                cout << " DVD added successfully.\n";
            }
            else if (choice == 3)
            {
                string t, e, d;
                int issue;
                getLineInput("Enter magazine title: ", t);
                getLineInput("Enter editor: ", e);
                getLineInput("Enter due date: ", d);
                cout << "Enter issue number: ";
                cin >> issue;
                cin.ignore();
                items.push_back(new Magazine(t, e, d, issue));
                cout << " Magazine added successfully.\n";
            }
            else if (choice == 4)
            {
                if (items.empty())
                {
                    cout << " No items found in the library.\n";
                }
                else
                {
                    cout << "\n------- Library Collection -------\n";
                    for (auto item : items)
                        item->showDetails();
                }
            }
            else if (choice == 5 || choice == 6)
            {
                string title;
                getLineInput("Enter title of the item: ", title);
                bool found = false;

                for (auto item : items)
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
                    cout << " Item not found in the library.\n";
            }
            else if (choice == 7)
            {
                cout << " Exiting... Thank you for using the system.\n";
            }
            else
            {
                cout << " Invalid choice. Try again.\n";
            }
        }
        catch (const exception &ex)
        {
            cerr << "Error: " << ex.what() << "\n";
        }

    } while (choice != 7);

    for (auto i : items)
        delete i;

    items.clear();
    cout << " All resources freed. Goodbye!\n";

    return 0;
}
