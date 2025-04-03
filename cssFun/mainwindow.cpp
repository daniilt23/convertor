#include <QMessageBox>
#include <QGuiApplication>
#include <QClipboard>
#include <string.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "validation.h"
#include "memory.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxFrom->addItem("10", DEC);
    ui->comboBoxFrom->addItem("2", BIN);
    ui->comboBoxFrom->addItem("16", HEX);
    ui->comboBoxTo->addItem("2", BIN);
    ui->comboBoxTo->addItem("10", DEC);
    ui->comboBoxTo->addItem("16", HEX);
    ui->errorLabel->setFixedSize(345, 27);
    ui->label_2->setFixedSize(345, 27);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::transformButton);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearButton);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::copyButton);
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::swapButton);
    connect(ui->entryLine, &QLineEdit::textChanged, this, &MainWindow::entryLine);
    connect(ui->comboBoxFrom, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateSysFromTo);
    connect(ui->comboBoxTo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateSysFromTo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::entryLine()
{
    Param* param = (Param*)malloc(sizeof(Param));
    context.sysFrom = (enum Sys)(ui->comboBoxFrom->currentData().toInt());
    context.sysTo = (enum Sys)(ui->comboBoxTo->currentData().toInt());

    std::string str = ui->entryLine->text().toStdString();
    const char* cstr = str.c_str();
    param->strValue = cstr;

    doOperation(Validation, &context, param);
    updateInterface(param);
}

void MainWindow::transformButton()
{
    context.sysFrom = (enum Sys)(ui->comboBoxFrom->currentData().toInt());
    context.sysTo = (enum Sys)(ui->comboBoxTo->currentData().toInt());
    buttonPressed = true;
    Param* param = (Param*)malloc(sizeof(Param));
    std::string str = ui->entryLine->text().toStdString();
    const char* cstr = str.c_str();
    param->strValue = cstr;
    doOperation(Validation, &context, param);
    doOperation(Transform, &context, param);
    updateInterface(param);
    free(param);
    buttonPressed = false;
}

void MainWindow::updateInterface(Param* param)
{
    context.sysFrom = (enum Sys)(ui->comboBoxFrom->currentData().toInt());
    context.sysTo = (enum Sys)(ui->comboBoxTo->currentData().toInt());
    std::string str = ui->entryLine->text().toStdString();
    const char* cstr = str.c_str();
    param->strValue = cstr;
    switch(context.status)
    {
    case CORRECT:
        setDefaultInterface();
        if (buttonPressed)
            ui->outputLine->setText(QString(context.newValue));
        break;
    case INCORRECT_DATA:
        if (buttonPressed)
            incorrectErrorDataNotification();
        else
            incorrectSysError();
        break;
    case MIN_LEN:
        if (buttonPressed)
            maxLenErrorNotification();
        else
            minLenError();
        break;
    case MAX_LEN:
        if (buttonPressed)
            maxLenErrorNotification();
        else
            maxLenError();
        break;
    case EMPTY_LINE:
        emptyLineNotification();
        break;
    }
}

void MainWindow::updateSysFromTo()
{
    context.sysFrom = (enum Sys)(ui->comboBoxFrom->currentData().toInt());
    context.sysTo = (enum Sys)(ui->comboBoxTo->currentData().toInt());

    Param* param = (Param*)malloc(sizeof(Param));
    std::string str = ui->entryLine->text().toStdString();
    const char* cstr = str.c_str();
    param->strValue = cstr;

    doOperation(Validation, &context, param);
    updateInterface(param);

    free(param);
}

void MainWindow::clearButton()
{
    Param* param = (Param*)malloc(sizeof(Param));
    doOperation(Clear, &context, param);
    ui->outputLine->setText(QString(context.newValue));
    free(param);
}

void MainWindow::swapButton()
{
    Param* param = (Param*)malloc(sizeof(Param));
    std::string str = ui->entryLine->text().toStdString();
    const char* cstr = str.c_str();
    param->strValue = cstr;
    std::string str2 = ui->outputLine->text().toStdString();
    const char* cstr2 = str2.c_str();
    context.newValue = cstr2;
    context.sysFrom = (enum Sys)(ui->comboBoxFrom->currentData().toInt());
    context.sysTo = (enum Sys)(ui->comboBoxTo->currentData().toInt());
    doOperation(Swap, &context, param);
    updateAll(&context, param);
    free(param);
}

void MainWindow::updateAll(AppContext* context, Param* param)
{
    ui->entryLine->setText(QString::fromStdString(param->strValue));
    ui->outputLine->setText(QString::fromStdString(context->newValue));
    ui->comboBoxFrom->setCurrentIndex(ui->comboBoxFrom->findData(context->sysFrom));
    ui->comboBoxTo->setCurrentIndex(ui->comboBoxTo->findData(context->sysTo));
}

void MainWindow::copyButton()
{
    QString copyText = ui->outputLine->text();
    QGuiApplication::clipboard()->setText(copyText);
}

void MainWindow::setDefaultInterface()
{
    ui->errorLabel->clear();
    ui->errorLabel->setStyleSheet("QLabel { background: #2C3E50;}");
}

void MainWindow::incorrectSysError()
{
    ui->errorLabel->setText("Число содержит символы, отсутствующие в выбранной системе счисления");
    ui->errorLabel->setStyleSheet("QLabel { color : black; background-color : red; }");
}

void MainWindow::incorrectErrorDataNotification()
{
    QMessageBox::critical(this, "Ошибка", "<div style='color: white;'>" "Вы не можете перевести число, содержащее данные символы" "</div>");
}

void MainWindow::minLenError()
{
    ui->errorLabel->setText("Введите число больше");
    ui->errorLabel->setStyleSheet("QLabel { color : black; background-color : red; }");
}

void MainWindow::maxLenError()
{
    ui->errorLabel->setText("Введите число меньше");
    ui->errorLabel->setStyleSheet("QLabel { color : black; background-color : red; }");
}

void MainWindow::maxLenErrorNotification()
{
    QMessageBox::critical(this, "Ошибка", "<div style='color: white;'>" "Вы не можете перевести число такой длины" "</div>");
}

void MainWindow::emptyLineNotification()
{
    QMessageBox::critical(this, "Ошибка", "<div style='color: white;'>" "Пожалуйста введите число для первода" "</div>");
}
