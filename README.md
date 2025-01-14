FINAL PROJECT: DOMOTIC SYSTEM

Course: Laboratorio di programmazione (B)
Degree Program: Ingegneria Informatica 
Academic Year: 2024-2025
Group: CGB
Group members: Bortolazzi Luca, Covali Catalin, Gavrilovska Kristina

-Project Goal:
  The aim of the project is to create a Domotic System for managing and monitoring the energy consumption
  of ideally household objects while keeps track of the current system time.

-Project Division:

   -Bortolazzi Luca:

     . Time.h/Time.cpp

          ---
     . UserInterface.h/UserInterface.cpp
          ---

     . Logger.h/Logger.cpp
          ---


   -Covali Catalin:

     . DeviceManager.h/DeviceManager.cpp
          ---

     . main.cpp
          ---


   -Gavrilovska Kristina:
 
     . Device.h/Device.cpp
          Base class of all Device's types both those that consume
          energy and those that produce energy.

     . CyclicDevice.h/CyclicDevice.cpp
          Derived class of Device specifies the aspects of devices that have
          a cycle duration at the end of which they turn off automatically.

     . ManualDevice.h/ManualDevice.cpp
          Derived class of Device specifies the aspects of devices that do not
          have a cycle duration but they only turn off manually.
