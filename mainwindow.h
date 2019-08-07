#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

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

signals:
    void countdownFinished();

private:
    void setInfoText();
    void updateCountdown();

    QTimer *timer;

    Ui::MainWindow *ui;
    DatabaseManager *database;

    int timerMinsLeft;
    int timerSecsLeft;
};

#endif // MAINWINDOW_H
