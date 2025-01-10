//nome: CATALIN COVALI
#include <iostream>
#include <string>
#include "Device.h"
#include "CyclicDevice.h"
#include "ManualDevice.h"
#include "DeviceManager.h"
#include "Time.h"
#include "Logger.h"
#include "UserInterface.h"


int main() {

  Time washingMachineCycle(1,50);
  Time dishwasherCycle(3,15);
  Time electricBlindsCycle(0,1);
  Time microwaveCycle(0,2);
  Time dryerCycle(1,0);
  Time televisionCycle(1,0);

  std::shared_ptr<Device> device1 = std::make_shared<ManualDevice>("Impianto fotovoltaico", 1.5);
  std::shared_ptr<Device> device2 = std::make_shared<CyclicDevice>("Lavatrice", -2.0, washingMachineCycle);
  std::shared_ptr<Device> device3 = std::make_shared<CyclicDevice>("Lavastoviglie", -1.5, dishwasherCycle);
  std::shared_ptr<Device> device4 = std::make_shared<ManualDevice>("Pompa di calore + termostato", -2.0);
  std::shared_ptr<Device> device5 = std::make_shared<CyclicDevice>("Tapparelle elettriche", -0.3, electricBlindsCycle);
  std::shared_ptr<Device> device6 = std::make_shared<ManualDevice>("Scaldabagno", -0.3);
  std::shared_ptr<Device> device7 = std::make_shared<ManualDevice>("Frigorifero", -0.4);
  std::shared_ptr<Device> device8 = std::make_shared<CyclicDevice>("Forno a microonde", -0.8, microwaveCycle);
  std::shared_ptr<Device> device9 = std::make_shared<CyclicDevice>("Asciugatrice", -0.5, dryerCycle);
  std::shared_ptr<Device> device10 = std::make_shared<CyclicDevice>("Televisore", -0.2, televisionCycle);

  DeviceManager manager;
  manager.addDevice(device1);
  manager.addDevice(device2);
  manager.addDevice(device3);
  manager.addDevice(device4);
  manager.addDevice(device5);
  manager.addDevice(device6);
  manager.addDevice(device7);
  manager.addDevice(device8);
  manager.addDevice(device9);
  manager.addDevice(device10);
  

  // Set up logging functionality 
  std::string outputFile = "output.txt";
  Logger log(outputFile);
  
  // Create a UserInterface object to handle user commands
  UserInterface user(manager, log);

  // Dysplay available commands
  std::cout<<"\n\n\nMENU: ('Q' to quit)\n\n";
  std::cout<<"set ${DEVICENAME} on\n";
  std::cout<<"set ${DEVICENAME} off\n";
  std::cout<<"set ${DEVICENAME} ${START}\n";
  std::cout<<"set ${DEVICENAME} ${START} ${STOP}\n";
  std::cout<<"rm ${DEVICENAME}\n";
  std::cout<<"show\n";
  std::cout<<"show ${DEVICENAME}\n";
  std::cout<<"set time ${TIME}\n";
  std::cout<<"reset time\n";
  std::cout<<"reset times\n";
  std::cout<<"reset all\n\n";

  
  std::string prompt = "";
  while (prompt != "Q") {
    std::getline(std::cin, prompt);
    if (prompt != "Q")
      user.exeCommand(prompt);  
  }


  return 0;
}
