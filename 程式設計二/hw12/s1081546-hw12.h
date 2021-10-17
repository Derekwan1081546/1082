#ifndef S1081546_HW12_H
#define S1081546_HW12_H
#include<fstream>
using namespace std;

struct Reservation
{
	char reservationNumber[12]; // used to identify a reservation
	char trainNumber[8];  // used to identify a train
	char idNumber[12];    // the id number of the contact person
	char phone[12];       // the (local or mobile) phone number of the contact person
	char date[12];        // outbound date
	int originStation;      // the origin station code
	int destinationStation; // the destination station code
	int carClass;           // the car class code; 1:standard car, 2:business car
	int adultTickets;       // the number of adult tickets
	int concessionTickets;  // the number of concession tickets
};

struct Train
{
	char trainNumber[8];          // used to identify a train
	char departureTimes[13][8]; // the departure time of a train for each station,
};

class bookingsystem
{
public:
	bookingsystem();
	~bookingsystem();

	int adultTicketPrice[13][13] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,    0,    0,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,    0,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

	char departureTimes[37][8] = { "",
	   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
	   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
	   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
	   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
	   "22:00", "22:30", "23:00", "23:30" };

	// input an integer in the range [ begin, end ]
	int inputAnInteger(int begin, int end) {
		char a[20] = { '\0' };
		cin >> a;

		if ((begin == 1 && end == 3) && (a[1] == '\0' && a[0] == '0'))
			return 0;
		else if (a[1] == '\0' && a[0] == '0')
			return -1;

		int num = 0;
		int index = strlen(a);
		int ten = 1;

		for (int i = 0; i < strlen(a); i++)
		{
			for (int j = index; j > 1; j--)
			{
				ten *= 10;
			}
			index--;
			num += ten * (a[i] - '0');
			ten = 1;
		}

		if (num >= begin && num <= end)
			return num;
		else
			return -1;
	}


