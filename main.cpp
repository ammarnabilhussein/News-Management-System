#include <iostream>
#include "Specification.h"
using namespace std;

user* login(user* head);

int main()
{   
    categories news;
    mostRecent recentNews;
    newsCategory ratedNews;
    
    // copilot wrote this part , delete so we don't get fucked
    
    user* usersHead = nullptr;
    // Code to initialize usersHead with some users would go here

    user* loggedInUser = login(usersHead);
    if (loggedInUser != nullptr)
    {
        cout << "Welcome, " << loggedInUser->getUserName() << "!" << endl;
        // Further actions based on user type can be implemented here
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