//name:Gavrilovska Kristina
#ifndef MANUALDEVICE_H
#define MANUALDEVICE_H
#include "Device.h"

class ManualDevice : public Device {
public:
    ManualDevice(std::string n, double power);
};
#endif // MANUALDEVICE_H
