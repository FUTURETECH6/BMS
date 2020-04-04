#ifndef QUERYPAD_H
#define QUERYPAD_H

#include <QDialog>
#include "Database.h"
// #include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class QueryPad;
}

class QueryPad : public QDialog {
    Q_OBJECT

  public:
    explicit QueryPad(QWidget *parent = nullptr);
    ~QueryPad();

  public slots:
    void on_pushBottoon_accepted();
    void on_pushBottoon_rejected();

  private:
    void resetTable();
    void displayLine(int &, Book &);
    string strMap(QString &);

    Ui::QueryPad *ui;
    QStandardItemModel *itemList;
};

#endif  // QUERYPAD_H
