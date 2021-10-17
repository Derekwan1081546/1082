#ifndef MAKE_RESERVATION_H
#define MAKE_RESERVATION_H

#include "ReservationDatabase.h"
#include "AvailSeatsDatabase.h"

class MakeReservation
{
public:
   MakeReservation( ReservationDatabase &theReservationDatabase,
      AvailSeatsDatabase &theSeatsDatabase );
   void execute();
private:
   ReservationDatabase &reservationDatabase;
   AvailSeatsDatabase &availSeatsDatabase;

   void inputDate( Date &date, Date currentDate, int partySize );
   void inputTimeCode( int &timeCode, Date date, int partySize );
};

#endif // MAKE_RESERVATION_H