#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class AirfieldTreeModel;
class InventoryModel;
class QSortFilterProxyModel ;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTreeViewSelectionChanged(const QModelIndex &current, const QModelIndex &previous);

private:

    void openMizFile();
    Ui::MainWindow *ui;
    AirfieldTreeModel* airfieldsTreeModel;
    InventoryModel* inventoryModel;
    QSortFilterProxyModel *inventoryProxyModel;

   DataManager  m_dataManager;

};
#endif // MAINWINDOW_H
