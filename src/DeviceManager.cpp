//nome: CATALIN COVALI
#include <iostream>
#include <vector>
#include <stdexcept>
#include "DeviceManager.h"
#include "Device.h"
#include "Time.h"

// Initializes DeviceManager with a max power limit
DeviceManger::DeviceManager(double maxPower) : powerLimit{maxPower}, powerUsage{0.0} {
  if (maxPower < 0)
    throw std::invlaid_argument("Errore: La potenza massima non puo essere negativa.");
}


// Adds a new device to the device list
void DeviceManager::addDevice(std::shared_ptr<Device> d) {
  devices.push_back(d);
}


void DeviceManager::turnOnDevice(std::shared_ptr<Device> d){
  // Check if device is already ON
  if (d->isOn()) {
    std::cout << currentTime << " Il dispositivo '" << d->getName() << "è già acceso\n";
    return;
  }

  // If the device's power usage exceeds the limit, apply the power limit policy
  while (d->getPowerConsumption() + DeviceManager::getPowerUsage > powerLimit)
    DeviceManager::powerLimitPolicy();

  // Add device to the active devices list
  activeDevices.push_back(d);

  // output message
  std::cout << currenttime << " ";

  d->turnOn();
}


void DeviceManager::turnOffDevice(std::shared_ptr<Device> d){
  // Check if device is already OFF
  if (!d->isOn()) {
    std::cout << currentTime << " Il dispositivo '" << d->getName() << "è già spento\n";
    return;
  }

  // Search for the device in the active devices list
  auto it = std::find(activeDevices.begin(), activeDevices.end(), d);

  // Erese device from active devices list
  if (it != activeDevices.end())
    activeDevices.erese(it);

  // output message
  std::cout << currenttime << " ";

  d->turnOff();
}


void DeviceManager::setStartTimer(std::shared_ptr<Device> d, Time time) {
  d->setStartTime(time);
}

void DeviceManager::setEndTimer(std::shared_ptr<Device> d, Time time) {
  d->setFinishTime(time);
}

void DeviceManager::removeTimer(std::shared_ptr<Device> d) {
  // idk
}

/*
void DeviceManager::refreshPowerUsage(std::shared_ptr<Device> d) {
  double newValue = ( d->getStartTime() + turnOffTime ) d->getPowerConsumption()
  d->updatePowerConsumed()
}
*/

std::shared_ptr<Device> DeviceManager::findDeviceByName(const std::string& name) {
  for (auto& device : devices)
    if (device->getName() == name)
      return device;

  // Message if the device is not found
  std::cout << "[ERROR] Dispositivo '" << name << "' non esiste.\n";
  return nullptr;
}


double DeviceManager::getPowerUsage() const {
  // Initialize the total power usage to zero
  powerUsage = 0.0;

  // Add power consumption if device is ON
  for (const auto& device : devices)
    if (device -> isOn())
      powerUsage += device->getPowerConsumption();

  // Return the total power usage of all currently ON devices
  return powerUsage;
}


void DeviceManager::powerLimitPolicy() {
  // Retrieve the last device that was turned ON (from activeDevices)
  std::shared_ptr<Device> lastDeviceTurnedOn;
  lastDeviceTurnOn = activeDevices.back();

  // Remove last device from active devices list
  activeDevices.pop_back();

  // Turn off the last device that was turned on, following the power limit policy
  DeviceManager::turnOffDevice(lastDeviceTurnedOn);
}

void DeviceManager::setTime(Time time) {
  // time cannot go backward
  if(time < currentTime)
    throw std::invalid_argument("[ERROR] Non si puo tornare indietro nel tempo");

  // Increment time until it matches the specified time
  while (currentTime.increment() != time) {
    // Check each device for scheduled start/finish times
    for (const auto& device : devices){
      if (device->getStartTime() == currentTime)
        DeviceManager::turnOnDevice(device);

      if (device->getFinishTime() == currentTime)
        DeviceManager::turnOffDevice(device);
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

