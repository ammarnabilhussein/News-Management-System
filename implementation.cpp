#include <iostream>
#include "specification.h"
#include<string>
using namespace std;

// article implementation

article :: article()
{
    title = "";
    category = "";
    description = "";
    publish_month = 0;
    publish_day = 0;
    rating = 0;
    id = 0;
    next = nullptr;
}

article :: article(string title, string category, string description, string author,int publish_month, int publish_day, int rating, int id, article* next)
{
    this->title = title;
    this->category = category;
    this->description = description;
    this->author = author;
    this->publish_month = publish_month;
    this->publish_day = publish_day;
    this->rating = rating;
    this->id = id;
    this->next = next;
}

newsCategory :: newsCategory()
{
    numberOfArticles = 0;
    categoryName = "";
    head = nullptr;
    tail = nullptr;
}

newsCategory ::~newsCategory()
{
    article* current = head;
    article* toDelete;

    while (current != nullptr)
    {
        toDelete = current;
        current = current ->next;
        delete toDelete;
    }
    head = tail = nullptr;
    numberOfArticles = 0;
}

void newsCategory ::addToHead(article* toAdd){
    if (isEmpty())
    {
        head = tail = toAdd;
    }else{
        toAdd ->next = head;
        head = toAdd;
    }
    numberOfArticles++;

}

void newsCategory ::addToTail(article* toAdd){
    if (isEmpty())
    {
        head = tail = toAdd;
    }else{
        tail ->next = toAdd;
        tail = toAdd;
    }
    numberOfArticles++;
}

bool newsCategory ::removeFromHead(){
    if (isEmpty())
    {
        return false;
    }
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }else{
        article* toDelete = head;
        head = head ->next;
        delete toDelete;
    }
    numberOfArticles--;
    return true;
}

bool newsCategory ::removeFromTail(){
    if (isEmpty())
    {
        return false;
    }
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }else{
        article* toDelete = head;
        article* previous;
        while (toDelete ->next != nullptr)
        {
            previous = toDelete;
            toDelete = toDelete ->next;
        }
        tail = previous;
        delete toDelete;
        tail ->next = nullptr;
    }
    numberOfArticles--;
    return true;
}

bool newsCategory ::removefromMid(int id){
    if (isEmpty())
    {
        return false;
    }
    if (head ->id == id)
    {
        removeFromHead();
    }else{
        article* toDelete = head;
        article* previous;
        while (toDelete != nullptr)
        {
            if (toDelete ->id == id)
            {
                break;
            }
            previous = toDelete;
            toDelete = toDelete ->next;
        }
        if (toDelete == nullptr)
        {
            return false;
        }
        previous ->next = toDelete ->next;
        delete toDelete;
        numberOfArticles--;
        return true;
    }
    
}

bool newsCategory ::isEmpty(){
    return numberOfArticles == 0;
}

categories ::categories(){
    numberOfCategories = 0;
    head = nullptr;
    tail = nullptr;
}

categories ::~categories(){
    newsCategory* current = head;
    newsCategory* toDelete;
    while (current != nullptr)
    {
        toDelete = current;
        current = current ->next;
        delete toDelete;
    }
    head = tail = nullptr;
    numberOfCategories = 0;
    
}

void categories ::addToHead(newsCategory* toAdd){
    if (isEmpty())
    {
        head = tail = toAdd;
    }else{
        toAdd ->next = head;
        head = toAdd;
    }
    numberOfCategories++;
}

void categories ::addToTail(newsCategory* toAdd){
    if (isEmpty())
    {
        head = tail = toAdd;
    }else{
        tail ->next = toAdd;
        tail = toAdd;
    }
    numberOfCategories++;
    
}

bool categories ::isEmpty(){
    return numberOfCategories == 0;
}

mostRecent ::mostRecent(){
    size = 0;
    head = nullptr;

}

mostRecent ::~mostRecent(){
    article* toDelete = head;
    while (head != nullptr)
    {
        toDelete = head;
        head = head ->next;
        delete toDelete;
    }
    size = 0;
    
}

void mostRecent ::push(article* toAdd){
    if (isEmpty())
    {
        head = toAdd;
    }else{
        toAdd ->next = head;
        head = toAdd;
    }
    size++;
}

void mostRecent ::pop(){
    if (isEmpty())
    {
        return;
    }
    article* toDelete = head;
    head = head ->next;
    delete toDelete;
    size--;
}

