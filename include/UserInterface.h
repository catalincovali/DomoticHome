#include <sstream>
#include <string>
#include <unordered_map>

class UserInterface{
	
	private:
		//mappa con chiave: stringa, e valore: funzione con paramatro iss (oggetto di tipo istringstream)
		std::unordered_map<std::string, std::function<void( std::istringstream& )>> commandMap = {
			{"set", [this](std::istringstream& iss) { handleSet(iss); }},
		    {"show", [this](std::istringstream& iss) { handleShow(iss); }},
		    {"reset", [this](std::istringstream& iss) { handleReset(iss); }}
		}
		//DA METTERE IN CPP????
		
	public:
	
		UserInterface(void);
		void exeCommand(const std::string& command);	
};


void setCommand(std::istringstream& iss);
void showCommand(std::istringstream& iss);
void resetCommand(std::istringstream& iss);
