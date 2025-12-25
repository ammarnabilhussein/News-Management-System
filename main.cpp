#include <iostream>
#include "Specification.h"
using namespace std;

user* login(user* head);
void addToMostRecent(mostRecent *news, article* toAdd);
void addToOrderAccordingToRate(ratingOrder* news, article* toAdd);
article* searchbydate(mostRecent* allNews, int month, int day);
void displayavragerateforcategory(categories* allCategories, string categoryName);

int main()
{   
    mostRecent allNews;
    ratingOrder allnews;

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

article* searchbydate(mostRecent* allNews, int month, int day)
{
    // Copying the stack so the original is not changed
    mostRecent temp = *allNews;

    while (!temp.isEmpty())
    {
        article* currentArticle = temp.top();
        temp.pop();

        if (currentArticle->publish_month == month && currentArticle->publish_day == day)
        {
            return currentArticle;
        }
    }

    return nullptr;
}

void displayavragerateforcategory(categories* allCategories, string categoryName)
{
     int totalRating = 0;
    int articleCount = 0;
    newsCategory* tempCategory = allCategories->head;
    while (tempCategory != nullptr)
    {
        if (tempCategory->categoryName == categoryName)
        {
            article* currentArticle = tempCategory->head;
            int totalRating = 0;
            int articleCount = 0;

            while (currentArticle != nullptr)
            {
                totalRating += currentArticle->rating;
                articleCount++;
                currentArticle = currentArticle->next;
            }

            if (articleCount > 0)
            {
                double averageRating = static_cast<double>(totalRating) / articleCount;
                cout << "Average rating for category " << categoryName << " is: " << averageRating << endl;
            }
            else
            {
                cout << "No articles found in category " << categoryName << endl;
            }
            return;
        }
        tempCategory = tempCategory->next;
    }
    cout << "Category " << categoryName << " not found." << endl;
}