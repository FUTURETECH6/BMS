#include "insbookpad.h"
#include "Database.h"
#include "ui_insbookpad.h"
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QString>

extern Database myDB;

insBookPad::insBookPad(QWidget *parent)
    : QDialog(parent), ui(new Ui::insBookPad) {
    ui->setupUi(this);

    QRegExp rgInt("^(0|[1-9][0-9]*)$");  //正则对象，只能输入正整数
    QRegExpValidator *vaInt =
        new QRegExpValidator(rgInt, this);  //动态创建正则检验器并绑定正则对象
    this->ui->Year->setValidator(vaInt);   //设置文本框的检验器
    this->ui->Total->setValidator(vaInt);  //设置文本框的检验器

    QRegExp rgFloat("^[0-9]+(.[0-9]{2})?$");  //正则表达式，只能输入正浮点数
    QRegExpValidator *vaFloat = new QRegExpValidator(rgFloat, this);
    this->ui->Price->setValidator(vaFloat);

    //    QRegExp rgNonEmpty("\\S");
    //    QRegExpValidator *vaStr = new QRegExpValidator(rgNonEmpty, this);
    //    this->ui->BookID->setValidator(vaStr);
    //    this->ui->Category->setValidator(vaStr);
    //    this->ui->Title->setValidator(vaStr);
    //    this->ui->Press->setValidator(vaStr);
    //    this->ui->Author->setValidator(vaStr);
}

insBookPad::~insBookPad() {
    delete ui;
}

void insBookPad::on_buttonBox_accepted() {
    Book book;
    if (isEmpty()) {
        QMessageBox::warning(this, "", "请不要留有空栏");
        return;
    }
    book.BookID   = ui->BookID->text().toStdString();
    book.Category = ui->Category->text().toStdString();
    book.Title    = ui->Title->text().toStdString();
    book.Press    = ui->Press->text().toStdString();
    book.Year     = ui->Year->text().toInt();
    book.Price    = ui->Price->text().toDouble();
    book.Author   = ui->Author->text().toStdString();
    book.Total    = ui->Total->text().toInt();
    book.Stock    = ui->Total->text().toInt();
    if (myDB.insertBook(book)) {
        QMessageBox::information(this, "", "入库成功");
        clearAll();
    } else
        QMessageBox::warning(this, "", "入库失败");
    return;
}

void insBookPad::on_buttonBox_rejected() {
    this->close();
}

bool insBookPad::isEmpty() {
    return ui->BookID->text().length() < 1 ||
           ui->Category->text().length() < 1 ||
           ui->Title->text().length() < 1 || ui->Press->text().length() < 1 ||
           ui->Year->text().length() < 1 || ui->Price->text().length() < 1 ||
           ui->Author->text().length() < 1 || ui->Total->text().length() < 1;
}

void insBookPad::clearAll() {
    ui->BookID->clear();
    ui->Category->clear();
    ui->Title->clear();
    ui->Press->clear();
    ui->Year->clear();
    ui->Price->clear();
    ui->Author->clear();
    ui->Total->clear();
}
