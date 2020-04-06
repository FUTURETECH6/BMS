#ifndef BORRET_H
#define BORRET_H

#include "Database.h"
#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class BorRet;
}

class BorRet : public QDialog {
    Q_OBJECT

  public:
    explicit BorRet(QWidget *parent = nullptr);
    ~BorRet();

  public slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

  private:
    Ui::BorRet *ui;
};

#endif  // BORRET_H
