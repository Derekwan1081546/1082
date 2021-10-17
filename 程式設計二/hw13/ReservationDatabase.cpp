// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
    Reservation buf;
    fstream file("Reservation details.dat", ios::out | ios::in | ios::binary);

    for (int i = 0; !file.eof(); i++)
    {
        file.read(reinterpret_cast<char*>(&buf), sizeof(buf));
        reservations.push_back(buf);
    }
}

void ReservationDatabase::storeReservations()
{
    fstream file("Reservation details.dat", ios::out | ios::in | ios::binary);

    for (int i = 0; i < reservations.size(); i++)
    {
        file.write(reinterpret_cast<char*>(&reservations[i]), sizeof(reservations[i]));
    }

}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "Reservation Cancelled.\n\n";
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats( string idNumber, string reservationNumber )
{
    vector< Reservation >::iterator it = searchReservation(idNumber, reservationNumber);
    int num = 0;
    int adultTickets = it.ptr->getAdultTickets();
    int concessionTickets = it.ptr->getConcessionTickets();
    
    cout << "How many adult tickets to cancel¡H";
    cin >> num;
    cin.ignore();
    adultTickets -= num;
    it.ptr->setAdultTickets(adultTickets);

    cout << "\nHow many concession tickets to cancel¡H";
    cin >> num;
    cin.ignore();
    cout << endl << endl;
    concessionTickets -= num;
    it.ptr->setConcessionTickets(concessionTickets);

    displayReservation(idNumber, reservationNumber);
    cout << "\nYou have successfully reduced the number of tickets!\n";
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}