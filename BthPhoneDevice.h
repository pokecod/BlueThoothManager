#ifndef BTHPHONEDEVICE_H
#define BTHPHONEDEVICE_H


#include "BthAbstractDevice.h"

class BthPhoneDevice : public BthAbstractDevice
{
public:

    BthPhoneDevice(HANDLE in_RadioHandle, PBLUETOOTH_DEVICE_INFO in_DeviceInfo):BthAbstractDevice(in_RadioHandle, in_DeviceInfo){



    }

    ~BthPhoneDevice(){

    }

private:


};

#endif // BTHPHONEDEVICE_H
