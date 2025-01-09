#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include "Logger.h"
#include "DeviceManager.h"

class UserInterface{
	
	private:
		//mappa con chiave = stringa, e valore = funzione con paramatri: rif oggetto istringstream, rif oggetto DeviceManager, rif oggetto Logger
		std::unordered_map <std::string, std::function<void( std::istringstream&, DeviceManager&, Logger& )>> commandMap;
		
		DeviceManager dm;
		Logger& lgr;
		
	public:
	
		UserInterface(DeviceManager& manager, Logger& logger);
		void exeCommand(const std::string& command);	
};


void setCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr);
void showCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr);
void resetCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr);
void rmCommand(std::istringstream& iss, DeviceManager& dm, Logger& lgr);
