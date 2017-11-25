
#include "BthAbstractDevice.h"

BOOL CALLBACK BthDefaultAuthCallback(LPVOID Param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS AuthParam){

    BLUETOOTH_AUTHENTICATE_RESPONSE response;

    ZeroMemory(&response,sizeof(BLUETOOTH_AUTHENTICATE_RESPONSE));

    response.authMethod = AuthParam->authenticationMethod;
    response.bthAddressRemote = AuthParam->deviceInfo.Address;
    response.negativeResponse = FALSE;

    DWORD error = BluetoothSendAuthenticationResponseEx(nullptr, &response);

    qDebug() << "callback error:" << error;

    return TRUE;

}


