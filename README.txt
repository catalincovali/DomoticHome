FINAL PROJECT: DOMOTIC SYSTEM

Course: Laboratorio di programmazione (B)
Degree Program: Ingegneria Informatica
Academic Year: 2024-2025
Group: CGB
Group members: Bortolazzi Luca, Covali Catalin, Gavrilovska Kristina


-Project Goal:
  The aim of the project is to create a Domotic System for managing and monitoring the energy consumption
  of ideally household objects while keeps track of the current system time.

-Project Structure and Division of Work:

   -Bortolazzi Luca:

     . MyTime.h/MyTime.cpp
          The MyTime class manages all device timers and the "house clock." A MyTime object consists of two
          variables: "minutes" and "hours." The class includes operator overloads to perform various
          operations between MyTime objects, as well as methods for converting the time into a string or the
          total number of minutes.
          
     . UserInterface.h/UserInterface.cpp
          The UserInterface class handles the commands provided by user input. Once a command is identified, 
          methods from the DeviceManager class are used to manage the various devices. Strings are then 
          generated, and the Logger class's "log" function is called to print the output.

     . Logger.h/Logger.cpp
          The Logger class is responsible for printing output to both the terminal and a log file based on the 	
          commands entered by the user. The log function, used by the UserInterface class, handles this 
          process.


   -Covali Catalin:

     . DeviceManager.h/DeviceManager.cpp
          The DeviceManager is responsible for managing all devices in the system, including
          adding devices and controlling their states. It tracks energy consumption and manages
          timers. Additionally, the DeviceManager enforces an energy policy. If necessary, 
          it will automatically turn off the last device turned on to prevent overloading the system.

     . main.cpp
          The main.cpp file serves as the entry point for the Domotic System. It initializes the
          devices (both manual and cyclic) with their respective energy usage and timers.
          The DeviceManager is instantiated to manage these devices, while a Logger is set up
          to record system events. The UserInterface handles user inputs, allowing interaction
          with the system through a menu-driven console interface. Users can control devices,
          set timers, and monitor the system's energy consumption. The program runs in a loop,
          processing commands until the user chooses to quit.


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
