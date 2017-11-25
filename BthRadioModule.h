#ifndef BTHRADIOMODULE_H
#define BTHRADIOMODULE_H

#include "BthAbstarctClass.h"
#include "BthAbstractDevice.h"
#include "BthPeripheralDevice.h"
#include "BthPhoneDevice.h"

class BthRadioModule : public BthAbstarctClass
{
public:

    BthRadioModule(QObject *parent = 0):BthAbstarctClass(BTH_RADIO, parent){

    }

    ~BthRadioModule(){

        foreach (BthAbstractDevice* Device, m_DeviceList) {

            delete Device;

        }

        m_DeviceList.clear();

        CloseHandle(m_hRadio);

    }

    virtual DWORD EnumerateDevice(){

        DWORD Res = ERROR_SUCCESS;

        BLUETOOTH_DEVICE_SEARCH_PARAMS BluetoothDeviceSearch = {sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
                                                                        TRUE,
                                                                        TRUE,
                                                                        TRUE,
                                                                        TRUE,
                                                                        TRUE,
                                                                        10,
                                                                        m_hRadio};

        BLUETOOTH_DEVICE_INFO BluetoothDeviceInfo = {sizeof(BLUETOOTH_DEVICE_INFO), 0};

        HBLUETOOTH_DEVICE_FIND hBluetoothDeviceFind = BluetoothFindFirstDevice(&BluetoothDeviceSearch, &BluetoothDeviceInfo);

        if(hBluetoothDeviceFind){

            do {

                BthAbstractDevice *Device = NULL;

                switch (GET_MAJOR_DEVICE_CLASS(BluetoothDeviceInfo.ulClassofDevice)) {

                    case BTH_MAJOR_DEVICE_PEREPHERAL:

                        Device = new BthPeripheralDevice(m_hRadio, &BluetoothDeviceInfo);

                    break;

                    case BTH_MAJOR_DEVICE_PHONE:

                        Device = new BthPhoneDevice(m_hRadio, &BluetoothDeviceInfo);

                    break;

                    default:

                        qDebug()<<"Unknown device!";

                    break;

                }

                if(Device){

                    Res = Device->Initialize();

                    if(Res){

                        delete Device;
                        break;

                    }

                    else {

                        if(!GetDeviceByName(QString::fromWCharArray(BluetoothDeviceInfo.szName))){

                            m_DeviceList.append(Device);

                        }

                    }

                }

            } while(BluetoothFindNextDevice(hBluetoothDeviceFind, &BluetoothDeviceInfo));

            BluetoothFindDeviceClose(hBluetoothDeviceFind);

        }

        else {

            Res = GetLastError();

        }

        return Res;

    }

    virtual DWORD Initialize(HANDLE hRadio){

        ZeroMemory(&RadioInfo,sizeof(BLUETOOTH_RADIO_INFO));

        RadioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);

        DWORD Result = BluetoothGetRadioInfo(hRadio, &RadioInfo);

        if(!Result){

            if (!DuplicateHandle(GetCurrentProcess(),
                                hRadio,
                                    GetCurrentProcess(),
                                        &m_hRadio,
                                            0,
                                                FALSE,
                                                    DUPLICATE_SAME_ACCESS)){

                return GetLastError();

            }


        }

        return Result;

    }

    virtual bool Enable(){

        return true;

    }

    virtual bool Disable(){

        return true;

    }

    virtual QString Name(){

        return QString::fromWCharArray(RadioInfo.szName);

    }

    BthAbstractDevice* GetDeviceByName(QString &DevName){

        foreach (BthAbstractDevice* Device, m_DeviceList) {

            if(Device->Name() == DevName){

                return Device;

            }

        }

        return NULL;

    }

    QList<BthAbstractDevice*> GetDeviceList(){

        return m_DeviceList;

    }

private:

    HANDLE m_hRadio = NULL;

    QList<BthAbstractDevice*> m_DeviceList;

    BLUETOOTH_RADIO_INFO RadioInfo;


};

#endif // BTHRADIOMODULE_H
