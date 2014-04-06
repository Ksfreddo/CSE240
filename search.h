#ifndef SEARCH_h
#define SEARCH_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "Date_Time.h"
#include "HubNode.h"
#include "FlightNode.h"

#pragma warning(disable: 4996)

using namespace std;

//class Date_Time;
class FlightNode;
class HubNode;
class Search;

void cheapest_Search(HubNode* source, string destination, Search* search_temp, Search* flight_temp, int depth, Date_Time *startDate, Date_Time *endDate, int total_bags);
void shortest_Search(HubNode* source, string destination, Search* search_temp, Search* flight_temp, int depth, Date_Time *startDate, Date_Time *endDate);

HubNode *head = NULL, *hubTemp;
FlightNode *flightTemp;

class Search
{
public:
	int total_bags;
	Date_Time *time;
	FlightNode *node[2];
	HubNode *source;
	HubNode *destination;

	Search::Search()
	{
		time = new Date_Time();
		source = NULL;
		destination = NULL;
	}
	
	Search::~Search()
	{
		delete time;
		source = NULL;
		destination = NULL;
	}
	
	float Search::cost(int flight_bags) 
	{
		float cost;
	
		cost = 0;
	
		if(node[0] == NULL)
		{
			return -1;
		}
	
		else
		{
			for (int i = 0; (i < 2 && node[i] != NULL); i++)
			{
				node[i]->setBags(flight_bags);
				cost = cost + (float) node[i]->price + (float) node[i]->getBaggageFees();
			}
		}
		return cost;
	}

	void Search::printItinerary() 
	{ //bags, cost, end time, hubs
		int i = 0;
		cost(total_bags); //Called to setBags during shortestflight
		while (node[i] != NULL && i < 2)
		{
			node[i]->toString();
			i++;
			cout << '\n';
		}
		i--;

		cout << "Number of Bags: " << total_bags << endl;
		cout <<"Total cost: "<< cost(total_bags) << endl;
	}

	Date_Time Search::endTime() 
	{
		int tempIT = 0;
		Date_Time endTime = node[0]->arriveAt;
	
		while (node[tempIT] != NULL && tempIT < 2)
		{
			endTime = node[tempIT]->arriveAt;
			tempIT++;
		}

		return endTime;
	}
	
	int Search::flight_time() 
	{
		int total_time = 0;

		if (node[0] == NULL)
		{
			return -1;
		}
		
		for (int i = 0; i < 2; i++)
		{
			if (node[i] != NULL)
			{
				total_time += node[i]->duration + node[i]-> getDelay();
			}
		}

		return total_time;
	}
};

HubNode* hubSearch(string search)
{
	HubNode *p = head, *b = p;

	while (p != NULL)
	{
		if (search.compare(p -> Name) == 0)
		{
			return p;
		}
		else
		{
			b = p;
			p = p-> next;
		}
	}
}

void flightSearch(Date_Time* startDate, Date_Time* endDate, string destination, int total_bags, string searchMethod) 
{
	Search* search_temp = new Search();
	Search* flight_temp = new Search();

	flight_temp->total_bags = search_temp->total_bags = total_bags;

	flight_temp->source = search_temp->source = hubSearch("Phoenix Sky Harbor International Airport");

	flight_temp->node[0] = search_temp->node[0] = flight_temp->node[1] = search_temp->node[1] = NULL;

	flight_temp->time = startDate;


	if (searchMethod.compare("shortest") == 0) 
	{
		shortest_Search(search_temp->source, destination, search_temp, flight_temp, 0, startDate, endDate);
	} 
	else 
	{
		cheapest_Search(search_temp->source, destination, search_temp, flight_temp, 0, startDate, endDate, total_bags);
	}

	search_temp->time = &search_temp->node[0]->departure;

	search_temp->printItinerary();


	flight_temp->time = NULL;
	search_temp->time = NULL;

	delete search_temp;   //Remove from memory
	delete flight_temp;   //Remove from memory
}


void cheapest_Search(HubNode* source, string dest, Search* search_temp, Search* flight_temp, int depth, Date_Time *startDate, Date_Time *endDate, int total_bags)
{
	if (flight_temp->destination != NULL && flight_temp->destination->Location.compare(dest) == 0 && flight_temp->time->dateCompare(*startDate) == 0)
	{
		float cheapestCost = search_temp->cost(total_bags);
		float lowestCost_temp = flight_temp->cost(total_bags);

		if (cheapestCost < 0 || lowestCost_temp < cheapestCost) 
		{
			for (int i = 0; i < 2; i++) 
			{
				search_temp->node[i] = flight_temp->node[i];
			}
			*search_temp->time = *flight_temp->time;
			search_temp->destination = flight_temp->destination;
		}

		return;  //break
	}
	else if (depth == 2)  //Return
	{
		return;
	} 
	else 
	{
		FlightNode* flightNode_temp = source->headFlights;

		while (flightNode_temp != NULL) 
		{
			if (depth == 0)
			{
				flight_temp->node[0] = NULL;
				flight_temp->node[1] = NULL;
			}
			if (flight_temp->node[0] == NULL || flight_temp->endTime().dateCompare(flightNode_temp->departure) == 0 ) 
			{
				flight_temp->node[depth] = flightNode_temp;
				flight_temp->destination = flightNode_temp->destination;
				*flight_temp->time = flightNode_temp->departure;
				flight_temp->time->AddMinutes(flightNode_temp->getDelay());
				cheapest_Search(flightNode_temp->destination,dest, search_temp, flight_temp, (depth + 1), startDate, endDate, total_bags);
			}

			flightNode_temp = flightNode_temp->next;
		}
	}
}

void shortest_Search(HubNode* source, string destination, Search* search_temp, Search* flight_temp, int depth, Date_Time *startDate, Date_Time *endDate) 
{
	if (flight_temp->destination != NULL && flight_temp->destination->Location.compare(destination) == 0 && flight_temp->time->dateCompare(*startDate) >= 0 && flight_temp->endTime().dateCompare(*endDate) >=0 ) 
	{
		int leastFlightTime = search_temp->flight_time();
		int time_Temp = flight_temp->flight_time();

		if (leastFlightTime < 0 || time_Temp < leastFlightTime) 
		{
			for (int i = 0; i < 2; i++) 
			{
			  search_temp->node[i] = flight_temp->node[i];
			}

			*search_temp->time = *flight_temp->time;
			search_temp->destination = flight_temp->destination;
		}

		return;

	} 
	else if (depth == 2) 
	{
		return;
	} 
	else 
	{
		FlightNode* flightNode_temp = source->headFlights;

		while (flightNode_temp != NULL) 
		{
			if (depth == 0)
			{
				flight_temp->node[0] = NULL;
				flight_temp->node[1] = NULL;
			}

			if (flight_temp->node[0] == NULL || flight_temp->endTime().dateCompare(flightNode_temp->departure) >= 0 ) 
			{
				flight_temp->node[depth] = flightNode_temp;
				flight_temp->destination = flightNode_temp->destination;

				*flight_temp->time = flightNode_temp->departure;

				//*flight_temp->node[depth] = *flightNode_temp->departure;
				flight_temp->time->AddMinutes(flightNode_temp->getDelay());
				shortest_Search(flightNode_temp->destination,destination, search_temp, flight_temp, (depth + 1), startDate, endDate);
			}

			flightNode_temp = flightNode_temp->next;
		}
	}	
}


#endif
