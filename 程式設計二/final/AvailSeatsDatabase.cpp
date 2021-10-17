#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailSeatsDatabase.h"

AvailSeatsDatabase::AvailSeatsDatabase()
{
	Date current;
	computeCurrentDate(current);
	Date date;
	date = current + 1;
	loadAvailSeats();
	if (current + 1 == availSeats[0].getDate())//add
		availSeats.resize(30);
	else {//add
		vector<AvailSeats> New;
		for (int i = 0; i < availSeats.size(); i++) {
			if (date == availSeats[i].getDate() && New.size() < 30) {//modify
				New.push_back(availSeats[i]);//add
				date = date + 1;//add
			}
			else if (New.size() == 30)//add
				break;
		}
		while (New.size() < 30) {//add
			AvailSeats buf;
			buf.setDate(date);
			for (int i = 1; i < 5; i++)
				buf.setNumAvailSeats(i, 20);
			New.push_back(buf);//add
			date = date + 1;//add
		}
		availSeats = New;//add
	}
	
}

AvailSeatsDatabase::~AvailSeatsDatabase()
{
   storeAvailSeats();
}

void AvailSeatsDatabase::decreaseAvailSeats( Date date, int timeCode, int requiredSeats )
{
	int seats;
	vector< AvailSeats >::iterator it = searchAvailSeats(date);
	for (int i = 0; i < availSeats.size(); i++)
	{
		if (availSeats[i].getDate() == it->getDate())
		{
			seats = it->getNumAvailSeats(timeCode);
			seats -= requiredSeats;
			it->setNumAvailSeats(timeCode, seats);
		}
	}
}

bool AvailSeatsDatabase::availableTimes( Date date, int requiredSeats )
{
	vector< AvailSeats >::iterator it = searchAvailSeats(date);
	for (int i = 1; i < 5; i++)
	{
		if(it->getNumAvailSeats(i)  >= requiredSeats)//modify
		{
			return true;
		}
	}
	return false;
}

bool AvailSeatsDatabase::availableTimes( Date date, int timeCode, int requiredSeats )
{
	vector< AvailSeats >::iterator it = searchAvailSeats(date);
	for (int i = 0; i < availSeats.size(); i++)
	{
		
		if (it->getNumAvailSeats(timeCode) >= requiredSeats)//modify
			return true;
		else 
			return false;
	}
	return false;

}

vector< AvailSeats >::iterator AvailSeatsDatabase::searchAvailSeats( Date date )
{
	vector< AvailSeats >::iterator it = availSeats.begin();
	for (; it != availSeats.end(); ++it)
	{
		if (it->getDate().operator==(date))
		{
			return it;
		}
	}
	return availSeats.end();
}

void AvailSeatsDatabase::loadAvailSeats()
{
	AvailSeats buf;
	fstream file("AvailSeats.dat", ios::in | ios::out | ios::binary);
	for (int i = 0; !file.eof(); i++)
	{
		file.read(reinterpret_cast<char*>(&buf), sizeof(buf));
		availSeats.push_back(buf);
	}
}

void AvailSeatsDatabase::storeAvailSeats()
{
	fstream file("AvailSeats.dat", ios::in | ios::out | ios::binary);
	for (int i = 0; i < availSeats.size(); i++)
	{
		file.write(reinterpret_cast<char*>(&availSeats[i]), sizeof(availSeats[i]));
	}
}