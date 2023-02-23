#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QCheckBox>
#include <QComboBox>
#include <QList>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_btn_add_clicked();

    void on_in_budget_returnPressed();

    void on_content_editingFinished();

    void on_money_editingFinished();

    void on_btn_login_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_btn_login_2_clicked();


private:
    Ui::MainWindow *ui;
    QString member_name;
};
#endif // MAINWINDOW_H
