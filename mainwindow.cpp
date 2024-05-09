#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

QString searchText(const QString& filePath, const QString& pattern) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << file.errorString();
        return QString(); // Return an empty QString on error
    }

    QTextStream in(&file);
    QString matchedLines;
    QRegularExpression emailRegex(pattern);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatchIterator matchIterator = emailRegex.globalMatch(line);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            matchedLines.append(match.captured(0)).append("\n"); // Append matched email addresses to the result
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
QString matchedLines;
QString fileContent;
QString stdFilename;
void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Files"),
        "C:/Users/Zakwan Alam/OneDrive/Desktop/regex--search",
        "Text File (*.txt)"
        );

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No file opened"));
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileContent.append(line + "\n");
    }

    file.close();
    // Call searchText function and set the output to textEdit_2
    stdFilename = filename;
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->search_output->clear();
    ui->file_contents->clear();
    QString userInput = ui->expressionSearch->toPlainText();
    matchedLines = searchText(stdFilename, userInput);
    ui->search_output->setPlainText(matchedLines);
    ui->file_contents->setPlainText(fileContent);
}

