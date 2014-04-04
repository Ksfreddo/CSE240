#include <iostream>
#include <fstream>
#include <string>
#include "Date_Time.h"

using namespace std;

class FlightNode;
class HubNode;
class Date_Time;
class FlightPlan;

HubNode *head = NULL, *hubTemp;
FlightNode *flightTemp;

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

	/*virtual ~FlightNode()
	{
		do
		{
			flightTemp = flightHead->next;
			delete flightHead;
			flightHead = flightTemp;
		}while (flightHead != NULL);
	}*/
};

class FlightPlan
{

};

class Southwest: public FlightNode
{
public:
	int bags;

	Southwest(): FlightNode()
	{
	}

	void setBags(int Bags)
	{
		bags = Bags;
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
public:
	int bags;

	Delta(): FlightNode()
	{
	}

	void setBags(int Bags)
	{
		bags = Bags;
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
public:
	int bags;
	
	USAirways(): FlightNode()
	{
	}

	void setBags(int Bags)
	{
		bags = Bags;
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

void freeHub()
{
	while (head != NULL)
	{
		hubTemp = head->next;
		free(head);
		head = hubTemp;
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
		while (getline(myfile, hubTemp -> Name, ','))
		{
			getline(myfile, hubTemp -> Location);

			hubTemp -> next = head;
			head = hubTemp;
			hubTemp = new HubNode;
	    }
		myfile.close();

	}
	else cout << "Unable to open file"; 

	printHub();

	string passline, number, price, source, destination, departuremin,departurehour,
		departureday,departuremonth,departureyear,duration, company;
	int min, hour, day, month, year;
	ifstream flightfile ("Flight.csv");
	if (flightfile.is_open() && flightfile != NULL)
	{
		getline(flightfile, passline);
		while (getline(flightfile, number, ',') )
		{
			getline(flightfile, price, ',');
			getline(flightfile, source, ',');
			getline(flightfile, destination, ',');
			getline(flightfile, departuremin, '/');
			getline(flightfile, departurehour, '/');
			getline(flightfile, departureday, '/');
			getline(flightfile, departuremonth, '/');
			getline(flightfile, departureyear, ',');
			getline(flightfile, duration, ',');
			getline(flightfile, company);

			if (company.compare("Southwest") == 0)
				flightTemp = new Southwest();
			else if (company.compare("Delta") == 0)
				flightTemp = new Delta();
			else if (company.compare("USAirway") == 0)
				flightTemp = new USAirways();

			flightTemp ->flightNumber = number;
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
			flightTemp -> next = flightTemp -> source -> headFlights;
			flightTemp -> source -> headFlights = flightTemp;
	    }
		myfile.close();
	}
	else cout << "Unable to open file";
	
	cout << '\n';
	freeHub();
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
