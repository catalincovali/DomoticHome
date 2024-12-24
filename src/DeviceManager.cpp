//nome: CATALIN COVALI
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cmath>
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



// Turns on the device if it’s off. Enforces power limit policy if needed
void DeviceManager::turnOnDevice(std::shared_ptr<Device> d){
  // Check if device is already ON
  if (d->isOn()) {
    std::cout << currentTime << " Il dispositivo '" << d->getName() << "è già acceso\n";
    return;
  }

  // If the device's power usage exceeds the limit, apply the power limit policy
  while (d->getPowerConsumption() + DeviceManager::getPowerUsage > powerLimit)
    DeviceManager::powerLimitPolicy();

  // Needed for counting kWh correctly in `refreshPowerUsage()`
  if (currentTime != d->getStartTime())
    d->setStartTime(currentTime);

  DeviceManager::addToActiveDevices(d);
  std::cout << currentTime << " ";
  d->turnOn();
}



// This method ensures that if the maximum threshold is exceeded
// devices are turned off according to the defined policy
void DeviceManager::addToActiveDevices(std::shared_ptr<Device> d) {
  // If the device should remain plugged or produces energy, add it at the beginning of the activeDevices list
  if (d->getKeepDevicePlugged() && d->getPowerConsumed() > 0)
    activeDevices.insert( activeDevices.begin(), d );
  // Else add it at the end of active devices list
    activeDevices.push_back();
}



// Turns off the device if it’s on. Removes from active list and updates power usage.
void DeviceManager::turnOffDevice(std::shared_ptr<Device> d){
  // Check if device is already OFF
  if (!d->isOn()) {
    std::cout << currentTime << " Il dispositivo '" << d->getName() << "è già spento\n";
    return;
  }

  // Remove device from active devices list
  auto it = std::find(activeDevices.begin(), activeDevices.end(), d);
  if (it != activeDevices.end())
    activeDevices.erese(it);

  // output message
  std::cout << currentTime.toString() << " ";

  DeviceManger::refreshPowerUsage(d);
  d->turnOff();
}



void DeviceManager::setStartTimer(std::shared_ptr<Device> d, Time time) {
  d->setStartTime(time);
}



void DeviceManager::setEndTimer(std::shared_ptr<Device> d, Time time) {
  if (time < currentTime) {
    std::cout << "[ERROR] Non puoi impostare timer nel passato\n";
    return;
  }
  d->setFinishTime(time);
}



void DeviceManager::removeTimer(std::shared_ptr<Device> d) {
  // idk
}



// Calculates the power consumed by the device based on the time it has been ON.
void DeviceManager::refreshPowerUsage(std::shared_ptr<Device> d) {
  // Total time device has been on since last TURN ON
  double timeBeingON = currentTime - d->getStartTime();
  // Convert time to hours and calculate the power consumed in kWh
  double newValue = timeBeingON.toMinutes() / 60 * d->getPowerConsumption()

  d->updatePowerConsumed(newValue);
}



std::shared_ptr<Device> DeviceManager::findDeviceByName(const std::string& name) {
  for (auto& device : devices)
    if (device->getName() == name)
      return device;

  // Message if the device is not found
  std::cout << "[ERROR] Dispositivo '" << name << "' non esiste.\n";
  return nullptr;
}



std:string DeviceManager::getStats(std::shared_ptd<Device> d) {
  // Update before printing infos
  if (d->getIsOn()) {
    DeviceManager::refreshPowerUsage(d);
    d->setStartTimer();
  }

  if (d->getPowerConsuption() < 0)
    return " Il dispositivo " + d->getName() + "ha consumato" + d->getPowerConsumed() + "kWh";

  if (d->getPowerConsuption() > 0)
    return " Il dispositivo " + d->getName() + "ha prodotto" + d->getPowerConsumed() + "kWh";
}



std::string DeviceManager::getAllStats() {

  std::string result = "";
  double powerProduced = currentTime.toMinutes() / 60 * powerLimit;

  for (auto& device : devices) {

    if (device->getPowerConsumption() > 0)
      powerProduced += device->getPowerConsumed();

    if (device->getPowerConsumption() < 0)
      powerConsumed += device->getPowerConsumed();
    result += "  -" + DeviceManager::showStats(device);

  }

  std::cout << currentTime.toString()
  std::cout << "Attualmente il sistema ha prodotto " << powerProduced <<" kWh ";
  std::cout << "e consumato " << fabs(powerConsumed) <<" kWh. Nello specifico";
  std::cout << result;
}



double DeviceManager::getPowerUsage() const {
  // Initialize the total power usage to zero
  powerUsage = 0.0;

  // Add power consumption if device is ON
  for (const auto& device : devices)
    if (device -> isOn() && device->getPowerConsumption < 0)
      powerUsage += device->getPowerConsumption();

  // Return the total power usage of all currently ON devices
  return fabs(powerUsage);
}



// Turns off the last device turned on to stay within power limits.
void DeviceManager::powerLimitPolicy() {
  std::shared_ptr<Device> lastDeviceTurnedOn;
  lastDeviceTurnOn = activeDevices.back();
  activeDevices.pop_back();
  DeviceManager::turnOffDevice(lastDeviceTurnedOn);
}



// Simulates time increment and triggers devices' start/finish times.
void DeviceManager::setTime(Time time) {
  // time cannot go backward
  if(time < currentTime)
    throw std::invalid_argument("[ERROR] Non si puo tornare indietro nel tempo");

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
  currentTime(0.0);
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

