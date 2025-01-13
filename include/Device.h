#ifndef DEVICE_H
#define DEVICE_H
#include <string>
#include "Time.h"

class Device {
protected:
    std::string name;               //device's name
    int id;                         // Unique and automatically calculated device's ID
    static int currentId;           // keeps track of the current ID to create different IDs for each object
    const double powerConsumption;  // energy consumption in kW
    double powerConsumed;           // energy consumed
    bool isOn;                      // reports whether the device is turned on or not
    bool keepDevicePlugged;         // reports which devices must remain on
    Time programmedStart;           // programmed Time when the device turns on
    Time programmedStop;            // programmed Time when the device turns off
    bool isProgrammedStartValid;    //reports if programmedStart is valid
    bool isProgrammedStopValid;     //reports if programmedStop is valid
    bool isStartValid=false;        //reports whether the start time is valid
    bool isStopValid=false;         //reports whether the end time is valid
    Time start;                     // Start time
    Time stop;                      // End time

public:
    Device(std::string n, double power);                //constructor
    virtual ~Device() {}                                //virtual destructor of the Device class

    void turnOn();                                      //turns on the device
    void turnOff();                                     //turns off the device
    bool getIsOn() const;                               //getter function of isOn

    bool getKeepDevicePlugged();                        //getter function of keepDevicePlugged
    void plugDevice();                                  //sets the variable keepDevicePlugged  to true

    void updatePowerConsumed(double newPower);          //updates the power consumed so far
    double getPowerConsumed() const;                    //getter function of powerConsumed

    double getPowerConsumption() const;                 //getter function of powerConsumption

    virtual void setProgrammedStart(const Time& time);  //set function of programmedStart
    virtual void setProgrammedStop(const Time& t);      //set function of programmedStop
    Time getProgrammedStart() const;                    //getter function of programmedStart
    Time getProgrammedStop() const;                     //getter function of programmedStop

    int getId() const;                                  //getter function of device's id

    std::string getName() const;                        //getter function of device's name

    void invalidateProgram();                           //sets isProgramValid to false
    bool getIsProgrammedStartValid() const;             //getter function of isProgrammedStartValid
    bool getIsProgrammedStopValid() const;              //getter function of isProgrammedStopValid

    Time getStart() const;                              //getter function of start
    Time getStop() const;                               //getter function of stop
    bool getIsStartValid() const;                       //getter function of isStartValid
    bool getIsStopValid() const;                        //getter function of isStopValid
    virtual void setStart(const Time& st);              //set function of start
};
#endif // DEVICE_H
