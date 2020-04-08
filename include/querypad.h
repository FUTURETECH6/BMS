#ifndef QUERYPAD_H
#define QUERYPAD_H

#include "Database.h"
#include <QDialog>
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
    void on_addAttr_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

  private:
    void resetTable();
    void displayLine(int &, Book &);
    string strMap(QString &);

    Ui::QueryPad *ui;
    QStandardItemModel *consList;
    QStandardItemModel *itemList;
    std::vector<std::tuple<std::string, std::string, std::string>> attrList;
};

#endif  // QUERYPAD_H
