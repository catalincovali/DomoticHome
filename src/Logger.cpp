#include <iostream>
#include "Logger.h"

Logger::Logger(const std::string& fileName){
	fileLog.open(fileName, std::ios::app);	//append: aggiunge righe invece di sovrascrivere
	if(!fileLog.is_open())
		throw std::runtime_error("Errore: impossibile aprire il file di log");
}


Logger::~Logger() {
        if (fileLog.is_open())
            fileLog.close();
}


void Logger::log(const std::string output){
	std::cout << output << std::endl;
	fileLog << output << std::endl;
}
