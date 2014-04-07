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
			flightTemp ->flightCompany = company;
			flightTemp -> price = atof(price.c_str());
			min = atoi(departuremin.c_str());
			hour = atoi(departurehour.c_str());
			day = atoi(departureday.c_str());
			month = atoi(departuremonth.c_str());
			year = atoi(departureyear.c_str());
			flightTemp -> duration = atoi(duration.c_str());

			Date_Time depart = Date_Time(min, hour, day, month, year);
			Date_Time arrive = depart;
			flightTemp -> departure = depart;
			arrive.AddMinutes((flightTemp->duration + flightTemp->getDelay()));
			flightTemp -> arriveAt = arrive;

			
			hubTemp = hubSearch(source);
			flightTemp -> source = hubTemp;
			flightTemp -> destination = hubSearch(destination);
			flightTemp -> next = flightTemp -> source -> headFlights;
			hubTemp -> headFlights = flightTemp;
	    }
		myfile.close();
	}
	else cout << "Unable to open file";
		
		
	int cont=0;
	while(cont==0){
	int iday=0;
	int imonth=0;
	int iyear=0;
	int ibag=0;
	int temp=0;
	string idest;
	string itype;

	while(imonth==0){
		cout << "What month would you like to leave(1-12)?\n";
		cin >> imonth;
		if (cin.fail()){
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
		if(imonth>12||imonth==0){
			cout << "Please enter a valid month.\n";
			imonth=0;
		}
	};
	while(iday==0){
		cout << "What day would you like to leave(1-31)?\n";
		cin >> iday;
		if (cin.fail()){
				cin.clear();
				cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
		if(imonth==1||3||5||7||8||10||12){
			if(iday>31)
				iday=0;
		}
		else if(imonth==2){
			if(iday>29)
				iday=0;
		}
		else if(imonth==4||6||9||11){
			if(iday>30)
				iday=0;
		}
		if (iday==0)
			cout << "Please enter a valid date.\n";
	};
	cout << "What year would you like to leave(yyyy)?\n";
	cin >> iyear;
	if (cin.fail()){
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(), '\n');
	}
	while(temp==0){
		cout << "Where would you like to travel?\n1.Tucson\n2.Los Angeles\n3.San Francisco\n4.San Diego\n5.Albany\n"; 
		cout <<	"6.Chicago Midway\n7.Chicago O'Hare\n8.General Edward Lawrence Logan\n9.Mc Carran\n10.John F Kennedy\n";
		cout << "11.Miami\n12.Honolulu\n13.Denver\n";
		cin >> temp;
		if (cin.fail()){
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
		switch (temp) {
			case 1:
				idest="Tucson";
				break;
			case 2:
				idest="Los Angeles";
			    break;
			case 3: 
				idest="San Francisco";
				break;   
			case 4:
				idest="San Diego";
				break;
			case 5:
				idest="Albany";
				break;
			case 6:
				idest="Chicago Midway";
				break;
			case 7:
				idest="Chicago O'Hare";
			    break;
			case 8:
				idest="General Edward Lawrence Logan";
				break;
			case 9:
				idest="Mc Carran";
			    break;
			case 10:
				idest="John F Kennedy";
			    break;
			case 11:
				idest="Miami";
				break;
			case 12:
				idest="Honolulu";
			    break;
			case 13:
				idest="Denver";
				break;
			default:
				cout << "Please enter a valid destination.\n";
				temp=0;
		}
	} 
	while(itype.empty()){
		cout << "Would you like the cheapest flight or shortest?(c or s)\n";
		cin >> itype;
		if(itype=="c")
			itype="Cheapest";
		else if(itype=="s")
			itype="Shortest";
		else{
			cout << "Please enter c or s.";
			itype.clear();
		}
	}
	cout << "How many bags?\n";
	cin >> ibag;

	Date_Time start = Date_Time(00,0,iday,imonth,iyear);
	Date_Time end = Date_Time(59,23,18,12,2014);
	Date_Time *startTest = &start, *endTest = &end;

	flightSearch(startTest, endTest, idest, ibag, itype);
	freeHub();

	int x=0;
	while(x==0){
		cout << "Would you like to search again?\n1.No\n2.Yes";
		cin >> temp;
		if (cin.fail()){
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
		if(temp==1){
			cont=0;
			x=1;
		}
		else if(temp==2){
			cont=1;
			x=1;
		}
		else
			cout << "Please enter 1 or 2.";
	}
	}
}
