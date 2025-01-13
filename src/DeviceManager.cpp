//nome: CATALIN COVALI
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cmath>
#include <memory>
#include <algorithm>
#include "DeviceManager.h"
#include "Device.h"
#include "Time.h"



// Constructor that initializes the power limit and current power usage.
// If maxPower is not provided, the default value is 3.5 kW.
DeviceManager::DeviceManager(double maxPower) : powerLimit{maxPower}, powerUsage{0.0} {
  if (maxPower < 0)
    throw std::invalid_argument("[ERROR] Maximum power limit cannot be negative.");
}



// Adds a device to the list if its power consumption is within limits.
void DeviceManager::addDevice(std::shared_ptr<Device> d) {
  if(d->getPowerConsumption() < 0 && fabs(d->getPowerConsumption()) > powerLimit) {
    std::cerr << "[ERROR] Unable to add device '" << d->getName()
              << "'. Power consumption (" << d->getPowerConsumption()
              << " kW) exceeds the maximum allowable limit of " << powerLimit
              << " kW.\n";
    return;
  }

  devices.push_back(d);
}



// This method ensures that if the maximum threshold is exceeded
// devices are turned off according to the defined policy
void DeviceManager::addToActiveDevices(std::shared_ptr<Device> d) {
  // If the device should remain plugged, add it at the beginning of the activeDevices list
  if (d->getKeepDevicePlugged())
    activeDevices.insert( activeDevices.begin(), d );
  // Else add it at the end of active devices list
  activeDevices.push_back(d);
}



// Removes the device from the active devices list, turns it off, and returns its name.
std::string DeviceManager::powerLimitPolicy() {
  if(activeDevices.empty())
    throw std::runtime_error("[ERROR] No active devices to turn off to enforce the power limit.");

  std::shared_ptr<Device> lastDeviceTurnedOn = activeDevices.back();
  activeDevices.pop_back();
  DeviceManager::turnOffDevice(lastDeviceTurnedOn);
  return lastDeviceTurnedOn -> getName();
}



// Calculates the power consumed by the device based on the time it has been ON.
void DeviceManager::updateDeviceUsage(std::shared_ptr<Device> d) {
  // If device is off kWh might be already been refreshed or 0
  if (!d->getIsOn())
    return;

  // Device was never turned ON, no need to update
  if (!d->getIsStartValid())
    return;

  // Calculate the time the device has been on
  Time timeBeingON = currentTime - d->getStart();
  // Convert time to hours and calculate the power consumed in kWh
  double newValue = static_cast<double>(timeBeingON.toMinutes()) / 60 * d->getPowerConsumption();

  d->updatePowerConsumed( fabs(newValue) );
}



// Updates kWh on the device and returns it
double DeviceManager::getDeviceUsage(std::shared_ptr<Device> d) {
  DeviceManager::updateDeviceUsage(d);

  if(d->getIsOn())
    d->setStart(currentTime);

  return d->getPowerConsumed();
}



// Returns the total power generated by the system, including devices that produce power.
double DeviceManager::getGeneratedPower() {
  double powerProduced = static_cast<double>(currentTime.toMinutes()) / 60 * powerLimit;
  // Adds the power produced by devices that generate energy.
  for (auto& device : devices)
    if (device->getPowerConsumption() > 0)
      powerProduced += DeviceManager::getDeviceUsage(device);

  return powerProduced;
}



double DeviceManager::sumDeviceKw() {
  double output = 0.0;
  for (auto& d : devices)
    if (d->getIsOn())
      output += d->getPowerConsumption();
  return fabs(output);
}



// Returns the total power consumption of active devices
double DeviceManager::getPowerUsage() {
  powerUsage = 0.0;

  for (auto& device : devices)
    if (device->getPowerConsumption() < 0)
      powerUsage += DeviceManager::getDeviceUsage(device);

  return powerUsage;
}


// Returns a vector of device names and their corresponding power usage.
std::vector<std::string> DeviceManager::getAllDevicesUsage() {
  std::vector<std::string> output;

  for (auto& device : devices) {
    output.push_back(device->getName());  // Add device NAME
    output.push_back( std::to_string(DeviceManager::getDeviceUsage(device)) );  // Add device power usage kWh
  }
  return output;
}



