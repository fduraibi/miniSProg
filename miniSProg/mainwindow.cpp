/* This file is part of miniSProg.

miniSProg is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
any later version.

miniSProg is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with miniSProg.  If not, see <http://www.gnu.org/licenses/>. */

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

    setDefaultConsoleColor();

    QString xc3sprog_path = "";
    QFileInfo xc3sprog_file;
    QSettings settings("ScarabHardware", "miniSProg");
    xc3sprog_path = settings.value("xc3sprog_path").toString();

    if (xc3sprog_path.isEmpty()){
        // Check if "xc3sprog" exist in the same folder with this application
        xc3sprog_file.setFile("./xc3sprog");
    } else {
        xc3sprog_file.setFile(xc3sprog_path);
    }

    // check if file exists and if yes: Is it really a file and no directory?
    if (xc3sprog_file.exists() && xc3sprog_file.isFile()) {
        ui->lineEdit_xc3sprog->setText(xc3sprog_file.canonicalFilePath());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDefaultConsoleColor(){
    // Set background color to black, and text to white
    ui->textEdit->setStyleSheet("QTextEdit { background-color: rgb(0, 0, 0) ;	color: rgb(255, 255, 255);}");
    ui->textEdit->setTextColor(Qt::white);
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::procStarted()
{
    //ui->textEdit->append("Started");
}

void MainWindow::procError(QProcess::ProcessError procError)
{
    ui->textEdit->setTextColor(Qt::red);
    ui->textEdit->append(tr("Error!!!"));
    ui->textEdit->append(proc->errorString());

    switch (procError) {
      case QProcess::FailedToStart:
        ui->textEdit->append(tr("Failed to start"));
        break;
      case QProcess::Crashed:
        ui->textEdit->append(tr("Crashed"));
        break;
    case QProcess::Timedout:
        ui->textEdit->append(tr("Timedout"));
        break;
    case QProcess::UnknownError:
        ui->textEdit->append(tr("Unknown Error"));
      default:
        ui->textEdit->append(tr("REALLY! Unknown Error"));
      }

    setDefaultConsoleColor();
}

void MainWindow::procExited(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->textEdit->append("Done.");
    //ui->textEdit->append(QString::number(exitCode));

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

void MainWindow::progStandardOutput()
{
    QString abc = proc->readAllStandardOutput();
    ui->textEdit->append(abc);
}

void MainWindow::progStandardError()
{
    QString abc = proc->readAllStandardError();
    ui->textEdit->append(abc);
}

void MainWindow::on_toolBtnProg_clicked()
{
    QString xc3sprog_path = QFileDialog::getOpenFileName(this, tr("Select the xc3sprog file"),"./","xc3sprog (xc3sprog)");
    ui->lineEdit_xc3sprog->setText(xc3sprog_path);

    QSettings settings("ScarabHardware", "miniSProg");
    settings.setValue("xc3sprog_path", xc3sprog_path);
}

void MainWindow::on_toolBtnBit_clicked()
{
    QString bitfile_path = QFileDialog::getOpenFileName(this, tr("Select the bit file"),"./",tr("bit Files (*.bit)"));
    ui->lineEdit_bitfile->setText(bitfile_path);
}

void MainWindow::on_checkBox_details_stateChanged(int status)
{
    // status 0 => Hide, 2 => Show
    if (status == 0) {
        ui->textEdit->setVisible(false);
        // Using this to make it resize when hiding the console
        QMetaObject::invokeMethod(this, "adjustSize", Qt::QueuedConnection);

    } else {
        ui->textEdit->setVisible(true);
    }
}

void MainWindow::on_pushButton_Program_clicked()
{
    if (ui->lineEdit_xc3sprog->text().isEmpty()) {
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("ERROR: Select the xc3sprog path first."));
        setDefaultConsoleColor();
    } else if (ui->lineEdit_bitfile->text().isEmpty()) {
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->append(tr("ERROR: Select the bit file first."));
        setDefaultConsoleColor();
    } else {
        QString program = ui->lineEdit_xc3sprog->text();
        QStringList arguments;
        arguments.append("-c");
        arguments.append("ftdi");
        arguments.append(ui->lineEdit_bitfile->text());
        proc->start(program, arguments);
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QString myTitle = "misiSProg";
    QString myBody = tr("<b>miniSProg by Scarab hardware</b><br><br>"
                        "A simple interface for 'xc3sprog' designed for<br>"
                        "the FPGA board miniSpartan6+.<br><br>"
                        "Source code: <a href='https://github.com/fduraibi/miniSProg'>https://github.com/fduraibi/miniSProg</a><br>"
                        "Developed by: Fahad Alduraibi<br>"
                        "v1.0");
    QMessageBox::about(this, myTitle, myBody);
}
