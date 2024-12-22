//nome: CATALIN COVALI
#include <iostream>
#include <vector>
#include <stdexcept>
#include "DeviceManager.h"
#include "Device.h"

DeviceManger::DeviceManager(double maxPower) : powerLimit{maxPower}, powerUsage{0.0} {
  if (maxPower < 0)
    throw std::invlaid_argument("Errore: La potenza massima non puo essere negativa.");
}


