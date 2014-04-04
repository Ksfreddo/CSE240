#ifndef HubNode_h
#define HubNode_h

#include <iostream>
#include <fstream>
#include <string>
#include "FlightNode.h"

using namespace std;
class FlightNode;

class HubNode {
public:	
	string Name;
	string Location;
	HubNode* next;
	FlightNode* headFlights;

	HubNode::HubNode()
	{
		next = NULL;
		headFlights = NULL;
	}

	HubNode::~HubNode()
	{
		next = NULL;
	}
};

#endif
