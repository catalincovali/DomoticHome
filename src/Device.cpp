//name:Gavrilovska Kristina
#include "Device.h"
#include <stdexcept> 

int Device::currentId=0;

Device::Device(std::string n, double power)
    : name(n), powerConsumption(power), powerConsumed(0), isOn(false), keepDevicePlugged(false) { 
    id = ++currentId;    // Assign a unique ID to the device
}

void Device::turnOn() {
    if (isOn) return;
        isOn = true;

}

void Device::turnOff() {
    if (!isOn) return;
        isOn = false;
  
        isStopValid = false;
}

bool Device::getIsOn() const {
return isOn;
}

bool Device::getKeepDevicePlugged() {
    return keepDevicePlugged;
}

void Device::plugDevice(){
    keepDevicePlugged=true;
}

void Device::updatePowerConsumed(double newPower) {
    powerConsumed+=newPower;
}

double Device::getPowerConsumed() const {
    return powerConsumed;
}

double Device::getPowerConsumption() const {
    return powerConsumption;
}

void Device::setProgrammedStart(const MyTime& time){
    programmedStart = time;   
    isProgrammedStartValid=true;
}

void Device::setProgrammedStop(const MyTime& t){
    if(programmedStart<t)  {
             programmedStop = t;
             isProgrammedStopValid=true;
     }
    else {
        isProgrammedStopValid=false;
        throw std::invalid_argument("programmed stop time must be after programmed start time"); 
    }
}

MyTime Device::getProgrammedStart() const{
    return programmedStart;
}

MyTime Device::getProgrammedStop() const{
    return programmedStop;
}

int Device::getId() const{
   return id;
}

 std::string Device::getName() const{
    return name;
 }

 void Device::invalidateProgram(){
     isProgrammedStartValid=false;
     isProgrammedStopValid=false;
 }
 
bool Device::getIsProgrammedStopValid() const{
    return isProgrammedStopValid;
}


bool Device::getIsProgrammedStartValid() const{
    return isProgrammedStartValid;
}

MyTime Device::getStart() const{
   return start;
}

MyTime Device::getStop() const{
   return stop;
}

bool Device::getIsStartValid() const{
  return isStartValid;
}

bool Device::getIsStopValid() const{
   return isStopValid;
}

void Device::setStart(const MyTime& st){ 
    start=st;
    isStartValid=true;
}
