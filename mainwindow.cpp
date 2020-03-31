#include <QTimer>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    inputFile = new QFile(":/ProgramFiles/data.txt");
    //inputSaveFile = new QSaveFile("qrc:/ProgramFiles/data.txt");
    inputSaveFile = new QSaveFile("C:/Users/a.kurtvuran/Documents/WriteInPulse/data.txt");
    connect(timer,SIGNAL(timeout()),this,SLOT(pulse()));
    timer->start(1000);
    ui->outputLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pulse()
{
    readFile();
}

void MainWindow::readFile()
{
    if (!isOpen){
        if (inputFile->open(QIODevice::ReadOnly))
        {
           qDebug() << "File opened";
           isOpen = true;
           inputTextStream = new QTextStream(inputFile);
        }else{
            qDebug() << "File not open";
            return;
        }
    }else{
        if (!inputTextStream->atEnd())
        {
           // *inputTextStream <<"use for append" <<endl;
            labelString = ui->outputLabel->text();
            labelString.append(inputTextStream->readLine() +"\n");
            ui->outputLabel->setText(labelString);
        }else{
            inputFile->close();
            isOpen = false;
            disconnect(timer,SIGNAL(timeout()),this,SLOT(pulse()));
            timer->stop();
            writeFile();
        }
    }
}

void MainWindow::writeFile()
{
    if (inputSaveFile->open(QIODevice::WriteOnly))  {
       qDebug() << "Save File opened";
       //QByteArray outputByteArray;
       labelString.append("SaveFile comitted\n");
      // outputByteArray.append("QSaveFile committed");
       inputSaveFile->write(labelString.toUtf8());
       inputSaveFile->commit();
        qDebug() << "Save File committed";
    }else{
        qDebug() << "Save File not open";
        return;
    }
}
