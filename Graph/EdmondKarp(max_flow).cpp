/*
*Max_flow (Adjacency Matrix)
*Input Graph : mit lecture example..
*Output : max_flow=4
*Complexity : BFS takes O(V^2) time, 
*             Therefore above implementation has O(E(V^3)) complexity  ==>> VE*(V^2)  //(VE) TIMES BFS 
*/

#include<iostream>
#include<queue>
#include<limits.h>
#include<vector>
using namespace std;

#define V 6

bool breadth_first_search(int mat[V][V], int source, int destination, int* path)  //check if dest is reachable from source
{
    queue <int> q;
    vector<bool> visited(V,false);
    

    q.push(source);
    visited[source] = true;
    path[source]=-1;

    while(!q.empty())
    {
        int curr_node = q.front();
        q.pop();
        for(int next_node = 0; next_node < V; next_node++)
        {
            if(visited[next_node] == false && mat[curr_node][next_node] > 0)
            {
                q.push(next_node);
                path[next_node] = curr_node;
                visited[next_node] = true;
            }
        }
    }
    return (visited[destination]==true);
}

int ford_fulkerson_compute(int mat[V][V],int source,int sink)
{
    int curr_node, parent_node;
    int max_flow = 0;
    int path[V];
    while(breadth_first_search(mat, source, sink, path)) //there exist augmenting path ...
    {
        int path_flow=INT_MAX; //residual capacity of aug_path
        for(curr_node=sink; curr_node != source; curr_node = path[curr_node]) //backtrack the aug-path...
        {
            parent_node=path[curr_node];
            path_flow=min(path_flow, mat[parent_node][curr_node]);
        }
        for(curr_node=sink; curr_node != source; curr_node = path[curr_node])
        {
            parent_node = path[curr_node];
            mat[parent_node][curr_node] -= path_flow;
            mat[curr_node][parent_node] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main()
{
    int mat[V][V]={//0  1  2  3  4  5
                    {0, 3, 2, 0, 0, 0},
                    {0, 0, 0, 2, 0, 0},
                    {0, 3, 0, 0, 3, 0},
                    {0, 0, 1, 0, 0, 3},
                    {0, 0, 0, 3, 0, 4},
                    {0, 0, 0, 0, 0, 0}
                };
    cout<<"Max flow= "<<ford_fulkerson_compute(mat, 0, 5)<<endl;
    return 0;
}
