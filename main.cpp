#include <iostream>
#include "Specification.h"
#include <fstream>
using namespace std;

user* login(user* head);
user* signup(user* head);
bool saveUsers(user* head);
bool loadUsers(user*& head);

int main()
{   
    categories news;
    mostRecent recentNews;
    newsCategory ratedNews;
    userList users;
    news.loadCategories("categories.txt");
    loadUsers(users.head);

    while (true)
    {
        int choice;
        cout << "1. Login\n2. Signup\n3. Exit\nEnter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            user* head = users.head;
            user* loggedInUser = login(head);
            if (loggedInUser != nullptr)
            {
                cout << "Welcome, " << loggedInUser->getUserName() << "!" << endl;
                int userChoice;
                do
                {
                    cout << "1. Search by Title\n2. Search by Date\n3. Search by Keywords\n4. Display Category News\n5. Display Latest News\n6. Display Trending News\n7. Logout\nEnter your choice: ";
                    cin >> userChoice;
                    switch (userChoice)
                    {
                        case 1:
                        {
                            char logout;
                            string title;
                            cout << "Enter title to search: ";
                            getline(cin, title);
                            loggedInUser->searchByTitle(title, &news);
                            cout << "do you want to logout? (y/n): ";
                            cin >> logout;
                            if (logout == 'y')
                            {
                                userChoice = 7;
                            }
                            break;
                        }
                        case 2:
                        {
                            char logout;
                            int month, day;
                            cout << "Enter month and day to search: ";
                            cin >> month >> day;
                            loggedInUser->searchByDate(&recentNews, month, day);
                            cout << "do you want to logout? (y/n): ";
                            cin >> logout;
                            if (logout == 'y')
                            {
                                userChoice = 7;
                            }
                            break;
                        }
                        case 3:
                        {
                            char logout;
                            string keywords;
                            cout << "Enter keywords to search: ";
                            getline(cin, keywords);
                            loggedInUser->searchByKeywords(keywords, &news);
                            cout << "do you want to logout? (y/n): ";
                            cin >> logout;
                            if (logout == 'y')
                            {
                                userChoice = 7;
                            }
                            break;
                        }
                        case 4:
                        {
                            char logout;
                            string categoryName;
                            cout << "Enter category name: ";
                            getline(cin, categoryName);
                            loggedInUser->displayCategoryNews(categoryName, &news);
                            cout << "do you want to logout? (y/n): ";
                            cin >> logout;
                            if (logout == 'y')
                            {
                                userChoice = 7;
                            }
                            break;
                        }
                        case 5:
                        {
                            char logout;
                            loggedInUser->displayLatestNews(&recentNews);
                            cout << "do you want to logout? (y/n): ";
                            cin >> logout;
                            if (logout == 'y')
                            {
                                userChoice = 7;
                            }
                            break;
                        }
                        case 6:
                        {
                            char logout;
                            loggedInUser->displayTrendingNews(&ratedNews);
                            cout << "do you want to logout? (y/n): ";
                            cin >> logout;
                            if (logout == 'y')
                            {
                                userChoice = 7;
                            }
                            break;
                        }
                            
                        case 7:
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (userChoice != 7);
            }

        }
        else if (choice == 2)
        {
            users.head = signup(users.head);
            saveUsers(users.head);
        }
        else if (choice == 3)
        {
            return 0;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

user* login(user* head)
{
    string uname, pass;
    cout << "Enter username: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pass;
    user* temp = head;
    while (temp != nullptr)
    {
        if (temp->getUserName() == uname && temp->getPassword() == pass)
        {
            cout << "Login successful" << endl;
            return temp;
        }
        temp = temp->next;
    }
    cout << "Invalid username or password." << endl;
    return nullptr;
}

user* signup(user* head)
{
    string uname, pass, type;
    cout << "Enter username: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pass;
    cout << "Enter user type (admin/user): ";
    cin >> type;

    user* newUser = new user(uname, pass, type, nullptr, nullptr);
    if (head == nullptr)
    {
        return newUser;
    }
    user* temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newUser;
    newUser->prev = temp;
    return head;
}

bool saveUsers(user* head) {
    ofstream outfile("Users.txt");
    if (!outfile.is_open()) {
        cout << "Error opening Users.txt for writing." << endl;
        return false;
    }
    user* current = head;
    while (current != nullptr) {
        outfile << current->getUserName() << " " << current->getPassword() << " " << current->getType() << endl;
        current = current->next;
    }
    outfile.close();
    return true;
}

bool loadUsers(user*& head) {
    ifstream infile("Users.txt");
    if (!infile.is_open()) {
        cout << "Error opening Users.txt for reading." << endl;
        return false;
    }
    head = nullptr;
    user* tail = nullptr;
    string uname, pass, type;
    while (infile >> uname >> pass >> type) {
        user* newUser = new user(uname, pass, type, nullptr, nullptr);
        if (head == nullptr) {
            head = newUser;
            tail = newUser;
        } else {
            tail->next = newUser;
            newUser->prev = tail;
            tail = newUser;
        }
    }
    infile.close();
    return true;
}