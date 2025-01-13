#ifndef CYCLICDEVICE_H
#define CYCLICDEVICE_H
#include "Device.h"

class CyclicDevice : public Device {
private:
    Time cycleDuration;  //cycle duration of cyclic devices
public:

    CyclicDevice(std::string n, double power, Time cycleDuration);
    Time getCycleDuration() const {return cycleDuration;}             // getter function of cycleDuration
    void setProgrammedStart(const Time& time)override;
    void setProgrammedStop(const Time& t)override;
    void setStart(const Time& st) override;
};
#endif // CYCLICDEVICE_H
