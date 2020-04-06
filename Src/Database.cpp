#include "Database.h"

#include <QMessageBox>
#include <fstream>
#include <string>
#include <vector>

Database::Database() {
    if ((mysql_library_init(0, NULL, NULL) == 0 &&
         (mysql = mysql_init(NULL)) != NULL) == false)
        return;  // Initialize connection's handle
    // if (!mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8"))  // Set
    // charset's encoding
    if (connect() == false)  // Try to coonnect
        return;
    if (checkDB() == false)  // Can't find DBs
        createDB();          // Create a new one

    string command = "use " + mysql_DB;
    mysql_query(mysql, command.c_str());
}

Database::~Database() {
    mysql_close(mysql);
    mysql_server_end();
}

/*
 * Connect to database
 * @RetValue: true: success; false: error
 */
bool Database::connect() {
    return (mysql_real_connect(mysql, mysql_hostname.c_str(),
                               mysql_username.c_str(), mysql_passwd.c_str(),
                               NULL, 0, NULL, 0) != NULL);
}

bool Database::checkDB() {
    string command = "show databases like " + string("'") + mysql_DB +
                     "'";  // Check if `mysql_DB` is existed
    mysql_query(mysql, command.c_str());

    MYSQL_RES *result = mysql_store_result(mysql);
    return mysql_num_rows(result);  // Check if it's empty set
}

void Database::recreateDB() {
    string command = "drop database if exits " + mysql_DB;
    mysql_query(mysql, command.c_str());
    createDB();
}

bool Database::createDB() {
    string command = "create database " + mysql_DB +
                     " default character set utf8 collate utf8_general_ci";
    if (mysql_query(mysql, command.c_str()))  // Create database
        return false;

    command = "use" + string(" ") + mysql_DB;
    if (mysql_query(mysql, command.c_str()))  // Use database
        return false;

    command =
        "create table book(BookID char(20) primary key, Category varchar(40), "
        "Title varchar(40), Press varchar(40), Year int, Author varchar(40), "
        "Price decimal(10,2), Total int, Stock int)";
    if (mysql_query(mysql, command.c_str()))  // Create table book
        return false;

    command =
        "create table card(CardID char(20) primary key, Name varchar(40), "
        "Department varchar(40), Type varchar(10), check(type in ('Teacher', "
        "'Student')))";
    if (mysql_query(mysql, command.c_str()))  // Create table card
        return false;

    command =
        "create table admin(AdminID char(20) primary key, Passwd varchar(20), "
        "Name varchar(40), Contacts varchar(40))";
    if (mysql_query(mysql, command.c_str()))  // Create table admin
        return false;

    command =
        "create table record(CardID char(8), BookID char(8), BorrowDate "
        "date, RetDate date, AdminID char(8), foreign key(CardID) references "
        "card(CardID) on delete cascade, foreign key(BookID) references "
        "book(BookID) on delete cascade, foreign key(AdminID) references "
        "admin(AdminID) on delete cascade)";
    if (mysql_query(mysql, command.c_str()))  // Create table record
        return false;

    command =
        "insert into admin values('root', '" + rootPasswd + "', NULL, NULL)";
    if (mysql_query(mysql, command.c_str()))  // Insert a basic admin account
        return false;

    curAdmin = "";  // Set to logout status

    return true;
}

/*
 * For debugging
 */
void Database::error_info() {
    printf("Error %u: %s\n", mysql_errno(mysql), mysql_error(mysql));
}

void Database::freeRes() {
    do {
        MYSQL_RES *pRes = mysql_store_result(mysql);
        if (pRes != NULL)
            mysql_free_result(pRes);
    } while (!mysql_next_result(mysql));
}

/*
 * Login
 * @Param: username and password used to log in
 * @RetValue: true: success; false: error
 */
