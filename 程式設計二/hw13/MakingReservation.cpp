// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger( int begin, int end );

extern string departureTimes[ 37 ];

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
}

void MakingReservation::execute()
{
   if( chooseTrain() ) // displays timetables for 10 coming trains, then let user choose a train
   {
      inputReservationDetails();

      inputContactPersonInfo();

      reservationDatabase.addReservation( reservation );

      cout << "\nReservation Completed!\n\n";
   }
   else
      cout << "\nSorry! No train is available!\n\n";
}

bool MakingReservation::chooseTrain()
{
    int originstation;
    int destinationstation;
    int departuretime;
    string trainnumber;
    cout << "Origin Station\n";
    char stationName[13][9] = { "" ,"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
    for (int i = 1; i < 13; i++) {
        cout << i << ". " << stationName[i] << endl;
    }
    do cout << "? ";
    while ((originstation = inputAnInteger(1, 13)) == -1);
    cout << endl;
    reservation.setOriginStation(originstation);

    cout << "Destination Station\n";
    for (int i = 1; i < 13; i++) {
        cout << i << ". " << stationName[i] << endl;
    }
    do cout << "? ";
    while ((destinationstation = inputAnInteger(1, 13)) == -1 || destinationstation == originstation);
    cout << endl;
    reservation.setDestinationStation(destinationstation);
    cout << "\nDeparture Time\n";
    for (int i = 1; i < 37; i++) {
        cout << i << ". " << departureTimes[i] << endl;
    }
    do cout << "? ";
    while ((departuretime = inputAnInteger(1, 36)) == -1);
    
    if (originstation > destinationstation)
    {
        NorthboundTimetable northbound;
        //Train train;
        if (northbound.trainsAvailable(departuretime, originstation, destinationstation))
        {
            northbound.displayComingTrains(departuretime, originstation, destinationstation);

            cout << "\nEnter Train Number: ";
            cin >> trainnumber;
            cin.ignore();
            reservation.setTrainNumber(trainnumber);
            return true;
        }
        else
            return false;
    }
    else
    {
        SouthboundTimetable southbound;
        //Train train;
        if (southbound.trainsAvailable(departuretime, originstation, destinationstation))
        {
            southbound.displayComingTrains(departuretime, originstation, destinationstation);
            cout << "\nEnter Train Number: ";
            cin >> trainnumber;
            cin.ignore();
            reservation.setTrainNumber(trainnumber);
            return true;
        }
        else
            return false;
    }
}

void MakingReservation::inputReservationDetails()
{
   cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";

   int carClass;
   do cout << "\n? ";
   while( ( carClass = inputAnInteger( 1, 2 ) ) == -1 );
   reservation.setCarClass( carClass );

	cout << "\nDeparture Date: ";

   char date[12];
   cin >> date;
   reservation.setDate( date );
   cin.ignore();

	cout << "\nHow many adult tickets? ";

   int adultTickets;
   cin >> adultTickets;
   reservation.setAdultTickets( adultTickets );

	cout << "\nHow many concession tickets? ";

   int concessionTickets;
   cin >> concessionTickets;
   reservation.setConcessionTickets( concessionTickets );

   cout << "\nTrip Details\n";
   reservation.displayReservationDetails();
}

void MakingReservation::inputContactPersonInfo()
{
   cout << "\nEnter Contact Person Information\n\n";

   cout << "ID Number: ";
   string idNumber;
   cin >> idNumber;
   reservation.setIdNumber( idNumber );

   cout << "\nPhone: ";
   string phone;
   cin >> phone;
   cin.ignore();
   reservation.setPhone( phone );

   srand( static_cast< unsigned int >( time( 0 ) ) );
   char reservationNumber[ 12 ];
   for( int i = 0; i < 8; i++ )
      reservationNumber[ i ] = rand() % 10 + '0';
   reservationNumber[ 8 ] = '\0';
   reservation.setReservationNumber( reservationNumber );
   
	cout << "\nReservation Number: " << reservationNumber << endl;
}