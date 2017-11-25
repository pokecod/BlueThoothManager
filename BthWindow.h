#ifndef BTHWINDOW_H
#define BTHWINDOW_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class BthWindow;
}

class BthWindow : public QWidget
{
    Q_OBJECT

public:

    explicit BthWindow(QWidget *parent = 0);
    explicit BthWindow(QWidget *parent, QStandardItemModel *StandardModel);

    ~BthWindow();

private:
    Ui::BthWindow *ui;
    QStandardItemModel *m_Model;

public:
signals:

    void doubleClick(QModelIndex);

public slots:



};

#endif // BTHWINDOW_H
