#ifndef CYCLICDEVICE_H
#define CYCLICDEVICE_H
#include "Device.h"

class CyclicDevice : public Device {
private:
    MyTime cycleDuration;  //cycle duration of cyclic devices
public:

    CyclicDevice(std::string n, double power, MyTime cycleDuration);
    MyTime getCycleDuration() const {return cycleDuration;}             // getter function of cycleDuration
    void setProgrammedStart(const MyTime& time)override;
    void setProgrammedStop(const MyTime& t)override;
    void setStart(const MyTime& st) override;
};
#endif // CYCLICDEVICE_H
