#include <iostream>
#include "specification.h"
#include<string>
#include <fstream>
using namespace std;

comment :: comment()
{
    commenterUserName = "";
    commentText = "";
    next = nullptr;
}

comment :: comment(string commenterName, string commentText, comment* next)
{
    this->commenterUserName = commenterName;
    this->commentText = commentText;
    this->next = next;
}

commentList :: commentList()
{
    numberOfComments = 0;
    head = nullptr;
    tail = nullptr;
}

commentList :: ~commentList()
{
    comment* current = head;
    comment* toDelete;

    while (current != nullptr)
    {
        toDelete = current;
        current = current ->next;
        delete toDelete;
    }
    head = tail = nullptr;
    numberOfComments = 0;
}

void commentList :: addComment(string commenterName, string commentText)
{
    comment* newComment = new comment(commenterName, commentText);
    if (isEmpty())
    {
        head = tail = newComment;
    }else{
        tail ->next = newComment;
        tail = newComment;
    }
    numberOfComments++;
}

bool commentList :: isEmpty()
{
    return numberOfComments == 0;
}

article :: article()
{
    title = "";
    category = "";
    description = "";
    publish_month = 0;
    publish_day = 0;
    rating = 0;
    id = 0;
    numberOfSpamReports = 0;
    next = nullptr;
}

article :: article(string title, string category, string description, string author,int publish_month, int publish_day, int rating, int id, int numberOfSpamReports, article* next)
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
    this->numberOfSpamReports = numberOfSpamReports;
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

string user :: getType()
{
    return type;
}

string user :: getUserName()
{
    return userName;
}

string user :: getPassword()
{
    return password;
}

void user ::displayArticle(article* articleToDisplay)
{
    article* current = spamCategory ->head;
    while (current != nullptr)
    {
        if (articleToDisplay ->id == current ->id)
        {
            return;
        }
        current = current ->next;
    }

    if (articleToDisplay ->rating < 2)
    {
        return;
    }

    cout << "\t\t\t\t" << articleToDisplay->title << endl
    << "\t\t\t\t" << articleToDisplay->description << endl
    << "By " << articleToDisplay->author << " | " 
    << articleToDisplay->publish_month << "/" << articleToDisplay->publish_day 
    << " | " << articleToDisplay->rating << "/10" 
    << " | " << articleToDisplay->numberOfSpamReports << " Spam Reports" << endl
    << "--------------------------------------------------" << endl;

    bookmark(articleToDisplay);
    rateNews(articleToDisplay);
    spam(articleToDisplay);
    addAComment(articleToDisplay);
}

void user::searchByTitle(string title, categories* news)
{
    newsCategory* cat = news->head;
    
    while (cat != nullptr)
    {
        article* temp = cat->head;
        while (temp != nullptr)
        {
            displayArticle(temp);   
            temp = temp->next;
        }
        cat = cat->next;
    }

}

void user ::searchByDate(mostRecent* allNews, int month, int day)
{
    // Copying the stack so the original is not changed
    mostRecent temp = *allNews;

    while (!temp.isEmpty())
    {
        article* currentArticle = temp.top();
        temp.pop();

        if (currentArticle->publish_month == month && currentArticle->publish_day == day)
        {
            displayArticle(currentArticle);
        }
    }

}

void user::searchByKeywords(string words, categories* news)
{
    newsCategory* cat = news->head;

    while (cat != nullptr)
    {
        article* temp = cat->head;
        while (temp != nullptr)
        {
            string word = "";
            bool found = false;
            for (int i = 0; i < temp ->description.size(); i++)
            {
                if (temp ->description[i] != ' ')
                {
                    word += temp ->description[i];
                }else{
                    if (word == words)
                    {
                        found = true;
                        break;
                    }
                    word = "";
                }
            }
            
            if (found)
            {
                displayArticle(temp);
                temp = temp ->next;
            }
            temp = temp->next;
        }
        cat = cat->next;
    }
    
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
            displayArticle(toDisplay);
            toDisplay = toDisplay ->next;
        }
        
    }else{
        cout << "No such category found." << endl;
    }
    
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
        displayArticle(temp);
        temp = temp->next;
    }
}

void user::displayTrendingNews(newsCategory* ratingList)
{
    if (ratingList == nullptr || ratingList->isEmpty())
    {
        cout << "No trending articles.\n";
        return;
    }

    article* temp = ratingList->head;

    cout << "Trending Articles:\n";

    while (temp != nullptr)
    {
        displayArticle(temp);
        temp = temp->next;
    }
}

void user::rateNews(article* toRate)
{
    char choice;
    int userRating;
    cout << "Do you want to rate this article? (y / n): ";
    cin >> choice;
    if (choice == 'y'){
        cout << "Enter your rating (1-10): ";
        cin >> userRating;
        
        toRate->rating = (toRate->rating + userRating) / 2;
        cout << "Thank you for rating!" << endl;
    }
}

