//nome: CATALIN COVALI
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Device.h"
#include "Time.h"

// Manages devices, tracks power usage, and handles time-based events
class DeviceManager {
private:
  std::vector< std::shared_ptr<Device> > devices;   // Registered devices
  double powerLimit;    // Maximum power that can be absorbed from the grid (3.5 kW)
  double powerUsage;    // Current power usage
  std::vector< std::shared_ptr<Device> > activeDevices;   // Active devcies, needed for power limit policy

  Time currentTime(0,0);    // Simulated current time (initialized to 00:00)

public:
  DeviceManager(double maxPower=3.5);
  Time getCurrentTime() { return currentTime; }

  void addDevice( std::shared_ptr<Device> d );
  void turnOnDevice( std::shared_ptr<Device> d );
  void turnOffDevice( std::shared_ptr<Device> d );
  void setStartTimer( std::shared_ptr<Device> d, Time time );
  void setEndTimer( std::shared_ptr<Device> d, Time time );
  void removeTimer( std::shared_ptr<Device> d );
  void refreshPowerUsage( std::shared_ptr<Device> d );
  std::shared_ptr<Device> findDeviceByName(const std::string& name);

  // Returns the current total power usage
  double getPowerUsage() const;

  // Shuts down devices in reverse order to stay within power limit
  void powerLimitPolicy();

  // Simulates the passage of time by incrementing the current time by one minute.
  // Updates device states and handles time-based events.
  void setTime(Time time);

  //For debug purposes
  void resetTime();
  void resetTimers();
  void resetAll();

};

#endif
