#include <sstream>
#include <string>
#include <unordered_map>
#include "Logger.h"
#include "DeviceManager.h"

class UserInterface{
	
	private:
		//mappa con chiave: stringa, e valore: funzione con paramatro iss (oggetto di tipo istringstream)
		std::unordered_map<std::string, std::function<void( std::istringstream& )>> commandMap;
		DeviceManager dm;
		Logger logger;
		
	public:
	
		UserInterface(DeviceManager& manager, Logger& logger);
		void exeCommand(const std::string& command);	
};


void setCommand(std::istringstream& iss, DeviceManager& dm);
void showCommand(std::istringstream& iss, DeviceManager& dm);
void resetCommand(std::istringstream& iss, DeviceManager& dm);
void rmCommand(std::istringstream& iss, DeviceManager& dm);
