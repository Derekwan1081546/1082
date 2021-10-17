#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h"

ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::exist( string phoneNumber )
{
	for (int i = 0; i < reservations.size(); i++)
	{
		if (reservations[i].getPhoneNumber() == phoneNumber)
		{
			return true;
		}
	}
	return false;
}

void ReservationDatabase::displayReservationInfo( string phoneNumber )
{
	int num = 1;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (reservations[i].getPhoneNumber() == phoneNumber)
		{
			cout << setw(2) << num << ". ";
			reservations[i].displayReservationInfo();
			cout << endl;
			num++;
		}
	}
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

void ReservationDatabase::loadReservations()
{
	Reservation reservation;
	fstream file("Reservations.dat", ios::in | ios::out | ios::binary);
	for (int i = 0; !file.eof(); i++)
	{
		file.read(reinterpret_cast<char*>(&reservation), sizeof(reservation));
		pushBack(reservation);
	}
}

void ReservationDatabase::storeReservations()
{
	fstream file("Reservations.dat", ios::in | ios::out | ios::binary);
	for (int i = 0; i < reservations.size(); i++)
	{
		file.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(reservations[i]));
	}
}