#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QHash>
#include "stack.h"
#include "stack.cpp"
#include <QStringList>
#include <QList>
#include <QMessageBox>

template class Stack<QChar>;
template class Stack<float>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Stack<QChar> stack;
    Stack<float> numStack;
    QHash<QChar, int> operandsLevel;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
