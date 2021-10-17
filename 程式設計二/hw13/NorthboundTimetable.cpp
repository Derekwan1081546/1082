// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
    Train buf;
    fstream file("Northbound timetable.dat", ios::in | ios::out | ios::binary);

    for (int i = 0; !file.eof(); i++)
    {
        file.read(reinterpret_cast<char*>(&buf), sizeof(buf));

        northboundTimetable.push_back(buf);
    }
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    Train train;
    for (int i = 0; i < northboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] <= northboundTimetable[i].getDepartureTimes((originStation - 13) * -1) && northboundTimetable[i].getDepartureTimes((destinationStation - 13) * -1) != "-")
        {
            return true;
        }
    }
    return false;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    Train train;
    cout << "Train No.  Departure  Arrival\n";
    int a = 1;
    for (int i = 0; i < northboundTimetable.size(); i++)
    {
        if (departureTimes[departureTime] <= northboundTimetable[i].getDepartureTimes((originStation - 13) * -1) && northboundTimetable[i].getDepartureTimes((destinationStation - 13) * -1) != "-")
        {
            train = northboundTimetable[i];
            cout << setw(9) << right << train.getTrainNumber() << setw(11) << right << train.getDepartureTimes((originStation - 13) * -1) << setw(9) << right << train.getDepartureTimes((destinationStation - 13) * -1) << endl;
            a++;
            if (a == 11) {
                break;
            }
        }
    }
   /* cout << "Train No.  Departure  Arrival\n";
    for (int i = 0; i < 10; i++) 
    {
        cout << setw(9) << right << train.getTrainNumber()[i] << setw(11) << right << train.getDepartureTimes(originStation)[i] << setw(9) << right << train.getDepartureTimes(destinationStation)[i] << endl;
    }*/

}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}