#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>


class Logger{
	
	private:
		std::ofstream fileLog;
		
	public:
	
		Logger(const std::string& fileName);	//accetta file di testo
		void log(const std::string output);	//stampa stringa "output" su terminale e fileLog
		~Logger();
};

#endif
