#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "entrypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AppContext context;
    void transformButton();
    void clearButton();
    void copyButton();
    void swapButton();
    void entryLine();
    void updateInterface(Param* param);
    void updateValue();
    void updateAll(AppContext* context, Param* param);
    void comboBoxFrom();
    void setDefaultInterface();
    void incorrectErrorDataNotification();
    void maxLenErrorNotification();
    void maxLenError();
    void minLenError();
    void incorrectSysError();
    void updateSysFromTo();
    void emptyLineNotification();
    bool buttonPressed = false;
};
#endif // MAINWINDOW_H
