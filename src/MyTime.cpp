//nome: Luca Bortolazzi

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "MyTime.h"

//se non forniti parametri imposta 00:00 di default
MyTime::MyTime(int h, int m) : hours{h}, minutes{m} {
	if(hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
		throw std::invalid_argument("orario non valido\n");
}


//costruttore di copia
MyTime::MyTime(const MyTime& t) {
    hours = t.hours;
    minutes = t.minutes;
}


//incrementa tempo di un minuto
void MyTime::increment(void){
	minutes++;
	if( minutes == 60 ){
		minutes = 0;
		hours++;
	}
}


//stampa [hh:mm] se withBrackets è true, e hh:mm se false
std::string MyTime::toString(bool withBrackets) const{
	std::string h;
	if( hours < 10 )		//aggiunge 0 per formattazione hh:mm
		h = "0" + std::to_string(hours);
	else
		h = std::to_string(hours);
		
	std::string m;
	if( minutes < 10 )		//aggiunge 0 per formattazione hh:mm
		m = "0" + std::to_string(minutes);
	else
		m = std::to_string(minutes);
		
	if(withBrackets)	
		return 	"[" + h + ":" + m + "]";
	else
		return 	h + ":" + m;
}



int MyTime::toMinutes(void) const{
	return hours*60 + minutes;
}



bool MyTime::operator <(const MyTime& t) const{
	if( this->hours < t.hours ) return true;
	if( this->hours == t.hours && this->minutes < t.minutes ) return true;
	return false;
}



bool MyTime::operator >(const MyTime& t) const{
	if( this->hours > t.hours ) return true;
	if( this->hours == t.hours && this->minutes > t.minutes ) return true;
	return false;
}



bool MyTime::operator ==(const MyTime& t) const{
	return this->hours == t.hours && this->minutes == t.minutes;
}



bool MyTime::operator !=(const MyTime& t) const{
	return this->hours != t.hours || this->minutes != t.minutes;
}



//tempo "t" fornito in minuti
MyTime MyTime::operator +(int t){
	int totalMinutes = this->minutes + t;
	int newHours = this->hours + (totalMinutes / 60);
	int newMinutes = totalMinutes % 60;
	if( newHours > 23 )
		newHours = newHours % 24;
	
	return MyTime(newHours, newMinutes);
}



MyTime MyTime::operator -(const MyTime& t) const{
	int time1 = this->toMinutes();
	int time2 = t.toMinutes();
	int totalMin = time1 - time2;
	int h = totalMin / 60;
	int m = totalMin % 60;
	return MyTime(h, m);
}


//trasforma stringhe in oggetti time
MyTime stringToTime(std::string t){
	std::stringstream ss(t);
	char separator;
	int h, m = 0;
	ss >> h >> separator >> m;
	return MyTime(h, m);
}

