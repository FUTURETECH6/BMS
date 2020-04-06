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

    string BookID = "";
    while (BookID == "")
        BookID = QInputDialog::getText(this, "", "请输入书号").toStdString();

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
}

void BorRet::on_buttonBox_rejected() {
    this->close();
}
