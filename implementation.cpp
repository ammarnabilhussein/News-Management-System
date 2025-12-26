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

void newsCategory ::removeFromHead(){
    if (isEmpty())
    {
        return;
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
    
}

void newsCategory ::removeFromTail(){
    if (isEmpty())
    {
        return;
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
}

void newsCategory ::removefromMid(article* toAdd, int id){
    if (isEmpty())
    {
        return;
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
            return;
        }
        previous ->next = toDelete ->next;
        delete toDelete;
        numberOfArticles--;
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

ratingOrder ::ratingOrder(){
    size = 0;
    head = tail = nullptr;
}

ratingOrder ::~ratingOrder(){
    while (!isEmpty())
    {
        dequeue();
    }
    
}

void ratingOrder ::enqueue(article* toAdd){
    if (isEmpty())
    {
        head = tail = toAdd;
    }else{
        tail ->next = toAdd;
        tail = toAdd;
    }
    size++;
}

article ratingOrder ::dequeue(){
    if (isEmpty())
    {
        return;
    }
    article* toDelete = head;
    head = head ->next;
    article toReturn = *toDelete;
    size--;
    return toReturn;
}

bool ratingOrder ::isEmpty(){
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

// ziad's part
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

