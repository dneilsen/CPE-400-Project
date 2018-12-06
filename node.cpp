//////////////////////////////////////////////////////////////////////////////////////////////////////
// CPE 400 Project
// dynamic routing mechanism design with focus on throughput
//
// Edited by
// David Neilson: Node class
// Nicholas Rini: edited Node class, created Network
// Michael Mills: edited node class, added linkStateAlgorithm, added file stream, added packet class
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// global constants
const int maxcapacity = 5;
const int updateTime = 10;



class Node{

	public:
	
    int ID;
	int queue;
	int capacity;
	int pSpeed;
	int weight;
	// forwarding table
	int destination[9];
	int link[9];
	// links from node
    vector<Node> neighbors;

	Node();
	~Node();

};

Node::Node(){

    ID = 0;
	queue = 0;
	capacity = maxcapacity;
	pSpeed = 5;
	weight = 1;
}

Node::~Node(){

	neighbors.clear();

}

// make forwarding table through link state algorithm, this means the network is centralized ospf
// the algorithm is dijkstra's page 393 in the book.
void linkStateAlgorithm( Node* array, int arrayNum ) // aka dijkstra's
{
	// initialize
	arrayNum;
	int cost[arrayNum];
	int parent[arrayNum];
	int nsize,i,j;
	for( i = 0; i < arrayNum; i++)
	{
		for( j = 0; j < arrayNum-1; j++ )			// the initialize
		{
			cost[i] = 0; // 0 will represent infinity
		}
		
		nsize = array[i].neighbors.size()			// the loop
		for( int j = 0; j < nsize; j++)
		{
			cost[array[i].neighbors[j].ID] = array[i].neighbors[j].weight;
		}
		for( int j = 0; j < arrayNum; j++ )
		{
			
		}
	}		
}

// packet class
class Packet
{
	public:
	// udp style packet leaving out length and checksum
	int source;
	int destination;
	Packet();
	~Packet();
	// data in packet, not creating separate data structure
	int ID, currentNode;	
	time_t startTime;
	time_t endTime;
	bool lost,done;
	vector<int> nodeStop; // size of nodeStop is # of hops
	vector<int> queueAtNode;
	
	makePacket( int s, int d, int id );
	
};
Packet::Packet()
{
	
}
Packet::~Packet()
{
	
}
Packet::makePacket( int s, int d, int id);
{
	source = s;
	destination = d;
	ID = id;
	currentNode = 99; // 99 means its waiting to enter network
	startTime = time(0);
	lost = false;
	nodeStop.push_back( s );
	queueAtNode.push_back( id );
}

int main( int argc, char* argv[] )
{
	int i, j, k = 0, numPackets = 0, list;

	// read in from file the source destinatin and # of packets
	ifstream packetFile;
	packetFile.open( argv[1] );
	if( !packetFile.is_open()) {cout << "potential error: input file open";}
	
	packetFile >> list;
	int rsource[list], rdestination[list], rpacketnum[list];	
	
	while( packetFile.good() )
	{
		packetFile >> rsource[i];
		packetFile >> rdestination[i];
		packetFile >> rpacketnum[i];
		k++;
	}
	if( k != list ){ cout << "potential error: input file length";}
	// create the network
	Node* array = new Node[8];

	for( i = 0; i < 8; i++)
	{
		array[i].ID = i;

	}
	// creates network
	array[0].neighbors.push_back(array[1]);
	array[0].neighbors.push_back(array[4]);

	array[1].neighbors.push_back(array[0]);
	array[1].neighbors.push_back(array[3]);

	array[2].neighbors.push_back(array[6]);

	array[3].neighbors.push_back(array[1]);

	array[4].neighbors.push_back(array[0]);
	array[4].neighbors.push_back(array[5]);

	array[5].neighbors.push_back(array[4]);
	array[5].neighbors.push_back(array[7]);
	array[5].neighbors.push_back(array[8]);

	array[6].neighbors.push_back(array[8]);
	array[6].neighbors.push_back(array[7]);

	array[7].neighbors.push_back(array[5]);
	array[7].neighbors.push_back(array[6]);

	array[8].neighbors.push_back(array[5]);
	array[8].neighbors.push_back(array[6]);
	
	// create packets for the network
	for( i = 0; i < list; i++ )
	{
		numPackets += rpacketnum[i]; // gets total number of packets
	}
	Packet rpacket[numPackets]; // creates a list of all packets

	for( i = 0; i < list; i++ )
	{
		for( j = 0; j < rpacketnum[i]; j++ )
		{
			rpackets[i] = makePacket( rsource[i], rdestination[i], i )
		}
	}
	// no longer have to worry about command line arguments
	// now to loop through all the packets through the nodes
	int count = 0;
	while( packetsLeft )
	{
		// load packets into network
		int previousNode = 99;
		for( i = 0; i < numPackets; i++ )
		{
			if( (rpacket[i].ID != previousNode) && (rpacket[i].currentNode != 99) )
			{
				rpacket[i].currentNode = rpacket[i].source;
			}
		}

	}
	// file output
	int plost = 0;
	ofstream results ("results.txt");
	if( results.is_open())
	{
		// calculate overall throughput and output to file // average( endTime - startTime + ( sum(queueatnode) * nodalDelay ) )
		
		// output #of packets lost
		for( i = 0; i < numPackets; i++ )
		{
			if( rpackets[i].lost ) plost++;
		}
		cout << "number of packets Lost: " << plost << endl() << endl();
		
		// output data from packets
		
		
		
		// close file
		results.close();
	}
	
	return 0;

}
