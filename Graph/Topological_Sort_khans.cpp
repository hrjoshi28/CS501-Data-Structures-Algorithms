/*  least lexicographic topological order :: kahn's algorithm using priority_queue (min heap) 
 
 *Problem statement : https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/tutorial/
 */

#include<bits/stdc++.h>   //standard c++
using namespace std;

// Class to represent a graph
class Graph
{
	vector< list<int>  > Alist;
	int size;
public:
	Graph(int );
	void addEdge(int,int);
	void tSort();
			
};
Graph::Graph(int n)
{
	size=n;
	Alist.resize(size+1);
}
void Graph::addEdge(int u,int v)
{
	Alist[u].push_back(v);
}
void Graph::tSort()
{	
	//vector<int> visited(size+1,0); not necessary as given graph is DAG !
	priority_queue< int, vector< int >, greater< int > > pq ;   //MIN HEAP
	vector<int> indegree(size+1,0);
	
	// Traverse adjacency lists to fill indegrees of
  // vertices.  This step takes O(V+E) time
	for(auto &u:Alist)
		for(auto &v:u)
			indegree[v]++;
		
	for(int i=1;i<=size;i++)
		if(indegree[i]==0)pq.push(i);
	
	int vertex;
	while(!pq.empty())
	{
		vertex=pq.top();
		cout<<vertex<<" ";
		pq.pop();
		for(auto &i:Alist[vertex])
		{	
			indegree[i]--;
			if(indegree[i]==0)pq.push(i);
		}	
	}
		
}
int main()
{
	int n,m,u,v;
	cin>>n>>m;
	Graph g(n);
	for(int i=0;i<m;i++)
	{	
		cin>>u>>v;
		g.addEdge(u,v);
	}
	g.tSort();  
	
	return 0;
}
