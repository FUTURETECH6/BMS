#ifndef INSBOOKPAD_H
#define INSBOOKPAD_H

#include <QDialog>

namespace Ui {
class insBookPad;
}

class insBookPad : public QDialog {
    Q_OBJECT

  public:
    explicit insBookPad(QWidget *parent = nullptr);
    ~insBookPad();

  public slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

  private:
    void clearAll();
    bool isEmpty();

    Ui::insBookPad *ui;
};

#endif  // INSBOOKPAD_H
