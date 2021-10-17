#include<iostream>
#include <iomanip>
#include <fstream>
#include"s1081546-hw12.h"
using namespace std;

int main()
{
	cout << "Taiwan High Speed Rail Booking System\n";
	srand(static_cast<unsigned int>(time(0)));

	Train southboundTimetable[100];
	Train northboundTimetable[100];
	bookingsystem book;
	int choice; // store user choice

	// enable user to specify action
	while (true)
	{
		cout << "\nEnter Your Choice\n"
			<< "1. Booking\n"
			<< "2. Booking History\n"
			<< "3. End Program";

		do cout << "\n? ";
		while ((choice = book.inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			book.makingReservation(southboundTimetable, northboundTimetable);
			break;
		case 2:
			book.reservationHistory(southboundTimetable, northboundTimetable);
			break;
		case 3:
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;
		default: // display error if user does not select valid choice
			cerr << "Incorrect Choice!\n";
			break;
		}
	}

	system("pause");
	return 0;
}
