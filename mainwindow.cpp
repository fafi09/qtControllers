#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>

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
    //工具栏
    //状态栏
    //核心控件
    //浮动窗口
}

MainWindow::~MainWindow()
{
}

