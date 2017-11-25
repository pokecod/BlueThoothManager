#ifndef BTHMANAGER_H
#define BTHMANAGER_H

#include <BthRadioModule.h>
#include <QObject>

class BthManager: public QObject
{

    Q_OBJECT

public:

    BthManager(QObject* parent = 0): QObject(parent){


    }

    ~BthManager(){

        foreach (BthRadioModule* RadioModule, ListRadioModules) {

            delete RadioModule;

        }

        ListRadioModules.clear();

    }

    QList<BthRadioModule*> BthEnumRadioModules(){

        HANDLE hRadio;

        BLUETOOTH_FIND_RADIO_PARAMS BluetoothRadioParams = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};

        HBLUETOOTH_RADIO_FIND hBluetoothRadioFind = BluetoothFindFirstRadio(&BluetoothRadioParams, &hRadio);

        if(hBluetoothRadioFind){

            do {

                BthRadioModule *RadioModule = new BthRadioModule();

                DWORD Res = RadioModule->Initialize(hRadio);

                CloseHandle(hRadio);

                if(Res){

                    delete RadioModule;

                    break;

                }

                ListRadioModules.append(RadioModule);

            } while(BluetoothFindNextRadio(hBluetoothRadioFind, &hRadio));

            BluetoothFindRadioClose(hBluetoothRadioFind);

        }

        return ListRadioModules;

    }

private:

    QList<BthRadioModule*> ListRadioModules;

public:
signals:

public slots:

    void Pair(BthAbstractDevice* AbstractDevice){

        AbstractDevice->Pair();

    }

};

#endif // BTHMANAGER_H
