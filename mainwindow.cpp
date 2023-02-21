#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QLineEdit>
#include <QDebug>
#include <QSqlDatabase>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtGui/QIcon>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QsqlError>
#include <QDebug>
#include <QSqlTableModel>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << QSqlDatabase::drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_budget_returnPressed()
{
    ui->budget->text();
    qDebug()<<"한달예산";
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox->currentText();
    qDebug()<<"종류";
}


void MainWindow::on_content_returnPressed()
{
    ui->content->text();
    qDebug()<<"내용";
}


void MainWindow::on_money_returnPressed()
{
    ui->money->text();
    qDebug()<<"돈";
}


void MainWindow::on_btn_add_clicked()
{

}

