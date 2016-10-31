// PROBLEM : https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/

//#include<bits/std++11>
#include<iostream>
#include<vector>
#include<list>
#include<stack>

using namespace std;

class Graph
{
	int size;
	vector< list<int> > Alist,AlistT;   //AlistT : Adjacency List Transpose
	stack<int> stk;
	public:		
	Graph(int v)
	{
		size=v+1;
		Alist.resize(size); //indexing from 1
		AlistT.resize(size);
		vector<int> visited(size,0);	
	}
	void addEdge(int u,int v)
	{
		Alist[u].push_back(v);
		AlistT[v].push_back(u); //Transpose matrix
	}
	void pushStk()
	{
		vector<int> visited(size,0);
		for(int i=1;i<size;i++)         //NOTE: size=n+1
			if(visited[i]==0)dfs(i,visited);
		//cout<<"\n";
		//for(int i=1;i<size;i++)
		//	cout<<visited[i]<<" ";
	
	}
	void dfs(int source ,vector<int> & visited)
	{
		visited[source]=1;
		//cout<<source;
		for(auto &v: Alist[source])
			if(visited[v]==0)dfs(v,visited);
		
		stk.push(source);   //push is decreasing order of finished time !
		
	}
	int dfs_count(int source ,vector<int> & visited)   //Traverse Transposed Adjacency List
	{
		
		int count=1;
		visited[source]=1;
		
		for(auto &v: AlistT[source])  
			if(visited[v]==0)
				count+=dfs_count(v,visited);
		
		return count;
					
	}
	
	
	int scc() //return {odd_sum-even_sum}
	{
		int c=0,d=0,n,i;  //c: odd sum , d: even sum
		vector<int> visited(size,0);
		while(!stk.empty())
		{
			i=stk.top();
			//cout<<i;
			stk.pop();
			if(visited[i]==0)
			{	if((n=dfs_count(i,visited))%2==0)d+=n;
					else c+=n;
			//cout<<n<<" ";
			}
		}
		return c-d;
	} 
	void printGraph()
	{
		for(auto &u:Alist)
		{	for(auto &v:u)
				cout<<v<<" ";
			cout<<endl;
		}
	}
	
};
int main()
{
	int n,m;
	cin>>n>>m;
	Graph g(n);
	int u,v;
	for(int i=0;i<m;i++)
	{
		cin>>u>>v;
		g.addEdge(u,v);
	}
	//g.printGraph();
	g.pushStk();
	cout<<"\n\n"<<g.scc();
	
}

