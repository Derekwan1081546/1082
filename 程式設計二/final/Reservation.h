#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"

class Reservation
{
public:
   Reservation();

   Reservation( string thePhoneNumber, string theName, Date theDate,
                int theTime, int thePartySize, int theMenu );

   void setPhoneNumber( string thePhoneNumber );
   void setName( string theName );
   void setDate( Date theDate );
   void setTime( int theTime );
   void setPartySize( int thePartySize );
   void setMenu( int theMenu );

   string getPhoneNumber();
   string getName();
   Date getDate();
   int getTime();
   int getPartySize();

   // displays 1: partySize
   //          2: date
   //          3: time
   void displayReservationInfo();

private:
   char phoneNumber[ 12 ]; // 電話號碼
   char name[ 8 ];         // 姓名
   Date date;              // 預約日期
   int time;               // 預約時間：1 for 11:30, 2 for 13:30, 3 for 17:45, 4 for 19:45
   int partySize;          // 消費人數
   int menu;               // 1 for NT$ 1080, 2 for NT$ 1680, 3 for NT$ 2280
};

#endif