#ifndef TIME_H
#define TIME_H

#include <ostream>

class Time{
	
	private:
		int hours;
		int minutes;
		
			
	public:
	
		Time(int h, int m);
		
		void increment(void);
		std::string toString(void) const;			//stampa formato [hh:mm]
		int toMinutes(void) const;
		
		bool operator <(const Time& t) const;
		bool operator >(const Time& t) const;
		bool operator ==(const Time& t) const;
		bool operator !=(const Time& t) const;
		Time operator +(int t);						//tempo formito in minuti
		Time operator -(const Time& t) const;		//sottrazione tra oggetti tempo
		friend std::ostream& operator<<(std::ostream& out, Time& t);		//stampa formato hh:mm
};

		Time stringToTime(std::string t);


#endif
