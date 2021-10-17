// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
    Train buf;
    fstream file("Southbound timetable.dat", ios::in | ios::out | ios::binary);

    for (int i = 0; !file.eof(); i++)
    {
        file.read(reinterpret_cast<char*>(&buf), sizeof(buf));
        southboundTimetable.push_back(buf);
    }

}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool SouthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    Train train;
    for (int i = 0; i < southboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] < southboundTimetable[i].getDepartureTimes(originStation) && southboundTimetable[i].getDepartureTimes(destinationStation) != "-")
        {
            return true;
        }
    }
    return false;
    
}

void SouthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    
    Train train;
    cout << "Train No.  Departure  Arrival\n";
    int a = 0;
    for (int i = 0; i < southboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] < southboundTimetable[i].getDepartureTimes(originStation) && southboundTimetable[i].getDepartureTimes(destinationStation) != "-")
        {
            train= southboundTimetable[i];
            cout << setw(9) << right << train.getTrainNumber() << setw(11) << right << train.getDepartureTimes(originStation) << setw(9) << right << train.getDepartureTimes(destinationStation) << endl;
            a++;
            if (a == 10) {
                break;
            }
        }
    }
}

vector< Train >::iterator SouthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = southboundTimetable.begin();
   for( ; it != southboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return southboundTimetable.end();
}