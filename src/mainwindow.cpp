#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "airfieldtreemodel.h"
#include "selectionvisitor.h"

//#include "lua.hpp"
//#include "LuaBridge.h"

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
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Miz file"), "", tr("miz Files (*.miz)"));

    if(!m_dataManager.openMizFile(fileName))
    {
        QMessageBox msgBox;
        msgBox.setText("Can't read file");
        msgBox.exec();
    }
    else{
        airfieldsTreeModel = new AirfieldTreeModel(m_dataManager.getAirfields(), this);
        ui->AirfieldTreeView->setModel(airfieldsTreeModel);

        QItemSelectionModel* treeViewSelectionModel= ui->AirfieldTreeView->selectionModel();
        connect(treeViewSelectionModel, &QItemSelectionModel::currentChanged, this, & MainWindow::onTreeViewSelectionChanged);

    }

}

void MainWindow::onTreeViewSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    TreeItemBase* selection = airfieldsTreeModel->getItemData(current);
    SelectionVisitor visitor;
    if(nullptr != selection)
    {
        selection->accept(&visitor);
    }

}

