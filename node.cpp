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

class Node{

	public:
	
    int ID;
	int queue;
	int capacity;
	int pSpeed;
	int weight;
	// forwarding table
	vector<int> destination;
	vector<int> link;
	// links from node
    vector<Node> neighbors;

	Node();
	~Node();

};

Node::Node(){

    ID = 0;
	queue = 0;
	capacity = 5;
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
	int cost[arrayNum-1];
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

	// data in packet, not creating separate data structure
	int ID;	
	time_t startTime;
	time_t endTime;
	int hops;
	vector<int> nodeStop;
	vector<int> queueAtNode;
	
	makePacket( int s, int d, int id );
	
}
Packet::makePacket( int s, int d, int id);
{
	source = s;
	destination = d;
	ID = id;
	startTime = time(0);
	hops = 0;
	nodeStop.push_back( s );
	queueAtNode.push_back( id );
}

int main( int argc, char* argv[] )
{
	int i, j, k = 0, numPackets = 0;
	int rsource[argc/3], rdestination[argc/3], rpacketnum[argc/3];
	// read in from command line the source destinatin and # of packets
	for( i = 0; i < argc/3; i++ )
	{
		rsource[i] = atoi( argv[k] );
		k++;
		rdestination[i] = atoi( argv[k] );
		k++;
		rpacketnum[i] = atoi( argv[k] );
		k++;
	}
	
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
	for( i = 0; i < argc/3; i++ )
	{
		numPackets += rpacketnum[i];
	}
	Packet rpacket[numPackets]
	k = 0;
	for( i = 0; i < argc/3; i++ )
	{
		for( j = 0; j < rpacketnum[i]; j++ )
		{
			rpackets[k] = makePacket( rsource[i], rdestination[i], k )
		}
	}
	
	// loop through packets and nodes
	
	// move packets through network one node at a time


	// file output
	ofstream results ("results.txt");
	if( results.is_open())
	{
		// calculate overall throughput and output to file // average( endTime - startTime + ( hops * nodalDelay ) )
		
		// output #of packets lost
		
		// output data from packets
		
		
		
		// close file
		results.close();
	}
	
	return 0;

}
