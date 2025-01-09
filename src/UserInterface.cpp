#include <iostream>
#include <vector>
#include "UserInterface.h"
#include "DeviceManager.h"
#include "Device.h"
#include "Time.h"
#include "Logger.h"


UserInterface::UserInterface(DeviceManager& manager, Logger& logger) : dm{manager}, lgr{logger} {
	commandMap = {
			{"set", [this](std::istringstream& iss, DeviceManager& dm, Logger& lgr) { setCommand(iss, dm, lgr); }},
		    {"show", [this](std::istringstream& iss, DeviceManager& dm, Logger& lgr) { showCommand(iss, dm, lgr); }},
		    {"reset", [this](std::istringstream& iss, DeviceManager& dm, Logger& lgr) { resetCommand(iss, dm, lgr); }},
		    {"rm", [this](std::istringstream& iss, DeviceManager& dm, Logger& lgr) { rmCommand(iss, dm, lgr); }}
		};
}



void UserInterface::exeCommand(const std::string& command){
	std::istringstream iss(command);	//per flusso di input
	std::string firstW;					//firstW cossisponde al comando (prima parola)
	iss >> firstW;						//divido il flusso in parole
	
	auto iter = commandMap.find(firstW);	//iteratore nella mappa dei comandi
	if(iter != commandMap.end())			//non punta al primo elemento dopo l'ultimo
		iter->second(iss, dm, lgr);			//second(iss): accede al valore associato a chiave trovata (valore = function)
	else
		lgr.log( "comando non valido!\n" );
}



void setCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr){
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
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
		dm.setTime( stringToTime( thirdW ) );
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
	}
	else if( !secondW.empty() ){							//set ${DEVICENAME} ${START} [${STOP}]
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			dm.setStartTimer( devPtr, stringToTime( thirdW ) );
			if(iss >> fourthW)
				dm.setStopTimer( devPtr, stringToTime( fourthW ) );
		}
			
		Device& devRef = *devPtr;
		lgr.log( dm.getCurrentTime().toString() );
		lgr.log( " Impostato un timer per il dispositivo " + secondW );
		lgr.log( " dalle " + devRef.getStart().toString(false) + " alle " + devRef.getStop().toString(false) + "\n" );
		
	}
	else
		lgr.log( "comando non valido\n" );
}



void showCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr){
	std::string secondW;
	iss >> secondW;
	
	if(secondW.empty()){		//"show"
		std::vector<std::string> v = dm.getAllDevicesUsage();
		lgr.log( dm.getCurrentTime().toString() );
		lgr.log( " Attualmente il sistema ha prodotto " + std::to_string( dm.getGeneratedPower() ) );
		lgr.log( "kWh e consumato " + std::to_string( dm.getPowerUsage() ) + "kWh\n" );
		lgr.log( "Nello specifico:\n" );
		for(int i=0; i<v.size(); i++)
			lgr.log( "\t- il dispositivo " + v.at(i) + " ha consumato " + v.at(++i) + "kWh\n" );
	}
	else{						//"show ${DeviceName}"
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			lgr.log( dm.getCurrentTime().toString() );
			lgr.log( " il dispositivo " + secondW + " ha attualmente consumato " + std::to_string( dm.getDeviceUsage( devPtr ) ) + " kWh\n" ); 
		}
	}
}



void resetCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr){
	std::string secondW;
	iss >> secondW;
	
	if( secondW == "time" ){			//"reset time"
		dm.resetTime();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
	}
	else if( secondW == "timers" ){		//"reset timers"
		lgr.log( dm.getCurrentTime().toString() );
		dm.resetTimers();
		lgr.log( "i timers sono stati resettati\n" );
	}
	else if( secondW == "all" ){		//"reset all"
		dm.resetAll();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
		lgr.log( dm.getCurrentTime().toString() + "i timers sono stati resettati\n" );
	}
	else
		lgr.log( "comando non valido\n" );
}



void rmCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr){
	std::string secondW;
	iss >> secondW;
	
	if( !secondW.empty() ){		//"rm ${DeviceName}"
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( secondW );
		if(devPtr != nullptr){
			dm.removeTimer( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Rimosso il timer dal dispositivo " + secondW + "\n" );
		}
	}
	else
		lgr.log( "comando non valido\n" );
}








