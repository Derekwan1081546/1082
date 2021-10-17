// AvailSeats-function definitions for class AvailSeats.
#include "AvailSeats.h"

AvailSeats::AvailSeats()
   : date(),
     numAvailSeats()
{
}

AvailSeats::AvailSeats( Date theDate, int *theNumAvailSeats )
{
   setDate( theDate );
   for( int i = 1; i <= 4; i++ )
      setNumAvailSeats( i, theNumAvailSeats[ i ] );
}

void AvailSeats::setDate( Date theDate )
{
   date = theDate;
}

void AvailSeats::setNumAvailSeats( int timeCode, int theNumAvailSeats )
{
   numAvailSeats[ timeCode ] = ( theNumAvailSeats >= 0 ? theNumAvailSeats : 0 );
}

Date AvailSeats::getDate()
{
   return date;
}

int AvailSeats::getNumAvailSeats( int timeCode )
{
   return numAvailSeats[ timeCode ];
}