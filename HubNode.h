#ifndef HubNode
#define HubNode

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

#endif
