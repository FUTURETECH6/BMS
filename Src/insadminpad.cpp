#include "insadminpad.h"
#include "Database.h"
#include "ui_insadminpad.h"
#include <QMessageBox>

extern Database myDB;

insAdminPad::insAdminPad(QWidget *parent)
    : QDialog(parent), ui(new Ui::insAdminPad) {
    ui->setupUi(this);
    ui->AdminID->setFocus();
}

insAdminPad::~insAdminPad() {
    delete ui;
}

void insAdminPad::on_buttonBox_accepted() {
    Admin admin;
    if (isEmpty()) {
        QMessageBox::warning(this, "", "请不要留有空栏");
        return;
    }
    if (ui->Passwd->text() != ui->Passwd2->text()) {
        QMessageBox::warning(this, "", "两次密码不匹配");
        return;
    }

    admin.AdminID  = ui->AdminID->text().toStdString();
    admin.Passwd   = ui->Passwd->text().toStdString();
    admin.Name     = ui->Name_2->text().toStdString();
    admin.Contacts = ui->Contacts->text().toStdString();

    if (myDB.insertAdmin(admin)) {
        QMessageBox::information(this, "", "创建成功");
        clearAll();
    } else
        QMessageBox::warning(this, "", "创建失败");
    return;
}

void insAdminPad::on_buttonBox_rejected() {
    this->close();
}

bool insAdminPad::isEmpty() {
    return ui->AdminID->text().length() < 1 ||
           ui->Passwd->text().length() < 1 || ui->Name_2->text().length() < 1 ||
           ui->Contacts->text().length() < 1;
}

void insAdminPad::clearAll() {
    ui->AdminID->clear();
    ui->Passwd->clear();
    ui->Passwd2->clear();
    ui->Name_2->clear();
    ui->Contacts->clear();
}