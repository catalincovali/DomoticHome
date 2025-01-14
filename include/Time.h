#ifndef TIME_H
#define TIME_H

#include <ostream>

class Time{
	
	private:
		int hours;
		int minutes;
		
			
	public:
		Time(int h=0, int m=0);		//se non forniti parametri imposta 00:00 di default
		Time(const Time& t);		//costruttore di copia
		
		void increment(void);										//incrementa tempo di un minuto
		std::string toString(bool withBrackets = true) const;		//stampa [hh:mm] se withBrackets è true, e hh:mm se false
		int toMinutes(void) const;									//oggetto time in minuti
		
		bool operator <(const Time& t) const;
		bool operator >(const Time& t) const;
		bool operator ==(const Time& t) const;
		bool operator !=(const Time& t) const;
		Time operator +(int t);						//tempo "t" fornito in minuti
		Time operator -(const Time& t) const;		//sottrazione tra oggetti time

};

		Time stringToTime(std::string t);			//trasforma stringhe in oggetti time


#endif
