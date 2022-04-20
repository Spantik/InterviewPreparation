#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "sys/types.h"
#include "assert.h"

/*
    207. Course Schedule
    https://leetcode.com/problems/course-schedule/
    There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
    You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must
    take course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
    Return true if you can finish all courses. Otherwise, return false.


    Example 1:
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: true
    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0. So it is possible.

    Example 2:
    Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
    Output: false
    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0, and to take course 0 you
    should also have finished course 1. So it is impossible.


    Constraints:

    1 <= numCourses <= 105
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.


    Hints:

    This problem is equivalent to finding if a cycle exists in a directed graph.
    If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    Topological sort could also be done via BFS.

    Solution: We can consider this problem as a graph (related to topological sorting) problem.
    All tasks are nodes of the graph and if task u is a prerequisite of task v,
    we will add a directed edge from node u to node v.

    Now, this problem is equivalent to detecting a cycle in the graph represented by prerequisites.
    If there is a cycle in the graph, then it is not possible to finish all tasks

    (because in that case there is no any topological order of tasks).
    Both BFS and DFS can be used to solve it.

    Since pair is inconvenient for the implementation of graph algorithms,
    we first transform it to a graph.

    If task u is a prerequisite of task v, we will add a directed edge from node u to node v.

    Prerequisite : Detect Cycle in a Directed Graph
    Using DFS For DFS, it will first visit a node, then one neighbor of it, then one neighbor of this neighbor… and so on.
    If it meets a node which was visited in the current process of DFS visit, a cycle is detected and we will return false.
    Otherwise it will start from another unvisited node and repeat this process till all the nodes have been visited.

    Note that you should make two records: one is to record all the visited nodes and the other is to record the visited nodes in
    the current DFS visit.
*/

// A DFS based function to check if there is a cycle in the directed graph.
int adj[100][100];
#define MAX 1000

typedef struct stack_ {
    int stack[MAX];
    int top;
} STACK;

void initializeStack(STACK *s)
{
	s->top=-1;
}

bool isEmpty(STACK *s)
{
	if(s->top == -1)
		return true;
	else
		return false;
}

bool isFull(STACK *s)
{
	if(s->top == MAX-1)
		return true;
	else
		return false;
}

void push(STACK *s, int x)
{
	if(isFull(s))
	{
		printf("Stack Overflow\n");
		return;
	}
	s->top = s->top+1;
	s->stack[s->top] = x;
}

int pop(STACK *s)
{
	int x;
	if(isEmpty(s))
	{
		printf("Stack Underflow\n");
		return -1;
	}
	x = s->stack[s->top];
	s->top = s->top-1;
	return x;
}

void addUnDirectedEdge(int v,int w)
{
    adj[w][v] = 1;
    adj[v][w] = 1;
}

void addDirectedEdge(int v,int w)
{
    adj[v][w] = 1;
}

void
printAdjMatrix (int n) {

    printf("Adjecency Matrix : \r\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", adj[i][j]);
        }
        printf("\r\n");
    }
    printf("\r\n");
    return;
}

// A BFS based function to check whether d is reachable from s.
bool isCycle(int s, int n, bool tracker[])
{
    memset(tracker, false, sizeof(tracker));
    tracker[s] = true;

    // Mark all the vertices as not visited
    bool visited[n];
    memset(visited, false, sizeof(visited));

    // Create a queue for BFS
    STACK stack;
    initializeStack(&stack);

    push(&stack, s);
    printf("Start : %d \r\n", s);

    while(false == isEmpty(&stack))
    {
        // Pop a vertex from stack and print it
        s = pop(&stack);
        printf("\tProcess : %d \r\n", s);

        // Mark the current node as visited
        visited[s]= true;

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it
        // visited  and enqueue it
        for (int i = 0; i < n; i++)
        {
            if (0 == adj[s][i]) {
                continue;
            }

            printf("\t\tReach : %d \r\n", i);
            if(true == tracker[i]) {
                return true;
            }

            // If this adjacent node is the source node, then return true
            if(false == visited[i]) {
                push(&stack, i);
            }
        }
    }

    return false;
}

bool canFinish (int numCourses) {

    bool tracker[numCourses];
    memset(tracker, false, sizeof(tracker));
    for (int i = 0; i < numCourses; i++) {
        if (true == isCycle(i, numCourses, tracker)) {
            return false;
        }
    }

    return true;
}

void main ()
{
    int numCourses = 5;
    int prerequisites[][2] = {{ 0, 1 },
                              { 0, 2 },
                              { 1, 3 },
                              { 1, 4 },
                              { 3, 4 }};
    int numRows = 5;

    for (int i = 0; i < numRows; i++) {
        addDirectedEdge(prerequisites[i][0], prerequisites[i][1]);
    }

    printAdjMatrix(numCourses);

    if (canFinish(numCourses)){
        printf("Can finish all cources \r\n");
    } else {
        printf("Cannot finish all cources \r\n");
    }
}