void user ::bookmark(article* articleToBookmark){
    char choice;
    if(bookmarkedCategory ->isEmpty()){
        cout << "Do you want to bookmark this article? (y / n): ";
        cin >> choice;
        if (choice == 'y')
        {
            bookmarkedCategory ->addToHead(articleToBookmark);
            cout << "Article bookmarked successfully." << endl;
        }
    }else{
        article* temp = bookmarkedCategory ->head;
        while (temp != nullptr){
            if (temp ->id == articleToBookmark ->id)
            {
                cout << "Article is bookmarked, do you want to remove it from bookmarks?" << endl;
                cout << "Enter choice (y / n): ";
                cin >> choice;
                if (choice == 'y')
                {
                    bookmarkedCategory ->removefromMid(articleToBookmark ->id);
                    cout << "Article removed from bookmarks." << endl;
                }
                return;
            }
            temp = temp ->next;
        }
        cout << "Do you want to bookmark this article? (y / n): ";
        cin >> choice;
        if (choice == 'y')
        {
            bookmarkedCategory ->addToTail(articleToBookmark);
            cout << "Article bookmarked successfully." << endl;    
        }
    }

}

void user ::spam(article* articleToSpam){
    char choice;
    cout << "Do you want to report the article as spam?" << endl;
    cin >> choice;
    if (choice == 'y')
    {
        spamCategory ->addToTail(articleToSpam);
        articleToSpam ->numberOfSpamReports++;
    }
    
}

