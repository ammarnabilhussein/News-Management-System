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
    void setTitle(string title);
    void setCategory(string category);
    void setDescription(string description);
    void setAuthor(string author);
    void setPublishMonth(int month);
    void setPublishDay(int day);
    void setRating(int rate);
    void setId(int id);

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


class mostRecent // stack to be used for arranging the articles based on date by a fn
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

class ratingOrder // queue to be used for arranging the articles base on rating by a fn
{
    public:
        int size;
        article* head, *tail;

        ratingOrder();
        ~ratingOrder();
        void enqueue(article*);
        article dequeue();
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
        article* searchByTitle(string title);
        article* searchByDate(int date);
        article* searchByKeywords(string words);
        void displayCategoryNews(string categoryName, categories* allnews);
        void displayLatestNews(mostRecent* allNews);
        void displayTrendingNews();
        void rateNews(int rate, article* articleToRate);
        void bookmark(article* articleToBookmark);

};


class admin : public user
{
    public:

        int idsCounter;
        admin();
        admin(string userName, string password, string type, user* next, user* prev);

        int idGenerator();
        void addArticle(categories* news, mostRecent* recentNews, ratingOrder* ratedNews);
        void removeArticle(int id,categories* news);
        void updateExisting(int id);
        newsCategory* addCategory(); // Use this when doing my function youssef
        void displayAvgRateForCat(string categoryName, categories* news);

};




#endif