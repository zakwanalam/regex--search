#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <string>
#include <iostream>

using namespace std;
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
    void on_pushButton_clicked();

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_2_copyAvailable(bool b);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTextEdit *regularExpressionBox;
    string pattern;
};
#endif // MAINWINDOW_H
