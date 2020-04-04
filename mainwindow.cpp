#include "mainwindow.h"
#include "adminpad.h"
#include "login.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>

extern Database myDB;
QLabel *ptrToAdminLable;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ptrToAdminLable = ui->CurAdmin;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_BTN_Login_clicked() {
    Login l;
    l.exec();
}
void MainWindow::on_BTN_Logout_clicked() {
    if (myDB.curAdmin != "") {
        myDB.logout();
        ui->CurAdmin->setText("N/A");
        QMessageBox::information(this, "", "登出成功");
    } else
        QMessageBox::warning(this, "", "未登录");
}

void MainWindow::on_BTN_Admin_clicked() {
    if (myDB.curAdmin != "") {
        AdminPad a;
        a.exec();
    } else
        QMessageBox::warning(this, "", "未登录");
}

void MainWindow::on_BTN_Query_clicked() {
    if (myDB.curAdmin != "") {
        AdminPad a;
        a.exec();
    } else
        QMessageBox::warning(this, "", "未登录");
}
