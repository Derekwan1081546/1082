// MakeReservation.cpp
// AvailSeats-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h"

extern int inputAnInteger( int begin, int end );

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
   AvailSeatsDatabase &theSeatsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availSeatsDatabase( theSeatsDatabase )
{
}

void MakeReservation::execute()
{
   cout << "\nEnter the party size (1~6): ";

   int partySize;
   do cout << "? ";
   while( ( partySize = inputAnInteger( 1, 6 ) ) == -1 );

   Date currentDate;
   computeCurrentDate( currentDate );

   Date date;
   inputDate( date, currentDate, partySize );

   int timeCode;
   inputTimeCode( timeCode, date, partySize );

   string name;
   cout << "\nEnter name: ";
   cin >> name;

   string phoneNumber;
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   cout << "\nChoose a menu:\n";
   cout << "1. NT$ 1080\n";
   cout << "2. NT$ 1680\n";
   cout << "3. NT$ 2280\n";

   int menuCode;
   do cout << "? ";
   while( ( menuCode = inputAnInteger( 1, 3 ) ) == -1 );

   Reservation newReservation( phoneNumber, name, date, timeCode, partySize, menuCode );

   cout << endl;
   newReservation.displayReservationInfo();

   cout << "\nReservation Completed\n";

   reservationDatabase.pushBack( newReservation );

   availSeatsDatabase.decreaseAvailSeats( date, timeCode, partySize );
}

void MakeReservation::inputDate( Date &date, Date currentDate, int partySize )
{
	Date dates[31];//add
	cout << "Choose a date\n";
	int change = 0;
	for (int i = 1; i < 31; i++) {//modify
		currentDate = currentDate + 1;
		dates[i] = currentDate;
		if (availSeatsDatabase.availableTimes(currentDate, partySize)) {
			cout << setw(5) << right << i << ". " << currentDate.getYear() << "/";
			if (currentDate.getMonth() < 10) {
				cout << "0" << currentDate.getMonth() << "/";
			}
			else cout << currentDate.getMonth() << "/";
			if (currentDate.getDay() < 10) {
				cout << "0" << currentDate.getDay();
			}
			else cout << currentDate.getDay();
			cout << "   ";
			change++;
			if (change % 4 == 0)
				cout << endl;
		}
	}

	bool exist = 0;
	int choice;
	cout << endl;
	do {
		cout << "? ";
		choice = inputAnInteger(1, 30);
		if (choice != -1) {
			if (availSeatsDatabase.availableTimes(dates[choice], partySize))//add
				exist = 1;
		}
	} while (!exist);
	date = dates[choice];//add
}

void MakeReservation::inputTimeCode( int &timeCode, Date date, int partySize )
{
	int timecode;
	std::string times[5] = { "","11:30", "13:30", "17:45", "19:45" };//add
	string timecode1 = "1. 11:30\n";
	string timecode2 = "2. 13:30\n";
	string timecode3 = "3. 17:45\n";
	string timecode4 = "4. 19:45\n";
	cout << "\nChoose a time:" << endl;
	for (int i = 1; i < 5; i++)
	{
		if (availSeatsDatabase.availableTimes(date, i, partySize)) 
		{
			cout << i << ". " << times[i] << endl;//modify
		}
	}
	bool exist = 0;
	int choice;
	do {
		cout << "? ";
		choice = inputAnInteger(1, 4);
		if (choice != -1) {
			if (availSeatsDatabase.availableTimes(date, choice, partySize))//add
				exist = 1;
		}
	} while (!exist);
	timeCode = choice;

}