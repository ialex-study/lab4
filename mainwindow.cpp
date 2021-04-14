#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , stack()
    , numStack()
    , operandsLevel()
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    operandsLevel['+'] = 1;
    operandsLevel['-'] = 1;
    operandsLevel['*'] = 2;
    operandsLevel['/'] = 2;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // count result
    QString input = ui->lineEdit->text();
    QString output = "";
    QString number = "";
    for(int i = 0; i < input.size(); i++)
    {
        QChar* tmp = new QChar(input[i]);
        if(tmp->digitValue() != -1 || *tmp == ".") {
            number += *tmp;
        }
        else {
            if(number != "") {
                output += number;
                output += ", ";
                number = "";
            }
            if(*tmp == '(')
                stack.add(tmp);
            else if(*tmp == ')') {
                QChar* executed_temp = stack.remove();
                while(*executed_temp != '(') {
                    output += *executed_temp;
                    output += ", ";
                    executed_temp = stack.remove();
                }
            }
            else {
                QChar* last_item = stack.remove();
                if(last_item == nullptr) {
                    // nothing
                }
                else if(operandsLevel[*last_item] >= operandsLevel[*tmp]) {
                    output += *last_item;
                    output += ", ";
                }
                else {
                    stack.add(last_item);
                }
                stack.add(tmp);
            }
        }
    }
    if(number != "") {
        output += number;
        output += ", ";
    }
    QChar* last_item = stack.remove();
    while(last_item != nullptr) {
        output += *last_item;
        output += ", ";
        last_item = stack.remove();
    }
    output.remove(output.size() - 2, 2);
    ui->lineEdit_3->setText(output);

    QStringList parts = output.split(", ");
    for(int i = 0; i < parts.size(); i++)
    {
        QString tmp = parts[i];
        if(operandsLevel.keys().contains(tmp[0])) {
            float* num1 = numStack.remove();
            float* num2 = numStack.remove();
            float *res;

            if(num1 == nullptr || num2 == nullptr) {
                QMessageBox box;
                box.setText("Проверьте корректность полей");
                box.exec();
                while(stack.size() != 0)
                    delete stack.remove();
                while(numStack.size() != 0)
                    delete numStack.remove();
                return;
            }

            if(tmp == "+") {
                res = new float(*num2 + *num1);
            }
            if(tmp == "-") {
                res = new float(*num2 - *num1);
            }
            if(tmp == "*") {
                res = new float(*num2 * *num1);
            }
            if(tmp == "/") {
                res = new float(*num2 / *num1);
            }

            numStack.add(res);
        }
        else {
            numStack.add(new float(tmp.toFloat()));
        }
    }
    float* res = numStack.remove();
    QString outputNum;
    outputNum.setNum(*res);
    ui->lineEdit_2->setText(outputNum);
}
