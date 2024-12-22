//nome: CATALIN COVALI
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <vector>

class DeviseManager {
private:
  std::vector<Device*> devices;
  double powerLimit;                // Maximum power that can be absorbed from the grid (3.5 kW)
  double currentPower;              // Current power usage
  std::vector<Device*> devicesON;   // needed for powerLimitPolicy

  Time currentTime(00,00);  //?

public:
  DeviseManager(double maxPower=3.5) : powerLimit{maxPower}, currentPower{0.0} }
  Time getCurrentTime() { return currentTime; }

  void addDevice(Device* device);

  void turnOnDevice(Device* device);
  void turnOffDevice(Device* device);
  void setTimer(Device* device, Time time );
  void removeTimer(Device* device);

  double getPowerConsumption() const;

  // Shuts down devices in reverse order until power consumption is less than production
  void powerLimitPolicy();

  //For debug purposes
  void timeSimulations(Time time);
  void resetTime();
  void resetTimers();
  void resetAll();

};

#endif
