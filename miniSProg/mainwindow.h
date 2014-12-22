#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QFileInfo>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_INVOKABLE void adjustSize() { QWidget::adjustSize(); }

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void procStarted();
    void procError(QProcess::ProcessError procError);
    void procExited(int exitCode, QProcess::ExitStatus exitStatus);
    void progStandardOutput();
    void progStandardError();

    void on_toolBtnProg_clicked();
    void on_toolBtnBit_clicked();

    void on_checkBox_details_stateChanged(int status);

    void on_pushButton_Program_clicked();

private:
    Ui::MainWindow *ui;
    QProcess * proc;

    void setDefaultConsoleColor();
};

#endif // MAINWINDOW_H
