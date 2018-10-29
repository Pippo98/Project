#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void serial_received();

    void on_pushButton_clicked();

    void on_radioButton_clicked(bool checked);

    void serial_actions();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
