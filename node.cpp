#include <vector>
using namespace std;

class Node{

public:
    int ID;
	int queue;
	int capacity;
	int pSpeed;
	int weight = 1;
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
}

Node::~Node(){

	neighbors.clear();

}

// make forwarding table through link state algorithm, this means the network is centralized ospf
// the algorithm is dijkstra's page 393 in the book.
void linkStateAlgorithm( Node* array, int arrayNum )
{
	// initialize
	arrayNum;
	int cost[arrayNum-1];
	int nsize,i,j;
	for( i = 0; i < arrayNum; i++)
	{
		for( j = 0; j < arrayNum-1; j++ )
		{
			cost[i] = 0; // 0 will represent infinity
		}
		
		nsize = array[i].neighbors.size()
		for( int j = 0; j < nsize; j++)
		{
			cost[array[i].neighbors[nsize].ID] = array[i].neighbors[nsize].weight;
		}
		for( int j = 0; j < arrayNum; j++ )
		{
			
		}
	}		
}

int main(){

	Node* array = new Node[8];

	for( int i = 0; i < 8; i++)
	{
		array[i].ID = i;

	}

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


	return 0;

}