bool Database::login(string username, string passwd) {
    string command = "select * from admin where AdminID = '" + username +
                     "' and Passwd = '" + passwd + "'";
    if (mysql_query(mysql, command.c_str()))  // Find usr with correct passwd
        return false;

    MYSQL_RES *result = mysql_store_result(mysql);  // Get the account

    if (mysql_num_rows(result)) {  // Whether account exists
        curAdmin = username;
        return true;  // Paired!
    } else {
        curAdmin = "";  // Not Found
        return false;
    }
}
void Database::logout() {
    curAdmin = "";
}

/*
 * Insert a book
 * @Param: a class Book
 * BookID, Category, Title, Press, Year, Author, Price, Total, Stock
 * @RetValue: prompt
 */
bool Database::insertBook(Book book) {
    // if (curAdmin == "")
    //     return "Not logged in\n";  // Check if is logged in

    string command = "insert into book values(" + book.str() + ")";
    return !mysql_query(mysql, command.c_str());
}

bool Database::insertBook(string pwd) {
    ifstream fp;
    fp.open(pwd);
    if (fp.fail())
        return 0;
    string input = "init";
    while (!fp.eof() || input == "") {
        getline(fp, input);
        string LF;
        string command = "insert into book values" + input;
        mysql_query(mysql, command.c_str());
    }
    fp.close();
    return 1;
}
/*
 * Insert a card
 * @Param: a class Card
 * CardID, Name, Department, Type
 * @RetValue: prompt
 */
bool Database::insertCard(Card card) {
    // if (curAdmin == "")
    //     return "Not Logged In\n";  // Check if is logged in

    string command = "insert into card values(" + card.str() + ")";
    return !mysql_query(mysql, command.c_str());
}

/*
 * Insert an admin
 * @Param: a class Admin
 * AdminID, Passwd, Name, Contacts
 * @RetValue: prompt
 */
bool Database::insertAdmin(Admin admin) {
    // if (curAdmin == "")
    //     return "Not Logged In\n";  // Check if is logged in

    string command = "insert into admin values(" + admin.str() + ")";
    return !mysql_query(mysql, command.c_str());
}

/*
 * Delete a card
 * @Param: a class Admin
 * AdminID, Passwd, Name, Contacts
 * @RetValue: prompt
 */
bool Database::deleteCard(string CardID) {
    // if (curAdmin == "")
    //     return "Not Logged In\n";  // Check if is logged in

    string command = "delete from card where CardID = '" + CardID + "'";
    return !mysql_query(mysql, command.c_str());
}

/*
 *
 * @Param: attribute: attr to query; value: match value;
 * lower,upper: Set bound for number query;
 * orderby: order by attr; isAsc: use ASC or DESC
 * @RetValue: a ptr to a static vector which stores all the results
 */
vector<Book> *Database::queryBook(string attribute, string value,
                                  string orderby) {
    if (curAdmin == "")
        return NULL;  // Check if is logged in
    string command = "select * from book where " + attribute + " like '%" +
                     value + "%' order by " + orderby;
    mysql_query(mysql, command.c_str());
    MYSQL_RES *tmp = mysql_store_result(mysql);
    return res2Ptr(tmp);
}
vector<Book> *Database::queryBook(string attribute, double lower, double upper,
                                  string orderby, bool isAsc) {
    if (curAdmin == "")
        return NULL;  // Check if is logged in
    string command = "select * from book where " + attribute +
                     " >= " + to_string(lower) + " and " + attribute +
                     " <= " + to_string(upper) + " order by " + orderby +
                     (isAsc ? " ASC" : " DESC");
    mysql_query(mysql, command.c_str());
    return res2Ptr(mysql_store_result(mysql));
}
string Database::queryBook(string BookID) {
    if (curAdmin == "")
        return NULL;  // Check if is logged in
    string command = "select Title from book where BookID = " + BookID;
    mysql_query(mysql, command.c_str());
    MYSQL_RES *result = mysql_store_result(mysql);
    return mysql_fetch_row(result)[0];
}
/*
 * Convert MYSQL_RES to vector
 */
