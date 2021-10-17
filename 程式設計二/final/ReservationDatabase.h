#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

#include <vector>
//#include "Vector.h"
#include "Reservation.h"

//extern int inputAnInteger( int begin, int end );

class ReservationDatabase
{
public:
   ReservationDatabase();  // call loadFromReservationFile
   ~ReservationDatabase(); // call saveToReservationFile

   bool empty(); // returns true if the ReservationDatabase is empty

   // returns true if there is a Reservation object containing specified phoneNumber
   bool exist( string phoneNumber );

   // displays all reservation informations for the AvailSeats object containing specified phoneNumber, and
   // returns the number of reservation informations displayed
   void displayReservationInfo( string phoneNumber );

   void pushBack( Reservation newReservation ); // add an element at the end of reservations

private:
   vector< Reservation > reservations; // vector of all reservations

   void loadReservations();  // loads reservations from the file Reservations.dat
   void storeReservations(); // stores reservations into the file Reservations.dat
};

#endif