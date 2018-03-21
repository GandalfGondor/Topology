#define MAXVEX 100

class EdgeNode
{
public:
	int adjvex;
	int weight;
	EdgeNode *next;
};

class VertexNode
{
public:
	int in;
	int data;
	EdgeNode *firstedge;
};
typedef VertexNode AdjList[MAXVEX];
class graphAdjList
{
public:
	AdjList adjList;
	int numVertexes,numEdges;
};
