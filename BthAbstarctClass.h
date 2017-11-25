#ifndef BTHABSTARCTCLASS_H
#define BTHABSTARCTCLASS_H

#include "defines.h"
#include <qt_windows.h>
#include <BluetoothAPIs.h>
#include <QObject>

#define MAX_SERVICES (10)

#define POWER_OFSET (0)
#define POWER_SET(x) (x|(1<<(POWER_OFSET)))
#define POWER_GET(x) ((x&(1<<(POWER_OFSET)))>>(POWER_OFSET))

#define PAIR_OFSET (1)
#define PAIR_SET(x) (x|(1<<(PAIR_OFSET)))
#define PAIR_GET(x) ((x&(1<<(PAIR_OFSET)))>>(PAIR_OFSET))

#define CONNECT_OFSET (1)
#define CONNECT_SET(x) (x|(1<<(CONNECT_OFSET)))
#define CONNECT_GET(x) ((x&(1<<(CONNECT_OFSET)))>>(CONNECT_OFSET))

#define GET_FORMAT(x)               (x&3)
#define GET_MINOR_DEVICE_CLASS(x)   ((x&(0x3f<<2))>>2)
#define GET_MAJOR_DEVICE_CLASS(x)   ((x&(0x1f<<8))>>8)
#define GET_MAJOR_DEVICE_SERVICE(x) ((x&(0x7ff<<13))>>13)

#define BTH_MAJOR_DEVICE_MISCELLANEOUS  (0)
#define BTH_MAJOR_DEVICE_COMPUTER       (1)
#define BTH_MAJOR_DEVICE_PHONE          (2)
#define BTH_MAJOR_DEVICE_NETWORK        (3)
#define BTH_MAJOR_DEVICE_PEREPHERAL     (4)
#define BTH_MAJOR_DEVICE_IMAGING        (5)
#define BTH_MAJOR_DEVICE_WEARABLE       (6)
#define BTH_MAJOR_DEVICE_TOY            (7)
#define BTH_MAJOR_DEVICE_HEALTH         (8)
#define BTH_MAJOR_DEVICE_UNCATEGORIZED  (9)

typedef enum {
    BTH_NOT_INITIALIZE,
    BTH_RADIO,
    BTH_DEVICE,
    BTH_SERVICE
}BTH_TYPE;

class BthAbstarctClass : public QObject
{
    Q_OBJECT
public:

    explicit BthAbstarctClass(BTH_TYPE bthType, QObject *parent = 0): QObject(parent){

        Type = bthType;
        State = 0;

    }

    ~BthAbstarctClass(){


    }

    PROPERTY_PROTECT(uint, State);
    PROPERTY_PROTECT(BTH_TYPE, Type);

    virtual bool Enable() = 0;
    virtual bool Disable() = 0;
    virtual QString Name() = 0;

signals:

public slots:
};

#endif // BTHABSTARCTCLASS_H
