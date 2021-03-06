//////////////////////////////////////////////////////////////////////////////////////////////////////
// CPE 400 Project
// dynamic routing mechanism design with focus on throughput
//
// Edited by
// David Neilson: Node class and network
// Nicholas Rini: edited Node class, created Network
// Michael Mills: edited node class, started linkStateAlgorithm aka dijkstra's, added file stream, added packet class
// Nicholas Rini: file input
// Michael Mills: changed file input
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// global constants
const int maxcapacity = 5;
const int updateTime = 10;
const int hopmax = 9;



class Node{

	public:
	
    int ID;
	int queue;
	int capacity;
	int weight;
	// forwarding table
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
	weight = 1;
}

Node::~Node(){

	neighbors.clear();

}

// make forwarding table through link state algorithm, this means the network is centralized ospf
// the algorithm is dijkstra's page 393 in the book.
void linkStateAlgorithm( Node* array, int &arrayNum ) // aka dijkstra's
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
		
		nsize = array[i].neighbors.size();			// the loop
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
	int ID, currentNode, hops;	
	time_t startTime;
	time_t endTime;
	bool lost,done;
	vector<int> nodeStop; // size of nodeStop is # of hops
	vector<int> queueAtNode;
	
	void makePacket( int s, int d, int id, Packet &pack );
	
};
Packet::Packet()
{
	
}
Packet::~Packet()
{
	
}
void makePacket( int s, int d, int id, Packet &pack )
{
	pack.source = s;
	pack.destination = d;
	pack.ID = id;
	pack.currentNode = 99; // 99 means its waiting to enter network
	pack.hops = 0;
	pack.startTime = time(0);
	pack.lost = false;
	pack.done = false;
}
//
// Main /////////////////////////////////////////////////////////////////////////////////////////////////////////
//
int main( int argc, char* argv[] )
{
	int i, j, k = 0, numPackets = 0, list;
	int packetsLeft = 99;
	// read in from file the source destination and # of packets
	ifstream packetFile;
	packetFile.open( argv[1] );
	if( !packetFile.is_open()) {cout << "potential error: input file open";}
	
	packetFile >> list;
	int rsource[list], rdestination[list], rpacketnum[list];	
	
	for( i = 0; i< list; i++ )
	{
		packetFile >> rsource[i];
		packetFile >> rdestination[i];
		packetFile >> rpacketnum[i];
		k++;
	}

	packetFile.close();
	if( k != list ){ cout << "potential error: input file length";}
	// create the network
	Node* array = new Node[9];

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
	cout << "array good" << endl;
	// initialize the forwarding table
	for( i = 0; i < 9; i++ )
	{
		array[0].link[i] = 0;
		array[1].link[i] = 0;
		array[2].link[i] = 0;
		array[3].link[i] = 0;
		array[4].link[i] = 0;
		array[5].link[i] = 0;
		array[6].link[i] = 0;
		array[7].link[i] = 0;
		array[8].link[i] = 0;
	}

	// create packets for the network
	for( i = 0; i < list; i++ )
	{
		numPackets += rpacketnum[i]; // gets total number of packets			
	}

	Packet rpacket[numPackets]; // creates a list of all packets
	cout << numPackets << endl;
	k = 0;
	for( i = 0; i < list; i++ )
	{
		for( j = 0; j < rpacketnum[i]; j++ )
		{
			makePacket( rsource[i], rdestination[i], k, rpacket[k] );
			k++;
		}
	}
	// now to loop all the packets through the nodes
	int count = 0;
	int nextNode;
	int previousNode;
	while( packetsLeft > 0 )
	{
		count++;
		// loop through packets that dont have currentNode as 99 and move them to the next node
		for( i = 0; i < numPackets; i++)
		{
			
			if( (rpacket[i].done == false) && rpacket[i].currentNode != 99 )
			{
				// check if its the destination
				if( rpacket[i].currentNode == rpacket[i].destination )
				{
					rpacket[i].done = true;
					rpacket[i].endTime = time(0);
				}
				// move the currentNode to the next node and decrease queue, update packet with next nodes id and queue, if queue full lost packet, increase next node queue
				 else
				{
					nextNode = array[rpacket[i].currentNode].link[rpacket[i].destination];
					array[rpacket[i].currentNode].queue -= 1;
					if( array[nextNode].queue <= array[nextNode].capacity )
					{
						array[nextNode].queue++;
						rpacket[i].currentNode = nextNode;
						rpacket[i].nodeStop.push_back( nextNode );
						rpacket[i].queueAtNode.push_back( array[nextNode].queue );
						rpacket[i].hops++;
						if( rpacket[i].hops >= hopmax )
						{
							rpacket[i].done = true;
							rpacket[i].lost = true;
							array[nextNode].queue--;
							rpacket[i].endTime = time(0);
						}
					}
					else
					{
						rpacket[i].lost = true;
						rpacket[i].done = true;
					}
				}
				
				
			}
		}
		// load packets into network
		previousNode = 99; // this makes sure they go into it one at a time.
		for( i = 0; i < numPackets; i++ )
		{
			if( (rpacket[i].currentNode == 99) && (rpacket[i].done == false) )
			{
				rpacket[i].currentNode = rpacket[i].source;
				array[rpacket[i].currentNode].queue += 1;
				rpacket[i].nodeStop.push_back(rpacket[i].currentNode);
				rpacket[i].queueAtNode.push_back(array[rpacket[i].currentNode].queue );
				previousNode = rpacket[i].source;
			}
		}
		packetsLeft = 0;
		// determine how many packets left
		for( i = 0; i < numPackets; i++ )
		{
			if( rpacket[i].done == false ) packetsLeft++;
		}
		
		// update count if count = updateTime reset count and update the forwarding table

	}
	
	// file output
	int plost = 0;
	ofstream results ("results.txt");
	if( results.is_open())
	{
		// calculate overall throughput and output to file // average( endTime - startTime ) then ( sum(queueatNode) * nodalDelay ) )
		
		// output #of packets lost
		for( i = 0; i < numPackets; i++ )
		{
			if( rpacket[i].lost ) plost++;
		}
		cout << "number of packets Lost: " << plost << endl << endl;
		
		// output data from packets
		cout << "ID    Time           nodes stopped at      queue at node stopped at" << endl;
		for( i = 0; i < numPackets; i++ )
		{
			cout << rpacket[i].ID << "    " <<  rpacket[i].endTime - rpacket[i].startTime  << "    ";
			for( j = 0; j < rpacket[i].nodeStop.size(); j++ )
			{
				cout << "  " << rpacket[i].nodeStop[j] << "    " << rpacket[i].queueAtNode[j];
			}
			cout << endl;
		}
		
		
		// close file
		results.close();
	}
	
	return 0;

}