	void makingReservation(Train southboundTimetable[100], Train northboundTimetable[100])
	{
		Reservation buffer;
		int departureTime = 0;
		int num1 = 0;
		int num2 = 0;
		char carclass[12];
		char stationName[13][12] = { "" ,"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
		inputReservationDetails(buffer, departureTime);
		loadSouthboundTimetable(southboundTimetable, num1);
		loadNorthboundTimetable(northboundTimetable, num2);
		if (buffer.destinationStation > buffer.originStation) {
			selectSouthboundTrain(southboundTimetable, num1, buffer, departureTime);
			display(buffer, southboundTimetable, stationName, carclass);
		}
		else {
			selectNorthboundTrain(northboundTimetable, num2, buffer, departureTime);
			display(buffer, northboundTimetable, stationName, carclass);
		}
		inputContactInfo(buffer);
		saveReservation(buffer);
	}

	// inputs originStation, destinationStation, carClass,
	// date, departureTime, adultTickets and concessionTickets
	void inputReservationDetails(Reservation& reservation, int& departureTime)
	{
		cout << "Origin Station\n";
		char stationName[13][9] = { "" ,"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
		for (int i = 1; i < 13; i++) {
			cout << i << ". " << stationName[i] << endl;
		}
		do cout << "? ";
		while ((reservation.originStation = inputAnInteger(1, 13)) == -1);
		cout << endl;

		cout << "Destination Station\n";
		for (int i = 1; i < 13; i++) {
			cout << i << ". " << stationName[i] << endl;
		}
		do cout << "? ";
		while ((reservation.destinationStation = inputAnInteger(1, 13)) == -1 && reservation.destinationStation == reservation.originStation);
		cout << endl;
		cout << "Car Class\n";
		cout << "1. Standard Car\n2. Business Car\n";
		bool zero;
		do {
			zero = 0;
			do cout << "? ";
			while ((reservation.carClass = inputAnInteger(1, 2)) == -1);
			if (reservation.carClass == 2) {
				if (adultTicketPrice[reservation.originStation][reservation.destinationStation] == 0) {
					zero = 1;
				}
			}
		} while (zero);
		cout << endl << endl;
		cout << "Departure Date :";
		cin >> reservation.date;
		cout << endl << endl;
		cout << "Departure Time\n";
		for (int i = 1; i < 37; i++) {
			cout << i << ". " << departureTimes[i] << endl;
		}
		do cout << "? ";
		while ((departureTime = inputAnInteger(1, 36)) == -1);
		cout << "How many adult tickets? ";
		cin >> reservation.adultTickets;
		cout << endl;
		cout << "How many concession tickets? ";
		cin >> reservation.concessionTickets;
	}

	// loads the southbound timetable from the file "Southbound timetable.dat"
	void loadSouthboundTimetable(Train southboundTimetable[100], int& numSouthboundTrains)
	{
		fstream file("Southbound timetable.dat", ios::in | ios::out | ios::binary);
		file.seekg(0, ios::end);
		int numLine = file.tellg() / sizeof(southboundTimetable);
		file.seekg(0, ios::beg);

		for (int i = 0; !file.eof(); i++)
		{
			file.read(reinterpret_cast<char*>(&southboundTimetable[i]), sizeof(southboundTimetable[i]));
		}
	}

	// loads the northbound timetable from the file "Northbound timetable.dat"
	void loadNorthboundTimetable(Train northboundTimetable[100], int& numNorthboundTrains)
	{
		fstream file("Northbound timetable.dat", ios::in | ios::out | ios::binary);
		file.seekg(0, ios::end);
		int numLine = file.tellg() / sizeof(northboundTimetable);
		file.seekg(0, ios::beg);
		for (int i = 0; !file.eof(); i++) 
		{
			file.read(reinterpret_cast<char*>(&northboundTimetable[i]), sizeof(northboundTimetable[i]));
		}
	}

	// displays timetables for 10 coming southbound trains, then let user select one
	void selectSouthboundTrain(Train southboundTimetable[100], int numSouthboundTrains,
		Reservation& reservation, int departureTime)
	{
		Train train[10];
		int k;
		for (int i = 0; i < 100; i++) {
			if (strcmp(departureTimes[departureTime], southboundTimetable[i].departureTimes[reservation.originStation]) == -1) {
				k = i;
				for (int j = i; j < i + 10; j++) {
					if (strcmp(southboundTimetable[k].departureTimes[reservation.originStation], "-") == 0 || strcmp(southboundTimetable[k].departureTimes[reservation.destinationStation], "-") == 0) {
						k++;
						j--;
						continue;
					}
					k++;
					train[j - i] = southboundTimetable[k - 1];
				}
				break;
			}
		}
		cout << "Train No.  Departure  Arrival\n";
		for (int i = 0; i < 10; i++) {
			cout << setw(9) << right << train[i].trainNumber << setw(11) << right << train[i].departureTimes[reservation.originStation] << setw(9) << right << train[i].departureTimes[reservation.destinationStation] << endl;
		}
		bool same = 0;
		while (!same) {
			cout << "\nEnter Train Number: ";
			cin >> reservation.trainNumber;
			for (int i = 0; i < 10; i++) {
				if (strcmp(reservation.trainNumber, train[i].trainNumber) == 0) {
					same = 1;
					break;
				}
			}
		}
	}

	// displays timetables for 10 coming northbound trains, then let user select one
	void selectNorthboundTrain(Train northboundTimetable[100], int numNorthboundTrains,
		Reservation& reservation, int departureTime)
	{
		Train train[10];
		int k;
		reservation.originStation = (reservation.originStation - 13) * -1;
		reservation.destinationStation = (reservation.destinationStation - 13) * -1;
		for (int i = 0; i < 100; i++) {
			if (strcmp(departureTimes[departureTime], northboundTimetable[i].departureTimes[reservation.originStation]) == -1) {
				k = i;
				for (int j = i; j < i + 10; j++) {
					if (strcmp(northboundTimetable[k].departureTimes[reservation.originStation], "-") == 0 || strcmp(northboundTimetable[k].departureTimes[reservation.destinationStation], "-") == 0) {
						k++;
						j--;
						continue;
					}
					k++;
					train[j - i] = northboundTimetable[k - 1];
				}
				break;
			}
		}
		cout << "Train No.  Departure  Arrival\n";
		for (int i = 0; i < 10; i++) {
			cout << setw(9) << right << train[i].trainNumber << setw(11) << right << train[i].departureTimes[reservation.originStation] << setw(9) << right << train[i].departureTimes[reservation.destinationStation] << endl;
		}
		bool same = 0;
		while (!same) {
			cout << "\nEnter Train Number: ";
			cin >> reservation.trainNumber;
			for (int i = 0; i < 10; i++) {
				if (strcmp(reservation.trainNumber, train[i].trainNumber) == 0) {
					same = 1;
					break;
				}
			}
		}
		reservation.originStation = (reservation.originStation - 13) * -1;
		reservation.destinationStation = (reservation.destinationStation - 13) * -1;
	}

	// inputs idNumber and phone, and randomly generate reservationNumber
	void inputContactInfo(Reservation& reservation)
	{
		cout << "\nEnter Contact Person Information\n\n";
		cout << "ID Number: ";
		cin >> reservation.idNumber;
		cout << endl << endl;
		cout << "Phone: ";
		cin >> reservation.phone;
		cout << endl << endl;
		cout << "Reservation Number: ";
		int num = time(0);
		for (int i = 0; i < 8; i++) {
			srand(i + num);
			reservation.reservationNumber[i] = '0' + rand() % 10;
		}
		reservation.reservationNumber[8] = '\0';
		cout << reservation.reservationNumber << endl << endl;
		cout << "Reservation Completed!\n\n";
	}

	// save reservation to the end of the file Reservation details.dat
	void saveReservation(Reservation reservation)
	{
		fstream file("Reservation details.dat", ios::out | ios::in | ios::binary);
		if (!file) {
			ofstream file("Reservation details.dat", ios::out | ios::binary);
			file.write(reinterpret_cast<const char*>(&reservation), sizeof(reservation));
			return;
		}
		file.seekg(0, ios::end);
		int numline = file.tellg() / sizeof(reservation);
		file.seekg(0, ios::beg);
		int cancel = 0;
		for (int i = 0; i < numline; i++) {
			Reservation buffer;
			file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
			if (strcmp(buffer.idNumber, reservation.idNumber) == 0 && strcmp(buffer.reservationNumber, reservation.reservationNumber) == 0) {
				cancel = file.tellg() / sizeof(Reservation);
				file.seekp((cancel - 1) * sizeof(Reservation), ios::beg);
				file.write(reinterpret_cast<const char*>(&reservation), sizeof(reservation));
				return;
			}
		}
		file.seekg(0, ios::end);
		file.write(reinterpret_cast<const char*>(&reservation), sizeof(reservation));
	}

	void reservationHistory(Train southboundTimetable[100],
		Train northboundTimetable[100])
	{
		int a;
		loadNorthboundTimetable(northboundTimetable, a);
		loadSouthboundTimetable(southboundTimetable, a);
		Reservation buffer;
		char carclass[12] = "";
		char stationName[13][12] = { "" ,"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
		fstream file("Reservation details.dat", ios::in | ios::out | ios::binary);
		bool exist;
		do {
			exist = 0;
			if (existReservation(file, buffer)) {
				if (buffer.originStation < buffer.destinationStation) {
					display(buffer, southboundTimetable, stationName, carclass);
				}
				else display(buffer, northboundTimetable, stationName, carclass);
				exist = 1;
			}
			else {
				cout << "Reservation record not found.\n";
			}
		} while (!exist);
		int choice;
		do {
			cout << "Enter Your Choice\n";
			cout << "1. Cancellation\n2. Reduce\n3. End";
			do cout << "\n? ";
			while ((choice = inputAnInteger(1, 3)) == -1);
			cout << endl;
			switch (choice)
			{
			case 1:
				break;
			case 2:
				reduceSeats(file, southboundTimetable, northboundTimetable, buffer);
				break;
			case 3:
				return;
			default: // display error if user does not select valid choice
				cerr << "Incorrect Choice!\n";
				break;
			}
		} while (choice == 2);
		file.seekg(0, ios::beg);
		Reservation zero;
		zero.reservationNumber[0] = '\0';
		zero.trainNumber[0] = '\0';
		zero.idNumber[0] = '\0';
		zero.phone[0] = '\0';
		zero.date[0] = '\0';
		zero.originStation = 0;
		zero.destinationStation = 0;
		zero.carClass = 0;
		zero.adultTickets = 0;
		zero.concessionTickets = 0;
		int cancel = 0;
		while (!file.eof()) {
			Reservation reservation;
			file.read(reinterpret_cast<char*>(&reservation), sizeof(reservation));
			if (strcmp(reservation.idNumber, buffer.idNumber) == 0
				&& strcmp(reservation.reservationNumber, buffer.reservationNumber) == 0) {
				cancel = file.tellg() / sizeof(Reservation);
				break;
				//file.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
			}
		}
		file.seekg(0, ios::beg);
		for (int i = 1; i <= cancel; i++) {
			Reservation reservation;
			if (i == cancel) {
				file.seekp((cancel - 1) * sizeof(Reservation), ios::beg);
				file.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
			}
			else file.read(reinterpret_cast<char*>(&reservation), sizeof(reservation));
		}
		cout << "\nReservation Cancelled!";
	}

	// inputs idNumber and reservationNumber, and
	// checks if the corresponding reservation exists
	bool existReservation(fstream& ioFile, Reservation& reservation)
	{
		cout << "Enter ID Number :";
		cin >> reservation.idNumber;
		cout << endl << endl;
		cout << "Enter Reservation Number: ";
		cin >> reservation.reservationNumber;
		ioFile.clear();
		ioFile.seekg(0, ios::beg);

		while (!ioFile.eof()) {
			Reservation buffer;
			ioFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
			if (strcmp(reservation.idNumber, buffer.idNumber) == 0
				&& strcmp(reservation.reservationNumber, buffer.reservationNumber) == 0) {
				reservation = buffer;
				return true;
			}
		}
		return false;
	}


	void displayReservations(Train southboundTimetable[100],
		Train northboundTimetable[100], Reservation reservation)
	{
		cout << "Reservation Details \n\n";
		char carclass[12];
		char stationName[13][12] = { "" ,"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
		if (reservation.originStation < reservation.destinationStation) {
			display(reservation, southboundTimetable, stationName, carclass);
		}
		else display(reservation, northboundTimetable, stationName, carclass);
	}

	// displays date, originStation, destinationStation, departureTime, arrival time,
	// fare for adultTickets, fare for concessionTickets and total fare
	void display(Reservation reservation, Train trainTimetable[100],
		char stations[13][12], char carClass[12])
	{
		Train now;
		for (int i = 0; i < 100; i++) {
			if (strcmp(reservation.trainNumber, trainTimetable[i].trainNumber) == 0) {
				now = trainTimetable[i];
				break;
			}
		}
		int price = 0;
		if (reservation.carClass == 1) {
			price = adultTicketPrice[reservation.destinationStation][reservation.originStation];
		}
		else price = adultTicketPrice[reservation.originStation][reservation.destinationStation];
		int total = price * reservation.adultTickets + price / 2 * reservation.concessionTickets;
		cout << "\nTrip Details\n\n";
		cout << "      Date  Train No.    From        To  Departure  Arrival   Adult  Concession  Fare     Class\n";
		cout << setw(10) << right << reservation.date
			<< setw(11) << right << reservation.trainNumber
			<< setw(8) << right << stations[reservation.originStation];
		cout << setw(10) << right << stations[reservation.destinationStation];
		cout << setw(11) << right << now.departureTimes[reservation.originStation];
		cout << setw(9) << right << now.departureTimes[reservation.destinationStation];
		cout << setw(6) << right << price << "*" << reservation.adultTickets;
		cout << setw(10) << right << price / 2 << "*" << reservation.concessionTickets;
		cout << setw(6) << right << total;
		if (reservation.carClass == 1) {
			cout << setw(11) << right << "Standard\n";
		}
		else cout << setw(11) << right << "Business\n";
	}

	// reduces adultTickets and/or concessionTickets in reservation
	void reduceSeats(fstream& ioFile, Train southboundTimetable[100],
		Train northboundTimetable[100], Reservation& reservation)
	{
		int num = 0;
		do {
			cout << "How many adult tickets to cancel¡H";
		} while ((num = inputAnInteger(1, reservation.adultTickets)) == -1);
		reservation.adultTickets -= num;
		do {
			cout << "\nHow many concession tickets to cancel¡H";
		} while ((num = inputAnInteger(1, reservation.concessionTickets)) == -1);
		cout << endl << endl;
		reservation.concessionTickets -= num;
		displayReservations(southboundTimetable, northboundTimetable, reservation);
		cout << "\nYou have successfully reduced the number of tickets!\n";
		saveReservation(reservation);
	}

};

bookingsystem::bookingsystem()
{
}

bookingsystem::~bookingsystem()
{
}
#endif 