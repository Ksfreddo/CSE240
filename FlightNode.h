#ifndef FlightNode_H
#define FlightNode_H

#include <iostream>
#include <fstream>
#include <string>
#include "Date_Time.h"
#include "HubNode.h"

using namespace std;

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

	FlightNode::FlightNode()
	{
		next = NULL;
	}

	virtual ~FlightNode()
	{
		source = NULL;
		destination = NULL;
		next = NULL;
	}

	virtual void FlightNode::setBags(int Bags) {}
	virtual int FlightNode::getBaggageFees()
	{
		return 0;
	}
	virtual int FlightNode::getDelay()
	{
		return 0;
	}
};

class Southwest: public FlightNode
{
public:
	int bags;

	Southwest(): FlightNode()
	{
	}

	void Southwest::setBags(int Bags)
	{
		bags = Bags;
	}

	int Southwest::getBaggageFees()
	{
		int fees;
		
		fees = bags * 25;
		return fees;
	}

	int Southwest::getDelay()
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

	void Delta::setBags(int Bags)
	{
		bags = Bags;
	}

	int Delta::getBaggageFees()
	{
		return 0;
	}

	int Delta::getDelay()
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

	void USAirways::setBags(int Bags)
	{
		bags = Bags;
	}

	int USAirways::getBaggageFees()
	{
		int fees;
		
		if (bags > 0)
			fees = (bags-1) * 25;
		else 
			return 0;

		return fees;
	}

	int USAirways::getDelay()
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
