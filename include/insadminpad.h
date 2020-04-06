#ifndef INSADMINPAD_H
#define INSADMINPAD_H

#include <QDialog>

namespace Ui {
class insAdminPad;
}

class insAdminPad : public QDialog {
    Q_OBJECT

  public:
    explicit insAdminPad(QWidget *parent = nullptr);
    ~insAdminPad();

  public slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

  private:
    bool isEmpty();
    void clearAll();
    Ui::insAdminPad *ui;
};

#endif  // INSADMINPAD_H
