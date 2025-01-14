//nome: CATALIN COVALI
#include <iostream>
#include <string>
#include "Device.h"
#include "CyclicDevice.h"
#include "ManualDevice.h"
#include "DeviceManager.h"
#include "MyTime.h"
#include "Logger.h"
#include "UserInterface.h"


int main() {
  MyTime deviceCycle2(1,50);  // 1 hour and 50 minutes for Lavatrice
  MyTime deviceCycle3(3,15);  // 3 hours and 15 minutes for Lavastoviglie
  MyTime deviceCycle5(0,1);   // 1 minute for Tapparelle elettriche
  MyTime deviceCycle8(0,2);   // 2 minutes for Forno a microonde
  MyTime deviceCycle9(1,0);   // 1 hour for Asciugatrice
  MyTime deviceCycle10(1,0);  // 1 hour for Televisore

  // Create devices
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
  
  device7->plugDevice();

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
  std::string outputFile = "../output.txt";
  Logger log(outputFile);
  
  // Create a UserInterface object to handle user commands
  UserInterface user(manager, log);



  std::cout<<"\n\n";
  std::cout<<"██████╗  ██████╗ ███╗   ███╗ ██████╗ ████████╗██╗ ██████╗    ██╗  ██╗ ██████╗ ███╗   ███╗███████╗\n";
  std::cout<<"██╔══██╗██╔═══██╗████╗ ████║██╔═══██╗╚══██╔══╝██║██╔════╝    ██║  ██║██╔═══██╗████╗ ████║██╔════╝\n";
  std::cout<<"██║  ██║██║   ██║██╔████╔██║██║   ██║   ██║   ██║██║         ███████║██║   ██║██╔████╔██║█████╗  \n";
  std::cout<<"██║  ██║██║   ██║██║╚██╔╝██║██║   ██║   ██║   ██║██║         ██╔══██║██║   ██║██║╚██╔╝██║██╔══╝  \n";
  std::cout<<"██████╔╝╚██████╔╝██║ ╚═╝ ██║╚██████╔╝   ██║   ██║╚██████╗    ██║  ██║╚██████╔╝██║ ╚═╝ ██║███████╗\n";
  std::cout<<"╚═════╝  ╚═════╝ ╚═╝     ╚═╝ ╚═════╝    ╚═╝   ╚═╝ ╚═════╝    ╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n";
                                                                                                 

  std::cout<<"\n";
  std::cout<<"╔═════════════════════════════════════════╦═════════════════════════════════════════════╗\n";
  std::cout<<"║  MENU: ('Q' to quit)                    ║   DEVICES:                                  ║\n";
  std::cout<<"╠═════════════════════════════════════════╬═════════════════════════════════════════════╣\n";
  std::cout<<"║  - set ${DEVICENAME} on                 ║   - [  M  ] Impianto fotovoltaico           ║\n";
  std::cout<<"║  - set ${DEVICENAME} off                ║   - [01:50] Lavatrice                       ║\n";
  std::cout<<"║  - set ${DEVICENAME} ${START}           ║   - [03:15] Lavastoviglie                   ║\n";
  std::cout<<"║  - set ${DEVICENAME} ${START} ${STOP}   ║   - [  M  ] Pompa di calore + termostato    ║\n";
  std::cout<<"║  - rm ${DEVICENAME}                     ║   - [00:01] Tapparelle elettriche           ║\n";
  std::cout<<"║  - show                                 ║   - [  M  ] Scaldabagno                     ║\n";
  std::cout<<"║  - show ${DEVICENAME}                   ║   - [  M  ] Frigorifero                     ║\n";
  std::cout<<"║  - set time ${TIME}                     ║   - [00:02] Forno a microonde               ║\n";
  std::cout<<"║  - reset time                           ║   - [01:00] Asciugtrice                     ║\n";
  std::cout<<"║  - reset timers                         ║   - [01:00] Televisore                      ║\n";
  std::cout<<"║  - reset all                            ║                                             ║\n";
  std::cout<<"╚═════════════════════════════════════════╩═════════════════════════════════════════════╝\n\n";

  
  std::string prompt = "";
  while (prompt != "Q") {
    std::getline(std::cin, prompt);
    if (prompt != "Q")
      user.exeCommand(prompt);  
  }


  return 0;
}
