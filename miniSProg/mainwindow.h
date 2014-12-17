#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonSet_clicked();

    void on_actionExit_triggered();

    void on_pushButton_2_clicked();

    void procStarted();
    void procError(QProcess::ProcessError procError);
    void procExited(int exitCode, QProcess::ExitStatus exitStatus);
    void progStandardOutput();
    void progStandardError();

private:
    Ui::MainWindow *ui;
    QProcess * proc;
};

#endif // MAINWINDOW_H
