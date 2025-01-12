#include <iostream>
#include <vector>
#include "UserInterface.h"
#include "DeviceManager.h"
#include "Device.h"
#include "Time.h"
#include "Logger.h"


UserInterface::UserInterface(DeviceManager& manager, Logger& logger) : dm{manager}, lgr{logger} {
	commandMap = {
			{"set", [this](std::vector<std::string> words, DeviceManager& dm, Logger& lgr) { setCommand(words, dm, lgr); }},
		    {"show", [this](std::vector<std::string> words, DeviceManager& dm, Logger& lgr) { showCommand(words, dm, lgr); }},
		    {"reset", [this](std::vector<std::string> words, DeviceManager& dm, Logger& lgr) { resetCommand(words, dm, lgr); }},
		    {"rm", [this](std::vector<std::string> words, DeviceManager& dm, Logger& lgr) { rmCommand(words, dm, lgr); }}
		};
}



void UserInterface::exeCommand(const std::string& command){
	std::istringstream iss(command);	//per flusso di input
	std::string firstW;					//firstW cossisponde al comando (prima parola)
	iss >> firstW;						//divido il flusso in parole
	
	auto iter = commandMap.find(firstW);	//iteratore nella mappa dei comandi
	std::vector<std::string> words;
	std::string word;

	while (iss >> word)				//inserisce nel vettore di stringhe "words", le parole del comando
  	  words.push_back(word);
	
	if(iter != commandMap.end())			//non punta al primo elemento dopo l'ultimo
		iter->second(words, dm, lgr);		//second(): accede al valore associato a chiave trovata (valore = function)
	else
		lgr.log( "comando non valido!\n" );
}




//gestisce comandi con prima parola = "set"
void setCommand(std::vector<std::string> words, DeviceManager& dm, Logger& lgr){		//"set ${DEVICENAME} on"
	
	if( words.at( words.size()-1 ) == "on" ){
	
		std::string deviceName = "";				//imposta Device Name
		for(int i=0; i < words.size()-1; i++){
			deviceName = deviceName + words.at(i);
			if(i != words.size()-2 )
				deviceName = deviceName + " ";
		}	
			
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
		if(devPtr != nullptr){
			std::vector<std::string> v = dm.turnOnDevice( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Il dispositivo " + v.at(v.size() -1) + " si e' acceso\n" );
		}
	}
	else if( words.at( words.size()-1 ) == "off" ){									//"set ${DEVICENAME} off"
	
		std::string deviceName = "";				//imposta Device Name
		for(int i=0; i < words.size()-1; i++){
			deviceName = deviceName + words.at(i);
			if(i != words.size()-2 )
				deviceName = deviceName + " ";
		}
			
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
		if(devPtr != nullptr){
			dm.turnOffDevice( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Il dispositivo " + deviceName + " si e' spento\n" );
		}
	}
	else if( words.at(0) == "time" ){								//"set time ${TIME}"
		std::string newTime = words.at(1);
		dm.setTime( stringToTime( newTime ) );
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
	}
	
	else if( words.size() != 0 ){									//"set ${DEVICENAME}"
			std::shared_ptr<Device> devPtr;
			std::string deviceName;
			if( containsNumber( words.at( words.size()-2 ) ) ){		//se penultima parola è un orario: set ${DEVICENAME} ${START} ${STOP}
				deviceName = "";
			
				for(int i=0; i < words.size()-2; i++){				//imposta Device Name
					deviceName = deviceName + words.at(i);
					if(i != words.size()-3 )
						deviceName = deviceName + " ";
				}	
				devPtr = dm.findDeviceByName( deviceName );
				if(devPtr != nullptr){
					dm.setStartTimer( devPtr, stringToTime( words.at( words.size()-2 ) ) );
					dm.setStopTimer( devPtr, stringToTime( words.at( words.size()-1 ) ) );
				}
			}
			else{														//set ${DEVICENAME} ${START}
				deviceName = "";		//imposta Device Name
				for(int i=0; i < words.size()-1; i++){
					deviceName = deviceName + words.at(i);
					if(i != words.size()-2 )
						deviceName = deviceName + " ";
				}
				devPtr = dm.findDeviceByName( deviceName );
				if(devPtr != nullptr)
					dm.setStartTimer( devPtr, stringToTime( words.at( words.size()-1 ) ) );
			}
		
			Device& devRef = *devPtr;
			lgr.log( dm.getCurrentTime().toString() );
			lgr.log( " Impostato un timer per il dispositivo " + deviceName );
			lgr.log( " dalle " + devRef.getProgrammedStart().toString(false));
			lgr.log( " alle " + devRef.getProgrammedStop().toString(false) + "\n" );
		
		}
		else
			lgr.log( "comando non valido\n" );
}





//gestisce comandi con prima parola = "show"
void showCommand(std::vector<std::string> words, DeviceManager& dm, Logger& lgr){
	
	if( words.size() == 0 ){		//"show"
		std::vector<std::string> v = dm.getAllDevicesUsage();
		lgr.log( dm.getCurrentTime().toString() );
		lgr.log( " Attualmente il sistema ha prodotto " + std::to_string( dm.getGeneratedPower() ) );
		lgr.log( "kWh e consumato " + std::to_string( dm.getPowerUsage() ) + "kWh\n" );
		lgr.log( "Nello specifico:\n" );
		
		for(int i=0; i<v.size(); i++){
			lgr.log( "\t- il dispositivo " + v.at(i));
			i++;
			lgr.log(" ha consumato " + v.at(i) + "kWh\n" );
		}
	}
	else{											//"show ${DeviceName}"
		std::string deviceName = "";	//imposta Device Name
		for(int i=0; i < words.size(); i++){
			deviceName = deviceName + words.at(i);
			if(i != words.size()-1 )
				deviceName = deviceName + " ";
		}	
			
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
		if(devPtr != nullptr){
			lgr.log( dm.getCurrentTime().toString() );
			lgr.log( " il dispositivo " + deviceName + " ha attualmente consumato " + std::to_string( dm.getDeviceUsage( devPtr ) ) + " kWh\n" ); 
		}
	}
}




//gestisce comandi con prima parola = "reset"
void resetCommand(std::vector<std::string> words, DeviceManager& dm, Logger& lgr){
	
	if( words.at(0) == "time" ){			//"reset time"
		dm.resetTime();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
	}
	else if( words.at(0) == "timers" ){		//"reset timers"
		lgr.log( dm.getCurrentTime().toString() );
		dm.resetTimers();
		lgr.log( "i timers sono stati resettati\n" );
	}
	else if( words.at(0) == "all" ){		//"reset all"
		dm.resetAll();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
		lgr.log( dm.getCurrentTime().toString() + "i timers sono stati resettati\n" );
	}
	else
		lgr.log( "comando non valido\n" );
}





//gestisce comandi con prima parola = "rm"
void rmCommand(std::vector<std::string> words, DeviceManager& dm, Logger& lgr){

	if( words.size() != 0 ){							//"rm ${DeviceName}"
		std::string deviceName = "";		//imposta Device Name
		for(int i=0; i < words.size(); i++){	
			deviceName = deviceName + words.at(i);
			if(i != words.size()-1 )
				deviceName = deviceName + " ";
		}	
			
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
		if(devPtr != nullptr){
			dm.removeTimer( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Rimosso il timer dal dispositivo " + deviceName + "\n" );
		}
	}
	else
		lgr.log( "comando non valido\n" );
}



bool containsNumber(const std::string& s) {
	return std::any_of(s.begin(), s.end(), ::isdigit);
}