vector<Book> *Database::res2Ptr(MYSQL_RES *result) {
    if (result == NULL)
        return NULL;
    int rowcount = mysql_num_rows(result);  //获取行数
    // rowcount     = min(rowcount, 50);       //取前50条

    // Book *res     = new Book[rowcount + 1];
    static vector<Book> ret;
    ret.resize(rowcount);
    MYSQL_ROW row = NULL;
    for (int i = 0; i < rowcount; ++i) {
        row = mysql_fetch_row(result);  //获取行信息
        ret[i].reset(row[0], row[1], row[2], row[3], atoi(row[4]), row[5],
                     atoi(row[6]), atof(row[7]), atof(row[8]));
    }
    return &ret;
}
/*
 * Borrow book
 * @Param: BID for book to be borrowed, and CID for card to be used
 * @RetValue: prompt
 */
string Database::borBook(string BookID, string CardID, QWidget *ui) {
    if (curAdmin == "")
        return "Not Logged In\n";  // Check if is logged in

    string command = "select Stock from book where BookID = '" + BookID + "'";
    if (mysql_query(mysql, command.c_str()))  // Check Stock
        return "Book Info Error\n";
    MYSQL_RES *result = mysql_store_result(mysql);
    if (mysql_num_rows(result) == 0)  // Check if is emoty set
        return "Book Not Found\n";
    MYSQL_ROW row = mysql_fetch_row(result);  // Get Results
    if (stoi(row[0]) == 0)
        return "No Stock\n";

    QString quesIn =
        QString::fromStdString("确定要借 " + queryBook(BookID) + " 吗？");
    auto confirm = QMessageBox::question(ui, "", quesIn);
    // QMessageBox::warning(ui, "", QString::number(confirm));
    if (confirm == 65536)
        return "Canceled\n";

    command = "update book set Stock = Stock - 1 where BookID = '" + BookID +
              "'";  // Minus stock by 1
    if (mysql_query(mysql, command.c_str()))
        return "ERROR\n";

    string BorrowDate;
    time_t now = time(0);
    tm *lt     = localtime(&now);                          // Get local time
    BorrowDate = to_string((lt->tm_year + 1900) * 10000 +  // Convert
                           (lt->tm_mon + 1) * 100 + (lt->tm_mday));

    command = "insert into record values( '" + CardID + "',  '" + BookID +
              "', " + BorrowDate + ", NULL, '" + curAdmin + "')";
    if (mysql_query(mysql, command.c_str()))
        return "ERROR\n";
    return "Borrow Successfully\n";
}

/*
 * Return book
 * @Param: BID for book to be returned, and CID for card to be used
 * @RetValue: prompt
 */
string Database::retBook(string BookID, string CardID, QWidget *ui) {
    if (curAdmin == "")
        return "Not Logged In\n";  // Check if is logged in

    string command = "update book set Stock = Stock + 1 where BookID = '" +
                     BookID + "'";  //库存减一
    if (mysql_query(mysql, command.c_str()))
        return "Book Info Error\n";

    QString quesIn =
        QString::fromStdString("确定要还 " + queryBook(BookID) + " 吗？");
    auto confirm = QMessageBox::question(ui, "", quesIn);
    // QMessageBox::warning(ui, "", QString::number(confirm));
    if (confirm == 65536)
        return "Canceled\n";

    string RetDate;
    time_t now = time(0);
    tm *lt     = localtime(&now);                          // Get local time
    RetDate    = to_string((lt->tm_year + 1900) * 10000 +  // Convert
                        (lt->tm_mon + 1) * 100 + (lt->tm_mday));

    command = "update record set RetDate = " + RetDate + " where CardID = '" +
              CardID + "' and BookID = '" + BookID +
              "' and RetDate is NULL limit 1";
    if (mysql_query(mysql, command.c_str()))
        return "ERROR\n";
    return "Return Successfully\n";
}

/*
update record set 还期 = 20190802 where  卡号 = '0002' and 书号 = '001' and 还期
= 00000000 limit 1
*/
