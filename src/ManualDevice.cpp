#include "ManualDevice.h"

ManualDevice::ManualDevice(std::string n, double power)
    : Device(n, power) {}

void ManualDevice::setProgrammedStart(const Time& time){
    programmedStart = time;
}

void ManualDevice::setProgrammedStop(const Time& t){
    if(programmedStart<t)  {
             programmedStop = t;
             isProgramValid=true;
     }
    else {
        throw std::invalid_argument("programmed stop time must be after programmed start time"); 
        isProgramValid=false;
    }
}
