#ifndef INSCARDPAD_H
#define INSCARDPAD_H

#include <QDialog>

namespace Ui {
class insCardPad;
}

class insCardPad : public QDialog {
    Q_OBJECT

  public:
    explicit insCardPad(QWidget *parent = nullptr);
    ~insCardPad();

  public slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

  private:
    bool isEmpty();
    void clearAll();

    Ui::insCardPad *ui;
};

#endif  // INSCARDPAD_H
