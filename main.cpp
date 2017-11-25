#include "BthWindow.h"
#include "BthManager.h"
#include "BthStandardModel.h"
#include <QApplication>

DWORD Initialize(BthStandardModel &BthModel, BthManager &BtManager){

    DWORD Res = ERROR_SUCCESS;

    QList<BthRadioModule*> RadioModuleList = BtManager.BthEnumRadioModules();

    foreach (BthRadioModule* Radio, RadioModuleList) {

        qDebug() <<"Radio:" << Radio->Name();

        Res = Radio->EnumerateDevice();

        if(Res!=ERROR_SUCCESS){

            return Res;

        }

        QList<BthAbstractDevice*> DeviceList = Radio->GetDeviceList();

        foreach (BthAbstractDevice* Device, DeviceList) {

            qDebug() << "Dvice Name:"<< Device->Name();

        }

        BthModel.AddRadioModul(*Radio);

    }

    return Res;

}

DWORD main(int argc, char *argv[]){

    QApplication a(argc, argv);

    BthStandardModel BthModel;

    BthManager BtManager;

    DWORD Res = Initialize(BthModel, BtManager);

    if(Res!=ERROR_SUCCESS){

        return Res;

    }

    BthWindow w(NULL, &BthModel);

    QObject::connect(&w, SIGNAL(doubleClick(QModelIndex)), &BthModel, SLOT(doubleClick(QModelIndex)));

    QObject::connect(&BthModel, SIGNAL(pair(BthAbstractDevice*)), &BtManager, SLOT(Pair(BthAbstractDevice*)));

    w.show();

    return a.exec();

}
