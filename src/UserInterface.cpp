#include <iostream>
#include <string>
#include <vector>
#include "UserInterface.h"
#include "DeviceManager.h"
#include "Device.h"
#include "Time.h"


UserInterface::UserInterface(DeviceManager& manager, Logger& logger) : dm{manager}, lgr{logger} {
	commandMap = {
			{"set", [this](std::istringstream& iss, DeviceManager& dm) { handleSet(iss, dm); }},
		    {"show", [this](std::istringstream& iss, DeviceManager& dm) { handleShow(iss, dm); }},
		    {"reset", [this](std::istringstream& iss, DeviceManager& dm) { handleReset(iss, dm); }},
		    {"rm", [this](std::istringstream& iss, DeviceManager& dm) { handleReset(iss, dm); }}
		};
}



void UserInterface::exeCommand(const std::string& command){
	std::istringstream iss(command);	//per flusso di input
	std::string firstW;					//firstW cossisponde al comando (prima parola)
	iss >> firstW;						//divido il flusso in parole
	
	auto iter = commandMap.find(firstW);	//iteratore nella mappa dei comandi
	if(it != commandMap.end())				//non punta al primo elemento dopo l'ultimo
		it->second(iss);					//second(iss) accede al valore associato a chiave trovata
	else
		lgr.log( "comando non valido!\n" );
}



void setCommand(std::istringstream& iss, DeviceManager& dm){
	std::string secondW, thirdW, fourthW;
	iss >> secondW >> thirdW;
	
	if( thirdW == "on" ){		//"set ${DEVICENAME} on"
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			std::vector<std::string> v = dm.turnOnDevice( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Il dispositivo " + v.at(v.size() -1) + " si e' acceso\n" );
		}
	}
	else if( thirdW == "off" ){		//"set ${DEVICENAME} off"
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			dm.turnOffDevice( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Il dispositivo " + secondW + " si e' spento\n" );
		}
	}
	else if( secondW == "time" ){	//"set time ${TIME}"
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime() + "\n" );
		dm.setTime( Time::stringToTime( thirdW ) );
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime() + "\n" );
	}
	else if( !secondW.empty() ){							//set ${DEVICENAME} ${START} [${STOP}]
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			dm.setStartTime( devPtr, Time::stringToTime( thirdW ) );
			if(iss >> fourthW)
				dm.setEndTimer( devPtr, Time::stringToTime( fourthW ) );
		}
			
		Device& devRef = *devPtr;
		lgr.log( dm.getCurrentTime().toString() );
		lgr.log( " Impostato un timer per il dispositivo " + secondW );
		lgr.log( " dalle " + devRef.getStartTime() + " alle " + devRef.getFinishTime() + "\n" );
		
	}
	else
		lgr.log( "comando non valido\n" );
}



void showCommand(std::istringstream& iss, DeviceManager& dm){
	std::string secondW;
	iss >> secondW;
	
	if(secondW.empty()){		//"show"
		std:.vector<std::string> v = dm.getAllDevicesUsage();
		lgr.log( dm.getCurrentTime().toString() );
		lgr.log( " Attualmente il sistema ha prodotto " + dm.getGeneratedPower() );
		lgr.log( "kWh e consumato " + dm.getPowerUsage() + "kWh\n" );
		lgr.log( "Nello specifico:\n" );
		for(int i=0; i<v.size(); i++)
			lgr.log( "il dispositivo " + v[i] + " ha consumato " + v[++i] + "kWh\n" );
	}
	else{						//"show ${DeviceName}"
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			lgr.log( dm.getCurrentTime().toString() );
			lgr.log( " il dispositivo " + secondW + " ha attualmente consumato " + dm.getStats( devPtr ) + " kWh\n" ); 
		}
	}
}



void resetCommand(std::istringstream& iss, DeviceManager& dm){
	std::string secondW;
	iss >> secondW;
	
	if( secondW == "time" ){			//"reset time"
		dm.resetTime();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime() + "\n" );
	}
	else if( secondW == "timers" ){		//"reset timers"
		lgr.log( dm.getCurrentTime().toString() );
		dm.resetTimers();
		lgr.log( "i timers sono stati resettati\n" );
	}
	else if( secondW == "all" ){		//"reset all"
		dm.resetAll();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime() + "\n" );
		lgr.log( "i timers sono stati resettati\n" );
	}
	else
		lgr.log( "comando non valido\n" );
}



void rmCommand(std::istringstream& iss, DeviceManager& dm){
	std::string secondW;
	iss >> secondW;
	
	if( !secondW.empty() ){		//"rm ${DeviceName}"
		td::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			dm.removeTimer( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Rimosso il timer dal dispositivo " + secondW + "\n" );
		}
	}
	else
		lgr.log( "comando non valido\n" );
}








