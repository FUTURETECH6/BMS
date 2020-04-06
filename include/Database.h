#ifndef DATABASH_H
#define DATABASH_H

#include <QWidget>
#include <iostream>
#include <mysql.h>

using namespace std;

class Book {

  public:
    Book() {
        BookID   = "";
        Category = "";
        Title    = "";
        Press    = "";
        Year     = EMPTY;
        Author   = "";
        Price    = EMPTY;
        Total    = EMPTY;
        Stock    = EMPTY;
    }
    Book(string input_BookID, string input_Category, string input_Title,
         string input_Press, int input_Year, string input_Author,
         double input_Price, int input_Total, int input_Stock) {
        BookID   = input_BookID;
        Category = input_Category;
        Title    = input_Title;
        Press    = input_Press;
        Year     = input_Year;
        Author   = input_Author;
        Price    = input_Price;
        Total    = input_Total;
        Stock    = input_Stock;
    }
    inline void reset(string input_BookID, string input_Category,
                      string input_Title, string input_Press, int input_Year,
                      string input_Author, double input_Price, int input_Total,
                      int input_Stock) {
        BookID   = input_BookID;
        Category = input_Category;
        Title    = input_Title;
        Press    = input_Press;
        Year     = input_Year;
        Author   = input_Author;
        Price    = input_Price;
        Total    = input_Total;
        Stock    = input_Stock;
    }
    inline string str() {
        return "'" + BookID + "', '" + Category + "', '" + Title + "', '" +
               Press + "', " + to_string(Year) + ", '" + Author + "', " +
               to_string(Price) + ", " + to_string(Total) + ", " +
               to_string(Stock);
    }

  public:
    static const int EMPTY = -1;
    string BookID;    // 书号
    string Category;  // 类别
    string Title;     // 书名
    string Press;     // 出版社
    int Year;         // 年份
    string Author;    // 作者
    double Price;     // 价格
    int Total;        // 藏书量
    int Stock;        // 库存
};

class Card {

  public:
    Card() {
        CardID     = "";
        Name       = "";
        Department = "";
        Type       = "";
    }
    Card(string input_CardID, string input_Name, string input_Department,
         string input_Type) {
        CardID     = input_CardID;
        Name       = input_Name;
        Department = input_Department;
        Type       = input_Type;
    };
    inline void reset(string input_CardID, string input_Name,
                      string input_Department, string input_Type) {
        CardID     = input_CardID;
        Name       = input_Name;
        Department = input_Department;
        Type       = input_Type;
    };
    inline string str() {
        return "'" + CardID + "', '" + Name + "', '" + Department + "', '" +
               Type + "'";
    }

  public:
    string CardID;      // 卡号
    string Name;        // 姓名
    string Department;  // 单位
    string Type;        // 类别 {"Student", "Teacher"}
};

class Admin {

  public:
    Admin() {
        AdminID  = "";
        Passwd   = "";
        Name     = "";
        Contacts = "";
    }
    Admin(string input_AdminID, string input_Passwd, string input_Name,
          string input_Contacts) {
        AdminID  = input_AdminID;
        Passwd   = input_Passwd;
        Name     = input_Name;
        Contacts = input_Contacts;
    }
    inline void reset(string input_AdminID, string input_Passwd,
                      string input_Name, string input_Contacts) {
        AdminID  = input_AdminID;
        Passwd   = input_Passwd;
        Name     = input_Name;
        Contacts = input_Contacts;
    }
    inline string str() {
        return "'" + AdminID + "', '" + Passwd + "', '" + Name + "', '" +
               Contacts + "'";
    }

  public:
    string AdminID;   //管理员id
    string Passwd;    //密码
    string Name;      //姓名
    string Contacts;  //联系方式
};

class Database {
  public:
    Database();
    ~Database();

    void freeRes();
    void error_info();
    bool login(string username, string passwd);
    void logout();

    // Admin
    bool insertBook(Book);
    bool insertBook(string pwd);
    bool insertCard(Card);
    bool insertAdmin(Admin);
    bool deleteCard(string CardID);  // Delete card with given ID

    // Query
    vector<Book> *queryBook(string attribute, string value,
                            string orderby);  // Default: order by ID
    vector<Book> *queryBook(string attribute, double lower, double upper,
                            string orderby, bool isAsc = 0);  // ASC
    string queryBook(string BookID);  // Find Title of the book
    vector<Book> *res2Ptr(MYSQL_RES *result);

    // BorRet
    string borBook(string BookID, string CardID,
                   QWidget *);  // Use BID & CID to specify
    string retBook(string BookID, string CardID,
                   QWidget *);  // Use BID & CID to specify

    string curAdmin;  // "" for logout
    MYSQL *mysql;     // Handle

  private:
    string mysql_hostname = "114.55.251.25";
    string mysql_DB       = "library";

    bool connect();
    bool checkDB();
    bool createDB();
    void recreateDB();

  protected:
    string mysql_username = "librarian";  // Basic Authoriz
    string mysql_passwd   = "123456";
    string rootPasswd     = "root";  // Password for root admin
};

#endif
