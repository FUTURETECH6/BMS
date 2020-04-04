#include "inscardpad.h"
#include "Database.h"
#include "ui_inscardpad.h"
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>

extern Database myDB;

insCardPad::insCardPad(QWidget *parent)
    : QDialog(parent), ui(new Ui::insCardPad) {
    ui->setupUi(this);
}

insCardPad::~insCardPad() {
    delete ui;
}

void insCardPad::on_buttonBox_accepted() {
    Card card;
    if (isEmpty()) {
        QMessageBox::warning(this, "", "请不要留有空栏");
        return;
    }
    card.CardID     = ui->CardID->text().toStdString();
    card.Name       = ui->Name->text().toStdString();
    card.Department = ui->Department->text().toStdString();
    card.Type = ui->Type->currentText() == "学生" ? "Student" : "Teacher";
    if (myDB.insertCard(card)) {
        QMessageBox::information(this, "", "办理成功");
        clearAll();
    } else
        QMessageBox::warning(this, "", "办理失败");
    return;
}
void insCardPad::on_buttonBox_rejected() {
    this->close();
}

bool insCardPad::isEmpty() {
    return ui->CardID->text().length() < 1 || ui->Name->text().length() < 1 ||
           ui->Department->text().length() < 1;
}

void insCardPad::clearAll() {
    ui->CardID->clear();
    ui->Name->clear();
    ui->Department->clear();
}
