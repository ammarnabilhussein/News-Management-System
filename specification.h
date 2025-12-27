#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <iostream>
using namespace std;

struct article
{
    string title, category, description,author;
    int publish_month, publish_day;
    int rating, id;
    article* next;

    article();
    article(string title, string category, string description, string author,int publish_month, int publish_day, int rating, int id, article* next = nullptr);

};

class newsCategory
{
    
    public:
        int numberOfArticles;
        string categoryName;
        article *head, *tail;
        newsCategory* next;
        
        newsCategory();
        ~newsCategory();
        void addToHead(article*);
        void addToTail(article*);
        bool removeFromHead();
        bool removeFromTail();
        bool removefromMid(int);
        bool isEmpty();

};

class categories
{
    public:
        int numberOfCategories;
        newsCategory* head;
        newsCategory* tail;

        categories();
        ~categories();
        void addToHead(newsCategory*);
        void addToTail(newsCategory*);
        bool isEmpty();
};


class mostRecent // stack to be used for arranging the articles based on date by addArticle
{
    public: 
        int size;
        article*head;

        mostRecent();
        ~mostRecent();
        void push(article*);
        void pop();
        article* top();
        bool isEmpty();
};

class user
{
    private:
        string userName, password, type;
        article* bookmarkedHead = nullptr;
        article* bookmarkedTail = nullptr;
    public:
        user* next;
        user* prev;


        user();
        user(string userName, string password , string type, user *next, user *prev);
        string getType();
        string getUserName();
        string getPassword();
        article* searchByTitle(string title,categories* news);
        article* searchByDate(mostRecent* allNews, int month, int day);
        article* searchByKeywords(string words,categories* news);
        void displayCategoryNews(string categoryName, categories* allnews);
        void displayLatestNews(mostRecent* allNews);
        void displayTrendingNews();
        void rateNews(article* articleToRate);
        void bookmark(article* articleToBookmark);

};


class admin : public user
{
    public:

        int idsCounter;
        admin();
        admin(string userName, string password, string type, user* next, user* prev);

        int idGenerator();
        void addArticle(categories* news, mostRecent* recentNews, newsCategory* ratedNews);
        void removeArticle(int id,categories* news, mostRecent* recentNews, newsCategory* ratedNews);
        void updateExisting(int id,categories* news);
        newsCategory* addCategory();
        void displayAverageRateForCategory(categories* allCategories, string categoryName);

};




#endif