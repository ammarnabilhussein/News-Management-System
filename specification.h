#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <iostream>
using namespace std;

struct article
{
    string title, category;
    int publishDate, rating, id;
    // Description (data type undecided yet)
};

class user
{
    private:
        string userName, password, type;
    public:
        user(string,string,string);

};

class admin : public user
{
    public:
        admin(string,string,string);

        void postNews(article toAdd);
        void updateExisting(int id);
        void addCategory(string categoryName);
        void displayAvgRateForCat(string categoryName);

};

class customers : public user
{
    public:
        customers(string,string,string);

        article* searchByTitle(string title);
        article* searchByDate(int date);
        article* searchByKeywords(string words);
        void displayCategoryNews(string Categoryname);
        void  displayLatestNews();
        void displayTrendingNews();
        void rateNews();
        void bookmark();

};


#endif