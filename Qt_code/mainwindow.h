#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "view.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void starttrain();
    void openFile();
    void openPath();
    void loadPic();
    void startRun();
    void display();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QPushButton *pathButton;
    QPushButton *trainButton;
    QPushButton *open;
    QPushButton *start;
    QComboBox *num;
    QTextEdit *dataGet;
    View *view1;
    View *view2;
    QString fileName;
    QString trainPath;
    QStringList results;
    QProcess *myProcess;
};

#endif // MAINWINDOW_H
