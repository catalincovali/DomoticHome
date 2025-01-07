#ifndef MANUALDEVICE_H
#define MANUALDEVICE_H
#include "Device.h"
#include "Time.h"

class ManualDevice : public Device {
public:
    ManualDevice(std::string n, double power);

    void setProgrammedStart(const Time& time) override;
    void setProgrammedStop(const Time& t) override;
};
#endif // MANUALDEVICE_H
