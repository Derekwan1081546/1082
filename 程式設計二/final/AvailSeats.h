#ifndef AVAIL_SEATS_H
#define AVAIL_SEATS_H

#include "Date.h"

class AvailSeats
{
public:
   AvailSeats();
   AvailSeats( Date theDate, int *theNumAvailSeats );

   void setDate( Date theDate );
   void setNumAvailSeats( int timeCode, int theNumAvailSeats );

   Date getDate();
   int getNumAvailSeats( int timeCode );

private:
   Date date;
   int numAvailSeats[ 5 ]; // number of available seats
};

#endif