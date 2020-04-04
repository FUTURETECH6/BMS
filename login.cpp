#include "login.h"
#include "ui_login.h"
#include <QLabel>
#include <QMessageBox>
#include <QString>

extern Database myDB;
extern QLabel *ptrToAdminLable;

Login::Login(QWidget *parent) : QDialog(parent), ui(new Ui::Login) {
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}

void Login::on_buttonBox_accepted() {
    string AdminID = ui->input_AdminID->text().toStdString();
    string Passwd  = ui->input_Passwd->text().toStdString();
    if (myDB.login(AdminID, Passwd)) {
        QMessageBox::information(this, "", "登陆成功");
        ptrToAdminLable->setText(QString::fromStdString(myDB.curAdmin));
        this->close();
    } else
        QMessageBox::warning(this, "", "账号或密码错误");
}

void Login::on_buttonBox_rejected() {
    this->close();
}

// addBook::addBook(Model &model, QWidget *parent ) :
//    QDialog(parent),
//    ui(new Ui::addBook),
//    pModel(&model)
//{
//    ui->setupUi(this);

//    QRegExp rxS("^(0|[1-9][0-9]*)$"); //正则对象，只能输入正整数
//    QRegExpValidator *validatorStock = new QRegExpValidator(rxS, this);
//    //动态创建正则检验器并绑定正则对象
//    /*
//     * 这里new的指针，不用delete释放内存，因为Qt会自动delete掉。
//     * 前提1：new的必须是QObject的子类.前提2：new时必须设定了父对象（本例中的this）
//    */
//    this->ui->lineEdit_stock->setValidator(validatorStock);
//    //设置文本框的检验器

//    QRegExp rxP("^[0-9]+(.[0-9]{2})?$");     //正则表达式，只能输入正浮点数
//    QRegExpValidator *validatorPrice = new QRegExpValidator(rxP, this);
//    this->ui->lineEdit_price->setValidator(validatorPrice);

//    this->ui->lineEdit_ISBN->setFocus();    //使ISBN文本编辑框获得焦点

//}
