#include "adminpad.h"
#include "Database.h"
#include "insadminpad.h"
#include "insbookpad.h"
#include "inscardpad.h"
#include "ui_adminpad.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>

extern Database myDB;

AdminPad::AdminPad(QWidget *parent) : QDialog(parent), ui(new Ui::AdminPad) {
    ui->setupUi(this);
}

AdminPad::~AdminPad() {
    delete ui;
}

void AdminPad::on_pushButton_clicked() {
    if (ui->select->currentText() == "单本入库") {
        insBookPad i;
        i.exec();
    } else if (ui->select->currentText() == "批量入库") {
        QString pwd = QFileDialog::getOpenFileName(this, tr("Open file"), " ",
                                                   tr("All file(*.*)"));
        // myDB.insertBook(pwd.toStdString());
        QMessageBox::warning(this, "", pwd);
        this->close();
    } else if (ui->select->currentText() == "借书证办理") {
        insCardPad i;
        i.exec();
    } else if (ui->select->currentText() == "借书证删除") {
        string ID =
            QInputDialog::getText(this, "", "请输入借书证号").toStdString();
        mysql_query(myDB.mysql,
                    ("select * from card where CardID = " + ID).c_str());
        if (mysql_num_rows(mysql_store_result(myDB.mysql)) == 0)
            QMessageBox::warning(this, "", "没有找到这张卡");
        else if (myDB.deleteCard(ID))
            QMessageBox::information(this, "", "删除成功");
        else
            QMessageBox::warning(this, "", "删除失败");
    } else if (ui->select->currentText() == "添加管理员(需要root权限)") {
        if (myDB.curAdmin == "root") {
            insAdminPad i;
            i.exec();
        } else {
            QMessageBox::warning(this, "", "必须要用root身份进行操作");
        }
    }
}
