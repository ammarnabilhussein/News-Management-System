#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <iostream>
#include <fstream>
using namespace std;

class comment
{
    public:
        string commenterUserName;
        string commentText;
        comment* next;
        comment();
        comment(string commenterName, string commentText, comment* next = nullptr);
};

class commentList
{
    public:
        int numberOfComments;
        comment* head, *tail;
        commentList();
        ~commentList();
        void addComment(string commenterName, string commentText);
        bool isEmpty();
};

struct article
{
    string title, category, description,author;
    int publish_month, publish_day;
    int rating, id;
    int numberOfSpamReports;
    article* next;
    commentList* comments;

    article();
    article(string title, string category, string description, string author,int publish_month, int publish_day, int rating, int id, int numberOfSpamReports, article* next = nullptr);

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

        newsCategory* bookmarkedCategory;
        newsCategory* spamCategory;

    public:
        user* next;
        user* prev;


        user();
        user(string userName, string password , string type, user *next, user *prev);
        string getType();
        string getUserName();
        string getPassword();
        void displayArticle(article* articleToDisplay);
        void searchByTitle(string title,categories* news);
        void searchByDate(mostRecent* allNews, int month, int day);
        void searchByKeywords(string words,categories* news);
        void displayCategoryNews(string categoryName, categories* allnews);
        void displayLatestNews(mostRecent* allNews);
        void displayTrendingNews(newsCategory* ratedNews);
        void rateNews(article* articleToRate);
        void bookmark(article* articleToBookmark);
        void spam(article* articleToAddToSpam);
        void addAComment(article* articleToComment);

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
        void displayAverageRateForCategory(categories* allCategories, string categoryName);
        newsCategory* addCategory(categories* allCategories);

};

class userList
{
    public:
        int numberOfUsers;
        user* head;
        user* tail;

        userList();
        ~userList();
        void addToHead(user* newUser);
        void addToTail(user* newUser);
        bool isEmpty();
};

bool saveUsers(user* head);
bool loadUsers(user*& head);

#endif