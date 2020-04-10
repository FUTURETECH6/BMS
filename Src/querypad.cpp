#include "querypad.h"
#include "ui_querypad.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <regex>
#include <vector>

#include <QWidget>

extern Database myDB;
extern QWidget *queryPadUi;

QueryPad::QueryPad(QWidget *parent) : QDialog(parent), ui(new Ui::QueryPad) {
    consList = new QStandardItemModel;
    // itemList       = new QStandardItemModel;
    consList->setHorizontalHeaderItem(0, new QStandardItem("属性"));
    consList->setHorizontalHeaderItem(1, new QStandardItem("条件"));
    ui->setupUi(this);
}

QueryPad::~QueryPad() {
    delete ui;
}

void QueryPad::on_addAttr_clicked() {
    QString raw_attr  = ui->attr->currentText();
    QString raw_value = ui->attrValue->text();
    string attr       = strMap(raw_attr);
    string value      = raw_value.toStdString();
    if (attr == "Year" || attr == "Price") {
        regex sep("\\s*-\\s*|\\s*-\\s*|\\s*,\\s*|\\s*，\\s*");
        sregex_token_iterator p(value.begin(), value.end(), sep, -1);
        sregex_token_iterator end;
        // vector<std::string> vec;
        // while (p != end)
        //     vec.emplace_back(*p++);
        // QMessageBox::warning(this, "", QString::number(vec.size()));
        // return;
        string lower = *p++;
        string upper;
        if (p != end)
            upper = *p;
        else {
            QMessageBox::warning(this, "", "参数不足！");
            return;
        }
        // QMessageBox::warning(this, "", QString::fromStdString(lower));
        // QMessageBox::warning(this, "", QString::fromStdString(upper));
        attrList.push_back(make_tuple(attr, lower, upper));
    } else {
        attrList.push_back(make_tuple(attr, value, ""));
    }
    ui->attrTable->setModel(consList);
    consList->setItem(attrList.size() - 1, 0, new QStandardItem(raw_attr));
    consList->setItem(attrList.size() - 1, 1, new QStandardItem(raw_value));
}

void QueryPad::on_buttonBox_accepted() {
    if (attrList.size() == 0) {
        QMessageBox::warning(this, "", "还未添加查询条件");
        return;
    }
    QString raw_attr    = ui->attr->currentText();
    QString raw_orderby = ui->orderby->currentText();
    string attr         = strMap(raw_attr);
    string orderby      = strMap(raw_orderby);

    queryPadUi = this;
    vector<Book> *ptr;
    if (ui->sortWay->currentText() == "升序")
        ptr = myDB.queryBookMul(attrList, orderby, 1);
    if (ui->sortWay->currentText() == "降序")
        ptr = myDB.queryBookMul(attrList, orderby, 0);

    attrList.resize(0);
    delete consList;
    consList = new QStandardItemModel;
    consList->setHorizontalHeaderItem(0, new QStandardItem("属性"));
    consList->setHorizontalHeaderItem(1, new QStandardItem("条件"));
    ui->attrTable->setModel(consList);

    // if (attr == "Year" || attr == "Price") {
    //     double lower = QInputDialog::getDouble(this, "", "请输入区间下界");
    //     double upper = QInputDialog::getDouble(this, "", "请输入区间上界");
    //     ptr          = myDB.queryBook(attr, lower, upper, orderby);
    // } else {
    //     string keyword =
    //         QInputDialog::getText(this, "", "请输入关键字").toStdString();
    //     ptr = myDB.queryBook(attr, keyword, orderby);
    // }

    if (ptr->size() == 0) {
        QMessageBox::warning(this, "", "没有找到你要的书");
        return;
    }
    delete itemList;
    resetTable();
    for (auto i = 0; i < (int)ptr->size(); i++) {
        displayLine(i, (*ptr)[i]);
    }
}
void QueryPad::on_buttonBox_rejected() {
    this->close();
}

void QueryPad::displayLine(int &row, Book &book) {
    itemList->setItem(row, 0,
                      new QStandardItem(QString::fromStdString(book.BookID)));
    itemList->setItem(row, 1,
                      new QStandardItem(QString::fromStdString(book.Category)));
    itemList->setItem(row, 2,
                      new QStandardItem(QString::fromStdString(book.Title)));
    itemList->setItem(row, 3,
                      new QStandardItem(QString::fromStdString(book.Press)));
    itemList->setItem(row, 4, new QStandardItem(QString::number(book.Year)));
    itemList->setItem(row, 5,
                      new QStandardItem(QString::fromStdString(book.Author)));
    itemList->setItem(row, 6, new QStandardItem(QString::number(book.Price)));
    itemList->setItem(row, 7, new QStandardItem(QString::number(book.Total)));
    itemList->setItem(row, 8, new QStandardItem(QString::number(book.Stock)));
}

string QueryPad::strMap(QString &rawQ) {
    string raw = rawQ.toStdString();
    if (raw == "类别")
        return "Category";
    else if (raw == "书名")
        return "Title";
    else if (raw == "出版社")
        return "Press";
    else if (raw == "年份")
        return "Year";
    else if (raw == "作者")
        return "Author";
    else if (raw == "价格")
        return "Price";
    return "";
}

void QueryPad::resetTable() {
    itemList = new QStandardItemModel;
    itemList->setHorizontalHeaderItem(0, new QStandardItem("书号"));
    itemList->setHorizontalHeaderItem(1, new QStandardItem("类别"));
    itemList->setHorizontalHeaderItem(2, new QStandardItem("书名"));
    itemList->setHorizontalHeaderItem(3, new QStandardItem("出版社"));
    itemList->setHorizontalHeaderItem(4, new QStandardItem("年份"));
    itemList->setHorizontalHeaderItem(5, new QStandardItem("作者"));
    itemList->setHorizontalHeaderItem(6, new QStandardItem("价格"));
    itemList->setHorizontalHeaderItem(7, new QStandardItem("总藏书量"));
    itemList->setHorizontalHeaderItem(8, new QStandardItem("库存"));
    ui->resTable->setModel(itemList);
}
