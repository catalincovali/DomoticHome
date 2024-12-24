//nome: CATALIN COVALI
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cmath>
#include <memory>
#include "DeviceManager.h"
#include "Device.h"
#include "Time.h"


// Constructor that initializes the power limit and current power usage.
// If maxPower is not provided, the default value is 3.5 kW.
DeviceManager::DeviceManager(double maxPower) : powerLimit{maxPower}, powerUsage{0.0} {
  if (maxPower < 0)
    throw std::invalid_argument("Errore: La potenza massima non puo essere negativa.");
}



// Adds a new device to the device list
void DeviceManager::addDevice(std::shared_ptr<Device> d) {
  devices.push_back(d);
}



// Adds a device to the active devices list
// If the device should stay plugged in or produce energy, it is added at the beginning
// of the list to give priority to other devices
void DeviceManager::turnOnDevice(std::shared_ptr<Device> d){
  // Check if device is already ON
  if (d->isOn()) {
    std::cout << " Il dispositivo '" << d->getName() << "è già acceso\n";
    return;
  }

  // If the device's power consumption exceeds the power limit, the policy is applied
  // to turn off other devices in order to stay within the limit
  while (d->getPowerConsumption() + DeviceManager::getPowerUsage() > powerLimit)
    DeviceManager::powerLimitPolicy();

  DeviceManager::addToActiveDevices(d);
  d->turnOn();
}



// This method ensures that if the maximum threshold is exceeded
// devices are turned off according to the defined policy
void DeviceManager::addToActiveDevices(std::shared_ptr<Device> d) {
  // If the device should remain plugged or produces energy, add it at the beginning of the activeDevices list
  if (d->getKeepDevicePlugged() && d->getPowerConsumed() > 0)
    activeDevices.insert( activeDevices.begin(), d );
  // Else add it at the end of active devices list
    activeDevices.push_back(d);
}


// Turns off a device if it is on. Removes it from the active devices list
// and updates the power consumption accordingly
void DeviceManager::turnOffDevice(std::shared_ptr<Device> d){
  // Check if device is already OFF
  if (!d->isOn()) {
    std::cout << " Il dispositivo '" << d->getName() << "è già spento\n";
    return;
  }

  // Remove device from active devices list
  auto it = std::find(activeDevices.begin(), activeDevices.end(), d);
  if (it != activeDevices.end())
    activeDevices.erase(it);

  DeviceManager::refreshPowerUsage(d);
  d->turnOff();
}



void DeviceManager::setStartTimer(std::shared_ptr<Device> d, Time time) {
  d->setStartTime(time);
}



void DeviceManager::setEndTimer(std::shared_ptr<Device> d, Time time) {
  if (time < currentTime) {
    std::cout << " [ERROR] Non puoi impostare timer nel passato\n";
    return;
  }
  d->setFinishTime(time);
}


// Invalidating any start or end times
void DeviceManager::removeTimer(std::shared_ptr<Device> d) {
  d->invalidateTime();
}



// Calculates the power consumed by the device based on the time it has been ON.
void DeviceManager::refreshPowerUsage(std::shared_ptr<Device> d) {
  // If device is off kWh might be already been refresh or 0
  if (!d->isOn())
    return;

  // Calculate the time the device has been on
  double timeBeingON = currentTime - d->getStart();
  // Convert time to hours and calculate the power consumed in kWh
  double newValue = timeBeingON.toMinutes() / 60 * d->getPowerConsumption();

  d->updatePowerConsumed(newValue);
}


// Finds and returns the device with the given name
std::shared_ptr<Device> DeviceManager::findDeviceByName(const std::string& name) const{
  for (auto& device : devices)
    if (device->getName() == name)
      return device;

  // Message if the device is not found
  std::cout << " [ERROR] Dispositivo '" << name << "' non esiste.\n";
  return nullptr;
}


// Returns a string with the stats of a device
std::string DeviceManager::getStats(std::shared_ptr<Device> d) {
  // Update before printing infos
  if (d->getIsOn()) {
    DeviceManager::refreshPowerUsage(d);
    d->setStart(currentTime);
  }

  if (d->getPowerConsumption() < 0)
    return " Il dispositivo " + d->getName() + "ha consumato" + d->getPowerConsumed() + "kWh\n";

  if (d->getPowerConsumption() > 0)
    return " Il dispositivo " + d->getName() + "ha prodotto" + d->getPowerConsumed() + "kWh\n";

  return "Il dispositivo " + d->getName() + " non ha né prodotto né consumato energia.\n";
}


// Displays stats for all registered devices
void DeviceManager::showAllStats() {

  std::string result = "";
  double powerProduced = currentTime.toMinutes() / 60 * powerLimit;
  double powerConsumed = 0;

  // Calculates total power produced and consumed by all devices
  for (auto& device : devices) {
    if (device->getPowerConsumption() > 0)
      powerProduced += device->getPowerConsumed();

    if (device->getPowerConsumption() < 0)
      powerConsumed += device->getPowerConsumed();

    result += "  -" + DeviceManager::getStats(device);
  }

  std::cout << " Attualmente il sistema ha prodotto " << powerProduced <<" kWh ";
  std::cout << "e consumato " << fabs(powerConsumed) <<" kWh. Nello specifico";
  std::cout << result;
}


// Returns the total power consumption of the system, considering only devices that are on.
double DeviceManager::getPowerUsage() const {
  powerUsage = 0.0;

  // Add power consumption if device is ON
  for (const auto& device : devices)
    if (device -> isOn() && device->getPowerConsumption() < 0)
      powerUsage += device->getPowerConsumption();

  return fabs(powerUsage);
}


// Applies the power limit policy: turns off the most recently turned on device
// to stay within the power limit
void DeviceManager::powerLimitPolicy() {
  if(activeDevices.empty())
    throw std::runtime_error("[ERROR] Non ci sono dispositivi attivi da spegnere per rispettare il limite di potenza");

  std::shared_ptr<Device> lastDeviceTurnedOn = activeDevices.back();
  activeDevices.pop_back();
  DeviceManager::turnOffDevice(lastDeviceTurnedOn);
}

// Simulates the passage of time and updates the state of devices, turning them on or off
// based on their timers
void DeviceManager::setTime(Time time) {
  if(time < currentTime)
    throw std::invalid_argument("[ERROR] Non si puo tornare indietro nel tempo");

  while (currentTime != time) {
    currentTime.increment();
    // Check each device for scheduled start/finish times and turns it on or off accordingly
    for (const auto& device : devices){
      if (device->getStartTime() == currentTime && device->isTimerValid())
        DeviceManager::turnOnDevice(device);

      if (device->getFinishTime() == currentTime && device->isTimerValid())
        DeviceManager::turnOffDevice(device);
    }
  }
}



// For debugging: resets the time and turns off all devices.
void DeviceManager::resetTime(){
  for (const auto& device : devices)
    device -> turnOff();
  currentTime(0,0);
}

// For debugging: invalidates all device timers.
void DeviceManager::resetTimers(){
  for (const auto& device : devices)
    device -> invalidateTimer();
}

// Resets both the time and all timers, returning the system to an initial state.
void DeviceManager::resetAll(){
  DeviceManager::resetTime();
  DeviceManager::resetTimers();
}

