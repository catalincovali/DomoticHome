//name:Gavrilovska Kristina
#include "CyclicDevice.h"

CyclicDevice::CyclicDevice(std::string n, double power, MyTime cycleDuration)
    : Device(n, power), cycleDuration(cycleDuration) {
}

void CyclicDevice::setProgrammedStart(const MyTime& time) {
    programmedStart = time;
    isProgrammedStartValid=true;
    programmedStop=programmedStart+cycleDuration.toMinutes();
      if(programmedStop<programmedStart){
         isProgrammedStopValid=false;
         return;
        }
    isProgrammedStopValid=true;
}

void CyclicDevice::setProgrammedStop(const MyTime& time){
    return;
}

void CyclicDevice::setStart(const MyTime& st) {
    start=st;
    isStartValid=true;
    stop=start+cycleDuration.toMinutes();
    
    if (stop < start){
      isStopValid=false;
      return;
    }

    isStopValid=true;
}
