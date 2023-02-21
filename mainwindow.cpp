#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QLineEdit>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtGui/QIcon>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QsqlError>
#include <QSqlTableModel>
#include <QDate>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool log_check = false;
    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
             db.setHostName("localhost");
             db.setDatabaseName("sy");
             db.setUserName("root");
             db.setPassword("00000000");

             if (!db.open()) {
                 qDebug() << "Database error occurred";
              }
             else {
                 qDebug() << "Database open Success";
             }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString type = ui->comboBox->currentText();
    qDebug()<<type;
    qDebug()<<"종류";
}


void MainWindow::on_btn_add_clicked()
{
    QString type = ui->comboBox->currentText();

    QString content = ui->content->text();

    QString money = ui->money->text();

    QString date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    qDebug()<<date;

    QString qry;
    qry = QString("INSERT INTO account(type, content, money, date) VALUES('%1', '%2', '%3', '%4')")
            .arg(ui->comboBox->currentText())
            .arg(ui->content->text())
            .arg(ui->money->text())
            .arg(date);
    QSqlQuery query;
    query.prepare(qry);
    query.exec(qry);
    ui->listWidget->addItem(date+"   "+type+"   "+content+"   "+money);
    ui->content->clear();
    ui->money->clear();
    ui->comboBox->setCurrentIndex(0);
}


void MainWindow::on_in_budget_returnPressed()
{
    ui->in_budget->text();
    ui->budget->setText(ui->in_budget->text());
    //ui->in_budget->clear();
    qDebug()<<"한달예산";
}


void MainWindow::on_content_editingFinished()
{
    QString content = ui->content->text();
    qDebug()<<content;
    qDebug()<<"내용";
}


void MainWindow::on_money_editingFinished()
{
    QString money = ui->money->text();
    qDebug()<<money;
    qDebug()<<"돈";
}


void MainWindow::on_btn_login_clicked()
{
    QString id = ui->id->text();
    QString pw = ui->pw->text();

    ui->btn_login->setText("로그아웃");
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    //ui->listWidget->clear();
    QString click_date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    //qDebug()<<click_date;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM account");
//    if (!qry.isActive())
//    {
//        qDebug<< "Query Error" + qry.lastError().text();
//    }
//    else while (qry.next())
//    {
//        QString in_type = qry.value(0).toString();
//        qDebug<<QString("%1").arg(in_type);
//    }
    if(qry.exec()){
        while(qry.next()){
            //QString name = qry.value(0).toString();
            QString in_type = qry.value(0).toString();
            QString in_content = qry.value(1).toString();
            QString in_money = qry.value(2).toString();
            QString in_date = qry.value(3).toString();
            qDebug()<<in_type<<in_content<<in_money<<in_date;
            //ui->listWidget->addItem(in_date+"   "+in_type+"   "+in_content+"   "+in_money);
        }
    }
//    qDebug()<<in_type<<in_content<<in_money<<in_date;
//    ui->listWidget->addItem(in_date+"   "+in_type+"   "+in_content+"   "+in_money);
}

