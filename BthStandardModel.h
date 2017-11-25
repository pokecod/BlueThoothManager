#ifndef BTHSTANDARDMODEL_H
#define BTHSTANDARDMODEL_H

#include <QStandardItemModel>
#include <QObject>
#include "BthRadioModule.h"

class BthStandardModel : public QStandardItemModel{

    Q_OBJECT

public:

    BthStandardModel(){

        clear();
        setRowCount(0);
        setColumnCount(1);

    }

    ~BthStandardModel(){


    }

    void AddRadioModul(BthRadioModule &RadioModul){

        QList<QStandardItem*> ItemList;

        QStandardItem *data = new QStandardItem(RadioModul.Name());

        data->setData((long)(&RadioModul),Qt::UserRole + 1);



        ItemList.append(data);

        appendRow(ItemList);

        QList<BthAbstractDevice*> DeviceList = RadioModul.GetDeviceList();

        foreach (BthAbstractDevice* Device, DeviceList) {

            QList<QStandardItem*> DeviceParam;

            DeviceParam.append(new QStandardItem(Device->Name()));

            DeviceParam[0]->setData((long)(Device),Qt::UserRole + 1);

            qDebug()<<(long)(Device);

            ItemList[0]->appendRow(DeviceParam);

        }

    }

    void RemoveRadioModul(BthRadioModule &RadioModul){



    }

private:

    QList<QString> ConnectWith(QModelIndex Сhosen){

        QList<QString> List;

        if(Сhosen.isValid()){

            List = ConnectWith(Сhosen.parent());
            List.append(Сhosen.data().toString());

        }

        return List;

    }

public:
signals:

    void pair(BthAbstractDevice*);
    void unpair(BthAbstractDevice*);

    void refresh(BthRadioModule*);

public slots:

    void doubleClick(QModelIndex Сhosen){

        BthAbstarctClass *BthGeneric = (BthAbstarctClass*)(Сhosen.data(Qt::UserRole + 1).toUInt());

        qDebug() << QString("Connect with:%0 addr:0x%1").arg(Сhosen.data().toString()).arg((ulong)BthGeneric);

        switch (BthGeneric->Type) {
            case BTH_RADIO:



            break;
            case BTH_DEVICE:{

                BthAbstractDevice* AbstractDevice = static_cast<BthAbstractDevice*>(BthGeneric);

                emit pair(AbstractDevice);

            }

            break;
            case BTH_SERVICE:

            break;
            default:
            break;
        }

    }

};

#endif // BTHSTANDARDMODEL_H


