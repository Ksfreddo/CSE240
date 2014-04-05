#ifndef HubNode_h
#define HubNode_h

#include <iostream>
#include <fstream>
#include <string>
#include "FlightNode.h"

using namespace std;
class FlightNode;

class HubNode { //Class for airport terminals.
public:	
	string Name;
	string Location;
	HubNode* next;
	FlightNode* headFlights;

	HubNode()
	{
		next = NULL;
		headFlights = NULL;
	}

	~HubNode()
	{
		next = NULL;
	}
};

#endif
