// Date.h
// Date class definition.
#ifndef DATA_H
#define DATA_H

class Date
{
   friend void computeCurrentDate( Date &currentDate );
public:
   Date();
   const Date &operator=( const Date & ); // assignment operator
   void setDate( int, int, int ); // set month, day, year
   void setYear( int );
   void setMonth( int );
   void setDay( int );
   int getYear() const;
   int getMonth() const;
   int getDay() const;
   bool operator==( const Date &date2 );
   bool operator<( const Date &date2 );
   bool leapYear( int ) const;
   int operator-( const Date &date2 );
   Date operator+( int numDays );

private:
	int year;
	int month;
   int day;

   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // array of days per month
};

#endif // DATA_H