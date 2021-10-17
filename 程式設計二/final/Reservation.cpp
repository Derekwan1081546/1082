#include <iostream>
#include <iomanip>
using namespace::std;
#include "Reservation.h" // Reservation class definition

Reservation::Reservation()
   : phoneNumber(),
     name(),
     date(),
     time(),
     partySize(),
     menu()
{
}

Reservation::Reservation( string thePhoneNumber, string theName, Date theDate,
                          int theTime, int thePartySize, int theMenu )
   : phoneNumber(),
     name(),
     date(),
     time(),
     partySize(),
     menu()
{
   setPhoneNumber( thePhoneNumber );
   setName( theName );
   setDate( theDate );
   setTime( theTime );
   setPartySize( thePartySize );
   setMenu( theMenu );
}

void Reservation::setPhoneNumber( string thePhoneNumber )
{
   int length = thePhoneNumber.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      phoneNumber[ i ] = thePhoneNumber[ i ];
   phoneNumber[ length ] = '\0';
}

void Reservation::setName( string theName )
{
   int length = theName.size();
   length = ( length < 8 ? length : 7 );
   for( int i = 0; i < length; i++ )
      name[ i ] = theName[ i ];
   name[ length ] = '\0';
}

void Reservation::setDate( Date theDate )
{
   date = theDate;
}

void Reservation::setTime( int theTime )
{
   time = ( theTime >= 0 ? theTime : 0 );
}

void Reservation::setPartySize( int thePartySize )
{
   partySize = ( thePartySize >= 0 ? thePartySize : 0 );
}

void Reservation::setMenu( int theMenu )
{
   menu = ( theMenu >= 0 ? theMenu : 0 );
}

string Reservation::getPhoneNumber()
{
   return phoneNumber;
}

string Reservation::getName()
{
   return name;
}

Date Reservation::getDate()
{
   return date;
}

int Reservation::getTime()
{
   return time;
}

int Reservation::getPartySize()
{
   return partySize;
}

void Reservation::displayReservationInfo()
{
	std::string times[5] = { "","11:30", "13:30", "17:45", "19:45" };//add
	std::cout << getPartySize() << " guests  "
		<< getDate().getYear() << "/";
	if (getDate().getMonth() < 10) {//modify
		std::cout << "0" << getDate().getMonth() << "/";
	}
	else std::cout << getDate().getMonth() << "/";//modify
	if (getDate().getDay() < 10) {
		std::cout << "0" << getDate().getDay();
	}
	else std::cout << getDate().getDay();//modify
	std::cout << "  " << times[getTime()];


}