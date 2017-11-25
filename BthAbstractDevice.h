#ifndef BTHABSTRACTDEVICE_H
#define BTHABSTRACTDEVICE_H

#include "BthAbstarctClass.h"

BOOL CALLBACK BthDefaultAuthCallback(LPVOID Param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS AuthParam);

class BthAbstractDevice : public BthAbstarctClass
{
public:

    BthAbstractDevice(HANDLE in_RadioHandle, PBLUETOOTH_DEVICE_INFO in_DeviceInfo):BthAbstarctClass(BTH_DEVICE),RadioHandle(in_RadioHandle){

        RtlCopyMemory(&m_DeviceInfo, in_DeviceInfo, sizeof(BLUETOOTH_DEVICE_INFO));

        setAuthCallBack(&BthDefaultAuthCallback);

    }

    ~BthAbstractDevice(){

        UnPair();
        m_ServiceList.clear();

    }

    virtual DWORD Initialize(){

        DWORD NumServices = MAX_SERVICES;

        GUID GuidServices[MAX_SERVICES] = {0};

        DWORD Res = BluetoothEnumerateInstalledServices(RadioHandle, &m_DeviceInfo, &NumServices, GuidServices);

        if(!Res){

            for(DWORD i=0; i<NumServices; i++){

                m_ServiceList.append(GuidServices[i].Data1);

            }

        }

        return Res;

    }

    virtual bool Enable(){

        return true;
    }

    virtual bool Disable(){

        return true;

    }

    virtual QString Name(){

        return QString::fromWCharArray(m_DeviceInfo.szName);

    }

    virtual void setAuthCallBack(BOOL CALLBACK(*pAuthCallback)(LPVOID Param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS AuthParam)){

        BthAuthCallback = pAuthCallback;

    }

    virtual DWORD Pair(){

        DWORD Res = BluetoothRegisterForAuthenticationEx(&m_DeviceInfo,
                                                                &hCallbackHandle,
                                                                    (PFN_AUTHENTICATION_CALLBACK_EX)BthAuthCallback,
                                                                        NULL);

        if (Res!=ERROR_SUCCESS){

            qDebug() << "Failed to register callback" << Res;

            return Res;

        }

        Res = BluetoothAuthenticateDeviceEx(NULL, RadioHandle, &m_DeviceInfo, NULL, MITMProtectionRequired);

        if(Res!=ERROR_SUCCESS){

            BluetoothUnregisterAuthentication(hCallbackHandle);

            hCallbackHandle = NULL;

            qDebug() << "Failed to register callback" << Res;

        }

        return Res;

    }

    virtual DWORD UnPair(){

        return BluetoothUnregisterAuthentication(hCallbackHandle)?ERROR_SUCCESS:GetLastError();

    }

    virtual QList<uuid> ListOfService(){

        return m_ServiceList;

    }

protected:

    QList<uuid> m_ServiceList;
    BLUETOOTH_DEVICE_INFO m_DeviceInfo;
    HANDLE RadioHandle;
    HANDLE hCallbackHandle;
    BOOL CALLBACK(*BthAuthCallback)(LPVOID Param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS AuthParam);

};

#endif // BTHABSTRACTDEVICE_H
