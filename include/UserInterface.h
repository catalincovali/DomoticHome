#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cctype>
#include "Logger.h"
#include "DeviceManager.h"

class UserInterface{
	
	private:
		//mappa con chiave = stringa, e valore = funzione con paramatri: rif oggetto istringstream, rif oggetto DeviceManager, rif oggetto Logger
		std::unordered_map <std::string, std::function<void( std::vector<std::string>, DeviceManager&, Logger& )>> commandMap;
		
		DeviceManager dm;
		Logger& lgr;
		
	public:
	
		UserInterface( DeviceManager& manager, Logger& logger );
		void exeCommand( const std::string& command );		//cerca nella mappa il comando inserito e chiama una delle 4 helper function
};


void setCommand( std::vector<std::string> words, DeviceManager& dm, Logger& lgr );	//gestisce comandi con prima parola = "set"
void showCommand( std::vector<std::string> words, DeviceManager& dm, Logger& lgr );	//gestisce comandi con prima parola = "show"
void resetCommand( std::vector<std::string> words, DeviceManager& dm, Logger& lgr );	//gestisce comandi con prima parola = "reset"
void rmCommand( std::vector<std::string> words, DeviceManager& dm, Logger& lgr );	//gestisce comandi con prima parola = "rmCommand"

bool containsNumber( const std::string& s) ;		//controlla se in una stringa sono presenti numeri