void user ::addAComment(article* articleToComment){
    comment* currentComment = articleToComment ->comments ->head;
    while (currentComment != nullptr)
    {
        cout << "-" << currentComment ->commenterUserName << ": " << currentComment ->commentText << endl;
        currentComment = currentComment ->next;
    }
    char choice;
    string displayName, commentText;
    cout << "Do you want to add a comment? (y / n): ";
    if (choice == 'y')
    {
        cout << "Enter your display name: ";
        cin >> displayName;
        cout << "Enter your comment: ";
        cin >> commentText;
        articleToComment ->comments ->addComment(displayName, commentText);
        cout << "Comment added successfully." << endl;
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

    article* newArticle = new article(title, category, description, author, publish_month, publish_day, 0, 0, idGenerator());
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
        newsCategory* newcat = addCategory(news);
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

userList :: userList(){
    numberOfUsers = 0;
    head = nullptr;
    tail = nullptr;
}

userList :: ~userList(){
    user* current = head;
    user* toDelete;
    while (current != nullptr)
    {
        toDelete = current;
        current = current ->next;
        delete toDelete;
    }
    head = tail = nullptr;
    numberOfUsers = 0;
}

void userList ::addToHead(user* newUser){
    if (isEmpty())
    {
        head = tail = newUser;
    }else{
        newUser ->next = head;
        head ->prev = newUser;
        head = newUser;
    }
    numberOfUsers++;
}
void userList ::addToTail(user* newUser){
    if (isEmpty())
    {
        head = tail = newUser;
    }else{
        tail ->next = newUser;
        newUser ->prev = tail;
        tail = newUser;
    }
    numberOfUsers++;
}
bool userList ::isEmpty(){
    return numberOfUsers == 0;
}
newsCategory* admin::addCategory(categories* allCategories)
{
    string name;
    cout << "Enter the name of new category: ";
    
    cin >> ws; 
    getline(cin, name);

    
    newsCategory* newCat = new newsCategory();
    newCat->categoryName = name;

    allCategories->addToTail(newCat);

    cout << "Category '" << name << "' created." << endl;

    return newCat;
}


void saveusers(user* head){
ofstream outfile("users.txt");
if (!outfile.is_open())
    {
        cout << "Error opening file for writing." << endl;
        return;
    }
  user* current = head;
  while (current != nullptr)
  {
    outfile << "Username: " << current->getUserName() << endl;
    outfile << "Password: " << current->getPassword() << endl;
    outfile << "Type: " << current->getType() << endl;
    int isadmin = (current->getType() == "admin") ? 1 : 0;
    outfile << "IsAdmin: " << isadmin << endl;

    current = current->next;
  }
outfile.close();
}

article* findArticleById(categories* news, int id) {
    if (!news || !news->head) return nullptr;
    newsCategory* cat = news->head;
    while (cat != nullptr) {
        article* art = cat->head;
        while (art != nullptr) {
            if (art->id == id) return art;
            art = art->next;
        }
        cat = cat->next;
    }
    return nullptr;
}

user* user::loadUsers(user *&head, categories* allNews) {
    ifstream inFile("users.txt");
    if (!inFile.is_open()) return nullptr;

    head = nullptr;
    user* tail = nullptr;
    string line;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        string username, password, type;
        
        
        size_t pos = line.find(":");
        username = line.substr(pos + 1);

       
        getline(inFile, line);
        pos = line.find(":");
        password = line.substr(pos + 1);

      
        getline(inFile, line);
        pos = line.find(":");
        type = line.substr(pos + 1);

        
        getline(inFile, line);
        
      
        user* newUser = nullptr;
        if (type == "admin") {
            newUser = new admin(username, password, type, nullptr, nullptr);
        } else {
            newUser = new user(username, password, type, nullptr, nullptr);
        }

        
        getline(inFile, line); 
        pos = line.find(":");
        string bookmarksStr = line.substr(pos + 1);
        
        
        size_t currentIdx = 0;
        while (currentIdx < bookmarksStr.length()) {
            
            size_t nextSpace = bookmarksStr.find(' ', currentIdx);
            
            
            if (nextSpace == string::npos) {
                nextSpace = bookmarksStr.length();
            }

            
            if (nextSpace > currentIdx) {
                string numStr = bookmarksStr.substr(currentIdx, nextSpace - currentIdx);
             
                try {
                    int artId = stoi(numStr);
                    if (artId == -1) break; 

                    article* art = findArticleById(allNews, artId);
                    if (art) {
                        newUser->bookmarkedCategory->addToTail(art);
                    }
                } catch (...) {
                   
                }
            }
            
            currentIdx = nextSpace + 1;
        }

       
        getline(inFile, line);
        pos = line.find(":");
        string spamStr = line.substr(pos + 1);
        
        currentIdx = 0;
        while (currentIdx < spamStr.length()) {
            size_t nextSpace = spamStr.find(' ', currentIdx);
            
            if (nextSpace == string::npos) {
                nextSpace = spamStr.length();
            }

            if (nextSpace > currentIdx) {
                string numStr = spamStr.substr(currentIdx, nextSpace - currentIdx);
                try {
                    int artId = stoi(numStr);
                    if (artId == -1) break;

                    article* art = findArticleById(allNews, artId);
                    if (art) {
                        newUser->spamCategory->addToTail(art);
                    }
                } catch (...) {}
            }
            currentIdx = nextSpace + 1;
        }

        if (head == nullptr) {
            head = newUser;
            tail = newUser;
        } else {
            tail->next = newUser;
            newUser->prev = tail;
            tail = newUser;
        }
    }

    inFile.close();
    return head;
}

bool user::saveUsers(user* head) {
    ofstream outFile("users.txt");
    if (!outFile.is_open()) return false;

    user* cur = head;
    while (cur != nullptr) {
        outFile << "Username:" << cur->getUserName() << '\n';
        outFile << "Password:" << cur->getPassword() << '\n';
        outFile << "Type:" << cur->getType() << '\n';
        outFile << '\n';

        outFile << "Bookmarks: ";
        if (cur->bookmarkedCategory != nullptr) {
            article* a = cur->bookmarkedCategory->head;
            while (a != nullptr) {
                outFile << a->id << " ";
                a = a->next;
            }
        }
        outFile << "-1\n";

        outFile << "Spam: ";
        if (cur->spamCategory != nullptr) {
            article* a = cur->spamCategory->head;
            while (a != nullptr) {
                outFile << a->id << " ";
                a = a->next;
            }
        }
        outFile << "-1\n";

        cur = cur->next;
    }

    outFile.close();
    return true;
}

void categories::saveCategories(const string& filename)
{
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    newsCategory* currentCat = head;
    while (currentCat != nullptr)
    {
        
        outFile << "---CATEGORY---" << endl;
        outFile << currentCat->categoryName << endl;

        article* currentArt = currentCat->head;
        while (currentArt != nullptr)
        {
            
            outFile << "---ARTICLE---" << endl;
            outFile << currentArt->id << endl;
            outFile << currentArt->title << endl;
            outFile << currentArt->category << endl;
            outFile << currentArt->description << endl;
            outFile << currentArt->author << endl;
            outFile << currentArt->publish_month << endl;
            outFile << currentArt->publish_day << endl;
            outFile << currentArt->rating << endl;
            outFile << currentArt->numberOfSpamReports << endl;
            
            currentArt = currentArt->next;
        }
        currentCat = currentCat->next;
    }

    outFile.close();
    cout << "Categories and articles saved successfully." << endl;
}


void categories:: loadCategories(const string& filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Warning: Could not open file " << filename << " (This is normal on first run)." << endl;
        return;
    }

    string line;
    newsCategory* currentCat = nullptr;

    while (getline(inFile, line))
    {
        if (line == "---CATEGORY---")
        {
            string catName;
            getline(inFile, catName);

          
            newsCategory* newCat = new newsCategory();
            newCat->categoryName = catName;
            this->addToTail(newCat);
            
            
            currentCat = newCat; 
        }
        else if (line == "---ARTICLE---")
        {
            if (currentCat == nullptr) continue; 

            string idStr, title, category, desc, author, monthStr, dayStr, ratingStr, spamStr;

            
            getline(inFile, idStr);
            getline(inFile, title);
            getline(inFile, category);
            getline(inFile, desc);
            getline(inFile, author);
            getline(inFile, monthStr);
            getline(inFile, dayStr);
            getline(inFile, ratingStr);
            getline(inFile, spamStr);

            int id = stoi(idStr);
            int month = stoi(monthStr);
            int day = stoi(dayStr);
            int rating = stoi(ratingStr);
            int spam = stoi(spamStr);

           
            article* newArticle = new article(title, category, desc, author, month, day, rating, id, spam, nullptr);
            
           
            newArticle->comments = new commentList();

           
            currentCat->addToTail(newArticle);
        }
    }

    inFile.close();
    cout << "Categories loaded successfully." << endl;
}