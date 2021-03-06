#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QInputDialog>

#include "task.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatus()
{
    int completedCount = 0;
    for (auto t : tasks_) {
        if (t->isCompleted()) {
            completedCount++;
        }
    }

    int todoCount = tasks_.size()-completedCount;
    ui->statusLabel->setText(QString(tr("Status: %1 todo / %2 completed"))
                             .arg(todoCount)
                             .arg(completedCount));
}

void MainWindow::addTask()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("Untitled task"),
                                         &ok);
    if (ok && !name.isEmpty()) {
        auto task = new Task(name);
        tasks_.append(task);
        ui->tasksLayout->addWidget(task);

        // When new task, immediately connecting
        // the *remove* signal/slot
        connect(task, &Task::removed, this, &MainWindow::removeTask);

        connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);

        updateStatus();
    }
}

void MainWindow::removeTask(Task *task)
{
    tasks_.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    qDebug() << task->parent()->objectName();
    task->setParent(nullptr);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task* /*task*/)
{
    updateStatus();
}
