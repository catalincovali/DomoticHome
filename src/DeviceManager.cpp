//nome: CATALIN COVALI
#include <iostream>
#include <vector>
#include <stdexcept>
#include "DeviceManager.h"
#include "Device.h"
#include "Time.h"

DeviceManger::DeviceManager(double maxPower) : powerLimit{maxPower}, powerUsage{0.0} {
  if (maxPower < 0)
    throw std::invlaid_argument("Errore: La potenza massima non puo essere negativa.");
}

void DeviceManager::addDevice(std::shared_ptr<Device> d) {
  devices.push_back(d);
}


void DeviceManager::turnOnDevice(std::shared_ptr<Device> d){
  if (d->isOn())
    std::cout << currentTime << " Il dispositivo '" << d->getName() << "è già acceso\n";

  while (d->getKW() + DeviceManager::getPowerUsage > powerLimit) { //[?]
    DeviceManger::powerLimitPolicy();
  }

  d->turnOn();
  activeDevices.push_back();
}


void DeviceManager::turnOffDevice(std::shared_ptr<Device> d){
  if (!d->isOn())
    std::cout << currentTime << " Il dispositivo '" << d->getName() << "è già spento\n";

  auto it = std::find(activeDevices.begin(), activeDevices.end(), d);
  if (it != activeDevices.end())
    activeDevices.erese(it);

  d->turnOff();


}


double DeviceManager::getPowerUsage() const {
  powerUsage = 0.0;
  for (const auto& deivce : devices)
    if (device -> isOn())
      powerUsage += device->getKW(); //[?]

  return powerUsage;
}


void DeviceManager::powerLimitPolicy() {
  std::shared_ptr<Device> lastDeviceTurnedOn;
  lastDeviceTurnOn = activeDevices.back();
  activeDevices.pop_back();
  DeviceManager::turnOffDevice(lastDeviceTurnedOn);
}

void setTime(Time time) {
  if(time < currentTime)
    throw std::invalid_argument("Errore: Non si puo tornare indietro nel tempo");

  while (currentTime.increment() != time) {
    for (const auto& device : devices){
      if (device->getStartTime() == currentTime)
        DeviceManger::turnOnDevice(device);
      if (device->getFinishTime() == currentTime)
        DeviceManger::turnOffDevice(device);
    }
  }
}

// For debug purposes
void DeviceManager::resetTime(){
  currentTime.reset();//[?]
}

void DeviceManager::resetTimers(){
  for (const auto& device : devices){
    device -> setStartTime(0,-1);//[?]
    device -> setFinishTime(0,-1);//[?]
  }
}

void DeviceManager::resetAll(){
  DeviceManger::resetTime()
  DeviceManger::resetTimers()
}

