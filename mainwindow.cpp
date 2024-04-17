#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPlainTextEdit>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

string searchText(const string& filename, const string& pattern) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return "";
    }

    regex reg(pattern);
    string matchedLines;
    string line;
    while (getline(file, line)) {
        if (regex_search(line, reg)) {
            matchedLines += "Matched line: " + line + "\n";  // Append the matched line
        }
    }
    file.close();
    return matchedLines;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    regularExpressionBox = ui->expressionSearch;
    regularExpressionBox->setPlaceholderText("Enter Regular Expression");
}

MainWindow::~MainWindow()
{
    delete ui;
}
string matchedLines;
QString fileContent;
void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Files"),
        "C:\\Users\\Lenovo L460\\Desktop\\TOA",
        "Text File (*.txt)"
        );

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file."));
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileContent.append(line + "\n");
    }

    file.close();


    // Call searchText function and set the output to textEdit_2
    string stdFilename = filename.toStdString();
    matchedLines = searchText(stdFilename, pattern);
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    // This slot is called when the copy action is available in textEdit
    // You can perform additional actions here if needed
}

void MainWindow::on_textEdit_2_copyAvailable(bool b)
{
    // This slot is called when the copy action is available in textEdit_2
    // You can perform additional actions here if needed
}

void MainWindow::on_pushButton_2_clicked()
{
    QString userInput = regularExpressionBox->toPlainText().trimmed();
    pattern = userInput.toStdString();
    qDebug()<<userInput;
    ui->textEdit_2->setPlainText(QString::fromStdString(matchedLines));
    ui->textEdit->setPlainText(fileContent);
}

