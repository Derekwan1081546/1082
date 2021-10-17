#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

extern int inputAnInteger( int begin, int end );

// ReservationHistory default constructor
ReservationHistory::ReservationHistory( ReservationDatabase &theReservationDatabase,
                                        SouthboundTimetable &theSouthboundTimetable,
                                        NorthboundTimetable &theNorthboundTimetable )
   : idNumber(),
     reservationNumber(),
     reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
	//ReservationDatabase reservations;
	//Reservation reservation;
	string idNumber;
	string reservationNumber;
	cout << "Enter ID Number :";
	cin >> idNumber;
	cin.ignore();
	cout << endl << endl;
	cout << "Enter Reservation Number: ";
	cin >> reservationNumber;
	cin.ignore();
	/*bool exist;
	exist = 0;*/
	if (reservationDatabase.exist(idNumber, reservationNumber))
	{
		reservationDatabase.displayReservation(idNumber, reservationNumber);
		//exist = 1;
	}
	else {
		cout << "Reservation record not found.\n";
		return;
	}


	int choice;
	cout << "\nEnter Your Choice\n";
	cout << "1. Cancellation\n2. Reduce\n3. End";
	do cout << "\n? ";
	while ((choice = inputAnInteger(1, 3)) == -1);
	cout << endl;
	switch (choice)
	{
	case 1:
		reservationDatabase.cancelReservation(idNumber, reservationNumber);
		break;
	case 2:
		reservationDatabase.reduceSeats(idNumber, reservationNumber);
		break;
	case 3:
		return;
	default: // display error if user does not select valid choice
		cerr << "Incorrect Choice!\n";
		break;
	}


}