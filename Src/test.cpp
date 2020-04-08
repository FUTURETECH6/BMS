#include "Database.h"
using namespace std;

int main() {
    Database myDB;
    myDB.login("root", "root");
    //导入测试

    myDB.borBook("00454990", "4353073", nullptr);
    myDB.insertBook("/Users/Ulysses/Documents/CODE/BMS/input.txt");

    Book b1("54882209", "Dictionary", "Mccoy Plaza", "Ports", 639,
            "Kimberly Shepherd", 22.0, 72, 54);
    Book b2("71966335", "Textbook", "Courtney Rapids", "Orchard", 738,
            "Shawn Warren", 38.0, 85, 14);
    Book b3("71966335", "Poem", "Christina Estate", "Well", 894,
            "Timothy Smith", 22.0, 61, 51);
    Book b4("71966335", "Textbook", "Weber Cliff", "Locks", 1214,
            "Debbie Murphy", 25.0, 76, 61);
    Book b5("34147011", "Textbook", "Gutierrez Hills", "Bridge", 838,
            "Martin Guerrero", 27.0, 94, 61);
    Book b6("03895402", "Poem", "Courtney Rapids", "Creek", 1114, "Scott Ward",
            48.0, 90, 46);
    Book b7("34147011", "History", "Brian Cliff", "Green", 946, "Nathan Adams",
            40.0, 60, 51);
    cout << myDB.insertBook(b1);
    cout << myDB.insertBook(b2);
    cout << myDB.insertBook(b3);
    cout << myDB.insertBook(b4);
    cout << myDB.insertBook(b5);
    cout << myDB.insertBook(b6);
    cout << myDB.insertBook(b7);

    Card c1("4353073", "Nicole Phillips DDS", "妈的 Science", "Teacher");
    Card c2("7879859", "Maria Castillo", "Management", "Student");
    Card c3("5208324", "Charles Shah", "Law", "Student");
    Card c4("4287118", "Derek Rice", "Education", "Student");

    cout << myDB.insertCard(c1);
    cout << myDB.insertCard(c2);
    cout << myDB.insertCard(c3);
    cout << myDB.insertCard(c4);

    string ID = "5208324";
    mysql_query(myDB.mysql,
                ("select * from card where CardID = " + ID).c_str());
    if (mysql_num_rows(mysql_store_result(myDB.mysql)) == 0)
        cout << "f0\n";
    else if (myDB.deleteCard(ID))
        cout << "f1\n";
    else
        cout << "f2\n";

    myDB.error_info();

    // vector<Book> *p = myDB.queryBook("Category", "Textbook");
    // vector<Book> *q = myDB.queryBook("Stock", 0, 100);

//     myDB.borBook("71966335", "5208324");
//     myDB.retBook("71966335", "5208324");

    // Card c1("7913389", "Amanda Bradshaw", "Computer Science", "G");
    // Card c2("7913389", "Amanda Bradshaw", "Computer Science", "Student");
    // cout << myDB.insertCard(c1);
    // cout << myDB.insertCard(c2);

    myDB.error_info();
    return 0;
}