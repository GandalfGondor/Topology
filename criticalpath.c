#include<iostream>
#include"list.h"

using namespace std;

int *etv,*ltv;
int *stack2;
int top2;

int TopologicalSort(graphAdjList *GL)
{
	EdgeNode *e;
	int i,k,gettop;
	int top = 0;
	int count = 0;
	int *stack = new int[GL->numVertexes];
	for(i=0;i<GL->numVertexes;i++)
		if(GL->adjList[i].in==0)
			stack[++top]=GL->adjList[i].data;
	top2 = 0;
	etv = new int[GL->numVertexes];
	for(i=0;i<GL->numVertexes;i++)
		etv[i]=0;
	stack2 = new int[GL->numVertexes];
	while(top!=0)
	{
		gettop = stack[top--];
		count++;
		stack2[top2++]=gettop;
		for(e=GL->adjList[gettop].firstedge;e;e=e->next)
		{
			k=e->adjvex;
			if(!(--GL->adjList[k].in))
				stack[++top]=k;
			if((etv[gettop]+e->weight>etv[k]))
				etv[k] = etv[gettop] + e->weight;
		}
	}
	if(count<GL->numVertexes)
		return 0;
	else 
		return 1;

}

void CriticalPath(graphAdjList *GL)
{
	EdgeNode *e;
	int i,gettop,k,j;
	int ete,lte;
	TopologicalSort(GL);
	ltv = new int[GL->numVertexes];
	for(i=0;i<GL->numVertexes;i++)
		ltv[i]=etv[GL->numVertexes -1];

	while(top2!=0)
	{
		gettop = stack2[top2--];
		for(e = GL->adjList[gettop].firstedge;e;e=e->next)
		{
			k=e->adjvex;
			if(ltv[k]-e->weight<ltv[gettop])
				ltv[gettop]=ltv[k]-e->weight;
		}
	}
	cout<<"The critical path is :"<<endl;
	for(j=0;j<GL->numVertexes;j++)
		for(e=GL->adjList[j].firstedge;e;e=e->next)
		{
			k=e->adjvex;
			ete = etv[j];
			lte = ltv[k] - e->weight;
			if(ete == lte)
				cout<<j<<" "<<k<<" "<<e->weight<<endl;
		}
}

int main()
{
	graphAdjList *GL = new graphAdjList;
	int i,j,k,w;
	EdgeNode *e;
	cout<<"Input numVertexes and numEdges: ";
	cin>>GL->numVertexes>>GL->numEdges;
	
	for(i=0;i<GL->numVertexes;i++)
	{
		GL->adjList[i].data = i;
		GL->adjList[i].in = 0;
	}
	cout<<"intput i j w :";
	for(k=0;k<GL->numEdges;k++)
	{
		cin>>i>>j>>w;
		GL->adjList[j].in++;
		e = new EdgeNode;
		e->weight = w;
		e->adjvex = j;
		e->next = GL->adjList[i].firstedge;
		GL->adjList[i].firstedge = e;
	}
	
	CriticalPath(GL);

	delete GL;
	delete e;
}
