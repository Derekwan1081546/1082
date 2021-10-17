// Date.cpp
// AvailSeats-function definitions for class Date.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#include "Date.h"

extern bool leapYear( int year );

Date::Date()
{
   year = 2000;
   month = 0;
   day = 0;
}

// const return avoids: ( a1 = a2 ) = a3
const Date &Date::operator=( const Date &right )
{
   if( &right != this ) // avoid self-assignment
   {
      month = right.month;
      day = right.day;
      year = right.year;
   } // end if

   return *this; // enables x = y = z, for example
} // end function operator=

void Date::setDate( int y, int m, int d )
{
   year = ( y >= 2000 ) ? y : 2000; // sets year
   month = ( m >= 1 && m <= 12 ) ? m : 1; // sets month

   if( month == 2 && leapYear( year ) )
      day = ( d >= 1 && d <= 29 ) ? d : 1;
   else
      day = ( d >= 1 && d <= days[ month ] ) ? d : 1;
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000; // sets year
} // end function setYear

void Date::setMonth( int m )
{
   month = ( m >= 1 && m <= 12 ) ? m : 1; // sets month
} // end function setMonth

void Date::setDay( int d )
{
   if( month == 2 && leapYear( year ) )
      day = ( d >= 1 && d <= 29 ) ? d : 1;
   else
      day = ( d >= 1 && d <= days[ month ] ) ? d : 1;
} // end function setDay

int Date::getYear() const
{
   return year;
}

int Date::getMonth() const
{
   return month;
}

int Date::getDay() const
{
   return day;
}

bool Date::operator==( const Date &date2 )
{
   return ( year == date2.year && month == date2.month && day == date2.day );
}

bool Date::operator<( const Date &date2 )
{
   if( year < date2.year )
      return true;
   if( year > date2.year )
      return false;

   if( month < date2.month )
      return true;
   if( month > date2.month )
      return false;

   if( day < date2.day )
      return true;

   return false;
}

// if the year is a leap year, return true; otherwise, return false
bool Date::leapYear( int testYear ) const
{
   if( testYear % 400 == 0 ||
      ( testYear % 100 != 0 && testYear % 4 == 0 ) )
      return true; // a leap year
   else
      return false; // not a leap year
} // end function leapYear

// return *this - date2 provided that *this > date2
int Date::operator-( const Date &date2 )
{
	int days = date2.getDay();
	day -= days;
	return day;
}

Date Date::operator+(int numDays)
{
	Date date;
	int year = getYear();
	int month = getMonth();
	int day = getDay();
	day += numDays;
	if (leapYear(year))
	{
		if (month == 2)
		{
			if (day >= 30)
			{
				month += 1;
				day -= 29;
				if (month == 13)
				{
					year += 1;
					month -= 12;
				}
			}
		}
		else
		{
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (day >= 32)
				{
					month += 1;
					day -= 31;
					if (month == 13)
					{
						year += 1;
						month -= 12;
					}
				}
			}
			else
			{
				if (day >= 31)
				{
					month += 1;
					day -= 30;
					if (month == 13)
					{
						year += 1;
						month -= 12;
					}
				}
			}
		}
	}
	else
	{
		if (month == 2)
		{
			if (day >= 29)
			{
				month += 1;
				day -= 28;
				if (month == 13)
				{
					year += 1;
					month -= 12;
				}
			}
			else
			{
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if (day >= 32)
					{
						month += 1;
						day -= 31;
						if (month == 13)
						{
							year += 1;
							month -= 12;
						}
					}
				}
				else
				{
					if (day >= 31)
					{
						month += 1;
						day -= 30;
						if (month == 13)
						{
							year += 1;
							month -= 12;
						}
					}
				}
			}
		}
	}
	date.setDate(year, month, day);
	date.setYear(year);
	date.setMonth(month);
	date.setDay(day);
	

	return date;
}