article* mostRecent ::top(){
    if (isEmpty())
    {
        return nullptr;
    }
    return head;
}

bool mostRecent ::isEmpty(){
    return size == 0;
}

user ::user()
{
    userName = "";
    password = "";
    type = "";
    next = nullptr;
    prev = nullptr;
}

user :: user(string userName, string password , string type, user *next, user *prev)
{
    this->userName = userName;
    this->password = password;
    this->type = type;
    this->next = next;
    this->prev = prev;
}

string user :: getUserName()
{
    return userName;
}

string user :: getPassword()
{
    return password;
}

string user :: getType()
{
    return type;
}

article* user::searchByTitle(string title, categories* news)
{
    newsCategory* cat = news->head;
    
    while (cat != nullptr)
    {
        article* temp = cat->head;
        while (temp != nullptr)
        {
            if (temp->title == title)
            return temp;
            
            temp = temp->next;
        }
        cat = cat->next;
    }
    return nullptr;
}

article* user ::searchByDate(mostRecent* allNews, int month, int day)
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

article* user::searchByKeywords(string words, categories* news)
{
    newsCategory* cat = news->head;

    while (cat != nullptr)
    {
        article* temp = cat->head;
        while (temp != nullptr)
        {
            if (temp->title.find(words) != string::npos ||
                temp->description.find(words) != string::npos)
            {
                return temp;
            }
            temp = temp->next;
        }
        cat = cat->next;
    }
    return nullptr;
}

void user ::displayCategoryNews(string categoryName, categories* news){
    newsCategory* temp = news ->head;
    while (temp != nullptr)
    {
        if (categoryName == temp ->categoryName)
        {
            break;
        }
        temp = temp ->next;
    }
    if (temp != nullptr)
    {
        article* toDisplay = temp ->head;
        while (toDisplay != nullptr)
        {
            cout << "\t\t\t\t" << toDisplay ->title << endl
            << "\t\t\t\t" << toDisplay ->description << endl
            << "By" << toDisplay ->author << " | " << toDisplay ->publish_month << "/" << toDisplay ->publish_day << " | " << toDisplay ->rating << "/10" << endl
            << "--------------------------------------------------" << endl;
            bookmark(toDisplay);
            rateNews(toDisplay);
            toDisplay = toDisplay ->next;
        }
        
    }else{
        cout << "No such category found." << endl;
    }
    
}

void user ::bookmark(article* articleToBookmark){
    char choice;
    if (bookmarkedHead == nullptr)
    {
        cout << "Do you want to bookmark this article? (y / n): ";
        cin >> choice;
        if (choice == 'y')
        {
            bookmarkedHead = articleToBookmark;
            bookmarkedTail = articleToBookmark;
            cout << "Article bookmarked successfully." << endl;
        }
        
    }else{
        article* temp = bookmarkedHead;
        while (temp != nullptr){
            if (temp ->id == articleToBookmark ->id)
            {
                cout << "Article already bookmarked." << endl;
                return;
            }
            temp = temp ->next;
        }
        cout << "Do you want to bookmark this article? (y / n): ";
        cin >> choice;
        if (choice == 'y')
        {
            bookmarkedTail ->next = articleToBookmark;
            bookmarkedTail = articleToBookmark;
            cout << "Article bookmarked successfully." << endl;    
        }
        
    }
}

admin :: admin()
{
    idsCounter = 0;
}

admin ::admin(string userName, string password, string type, user* next, user* prev) : user(userName, password, type, next, prev)
{
    
}

int admin :: idGenerator()
{
    return ++idsCounter;
}

