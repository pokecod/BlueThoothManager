#ifndef BTHPERIPHERALDEVICE_H
#define BTHPERIPHERALDEVICE_H

#include "BthAbstractDevice.h"

class BthPeripheralDevice : public BthAbstractDevice
{
public:

    BthPeripheralDevice(HANDLE in_RadioHandle, PBLUETOOTH_DEVICE_INFO in_DeviceInfo):BthAbstractDevice(in_RadioHandle, in_DeviceInfo){


    }

    ~BthPeripheralDevice(){


    }

private:


};

#endif // BTHPERIPHERALDEVICE_H
