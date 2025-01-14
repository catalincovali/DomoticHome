//nome: Luca Bortolazzi

#ifndef MYTIME_H
#define MYTIME_H

#include <ostream>

class MyTime{
	
	private:
		int hours;
		int minutes;
		
			
	public:
		MyTime(int h=0, int m=0);		//se non forniti parametri imposta 00:00 di default
		MyTime(const MyTime& t);		//costruttore di copia
		
		void increment(void);										//incrementa tempo di un minuto
		std::string toString(bool withBrackets = true) const;		//stampa [hh:mm] se withBrackets è true, e hh:mm se false
		int toMinutes(void) const;									//oggetto time in minuti
		
		bool operator <(const MyTime& t) const;
		bool operator >(const MyTime& t) const;
		bool operator ==(const MyTime& t) const;
		bool operator !=(const MyTime& t) const;
		MyTime operator +(int t);						//tempo "t" fornito in minuti
		MyTime operator -(const MyTime& t) const;		//sottrazione tra oggetti time

};

		MyTime stringToTime(std::string t);			//trasforma stringhe in oggetti time


#endif
