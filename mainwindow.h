#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QSaveFile>



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
    void readFile();
public slots:
    void pulse();
    void writeFile();

private:
    Ui::MainWindow *ui;
    bool isOpen = false;
    QFile *inputFile;
    QSaveFile *inputSaveFile;
    QTextStream *inputTextStream;
    QTimer *timer;
    QString labelString;
};
#endif // MAINWINDOW_H
