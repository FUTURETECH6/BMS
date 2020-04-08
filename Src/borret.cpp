#include "borret.h"
#include "Database.h"
#include "ui_borret.h"
#include <QInputDialog>
#include <QMessageBox>

extern Database myDB;

BorRet::BorRet(QWidget *parent) : QDialog(parent), ui(new Ui::BorRet) {
    ui->setupUi(this);
    ui->CardID->setFocus();
}

BorRet::~BorRet() {
    delete ui;
}

void BorRet::on_CardID_editingFinished() {
    refereshTable();
}
void BorRet::refereshTable() {
    delete itemList;
    itemList = new QStandardItemModel;
    itemList->setHorizontalHeaderItem(0, new QStandardItem("书号"));
    itemList->setHorizontalHeaderItem(1, new QStandardItem("书名"));
    itemList->setHorizontalHeaderItem(2, new QStandardItem("借书日期"));
    itemList->setHorizontalHeaderItem(3, new QStandardItem("还书日期"));
    itemList->setHorizontalHeaderItem(4, new QStandardItem("经手人"));
    ui->resTable->setModel(itemList);

    string command = "select BookID, Title, BorrowDate, RetDate, AdminID from "
                     "record natural join book where CardID = " +
                     ui->CardID->text().toStdString();

    mysql_query(myDB.mysql, command.c_str());
    MYSQL_RES *result = mysql_store_result(myDB.mysql);
    int rowNum        = mysql_num_rows(result);

    // QMessageBox::information(this, "",
    //                          "Find " + QString::number(rowNum) + " records");
    for (auto i = 0; i < rowNum; i++) {
        MYSQL_ROW row = mysql_fetch_row(result);
        itemList->setItem(i, 0,
                          new QStandardItem(QString::fromStdString(row[0])));
        itemList->setItem(i, 1,
                          new QStandardItem(QString::fromStdString(row[1])));
        itemList->setItem(i, 2,
                          new QStandardItem(QString::fromStdString(row[2])));
        if (string(row[3]) != string("1984-01-01"))
            itemList->setItem(
                i, 3, new QStandardItem(QString::fromStdString(row[3])));
        else
            itemList->setItem(i, 3, new QStandardItem("未还"));
        itemList->setItem(i, 4,
                          new QStandardItem(QString::fromStdString(row[4])));
    }
}

void BorRet::on_buttonBox_accepted() {
    if (ui->CardID->text().length() < 0) {
        QMessageBox::warning(this, "", "不能为空");
        return;
    }
    string CardID = ui->CardID->text().toStdString();
    mysql_query(myDB.mysql,
                ("select * from card where CardID = " + CardID).c_str());
    if (mysql_num_rows(mysql_store_result(myDB.mysql)) == 0) {
        QMessageBox::warning(this, "", "系统中没有这张借书证");
        return;
    }

    string BookID = QInputDialog::getText(this, "", "请输入书号").toStdString();
    if (BookID == "")
        return;

    if (ui->select->currentText() == "借书") {
        string prompt = myDB.borBook(BookID, CardID, this);
        if (prompt == "Book Info Error\n" || prompt == "Book Not Found\n")
            QMessageBox::warning(this, "", "查无此书");
        else if (prompt == "No Stock\n")
            QMessageBox::warning(this, "", "对不起，本书暂时无库存");
        else if (prompt == "ERROR\n")
            QMessageBox::warning(this, "", "操作错误");
        else if (prompt == "Borrow Successfully\n")
            QMessageBox::warning(this, "", "借阅成功！");
    } else {
        string prompt = myDB.retBook(BookID, CardID, this);
        if (prompt == "Book Info Error\n")
            QMessageBox::warning(this, "", "查无此书");
        else if (prompt == "ERROR\n")
            QMessageBox::warning(this, "", "操作错误");
        else if (prompt == "Return Successfully\n")
            QMessageBox::warning(this, "", "还书成功！");
    }
    refereshTable();
}

void BorRet::on_buttonBox_rejected() {
    this->close();
}
