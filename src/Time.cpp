#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Time.h"

Time::Time(int h, int m) : hours{h}, minutes{m} {
	if(hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
		throw std::invalid_argument("orario non valido\n");
}


Time::Time(const Time& t) {
    hours = t.hours;
    minutes = t.minutes;
}


void Time::increment(void){
	minutes++;
	if( minutes == 60 ){
		minutes = 0;
		hours++;
	}
}



std::string Time::toString(bool withBrackets) const{
	std::string h;
	if( hours < 10 )
		h = "0" + std::to_string(hours);
	else
		h = std::to_string(hours);
		
	std::string m;
	if( minutes < 10 )
		m = "0" + std::to_string(minutes);
	else
		m = std::to_string(minutes);
		
	if(withBrackets)	
		return 	"[" + h + ":" + m + "]";
	else
		return 	h + ":" + m;
}



int Time::toMinutes(void) const{
	return hours*60 + minutes;
}



bool Time::operator <(const Time& t) const{
	if( this->hours < t.hours ) return true;
	if( this->hours == t.hours && this->minutes < t.minutes ) return true;
	return false;
}



bool Time::operator >(const Time& t) const{
	if( this->hours > t.hours ) return true;
	if( this->hours == t.hours && this->minutes > t.minutes ) return true;
	return false;
}



bool Time::operator ==(const Time& t) const{
	return this->hours == t.hours && this->minutes == t.minutes;
}



bool Time::operator !=(const Time& t) const{
	return this->hours != t.hours || this->minutes != t.minutes;
}



Time Time::operator +(int t){
	int totalMinutes = this->minutes + t;
	int newHours = this->hours + (totalMinutes / 60);
	int newMinutes = totalMinutes % 60;
	if( newHours > 23 )
		newHours = newHours % 24;
	
	return Time(newHours, newMinutes);
}



Time Time::operator -(const Time& t) const{
	int time1 = this->toMinutes();
	int time2 = t.toMinutes();
	int totalMin = time1 - time2;
	int h = totalMin / 60;
	int m = totalMin % 60;
	return Time(h, m);
}


Time stringToTime(std::string t){
	std::stringstream ss(t);
	char separator;
	int h, m = 0;
	ss >> h >> separator >> m;
	return Time(h, m);
}

