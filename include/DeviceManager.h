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
  std::vector< std::shared_ptr<Device> > devices;   // Registered devices
  double powerLimit;    // Maximum power that can be absorbed from the grid (3.5 kW)
  double powerUsage;    // Current power usage
  std::vector< std::shared_ptr<Device> > activeDevices;   // Active devcies, needed for power limit policy

  Time currentTime(0,0);    // Simulated current time (initialized to 00:00)

  // Adds a device to the active devices list (internal method)
  void addToActiveDevices(std::shared_ptr<Device> d);

public:
  // Constructor initializes the power limit, and power usage
  // If maxPower is not provided, it defaults to 3.5 kW
  DeviceManager(double maxPower=3.5);

  // Returns the current simulated time.
  Time getCurrentTime() { return currentTime; }

  // Adds a device to the list of devices managed by this class
  void addDevice( std::shared_ptr<Device> d );

  // Turns on a device, checks if turning it on would exceed the power limit
  void turnOnDevice( std::shared_ptr<Device> d );

  // Turns off a device if it is currently on, and removes it from the list of active devices
  void turnOffDevice( std::shared_ptr<Device> d );

  //This is used to schedule when the device should start
  void setStartTimer( std::shared_ptr<Device> d, Time time );

  //This schedules when the device should turn off
  void setStopTimer( std::shared_ptr<Device> d, Time time );

  //Invalidates scheduled start/end time
  void removeTimer( std::shared_ptr<Device> d );

  // Updates the power usage of the given device, based on how long it has been on
  void refreshPowerUsage( std::shared_ptr<Device> d );

  // Finds and returns a device by its name. Returns nullptr if not found
  std::shared_ptr<Device> findDeviceByName(const std::string& name) const;

  // Prints out the stats for a specific device (total kWh)
  std::string getStats(std::shared_ptr<Device> d);

  // Prints out the stats for all devices currently registered with the manager.
  void showAllStats();

  // Returns the current total power usage
  double getPowerUsage() const;

  // Shuts down devices in reverse order to stay within power limit
  void powerLimitPolicy();

  // Simulates the passage of time by incrementing the current time by one minute
  // Updates device states and handles time-based events.
  void setTime(Time time);

  // For debugging: resets the time and turns off all devices.
  void resetTime();

  // For debugging: invalidates all device timers.
  void resetTimers();

  // Resets both the time and all timers, returning the system to an initial state.
  void resetAll();

};

#endif
