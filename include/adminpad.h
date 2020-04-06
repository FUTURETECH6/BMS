#ifndef ADMINPAD_H
#define ADMINPAD_H

#include <QDialog>

namespace Ui {
class AdminPad;
}

class AdminPad : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPad(QWidget *parent = nullptr);
    ~AdminPad();

public slots:
    void on_pushButton_clicked();

private:
    Ui::AdminPad *ui;
};

#endif // ADMINPAD_H
