#include "CyclicDevice.h"

CyclicDevice::CyclicDevice(std::string n, double power, Time cycleDuration)
    : Device(n, power), cycleDuration(cycleDuration) {
}

void CyclicDevice::setProgrammedStart(const Time& time) {
    programmedStart = time;
    programmedStop=programmedStart+cycleDuration.toMinutes();
    isProgramValid=true;
}

void CyclicDevice::setProgrammedStop(const Time& time){
    return;
}

void CyclicDevice::setStart(const Time& st) {
    start=st;
    isStartValid=true;
    stop=start+cycleDuration.toMinutes();
    isStopValid=true;
}
