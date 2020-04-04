#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void on_BTN_Login_clicked();
    void on_BTN_Logout_clicked();
    void on_BTN_Admin_clicked();
        void on_BTN_Query_clicked();
    //    void on_BTN_BorRet_clicked();

  private:
    Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
