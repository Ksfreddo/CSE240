#ifndef FlightNode_h
#define FlightNode_h

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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


#endif
