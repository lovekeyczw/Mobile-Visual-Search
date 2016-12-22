#include <QtWidgets>
#include <QProcess>
#include <QFile>
#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    myProcess = new QProcess();
    myProcess->setProcessChannelMode(QProcess::MergedChannels);
    myProcess->start("D:/Qt/MobileVisualSearch.exe",QProcess::Unbuffered|QProcess::ReadWrite);
    myProcess->waitForStarted();
    //myProcess->write("start\n");
    this->setWindowTitle(QStringLiteral("移动视觉搜索"));
    QWidget *central = new QWidget(this);
    QVBoxLayout *m = new QVBoxLayout;

    view1 = new View(this);
    view1->setBaseSize(200,200);

    QHBoxLayout *buttons = new QHBoxLayout;
    pathButton = new QPushButton(this);
    pathButton->setText(QStringLiteral("训练集路径选择"));
    trainButton = new QPushButton(this);
    trainButton->setText(QStringLiteral("训练开始"));
    open = new QPushButton(this);
    open->setText(QStringLiteral("打开图片"));
    num = new QComboBox(this);
    for(int i=1;i<=5;i++)
        num->addItem(QString::number(i));
    start= new QPushButton(this);
    start->setText(QStringLiteral("开  始"));
    dataGet = new QTextEdit(this);
    buttons->addWidget(pathButton);
    buttons->addWidget(trainButton);
    buttons->addWidget(open);
    buttons->addWidget(num);
    buttons->addWidget(start);
    view2 = new View(this);

    //m->addWidget(view1);
    m->addLayout(buttons);
    m->addWidget(dataGet);
    central->setLayout(m);
    this->setCentralWidget(central);

    QDockWidget *dock=new QDockWidget(this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::TopDockWidgetArea);
    dock->setWidget(view1);
    addDockWidget(Qt::TopDockWidgetArea,dock);

    //设置停靠窗口2
    dock=new QDockWidget(this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    dock->setWidget(view2);
    addDockWidget(Qt::BottomDockWidgetArea,dock);
    connect(open, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(pathButton, &QPushButton::clicked,this, &MainWindow::openPath);
    connect(trainButton, &QPushButton::clicked,this, &MainWindow::starttrain);
    connect(start, &QPushButton::clicked,this,&MainWindow::startRun);


}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile()
{
    QFileDialog *file = new QFileDialog(this);
    file->setFileMode(QFileDialog::ExistingFile);
    if ( file->exec() == QDialog::Accepted )
        fileName = file->selectedFiles()[0];
    if (!fileName.isEmpty())
        this->loadPic();

}
void MainWindow::loadPic()
{
    view1->clear();
    view1->addPic(fileName);
    dataGet->append(fileName);
}

void MainWindow::startRun()
{
    results.clear();
    myProcess->write("query\n");
    myProcess->write(fileName.toStdString().c_str());
    myProcess->write("\n");
    myProcess->write(num->currentText().toStdString().c_str());
    myProcess->write("\n");
    myProcess->waitForReadyRead();
    QStringList args;
    args << myProcess->readLine();
    dataGet->append(args[0]);
    for(int i =0;i<=num->currentIndex();i++)
    {
        myProcess->waitForReadyRead();
        results << myProcess->readLine();
        results[i]=results[i].simplified();
        dataGet->append(results[i]);
    }
    this->display();
}

void MainWindow::display()
{
    view2->clear();
    /*
    QFile file("/home/administrator/testdir/test.txt");
    QTextStream in(&file);
    QStringList lines;
    while( !in.atEnd()){
        lines << in.readLine();
    }
    */

    for(int i=0;i<results.size();i++)
    {
        view2->addPic(results[i]);
    }
}

void MainWindow::openPath()
{
    QFileDialog *file = new QFileDialog(this);
    file->setFileMode(QFileDialog::Directory);
    if ( file->exec() == QDialog::Accepted )
        trainPath = file->selectedFiles()[0];
    if (!trainPath.isEmpty())
        this->loadPic();
}

void MainWindow::starttrain()
{
    myProcess->write("train\n");
    myProcess->write(trainPath.toStdString().c_str());
    myProcess->write("\n");
    //myProcess->write("Book\n");
    myProcess->waitForReadyRead();
    QStringList args;
    args << myProcess->readLine();
    dataGet->append(args[0]);

    myProcess->waitForReadyRead(3000000);
    args.clear();
    args << myProcess->readLine();
    dataGet->append(args[0]);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    myProcess->write(("stop\n"));
    myProcess->waitForFinished();
    event->accept();
}
