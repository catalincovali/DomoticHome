#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <vector>
#include <map>

class DeviseManager {
private:
  std::map<std::string, Device> devices;

public:
  void addDevice(const std::string& name, Device device);
  void removeDevice(const std::string& name);
  Device* getDevice(const std::string& name);
  std::vector<Device> getAllDevices() const;

  void turnOnDevice(const std::string& name);
  void turnOffDevice(const std::string& name);
  void setTimer(const std::string& name, /* ? */ );
  void removeTimer(const std::string& name);

  double getTotalConsumption() const;
};