// Turns on the device, turning off others if needed to stay within the power limit.
// Returns a vector of names: the last is the turned-on device, others are turned off.
std::vector<std::string> DeviceManager::turnOnDevice(std::shared_ptr<Device> d){
  std::vector<std::string> output;

  if (d->getIsOn()) {
    return {};
  }

  // Turn off devices until the total power usage is within the limit
  if(d->getPowerConsumption() < 0)
    while ( DeviceManager::sumDeviceKw() + fabs(d->getPowerConsumption()) > powerLimit)
      output.push_back( DeviceManager::powerLimitPolicy() );// Turn off a device and save its name

  DeviceManager::addToActiveDevices(d);
  d->turnOn();
  d->setStart(currentTime);

  // Add the name of the newly turned-on device to the output vector
  output.push_back( d->getName() );
  return output;
}





// Turns off a device if it is on. Removes it from the active devices list
// and updates the power consumption accordingly
void DeviceManager::turnOffDevice(std::shared_ptr<Device> d){
  if (!d->getIsOn())
    return;
  

  // Remove device from active devices list
  auto it = std::find(activeDevices.begin(), activeDevices.end(), d);
  if (it != activeDevices.end())
    activeDevices.erase(it);

  // When the device is turned off during its cycle
  if (d->getIsProgrammedStartValid() && d->getProgrammedStart() < currentTime)
    d->invalidateProgram();

  DeviceManager::updateDeviceUsage(d);
  d->turnOff();
  
}



void DeviceManager::setStartTimer(std::shared_ptr<Device> d, const Time& time) {
  d->setProgrammedStart(time);
}



void DeviceManager::setStopTimer(std::shared_ptr<Device> d, const Time& time) {
  d->setProgrammedStop(time);
}


// Invalidating any start or stop times
void DeviceManager::removeTimer(std::shared_ptr<Device> d) {
  d->invalidateProgram();
}





// Finds and returns the device with the given name
std::shared_ptr<Device> DeviceManager::findDeviceByName(const std::string& name) const{
  for (auto& device : devices)
    if (device->getName() == name)
      return device;

  std::cout << " [ERROR] Device '" << name << "' not found.\n";
  return nullptr;
}



// Simulates the passage of time and updates the state of devices, turning them on or off
// Enforces the power limit policy by turning off the most recently turned-on device.
//
// Returns a vcetor with:
// - A string representing the action ("1" for turning on, "0" for turning off).
// - the name of the device that was turned on or off.
std::vector<std::string> DeviceManager::setTime(Time time) {
  if(time < currentTime)
    throw std::invalid_argument("[ERROR] Time cannot go backwards");
  
  std::vector<std::string> output;

  while (currentTime != time) {
    // Check each device for scheduled start/finish times and turns it on or off accordingly
    for (auto& d : devices){
      if ( d->getIsOn() && currentTime == d->getProgrammedStart())
        d->invalidateProgram();

      if ( d->getIsProgrammedStartValid() && d->getProgrammedStart() == currentTime ) {
        output.push_back("1");  // Indicating the device is being turned on
        output.push_back(currentTime.toString(false));
        output.push_back(d->getName());
        DeviceManager::turnOnDevice(d);
      }
 
      if ( d->getIsProgrammedStopValid() && d->getProgrammedStop() == currentTime ) {
        output.push_back("0");  // Indicating the device is being turned off
        output.push_back(currentTime.toString(false));
        output.push_back(d->getName());
        DeviceManager::turnOffDevice(d);
      }

      if ( d->getIsStopValid() && d->getStop() == currentTime ) {
        output.push_back("0");  // Indicating the device is being turned off  
        output.push_back(currentTime.toString(false));
        output.push_back(d->getName());
        DeviceManager::turnOffDevice(d);
      }
    }
  // Move to the next time unit
  currentTime.increment();
  }

  return output;
}




// For debugging: resets the time and turns off all devices.
void DeviceManager::resetTime(){
  for (auto& device : devices)
    device -> turnOff();
  Time time;  // time = [00:00]
  currentTime = time;
}

// For debugging: invalidates all device timers.
void DeviceManager::resetTimers(){
  for (auto& device : devices) {
    device -> invalidateProgram();
  }
}

// Resets both the time and all timers, returning the system to an initial state.
void DeviceManager::resetAll(){
  DeviceManager::resetTime();
  DeviceManager::resetTimers();
  // reset kWh
  for (auto& device : devices)
    device->updatePowerConsumed( -device->getPowerConsumed() );
}
