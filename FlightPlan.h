#ifndef FlightPlan_H
#define FlightPlan_H

#include <iostream>
#include <fstream>
#include <string>
#include "HubNode.h"
#include "FlightNode.h"
#include "Date_Time.h"


class FlightNode;
class HubNode;
class Date_Time;

class FlightPlan
{
	FlightNode *flights[2];
};

#endif
