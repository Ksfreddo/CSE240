#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Date_Time.h"
#include "FlightNode.h"
#include "HubNode.h"
#include "search.h"

using namespace std;

class FlightNode;
class HubNode;
class Date_Time;

HubNode* hubSearch (string);

void freeHub()
{
	while (head != NULL)
	{
		hubTemp = head->next;
		delete head;
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

			if (company.compare("SouthWest") == 0)
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

			Date_Time depart = Date_Time(min, hour, day, month, year);
			Date_Time arrive = depart;
			arrive.AddMinutes((flightTemp->duration + flightTemp->getDelay()));
			
			flightTemp -> departure = &depart;
			hubTemp = hubSearch(source);
			flightTemp -> source = hubTemp;
			flightTemp -> destination = hubSearch(destination);
			flightTemp -> next = flightTemp -> source -> headFlights;
			hubTemp -> headFlights = flightTemp;
	    }
		myfile.close();
	}
	else cout << "Unable to open file";
	Date_Time start = Date_Time(00,0, 16, 12,2013);
	Date_Time end = Date_Time(59,23,18,12,2013);
	Date_Time *startTest = &start, *endTest = &end;

	flightSearch(startTest, endTest, "Los Angeles", 3, "Cheapest");
	cout << '\n';
	freeHub();
	cin >> x;
}
