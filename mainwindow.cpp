#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //菜单栏
    QMenuBar* menuBar = MainWindow::menuBar();
    QMenu* menuFile = menuBar->addMenu("File");
    QAction* menuNewAction = menuFile->addAction("new");
    connect(menuNewAction,&QAction::triggered,
            [](){
        qDebug()<<"file new";
    });

    menuFile->addSeparator();

    QAction* menuOpenAction = menuFile->addAction("open");
    connect(menuOpenAction, &QAction::triggered,
            [](){
       qDebug()<<"file open";
    });

    menuFile->addSeparator();

    //模态对话框
    QAction* menuModelDialogAction = menuFile->addAction("ModelDialog");
    connect(menuModelDialogAction,&QAction::triggered,
            [](){
        QDialog dlg1;
        dlg1.exec();
        qDebug()<<"model dialog";
    });

    //非模态对话框
    QAction* menuModelessDialogAction = menuFile->addAction("ModelessDialog");
    connect(menuModelessDialogAction,&QAction::triggered,
            [=](){
        //这样定义一闪而过，因为是局部变量，可以定义为成员变量
        //QDialog dlg1;
        //dlg1.show();

        //modelessDialog.show();

        //采用指针方式 这种方式指定父对象，但如果总触发这个事件而不关闭主窗口，
        //同样面临内存泄露问题，所以不应指定父对象，采用下面方法
        //QDialog* _modelessDialog = new QDialog(this);
        //_modelessDialog->show();

        QDialog* _modelessDialog = new QDialog;
        _modelessDialog->setAttribute(Qt::WA_DeleteOnClose);
        _modelessDialog->show();

        qDebug()<<"modeless dialog";
    });

    //标准对话框
    QAction* menuAboutAction = menuFile->addAction("about");
    connect(menuAboutAction,&QAction::triggered,
            [=](){
        QMessageBox::about(this,"about","ver1.0");
        qDebug()<<"about dialog";
    });

    QAction* menuQuesAction = menuFile->addAction("question");
    connect(menuQuesAction,&QAction::triggered,
            [=](){
        int ret = QMessageBox::question(this,"question","are you ok?", QMessageBox::Ok, QMessageBox::Cancel);
        switch(ret) {
        case QMessageBox::Yes:
            qDebug()<<"yes";
            break;
        case QMessageBox::No:
            qDebug()<<"no";
            break;
        case QMessageBox::Ok:
            qDebug()<<"ok";
            break;
        case QMessageBox::Cancel:
            qDebug()<<"Cancel";
            break;
        default:
            break;
        }

        qDebug()<<"question dialog";
    });

    menuFile->addSeparator();
    //文件对话框
    QAction* menufileAction = menuFile->addAction("file dialog");
    connect(menufileAction,&QAction::triggered,
            [=](){
        QString path = QFileDialog::getOpenFileName(this,"open","../","source(*.cpp *.h);;"
                                                                      "Image Files (*.png *.jpg *.bmp);;all(*.*)");
        qDebug()<<path;
    });

    //工具栏
    QToolBar* toolBar = addToolBar("toolbar");
    toolBar->addAction(menuNewAction);

    QPushButton* smileBtn = new QPushButton(this);
    smileBtn->setText("^_^");
    connect(smileBtn,&QPushButton::released,
            [](){
        qDebug()<<"smile";
    });


    toolBar->addWidget(smileBtn);

    //状态栏
    QStatusBar* _statusBar =  statusBar();
    QLabel* status1 = new QLabel(this);
    status1->setText("normal text");
    _statusBar->addWidget(status1);
    //从左往右依次添加
    _statusBar->addWidget(new QLabel("2",this));
    //从右往左添加
    _statusBar->addPermanentWidget(new QLabel("3",this));

    //核心控件
    QTextEdit* coreEdit = new QTextEdit(this);
    setCentralWidget(coreEdit);


    //浮动窗口
    QDockWidget* dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    //给浮动窗口添加控件
    QTextEdit* coreEdit1 = new QTextEdit(this);
    dock->setWidget(coreEdit1);



}

MainWindow::~MainWindow()
{
}

