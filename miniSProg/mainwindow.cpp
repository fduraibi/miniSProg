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

    // Set background color to black, and text to off-white
    ui->textEdit->setStyleSheet("QTextEdit { background-color: rgb(0, 0, 0) ;	color: rgb(208, 208, 208);}");

    // Check if "xc3sprog" exist in the same folder with this application
    QFileInfo checkFile("./xc3sprog");
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        ui->textEdit->append("Yes it is there");
        ui->lineEdit_xc3sprog->setText("./xc3sprog");
    } else {
        ui->textEdit->append("COULDN'T FIND IT");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_pushButton()
//{
//    QFileInfo checkFile("xc3sprog");
//    // check if file exists and if yes: Is it really a file and no directory?
//    if (checkFile.exists() && checkFile.isFile()) {
//        ui->textEdit->append("Yes it is there");
//    } else {
//        ui->textEdit->append("COULDN'T FIND IT");
//    }

//}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::procStarted(){
    ui->textEdit->append("Started");

}

void MainWindow::procError(QProcess::ProcessError procError){
    ui->textEdit->append("Error!!!");
    ui->textEdit->append(proc->errorString());

    switch (procError) {
      case QProcess::FailedToStart:
        ui->textEdit->append("Failed to start");
        break;
      case QProcess::Crashed:
        ui->textEdit->append("Crashed");
        break;
    case QProcess::Timedout:
        ui->textEdit->append("Timedout");
        break;
    case QProcess::UnknownError:
        ui->textEdit->append("Unknown Error");
      default:
        ui->textEdit->append("REALLY! Unknown Error");
      }

}

void MainWindow::procExited(int exitCode, QProcess::ExitStatus exitStatus){
    ui->textEdit->append("Exited");
    ui->textEdit->append(QString::number(exitCode));

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
    ui->textEdit->append("there is standard out");

    QString abc = proc->readAllStandardOutput();
    ui->textEdit->setTextColor(Qt::green);
    ui->textEdit->append(abc);
}

void MainWindow::progStandardError(){
    ui->textEdit->append("there is standard Error");

    QString abc = proc->readAllStandardError();
    ui->textEdit->setTextColor(Qt::red);
    ui->textEdit->append(abc);
}

void MainWindow::on_toolBtnProg_clicked()
{
    QString xc3sprog_path = QFileDialog::getOpenFileName(this, tr("Select the xc3sprog file"),"./",tr("xc3sprog"));
    ui->lineEdit_xc3sprog->setText(xc3sprog_path);
}

void MainWindow::on_toolBtnBit_clicked()
{
    QString bitfile_path = QFileDialog::getOpenFileName(this, tr("Select the bit file"),"./",tr("bit Files (*.bit)"));
    ui->lineEdit_bitfile->setText(bitfile_path);
}

void MainWindow::on_checkBox_details_stateChanged(int status)
{
    // status 0 => Hide, 2 => Show
    ui->textEdit->append(QString::number(status));

    if (status == 0) {
        ui->textEdit->setVisible(false);


    } else {
        ui->textEdit->setVisible(true);
    }
}

void MainWindow::on_pushButton_Program_clicked()
{
    if (ui->lineEdit_xc3sprog->text().isEmpty()) {
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append("ERROR: Set the xc3sprog path first.");

    } else {
        QString program = "./xc3sprog -c ftdi";
        //QStringList arguments;
        //arguments.append("-c");
        //arguments.append("ftdi");

        //proc->setWorkingDirectory(MainDir);
        //proc->setStandardOutputFile(MainDir + "/...");
        //    setEnvironment
        //proc->start(program, arguments);
        proc->start(program);
    }
}
