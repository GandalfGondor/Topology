#include<iostream>
#include"list.h"
using namespace std;

int TopologicalSort(graphAdjList* GL)
{
	EdgeNode *e;
	int* stack = new int[GL->numVertexes];
	int top=0;
	int gettop;
	int i,k;
	int count = 0;
	for(i=0;i<GL->numVertexes;i++)
	{
		if(GL->adjList[i].in==0)
			stack[++top]=i;
	}
	while(top!=0)
	{
		gettop = stack[top--];	
		cout<<GL->adjList[gettop].data;
		count++;
		for(e=GL->adjList[gettop].firstedge;e;e=e->next)
		{
			k=e->adjvex;
			if(!(--GL->adjList[k].in))
				stack[++top]=k;
		}

	}
	if(count < GL->numEdges)
	{
		cout<<"Error"<<endl;
		return 0;
	}
	else 
		return 1;

}

int main()
{
	graphAdjList* GL=new graphAdjList;
	int i,j,k,w;
	EdgeNode *e;
	cout<<"input numVertexes and numEdges: ";
	cin>>GL->numVertexes>>GL->numEdges;
	cout<<"intput vertexes name: ";
	for(i=0;i<GL->numVertexes;i++)
	{
		cin>>GL->adjList[i].data;
		GL->adjList[i].firstedge = NULL;
	}
	for(k=0;k<GL->numEdges;k++)
	{
		cout<<"input i j w: ";
		cin >>i>>j>>w;
		e = new EdgeNode;
		e->adjvex = j;
		e->weight = w;
		e->next = GL->adjList[i].firstedge;
		GL->adjList[j].in++;
		GL->adjList[i].firstedge = e;
	}
	for(i=0;i<GL->numVertexes;i++)
	{
		cout<<GL->adjList[i].data<<" ";
		e = GL->adjList[i].firstedge;
		while(e!=NULL)
		{
			cout<<e->adjvex<<" ";
			e = e->next;
		}
		cout<<endl;
	}
	delete GL;
}
