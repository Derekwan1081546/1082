#include <iostream>
#include <ctime>
using namespace::std;

#include "MakeReservation.h"

void viewReservation( ReservationDatabase &reservationDatabase );

int inputAnInteger( int begin, int end ); // input an integer in the range [ begin, end ]
void computeCurrentDate( Date &currentDate );
bool leapYear( int year ); // if the year is a leap year, return true; otherwise, return false

int main()
{
   cout << "Welcome to Zuo Zhe Zuo Sushi Wo Shou Si\n";

   ReservationDatabase reservationDatabase;
   AvailSeatsDatabase availSeatsDatabase;
   MakeReservation makeReservation( reservationDatabase, availSeatsDatabase );

   int choice;
   while( true )
   {
      cout << "\nEnter Your Choice\n"
         << "1. Make Reservation\n"
         << "2. Reservation Enquiry\n"
         << "3. End Program\n";

      do cout << "? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      switch( choice )
      {
      case 1:
         makeReservation.execute();
         break;
      case 2:
         viewReservation( reservationDatabase );
         break;
      case 3:
         cout << "Thank you. Goodbye.\n\n";
         system( "pause" );
         return 0;
      default:
         cerr << "Incorrect Choice!\n";
         break;
      }
   }

   system( "pause" );
}

void viewReservation( ReservationDatabase &reservationDatabase )
{
   string phoneNumber;
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   if( reservationDatabase.empty() )
   {
      cout << "\nNo reservations!\n";
      return;
   }

   if( !reservationDatabase.exist( phoneNumber ) )
   {
      cout << "\nYou have no reservations!\n";
      return;
   }

   reservationDatabase.displayReservationInfo( phoneNumber );
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

void computeCurrentDate( Date &currentDate )
{
   int remainingSeconds = static_cast< int >( time( 0 ) ) + 8 * 60 * 60;

   int year = 1970;

   int secondsPerYear = 365 * 24 * 60 * 60;
   if( leapYear( year ) )
      secondsPerYear += 24 * 60 * 60;

   while( remainingSeconds >= secondsPerYear )
   {
      remainingSeconds -= secondsPerYear;
      year++;

      secondsPerYear = 365 * 24 * 60 * 60;
      if( leapYear( year ) )
         secondsPerYear += 24 * 60 * 60;
   }

   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if( leapYear( year ) )
      days[ 2 ] = 29;

   int month = 1;
   while( remainingSeconds >= days[ month ] * 24 * 60 * 60 )
   {
      remainingSeconds -= days[ month ] * 24 * 60 * 60;
      month++;
   }

   int day = remainingSeconds / ( 24 * 60 * 60 ) + 1;

   currentDate.setYear( year );
   currentDate.setMonth( month );
   currentDate.setDay( day );
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}