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

    void on_budget_returnPressed();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_content_returnPressed();

    void on_money_returnPressed();

    void on_btn_add_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H