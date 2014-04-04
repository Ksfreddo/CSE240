#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FlightNode;
class HubNode;
class Date_Time;
class FlightPlan;

typedef enum {Junk, Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec} Month;

HubNode *head = NULL, *hubTemp;
FlightNode *flightHead = NULL, *flightTemp;

class HubNode {
public:	
	string Name;
	string Location;
	HubNode* next;
	FlightNode* headFlights;

	HubNode::HubNode()
	{
	}
	
	virtual ~HubNode()
	{
		do
		{
			hubTemp = head->next;
			delete head;
			head = hubTemp;
		}while (head != NULL);

	}
};

HubNode* hubSearch (string);

class Date_Time {
public:
	int minutes;
	int hours;
	int day;
	int month;
	int year;

	Date_Time::Date_Time()
	{
	}

	Date_Time::Date_Time(int a, int b, int c, int d, int e)
	{
		minutes = a;
		hours = b;
		day = c;
		month = d;
		year = e;
	}

	void AddMinutes(int min)
	{
		minutes = minutes + min;
		if (minutes >= 60)
		{
			minutes = minutes - 60;
			hours++;
			if (hours >= 24)
			{
				hours = hours - 24;
				day++;
				if (day > 29 && month == Feb)
				{
					day = day-29;
					month++;
				}else if (day > 30 && month == Apr||month ==Jun||month ==Sept||month ==Nov)
				{
					day = day-30;
					month++;
				}else if(day > 31)
				{
					day = day-31;
					month++;
				}
				if (month > Dec)
				{
					month = Jan;
					year++;
				}
			}
		}
	}

	void toString()
	{
		cout<< hours << ":" << minutes << " "<< month << "/"<< day << "/"<< year << '\n';
	}
};

class FlightNode {
public:
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time departure;
	int duration;
	HubNode* source;
	HubNode* destination;
	FlightNode * next;

	FlightNode::FlightNode()
	{
	}

	int getBaggageFees();
	int getDelay();

	virtual ~FlightNode()
	{
		do
		{
			flightTemp = flightHead->next;
			delete flightHead;
			flightHead = flightTemp;
		}while (flightHead != NULL);
	}
};

class FlightPlan
{

};

class Southwest: public FlightNode
{
	int bags;

	Southwest(int noOfBags): FlightNode()
	{
		bags = noOfBags;
	}

	int getBaggageFees()
	{
		int fees;
		
		fees = bags * 25;
		return fees;
	}

	int getDelay()
	{
		if (departure.hours >= 7 || departure.hours <= 17)
			return 30;
		else
			return 0;
	}
};

class Delta: public FlightNode
{
	int bags;

	Delta(int noOfBags): FlightNode()
	{
		bags = noOfBags;
	}

	int getBaggageFees()
	{
		return 0;
	}

	int getDelay()
	{
		return 20;
	}
};

class USAirways: public FlightNode
{
	int bags;
	
	USAirways(int noOfBags): FlightNode()
	{
		bags = noOfBags;
	}

	int getBaggageFees()
	{
		int fees;
		
		if (bags > 0)
			fees = (bags-1) * 25;
		else 
			return 0;

		return fees;
	}

	int getDelay()
	{
		if (departure.hours >= 7 || departure.hours <= 17)
			return 10;
		else if (departure.hours > 17 || departure.hours <= 1)
			return 15;
		else
			return 0;
	}
};

void printHub()
{
	hubTemp = head;
	while (hubTemp != NULL)
	{
		cout << hubTemp -> Name << ' ' << hubTemp -> Location << '\n';
		hubTemp = hubTemp -> next;
	}
}

void printFlight()
{
	flightTemp = flightHead;
	while (flightTemp != NULL)
	{
		cout << flightTemp -> flightNumber << ' ' << flightTemp -> price << ' ' << flightTemp ->
			flightCompany << ' ';
		flightTemp -> departure.toString();
		cout << flightTemp -> source -> Name << ' ' << flightTemp -> destination -> Name << ' ' << flightTemp ->
			duration << '\n';

		flightTemp = flightTemp -> next;
	}
}

void freeHub()
{
	while (head != NULL)
	{
		hubTemp = head->next;
		free(head);
		head = hubTemp;
	}
}

void freeFlight()
{
	while (flightHead != NULL)
	{
		flightTemp = flightHead->next;
		free(flightHead);
		flightHead = flightTemp;
	}
}

int main () {
	int x;
	hubTemp = new HubNode;
	string skipline;
	ifstream myfile ("Hub.csv");
	if (myfile.is_open() && myfile != NULL)
	{
		getline(myfile, skipline);
		while (myfile.good())
		{
			getline(myfile, hubTemp -> Name, ',');
			getline(myfile, hubTemp -> Location);

			hubTemp -> next = head;
			head = hubTemp;
			hubTemp = new HubNode;
	    }
		myfile.close();
		hubTemp = head ->next;
		free(head);
		head = hubTemp;
	}
	else cout << "Unable to open file"; 

	printHub();

	flightTemp = new FlightNode;
	string passline, number, price, source, destination, departuremin,departurehour,
		departureday,departuremonth,departureyear,duration, company;
	int min, hour, day, month, year;
	ifstream flightfile ("Flight.csv");
	if (flightfile.is_open() && flightfile != NULL)
	{
		getline(flightfile, passline);
		while ( flightfile.good() )
		{
			getline(flightfile, flightTemp -> flightNumber, ',');
			getline(flightfile, price, ',');
			getline(flightfile, source, ',');
			getline(flightfile, destination, ',');
			getline(flightfile, departuremin, '/');
			getline(flightfile, departurehour, '/');
			getline(flightfile, departureday, '/');
			getline(flightfile, departuremonth, '/');
			getline(flightfile, departureyear, ',');
			getline(flightfile, duration, ',');
			getline(flightfile, flightTemp -> flightCompany);

			flightTemp -> price = atof(price.c_str());
			min = atoi(departuremin.c_str());
			hour = atoi(departurehour.c_str());
			day = atoi(departureday.c_str());
			month = atoi(departuremonth.c_str());
			year = atoi(departureyear.c_str());
			flightTemp -> duration = atoi(duration.c_str());

			Date_Time y = Date_Time(min, hour, day, month, year);
			
			flightTemp -> departure = y;
			flightTemp -> source = hubSearch(source);
			flightTemp -> destination = hubSearch(destination);
			flightTemp -> next = flightHead;
			flightHead = flightTemp;
			flightTemp = new FlightNode;
	    }
		myfile.close();

		flightTemp = flightHead -> next;
		free(flightHead);
		flightHead = flightTemp;
	}
	else cout << "Unable to open file";
	
	cout << '\n';
	printFlight();
	freeHub();
	freeFlight();
	cin >> x;
}

HubNode* hubSearch(string search)
{
	HubNode *p = head, *b = p;

	while (p != NULL)
	{
		if (search.compare(p -> Name) == 0)
		{
			return b;
		}
		else
		{
			b = p;
			p = p-> next;
		}
	}
}