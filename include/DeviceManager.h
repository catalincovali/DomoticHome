//nome: CATALIN COVALI
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cmath>
#include <memory>
#include "Device.h"
#include "Time.h"


// The DeviceManager class is responsible for managing devices, tracking their power usage
// and handling time-based events like turning devices on and off based on timers or power limits
class DeviceManager {
private:

  std::vector< std::shared_ptr<Device> > devices;         // Registered devices
  std::vector< std::shared_ptr<Device> > activeDevices;   // Active devcies, needed for power limit policy
  double powerLimit;    // Maximum power that can be absorbed from the grid (3.5 kW)
  Time currentTime;     // Simulated current time (initialized to 00:00)

  // Adds a device to the active devices list
  void addToActiveDevices(std::shared_ptr<Device> d);

  // Enforces the power limit policy by turning off the most recently turned-on device.
  // Returns its name.
  std::string powerLimitPolicy();

  // Updates the power usage of the given device, based on how long it has been on
  void updateDeviceUsage( std::shared_ptr<Device> d );

public:

  // Constructor initializes the power limit, and power usage
  // If maxPower is not provided, it defaults to 3.5 kW
  DeviceManager(double maxPower=3.5);

  // Adds a device to the list of devices managed by this class
  // if its power consumption is within limits
  void addDevice( std::shared_ptr<Device> d );

  // Returns the current simulated time.
  Time getCurrentTime() { return currentTime; }

  // Returns the total power generated by the system, including both the generated power
  // based on the power limit and additional power produced by devices that generate power.
  double getGeneratedPower();

  double sumDeviceKw();

  // Returns the total power consumption of active devices.
  double getPowerUsage();

  // Updates kWh on the device and returns it.
  double getDeviceUsage(std::shared_ptr<Device> d);

  // Returns a vector of device names and their corresponding power usage. {name1, kwh1, name2, kWh2 ... }
  std::vector<std::string> getAllDevicesUsage();

  // Turns on the device, turning off others if needed to stay within the power limit.
  // Returns a vector of names: the last is the turned-on device, others were turned off.
  std::vector<std::string> turnOnDevice( std::shared_ptr<Device> d );

  // Turns off a device if it is currently on, and removes it from the list of active devices
  bool turnOffDevice( std::shared_ptr<Device> d );

  //This is used to schedule when the device should start
  void setStartTimer( std::shared_ptr<Device> d, const Time& time );

  //This schedules when the device should turn off
  void setStopTimer( std::shared_ptr<Device> d, const Time& time );

  //Invalidates scheduled start/end time
  void removeTimer( std::shared_ptr<Device> d );

  // Finds and returns a device by its name. Returns nullptr if not found
  std::shared_ptr<Device> findDeviceByName(const std::string& name) const;

  // Simulates the passage of time by incrementing the current time by one minute
  // Updates device states and handles time-based events.
  // Returns a vector { 1 , name1 , 0 , name2 , ... }
  // - A string representing the action ("1" for turning on, "0" for turning off).
  // - The name of the device that was turned on or off.
  std::vector<std::string> setTime(Time time);

  // For debugging: resets the time and turns off all devices.
  void resetTime();

  // For debugging: invalidates all device timers.
  void resetTimers();

  // Resets both the time and all timers, returning the system to an initial state.
  void resetAll();
};

#endif
