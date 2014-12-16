#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    proc(new QProcess(this))
{
    ui->setupUi(this);

    connect(proc, SIGNAL(started()),this, SLOT(procStarted()));
    connect(proc, SIGNAL(error(QProcess::ProcessError)),this, SLOT(procError(QProcess::ProcessError)));
    connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(procExited(int,QProcess::ExitStatus)));
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(progStandardOutput()));
    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(progStandardError()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSet_clicked()
{
    ui->label->setText("Hello FAD!");
    ui->lineEdit->setText("Hello FAD!");
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString program = "/bin/yum";
    QStringList arguments;
    arguments.append("provides ");
    arguments.append("*/qt");

    //proc->setWorkingDirectory(MainDir);
    //proc->setStandardOutputFile(MainDir + "/...");
    //    setEnvironment
    proc->start(program, arguments);
    //proc->start(program);

}

void MainWindow::procStarted(){
    ui->lineEdit->setText("Started");

}

void MainWindow::procError(QProcess::ProcessError procError){
    ui->lineEdit->setText("Error!!!");
    ui->lineEdit_2->setText(proc->errorString());

    switch (procError) {
      case QProcess::FailedToStart:
        ui->label_2->setText("Failed to start");
        break;
      case QProcess::Crashed:
        ui->label_2->setText("Crashed");
        break;
    case QProcess::Timedout:
        ui->label_2->setText("Timedout");
        break;
    case QProcess::UnknownError:
        ui->label_2->setText("Unknown Error");
      default:
        ui->label_2->setText("REALLY! Unknown Error");
      }

}

void MainWindow::procExited(int exitCode, QProcess::ExitStatus exitStatus){
    ui->lineEdit->setText("Exited");
    ui->label->setText(QString::number(exitCode));

//    if ( myProcess->exitStatus() == 0)
//    {
//    qDebug () << "Program ran successfully";
//    }
//    if ( myProcess->exitStatus() == 2)
//    {
//    qDebug () << "Customized message";
//    }
//    if ( myProcess->exitStatus() == 3)
//    {
//    qDebug () << "Another text warning message";
//    }

}

void MainWindow::progStandardOutput(){
    ui->label_3->setText("there is standard out");

    QString abc = proc->readAllStandardOutput();
    ui->textEdit->setTextColor(Qt::green);
    ui->textEdit->append(abc);
}

void MainWindow::progStandardError(){
    ui->label_4->setText("there is standard Error");

    QString abc = proc->readAllStandardError();
    ui->textEdit->setTextColor(Qt::red);
    ui->textEdit->append(abc);
}
