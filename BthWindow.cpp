#include "BthWindow.h"
#include "ui_BthWindow.h"

BthWindow::BthWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BthWindow)
{
    ui->setupUi(this);
}

BthWindow::BthWindow(QWidget *parent, QStandardItemModel *StandardModel):
    QWidget(parent),
    ui(new Ui::BthWindow)
{
    ui->setupUi(this);

    ui->treeView->setModel(StandardModel);

    ui->treeView->expandAll();

    connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)), this, SIGNAL(doubleClick(QModelIndex)));

}

BthWindow::~BthWindow()
{
    delete ui;
}
