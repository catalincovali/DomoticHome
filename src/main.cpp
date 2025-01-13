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

  Time deviceCycle2(1,50);
  Time deviceCycle3(3,15);
  Time deviceCycle5(0,1);
  Time deviceCycle8(0,2);
  Time deviceCycle9(1,0);
  Time deviceCycle10(1,0);

  std::shared_ptr<Device> device1 = std::make_shared<ManualDevice>("Impianto fotovoltaico", 1.5);
  std::shared_ptr<Device> device2 = std::make_shared<CyclicDevice>("Lavatrice", -2.0, deviceCycle2);
  std::shared_ptr<Device> device3 = std::make_shared<CyclicDevice>("Lavastoviglie", -1.5, deviceCycle3);
  std::shared_ptr<Device> device4 = std::make_shared<ManualDevice>("Pompa di calore + termostato", -2.0);
  std::shared_ptr<Device> device5 = std::make_shared<CyclicDevice>("Tapparelle elettriche", -0.3, deviceCycle5);
  std::shared_ptr<Device> device6 = std::make_shared<ManualDevice>("Scaldabagno", -0.3);
  std::shared_ptr<Device> device7 = std::make_shared<ManualDevice>("Frigorifero", -0.4);
  std::shared_ptr<Device> device8 = std::make_shared<CyclicDevice>("Forno a microonde", -0.8, deviceCycle8);
  std::shared_ptr<Device> device9 = std::make_shared<CyclicDevice>("Asciugatrice", -0.5, deviceCycle9);
  std::shared_ptr<Device> device10 = std::make_shared<CyclicDevice>("Televisore", -0.2, deviceCycle10);

  DeviceManager manager();
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
  std::string outputFile = "../output.txt";
  Logger log(outputFile);
  
  // Create a UserInterface object to handle user commands
  UserInterface user(manager, log);






  std::cout<<"\n\n";
  std::cout<<"        ____                        __  _      __  __                   \n";
  std::cout<<"       / __ \\____  ____ ___  ____  / /_(_)____/ / / /___  ____ ___  ___\n"; 
  std::cout<<"      / / / / __ \\/ __ `__ \\/ __ \\/ __/ / ___/ /_/ / __ \\/ __ `__ \\/ _ \\\n";
  std::cout<<"     / /_/ / /_/ / / / / / / /_/ / /_/ / /__/ __  / /_/ / / / / / /  __/\n";
  std::cout<<"    /_____/\\____/_/ /_/ /_/\\____/\\__/_/\\___/_/ /_/\\____/_/ /_/ /_/\\___/\n\n"; 

  std::cout<<"\n\n";
  std::cout<<"+-----------------------------------------+-------------------------------------+\n";
  std::cout<<"|  MENU: ('Q' to quit)                    |   DEVICES:                          |\n";
  std::cout<<"|                                         |                                     |\n";
  std::cout<<"|  - set ${DEVICENAME} on                 |   - Impianto fotovoltaico           |\n";
  std::cout<<"|  - set ${DEVICENAME} off                |   - Lavatrice                       |\n";
  std::cout<<"|  - set ${DEVICENAME} ${START}           |   - Lavastoviglie                   |\n";
  std::cout<<"|  - set ${DEVICENAME} ${START} ${STOP}   |   - Pompa di calore + termostato    |\n";
  std::cout<<"|  - rm ${DEVICENAME}                     |   - Tapparelle elettriche           |\n";
  std::cout<<"|  - show                                 |   - Scaldabagno                     |\n";
  std::cout<<"|  - show ${DEVICENAME}                   |   - Frigorifero                     |\n";
  std::cout<<"|  - set time ${TIME}                     |   - Forno a microonde               |\n";
  std::cout<<"|  - reset time                           |   - Asciugtrice                     |\n";
  std::cout<<"|  - reset times                          |   - Televisore                      |\n";
  std::cout<<"|  - reset all                            |                                     |\n";
  std::cout<<"+-----------------------------------------+-------------------------------------+\n\n";

  
  std::string prompt = "";
  while (prompt != "Q") {
    std::getline(std::cin, prompt);
    if (prompt != "Q")
      user.exeCommand(prompt);  
  }


  return 0;
}
