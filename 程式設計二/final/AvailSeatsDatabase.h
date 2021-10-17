#ifndef AVAIL_SEATS_DATABASE_H
#define AVAIL_SEATS_DATABASE_H

#include <vector>
#include "AvailSeats.h"

class AvailSeatsDatabase
{
public:
   AvailSeatsDatabase();
   ~AvailSeatsDatabase(); // call storeAvailSeats

   void decreaseAvailSeats( Date date, int timeCode, int requiredSeats );

   bool availableTimes( Date date, int requiredSeats );

   bool availableTimes( Date date, int timeCode, int requiredSeats );

private:
   vector< AvailSeats > availSeats;  // Vector of available seats

   void loadAvailSeats();  // loads availSeats from the file AvailSeats.dat
   void storeAvailSeats(); // stores availSeats into the file AvailSeats.dat

   vector< AvailSeats >::iterator searchAvailSeats( Date date );
};

#endif