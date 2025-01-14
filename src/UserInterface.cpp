//nome: Luca Bortolazzi

#include <iostream>
#include <vector>
#include "UserInterface.h"
#include "DeviceManager.h"
#include "Device.h"
#include "MyTime.h"
#include "Logger.h"


UserInterface::UserInterface( DeviceManager& manager, Logger& logger ) : dm{manager}, lgr{logger} {
	commandMap = {
			{"set", [this]( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ) { setCommand(words, dm, lgr); }},
		    {"show", [this]( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ) { showCommand(words, dm, lgr); }},
		    {"reset", [this]( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ) { resetCommand(words, dm, lgr); }},
		    {"rm", [this]( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ) { rmCommand(words, dm, lgr); }}
		};
}


//chiama la funzione giusta per ogni comando
void UserInterface::exeCommand( const std::string& command ){
	std::istringstream iss(command);	//flusso di input
	std::string firstW;					//firstW = comando (prima parola)
	iss >> firstW;						//divisione flusso in parole
	
	auto iter = commandMap.find(firstW);	//iteratore nella mappa dei comandi
	std::vector<std::string> words;
	std::string word;

	while ( iss >> word )				//inserisce nel vettore di stringhe "words", le parole in input
  	  words.push_back(word);
	
	if( iter != commandMap.end() )			//non punta al primo elemento dopo l'ultimo
		iter->second(words, dm, lgr);		//second(): accede al valore associato a chiave trovata (valore = function)
	else
		lgr.log( "comando non valido!\n" );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//gestisce comandi con prima parola = "set"
void setCommand( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){
	
	if( words.at( words.size()-1 ) == "on" ){			//"set ${DEVICENAME} on"
		handleSetOn(words, dm, lgr);
	}
	else if( words.at( words.size()-1 ) == "off" ){		//"set ${DEVICENAME} off"
		handleSetOff(words, dm, lgr);
	}
	else if( words.at(0) == "time" ){					//"set time ${TIME}"
		handleSetTime(words, dm, lgr);
	}
	else if( !words.empty() ){							//"set ${DEVICENAME}" ${START} [${STOP}]
		handleSetTimers(words, dm, lgr);
	}
	else
		lgr.log( "comando non valido\n" );
}



void handleSetOn( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){			//"set ${DEVICENAME} on" _____________________
	std::string deviceName = "";				//imposta Device Name
	for(int i=0; i < words.size()-1; i++){
		deviceName = deviceName + words.at(i);
		if(i != words.size()-2 )
			deviceName = deviceName + " ";
	}	
		
	std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
	if(devPtr != nullptr){
		std::vector<std::string> deviceList = dm.turnOnDevice( devPtr );
		//device list e' un vettore es: {0 o 1, tempo, nome Dispositivo, ...}
			
		if( !deviceList.empty() ){	//se dispositivo è spento
			for( int i=0; i < deviceList.size(); i++ ){		//se soglia kW raggiunta vengono spenti gli ultimi device accesi
				if( deviceList.at(i) == "0" ){				//se 0 il dispositivo si è spento
					MyTime t = stringToTime( deviceList.at(++i) );
					lgr.log( t.toString() + " Il dispositivo '" + deviceList.at(++i) + "' si e' spento\n" ); 
				}
				if( deviceList.at(i) == "1" ){				//se 1 il dispositivo si è acceso
					MyTime t = stringToTime( deviceList.at(++i) );
					lgr.log( t.toString() + " Il dispositivo '" + deviceList.at(++i) + "' si e' acceso\n" ); 
				}
			}
		}
		else
			lgr.log( dm.getCurrentTime().toString() + " Il dispositivo '" + deviceName + "' e' gia' acceso\n" );
	}
}



void handleSetOff( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){		//"set ${DEVICENAME} off"_____________________
	std::string deviceName = "";				//imposta Device Name
	for(int i=0; i < words.size()-1; i++){
		deviceName = deviceName + words.at(i);
		if(i != words.size()-2 )
			deviceName = deviceName + " ";
	}
			
	std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
	if(devPtr != nullptr){
		if( dm.turnOffDevice( devPtr ) )		//se dispositivo gia' spento
			lgr.log( dm.getCurrentTime().toString() + " Il dispositivo '" + deviceName + "' si e' spento\n" );
		else
			lgr.log( dm.getCurrentTime().toString() + " Il dispositivo '" + deviceName + "' e' gia' spento\n" );
	}
}





void handleSetTime( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){		//"set time ${TIME}"__________________________
	std::string newTime = words.at(1);
	std::vector<std::string> deviceList = dm.setTime( stringToTime( newTime ) );
	//device list e' un vettore es: {0 o 1, tempo, nome Dispositivo, ...}
		
	for(int i=0; i < deviceList.size(); i++){		//stampa lista Device che si accendono o spengono
		if( deviceList.at(i) == "0" ){				//se 0 il dispositivo si è spento
			MyTime t = stringToTime( deviceList.at(++i) );
			lgr.log( t.toString() + " Il dispositivo '" + deviceList.at(++i) + "' si e' spento\n" ); 
		}
		if( deviceList.at(i) == "1" ){				//se 1 il dispositivo si è acceso
			MyTime t = stringToTime( deviceList.at(++i) );
			lgr.log( t.toString() + " Il dispositivo '" + deviceList.at(++i) + "' si e' acceso\n" ); 
		}
	}
		
lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
}



void handleSetTimers( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){		//"set ${DEVICENAME}" ${START} [${STOP}] ___________
	std::shared_ptr<Device> devPtr;
	std::string deviceName;

	if( containsNumber( words.at( words.size()-2 ) ) ){		//se penultima parola è un orario: set ${DEVICENAME} ${START} ${STOP}
		deviceName = "";
			
		for(int i=0; i < words.size()-2; i++){			//imposta Device Name
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
	else{													//set ${DEVICENAME} ${START}
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
	lgr.log( " Impostato un timer per il dispositivo '" + deviceName );
	lgr.log( "' dalle " + devRef.getProgrammedStart().toString(false));
	lgr.log( " alle " + devRef.getProgrammedStop().toString(false) + "\n" );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//gestisce comandi con prima parola = "show"
void showCommand( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){
	
	if( words.size() == 0 ){																//"show" _____________________________________
		std::vector<std::string> v = dm.getAllDevicesUsage();
		//v e' vettore tipo: {nomeDevice, consumo kWh, ...}
		lgr.log( dm.getCurrentTime().toString() );
		lgr.log( " Attualmente il sistema ha prodotto " + std::to_string( dm.getGeneratedPower() ) );
		lgr.log( "kWh e consumato " + std::to_string( dm.getPowerUsage() ) + "kWh\n" );
		lgr.log( "Nello specifico:\n" );
		
		for(int i=0; i<v.size(); i++){	//"Impianto fotovoltaico" produce, non consuma
			if ( v.at(i) == "Impianto fotovoltaico" ){
				lgr.log( "\t- il dispositivo '" + v.at(i));
				lgr.log("' ha prodotto " + v.at(++i) + "kWh\n" );
			}
			else{
				lgr.log( "\t- il dispositivo '" + v.at(i));
				lgr.log("' ha consumato " + v.at(++i) + "kWh\n" );
			}	
		}
	}
	else{																					//"show ${DeviceName}"________________________
		std::string deviceName = "";	//imposta Device Name
		for(int i=0; i < words.size(); i++){
			deviceName = deviceName + words.at(i);
			if(i != words.size()-1 )
				deviceName = deviceName + " ";
		}	
			
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
		if(devPtr != nullptr){
			lgr.log( dm.getCurrentTime().toString() );
			if( deviceName == "Impianto fotovoltaico" )		//Impianto fotovoltaico produce kWh
				lgr.log( " il dispositivo '" + deviceName + "' ha attualmente prodotto " + std::to_string( dm.getDeviceUsage( devPtr ) ) + " kWh\n" ); 
			else	
				lgr.log( " il dispositivo '" + deviceName + "' ha attualmente consumato " + std::to_string( dm.getDeviceUsage( devPtr ) ) + " kWh\n" ); 
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//gestisce comandi con prima parola = "reset"
void resetCommand( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){
	
	if( words.at(0) == "time" ){															//"reset time"________________________________
		dm.resetTime();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
	}
	else if( words.at(0) == "timers" ){														//"reset timers"______________________________
		lgr.log( dm.getCurrentTime().toString() );
		dm.resetTimers();
		lgr.log( " i timers sono stati resettati\n" );
	}
	else if( words.at(0) == "all" ){														//"reset all"_________________________________
		dm.resetAll();
		lgr.log( dm.getCurrentTime().toString() + " L’orario attuale è " + dm.getCurrentTime().toString(false) + "\n" );
		lgr.log( dm.getCurrentTime().toString() + " i timers sono stati resettati\n" );
	}
	else
		lgr.log( "comando non valido\n" );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//gestisce comandi con prima parola = "rm"
void rmCommand( std::vector<std::string>& words, DeviceManager& dm, Logger& lgr ){

	if( words.size() != 0 ){																//"rm ${DeviceName}" _________________________
		std::string deviceName = "";		//imposta Device Name
		for(int i=0; i < words.size(); i++){	
			deviceName = deviceName + words.at(i);
			if(i != words.size()-1 )
				deviceName = deviceName + " ";
		}	
			
		std::shared_ptr<Device> devPtr = dm.findDeviceByName( deviceName );
		if(devPtr != nullptr){
			dm.removeTimer( devPtr );
			lgr.log( dm.getCurrentTime().toString() + " Rimosso il timer dal dispositivo '" + deviceName + "'\n" );
		}
	}
	else
		lgr.log( "comando non valido\n" );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//controlla se in una stringa sono presenti numeri
bool containsNumber( const std::string& s ) {
	return std::any_of(s.begin(), s.end(), ::isdigit);
}


