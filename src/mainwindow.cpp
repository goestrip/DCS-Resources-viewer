#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QSortFilterProxyModel>

#include "airfieldtreemodel.h"
#include "selectionvisitor.h"
#include "inventorymodel.h"
#include "coalitiontreemodel.h"

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
        ui->AirfieldTreeView->resizeColumnToContents(0);
        QItemSelectionModel* treeViewSelectionModel= ui->AirfieldTreeView->selectionModel();
        connect(treeViewSelectionModel, &QItemSelectionModel::currentChanged, this, & MainWindow::onTreeViewSelectionChanged);

        inventoryModel = new InventoryModel();
        inventoryProxyModel = new QSortFilterProxyModel(this);
        inventoryProxyModel->setSourceModel(inventoryModel);

        ui->AircraftTableView->setModel(inventoryProxyModel);
        ui->AircraftTableView->setSortingEnabled(true);
        ui->AircraftTableView->horizontalHeader()->setSectionsClickable(true);
        ui->AircraftTableView->sortByColumn(1, Qt::SortOrder::AscendingOrder);


        ui->label_mission_date->setText(m_dataManager.getMissionDate().toString());


        coalitionTreeModel = new CoalitionTreeModel(m_dataManager.getMission());
        ui->CoalitionTreeView->setModel(coalitionTreeModel );

    }

}

void MainWindow::onTreeViewSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    TreeItemBase* selection = airfieldsTreeModel->getItemData(current);
    SelectionVisitor visitor;
    if(nullptr != selection)
    {
        selection->accept(&visitor);
        if(nullptr != visitor.getInventory())
        {
            inventoryModel->setCustomData(*visitor.getInventory());
             ui->AircraftTableView->resizeColumnToContents(0);
             ui->AircraftTableView->resizeColumnToContents(1);
        }
    }

}

