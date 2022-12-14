#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL 0
#define VISITED 1
#define FINISHED 2

#define MAX 30

struct Vertex
{
	char name[50];
	int state;
	int discoveryTime;
    int finishingTime;
};

int time;

struct Vertex vertexList[MAX];

int adj[MAX][MAX]; /* Adjacency Matrix */
int n=0;	/* Number of vertices in the graph */
int e=0; /* Number of edges in the graph */

void display();
int getIndex(char s[]);
int isAdjacent(char s1[], char s2[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[]);
void deleteEdge(char s1[], char s2[] );

void dfsTraversalAll();
void dfs(int v);

main()
{
	insertVertex("Zero");
	insertVertex("One");
	insertVertex("Two");
	insertVertex("Three");
	insertVertex("Four");
	insertVertex("Five");
	insertVertex("Six");
	insertVertex("Seven");
	insertVertex("Eight");
	insertVertex("Nine");
	insertVertex("Ten");
	insertVertex("Eleven");
	insertVertex("Twelve");
	insertVertex("Thirteen");
	insertVertex("Fourteen");
	insertVertex("Fifteen");
	insertVertex("Sixteen");

	insertEdge("Zero","One");
	insertEdge("Zero","Two");
	insertEdge("Zero","Four");
	insertEdge("One","Three");
	insertEdge("Two","Three");
	insertEdge("Two","Four");
	insertEdge("Two","Five");
	insertEdge("Three","Zero");
	insertEdge("Four","Five");
	insertEdge("Five","Three");
	insertEdge("Six","One");
	insertEdge("Six","Seven");
	insertEdge("Six","Eight");
	insertEdge("Six","Nine");
	insertEdge("Seven","Nine");
	insertEdge("Eight","Ten");
	insertEdge("Nine","Five");
	insertEdge("Ten","Six");
	insertEdge("Ten","Nine");
	insertEdge("Eleven","Eight");
	insertEdge("Eleven","Thirteen");
	insertEdge("Eleven","Fifteen");
	insertEdge("Twelve","Eleven");
	insertEdge("Thirteen","Eight");
	insertEdge("Thirteen","Fourteen");
	insertEdge("Thirteen","Fifteen");
	insertEdge("Thirteen","Sixteen");
	insertEdge("Fourteen","Sixteen");
	insertEdge("Fifteen","Twelve");
	insertEdge("Fifteen","Sixteen");

	dfsTraversalAll();
}

void dfs(int v)
{
    int i;
	vertexList[v].state = VISITED;
	vertexList[v].discoveryTime = ++time;

    for(i=0; i<n; i++)
   	{
   	    if( adj[v][i] !=0 )
   		{
   		    if(vertexList[i].state == INITIAL)
   		    {
   		       printf("Tree Edge - (%s, %s)\n", vertexList[v].name, vertexList[i].name);
   			   dfs(i);
   			}
   			else if(vertexList[i].state == VISITED)
   			   printf("Back Edge - (%s, %s)\n", vertexList[v].name, vertexList[i].name);
   			else if(vertexList[v].discoveryTime < vertexList[i].discoveryTime)
			   printf("Forward Edge - (%s, %s)\n", vertexList[v].name, vertexList[i].name );
			else
			   printf("Cross Edge - (%s, %s)\n", vertexList[v].name, vertexList[i].name);
		  }
   	 }
   	 vertexList[v].state = FINISHED;
   	 vertexList[v].finishingTime = ++time;
}

void dfsTraversalAll()
{
	int u,v;
	char s[50];

   	printf("Enter starting vertex for Depth First Search : ");
   	scanf("%s", &s);
  	u = getIndex(s);
	if(u == -1)
		return;

	for (v = 0; v < n; v++)
   		vertexList[v].state = INITIAL;

	dfs(u);

	for(v=0; v<n; v++)
	    if( vertexList[v].state == INITIAL )
		     dfs(v);
}
void display()
{
	int i,j;

	printf("Adjacency Matrix - \n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			printf("%4d",adj[i][j]);
		printf("\n");
	}

	printf("\nVertices - ");
	for(i=0; i<n; i++)
		printf("%s  ", vertexList[i].name);

	printf("\nEdges - ");
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		   if( adj[i][j] != 0 )
				printf("(%s, %s)  ", vertexList[i].name,vertexList[j].name);
	printf("\n\n");
}

int getIndex(char s[])
{
	int i;
    for (i = 0; i<n; i++)
       if ( strcmp(s,vertexList[i].name) == 0 )
 	       return i;
    printf("Invalid Vertex - %s \n\n", s);
	return -1;
}

void insertVertex(char s[])
{
	int i;

    for(i = 0; i<n; i++ )
		if( strcmp(vertexList[i].name, s) == 0)
		{
			printf("Vertex already present\n\n");
			return;
		}

	strcpy(vertexList[n].name, s);
	n++;
}

void deleteVertex(char s[])
{
	int i, x = getIndex(s), u;

	if(x == -1)
		return;

	u = x;
	while (u < n-1)
	{
        for (i = 0; i < n; i++) /* shift rows to the left */
		    adj[i][u] = adj[i][u+1];

		for (i = 0; i < n; i++)  /* shift columns up */
			adj[u][i] = adj[u+1][i];
	    u++;
	}

	for(i = x; i < n-1; i++)
		vertexList[i] = vertexList[i+1];
	n--;
}

int isAdjacent(char s1[], char s2[])
{
	int u,v;
	u = getIndex(s1);
	v = getIndex(s2);

	if (u == -1 || v == -1)
		return -1;

	return adj[u][v];
}

/* Insert an edge (s1,s2) */
void insertEdge(char s1[], char s2[])
{
	  int u = getIndex(s1);
	  int v = getIndex(s2);

	  if (u == v)
	  {
		 printf("Not a valid edge\n\n");
		 return;
	  }

      if (adj[u][v] != 0 )
        printf("Edge already present\n\n");
      else
      {
         adj[u][v] = 1;
         e++;
      }
}

/* Delete the edge (s1,s2) */
void deleteEdge(char s1[], char s2[])
{
    int u = getIndex(s1);
    int v = getIndex(s2);

	if(u==-1 || v ==-1)
		return;

    if( adj[u][v] == 0 )
        printf("Edge not present\n\n");
    else
    {
         adj[u][v] = 0;
         e--;
    }
}








