#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>


class Logger{
	
	private:
		std::ofstream fileLog;
		
	public:
	
		Logger(const std::string& fileName);
		void log(const std::string output);	
		~Logger();
};

#endif
