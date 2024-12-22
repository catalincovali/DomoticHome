//nome: CATALIN COVALI
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Device.h"
#include "Time.

class DeviceManager {
private:
  std::vector< std::shared_ptr<Device> > devices;
  double powerLimit;    // Maximum power that can be absorbed from the grid (3.5 kW)
  double powerUsage;    // Current power usage
  std::vector< std::shared_ptr<Device> > activeDevices;   // needed for powerLimitPolicy

  Time currentTime(0,0);

public:
  DeviceManager(double maxPower=3.5);
  Time getCurrentTime() { return currentTime; }

  void addDevice( std::shared_ptr<Device> d );
  void turnOnDevice( std::shared_ptr<Device> d );
  void turnOffDevice( std::shared_ptr<Device> d );
  void setTimer( std::shared_ptr<Device> d, Time time );
  void removeTimer( std::shared_ptr<Device> d );

  double getPowerUsage() const;

  // Shuts down devices in reverse order until power consumption is less than production
  void powerLimitPolicy();

  // Simulates the passage of time by incrementing the current time by one minute.
  // It updates device states and handles time-based events.
  void setTime(Time time);

  //For debug purposes
  void resetTime();
  void resetTimers();
  void resetAll();

};

#endif
