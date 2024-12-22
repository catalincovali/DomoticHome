#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <vector>
#include <map>

class DeviseManager {
private:
  std::vector<Device*> devices;
  double powerLimit;        // Maximum power that can be absorbed from the grid (3.5 kW)
  double currentPower;      // Current power usage

  Time currentTime(00,00);  //?

public:
  DeviseManager(double maxPower=3.5) : powerLimit{maxPower}, currentPower{0.0} }

  void addDevice(Device* device);

  void turnOnDevice(Device* device);
  void turnOffDevice(Device* device);
  void setTimer(Device* device, /* ? */ );
  void removeTimer(Device* device);

  double getPowerConsumption() const;

  void powerLimitPolicy();

  //For debug purposes
  void timeSimulations(Time time);
  void resetTime();
  void resetTimers();
  void resetAll();

};

#endif
