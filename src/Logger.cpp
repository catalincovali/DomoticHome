//nome: Luca Bortolazzi

#include <iostream>
#include "Logger.h"

Logger::Logger(const std::string& fileName){
	fileLog.open(fileName, std::ios::app);	//append: aggiunge righe invece di sovrascrivere
	if(!fileLog.is_open())
		throw std::runtime_error("Errore: impossibile aprire il file di log");
}


Logger::~Logger() {		//chiude file log
        if (fileLog.is_open())
            fileLog.close();
}


void Logger::log(const std::string output){		//stampa stringa "output" su terminale e fileLog
	std::cout << output;
	fileLog << output;
}
