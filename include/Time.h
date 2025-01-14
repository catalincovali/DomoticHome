#ifndef TIME_H
#define TIME_H

#include <ostream>

class Time{
	
	private:
		int hours;
		int minutes;
		
			
	public:
	
		Time(int h=0, int m=0);		//se non forniti imposta 00:00 di default
		Time(const Time& t);		//costruttore di copia
		
		void increment(void);
		std::string toString(bool withBrackets = true) const;		//stampa [hh:mm] se withBrackets è true, e hh:mm se false
		int toMinutes(void) const;		//oggetto time in minuti
		
		bool operator <(const Time& t) const;
		bool operator >(const Time& t) const;
		bool operator ==(const Time& t) const;
		bool operator !=(const Time& t) const;
		Time operator +(int t);				//tempo "t" formito in minuti
		Time operator -(const Time& t) const;		//sottrazione tra oggetti tempo

};

		Time stringToTime(std::string t);


#endif
