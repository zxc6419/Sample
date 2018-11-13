#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class MainWindow;
}

class Task;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addTask();
    void removeTask(Task* task);

private:
    Ui::MainWindow *ui;
    QVector<Task*> tasks_;
};

#endif // MAINWINDOW_H
