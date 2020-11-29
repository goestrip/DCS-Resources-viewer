#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionload_miz, &QAction::triggered, this, &MainWindow::openMizFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openMizFile()
{
    qDebug() <<"Trigger open file selector";
}

