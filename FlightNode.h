#ifndef FlightNode_h
#define FlightNode_h

#include <iostream>
#include <fstream>
#include <string>
#include "Date_Time.h"
#include "HubNode.h"

using namespace std;

class HubNode;

class FlightNode {
public:
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time *departure;
	Date_Time *arriveAt;
	int duration;
	HubNode* source;
	HubNode* destination;
	FlightNode * next;

	FlightNode()
	{
		next = NULL;
	}

	virtual void setBags(int Bags) {};
	virtual int getBaggageFees() {};
	virtual int getDelay() {};

	virtual ~FlightNode()
	{
		source = NULL;
		destination = NULL;
		next = NULL;
	}
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
		if (departure->hours >= 7 || departure->hours <= 17)
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
		if (departure->hours >= 7 || departure->hours <= 17)
			return 10;
		else if (departure->hours > 17 || departure->hours <= 1)
			return 15;
		else
			return 0;
	}
};


#endif
