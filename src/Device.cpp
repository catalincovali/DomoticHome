#include "Device.h"
#include <iostream>
#include <stdexcept> 

int Device::currentId=0;

Device::Device(std::string n, double power)
    : name(n), powerConsumption(power), powerConsumed(0), isOn(false), keepDevicePlugged(false) { 
    id = ++currentId;    // Assign a unique ID to the device
}

void Device::turnOn() {
    if (isOn) return;     //DA SISTEMARE
        isOn = true;
}

void Device::turnOff() {
    if (!isOn) return;     //DA SISTEMARE
        isOn = false;
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

void Device::setProgrammedStart(const Time& time){
    programmedStart = time;    
}

void Device::setProgrammedStop(const Time& t){
    if(programmedStart<t)  {
             programmedStop = t;
             isProgramValid=true;
     }
    else {
        throw std::invalid_argument("programmed stop time must be after programmed start time"); 
        isProgramValid=false;
    }
}

Time Device::getProgrammedStart() const{
    return programmedStart;
}

Time Device::getProgrammedstop() const{
    return programmedStop;
}

int Device::getId() const{
   return id;
}

 std::string Device::getName() const{
    return name;
 }

 void Device::invalidateProgram(){
     isProgramValid=false;
 }
 
bool Device::getIsProgramValid() const{
    return isProgramValid;
}

Time Device::getStart() const{
   return start;
}

Time Device::getStop() const{
   return stop;
}

bool Device::getIsStartValid() const{
  return isStartValid;
}

bool Device::getIsStopValid() const{
   return isStopValid;
}

void Device::setStart(const Time& st){ 
    start=st;
    isStartValid=true;
}