void admin ::addArticle(categories* news, mostRecent* recentNews, newsCategory* ratedNews)
{
    string title, category, description, author;
    int publish_month, publish_day, id;
    cout << "Enter article title: ";
    getline(cin, title);
    cout << "Enter article category: ";
    getline(cin, category);
    cout << "Enter article description: ";
    getline(cin, description);
    cout << "Enter article author: ";
    getline(cin, author);
    cout << "Enter publish month and day: ";
    cin >> publish_month >> publish_day;

    article* newArticle = new article(title, category, description, author, publish_month, publish_day, 0, idGenerator());
    newsCategory* temp = news ->head;
    while (temp != nullptr)
    {
        if (newArticle ->category == temp ->categoryName)
        {
            break;
        }
        temp = temp ->next;
        
    }
    if (temp == nullptr)
    {
        newsCategory* newcat = addCategory();
        newcat ->addToTail(newArticle);
    }else{
        temp ->addToTail(newArticle);
    }
    
    mostRecent *storeMoreRecent;
    while (!recentNews ->isEmpty())
    {
        article *current = recentNews ->top();
        if (newArticle ->publish_month < current ->publish_month)
        {
            recentNews ->push(newArticle);
            break;
        }else if(newArticle ->publish_month == current ->publish_month){
            if (newArticle ->publish_day <= current ->publish_day)
            {
                recentNews ->push(newArticle);
                break;
            }
        
        }
        storeMoreRecent ->push(recentNews ->top());
        recentNews ->pop();
    }
    
    while (!storeMoreRecent ->isEmpty())
    {
        recentNews ->push(storeMoreRecent ->top());
        storeMoreRecent ->pop();
    }

    article* current = ratedNews ->head;
    article* previous;
    if (current == nullptr)
    {
        ratedNews ->addToHead(newArticle);
    }else {
        while (current != nullptr)
        {
            if (newArticle ->rating > current ->rating)
            {
                break;
            }
            previous = current;
            current = current ->next;
        }
    }

    if (current == nullptr)
    {
        ratedNews ->addToTail(newArticle);
    }else{
        previous ->next = newArticle;
        newArticle ->next = current;
        ratedNews ->numberOfArticles++;
    }
    
}

void admin ::removeArticle(int id,categories* news, mostRecent* recentNews, newsCategory* ratedNews){
    newsCategory* currentCat = news ->head;
    while (currentCat != nullptr)
    {
        if (currentCat ->removefromMid(id))
        {
            break;
        }
        currentCat = currentCat ->next;
    }
    if (currentCat == nullptr)
    {
        cout << "Article not found " << endl;
        return;
    }
    mostRecent* temp;
    while (!recentNews ->isEmpty())
    {
        article* current = recentNews ->top();
        if (current ->id == id)
        {
            recentNews ->pop();
            break;
        }
        temp ->push(recentNews ->top());
        temp ->pop();
    }
    while (!temp ->isEmpty())
    {
        recentNews ->push(temp ->top());
        temp ->pop();
    }
    
    ratedNews ->removefromMid(id);
    cout << "Article removed successfully." << endl;

}


void admin::updateExisting(int id, categories* news)
{
    newsCategory* cat = news->head;

    while (cat != nullptr)
    {
        article* temp = cat->head;
        while (temp != nullptr)
        {
            if (temp->id == id)
            {
                cout << "Updating Article ID " << id << endl;

                cout << "New title: ";
                cin.ignore();
                getline(cin, temp->title);

                cout << "New description: ";
                getline(cin, temp->description);

                cout << "New author: ";
                getline(cin, temp->author);

                cout << "New rating: ";
                cin >> temp->rating;

                cout << "Article updated successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cat = cat->next;
    }

    cout << "Article not found.\n";
}

void user::displayLatestNews(mostRecent* recent)
{
    if (recent == nullptr || recent->isEmpty())
    {
        cout << "no recent news to display.\n";
        return;
    }

    article* temp = recent->head;

    cout << "latest News:\n";

    while (temp != nullptr)
    {
        cout << "Title: " << temp->title << endl;
        cout << "Rating: " << temp->rating << endl; 
        cout << endl;
        temp = temp->next;
    }
}

void user::rateNews(int id, int rating, categories* news)
{
    if (news == nullptr)
        return;

    newsCategory* cat = news->head;

    while (cat != nullptr)
    {
        article* temp = cat->head;

        while (temp != nullptr)
        {
            if (temp->id == id)
            {
                temp->rating = rating;
                cout << "rating updated.\n";
                return;
            }

            temp = temp->next;
        }

        cat = cat->next;
    }

    cout << "article not found.\n";
}


void user::displayTrendingNews(ratingOrder* ratingQueue)
{
    if (ratingQueue == nullptr || ratingQueue->isEmpty())
    {
        cout << "No trending articles.\n";
        return;
    }

    article* temp = ratingQueue->head;

    cout << "Trending Articles:\n";

    while (temp != nullptr)
    {
        cout << "Title: " << temp->title << endl;
        cout << "Rating: " << temp->rating << endl;
        cout << endl;

        temp = temp->next;
    }
}
void admin ::displayAverageRateForCategory(categories* allCategories, string categoryName)
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
