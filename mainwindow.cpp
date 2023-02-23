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
    ui->loginstack->setCurrentIndex(0);

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
    member_name;

    QString type = ui->comboBox->currentText();

    QString content = ui->content->text();

    QString money = ui->money->text();

    QString date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    qDebug()<<date;

    QString qry;
    qry = QString("INSERT INTO account(name, type, content, money, date) VALUES('%1', '%2', '%3', '%4', '%5')")
            .arg(member_name)
            .arg(ui->comboBox->currentText())
            .arg(ui->content->text())
            .arg(ui->money->text())
            .arg(date);
    QSqlQuery query;
    query.prepare(qry);
    query.exec(qry);
    qDebug()<<member_name;
    ui->listWidget->addItem(date+"   "+member_name+"   "+type+"   "+content+"   "+money);
    ui->content->clear();
    ui->money->clear();
    ui->comboBox->setCurrentIndex(0);
}


void MainWindow::on_in_budget_returnPressed()
{
    QString budget_money = ui->in_budget->text();
    int budgetmoney = budget_money.toInt();
    qDebug()<<budgetmoney;
    ui->budget->setText(budget_money);
    ui->in_budget->clear();
    qDebug()<<"한달예산";
    QSqlQuery qry;
    qry.prepare("SELECT SUM(money) FROM account");
    if(qry.exec())
    {
        while(qry.next())
        {
            int summoney = qry.value(0).toInt();    // 돈
            qDebug()<<summoney;
            QString sum_money = QString::number(summoney);
            ui->month_money->setText(sum_money);
            int i = budgetmoney - summoney;
            QString in_change =  QString::number(i);
            qDebug()<<in_change;
            ui->change->setText(in_change);
        }
    }
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

    if(id=="" or pw=="")
    {
        QMessageBox::information(this, "알림", "모두 입력해주세요.");
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT * FROM member WHERE id = :id");
    qry.bindValue(":id", id);
    if(qry.exec())
    {
        while(qry.next())
        {
            QString member_id = qry.value(0).toString();      // 아이디
            QString member_pw = qry.value(1).toString();      // 비밀번호
            member_name = qry.value(2).toString();    // 이름
            if(id != member_id or pw != member_pw)
            {
                QMessageBox::information(this, "알림", "아이디 또는 비밀번호를 확인해주세요.");
            }
            else if(id==member_id and pw==member_pw)
            {
                QMessageBox::information(this, "알림", member_name+" 로그인 완료");

                ui->id->clear();
                ui->pw->clear();
                ui->loginstack->setCurrentIndex(1);
            }
        }
    }

    QSqlQuery query;
    query.prepare("SELECT SUM(money) FROM account WHERE date BETWEEN '2023-02-19' AND '2023-02-25'");
    if(query.exec())
    {
        while(query.next())
        {
            int weeksum = query.value(0).toInt();
            qDebug()<<weeksum;
            QString weekmoney = QString::number(weeksum);
            ui->week4->setText(weekmoney);
            QString num = QString::number(0);
            ui->week1->setText(num);
            ui->week2->setText(num);
            ui->week3->setText(num);
            ui->week5->setText(num);
        }
    }
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    ui->listWidget->clear();
    QString click_date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QSqlQuery qry;
    qry.prepare("SELECT * FROM account WHERE date = :click_date");
    qry.bindValue(":click_date", click_date);
    if(qry.exec())
    {
        while(qry.next())
        {
            QString in_name = qry.value(0).toString();     // 이름
            QString in_type = qry.value(1).toString();     // 유형
            QString in_content = qry.value(2).toString();  // 내용
            QString in_money = qry.value(3).toString();    // 돈
            QString in_date = qry.value(4).toString();     // 날짜
            //qDebug()<<in_type<<in_content<<in_money<<in_date;
            ui->listWidget->addItem(in_date+"   "+in_name+"   "+in_type+"   "+in_content+"   "+in_money);
        }
    }
}


void MainWindow::on_btn_login_2_clicked()
{
    ui->loginstack->setCurrentIndex(0);
    QMessageBox::information(this, "알림", "로그아웃 되었습니다");
}



