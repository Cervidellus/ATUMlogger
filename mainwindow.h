#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DatabaseManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setInfoText();

    Ui::MainWindow *ui;
    DatabaseManager *database;
};

#endif // MAINWINDOW_H
