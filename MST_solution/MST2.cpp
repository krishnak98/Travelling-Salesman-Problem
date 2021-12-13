
#include <iostream>
#include<vector>
using namespace std;
 
// Number of vertices in the graph 
#define V 5 

// Dynamic array to store the final answer
vector<int> final_ans;

int minimum_key(int key[], bool mstSet[]) 
{ 
    int min = INT_MAX, min_index; 
 
    for (int v = 0; v < V; v++) 
        if (mstSet[v] == false && key[v] < min) 
            min = key[v], min_index = v; 
 
    return min_index; 
} 
 
vector<vector<int> > MST(int parent[], int graph[V][V]) 
{ 
    vector<vector<int> > v;
    for (int i = 1; i < V; i++) 
    {
        vector<int> p;
        p.push_back(parent[i]);
        p.push_back(i);
        v.push_back(p);
        p.clear();
    }
    return v;  
} 
 
// getting the Minimum Spanning Tree from the given graph
// using Prim's Algorithm
vector<vector<int> > primMST(int graph[V][V]) 
{ 
    int parent[V]; 
    int key[V];

    // to keep track of vertices already in MST 
    bool mstSet[V]; 

    // initializing key value to INFINITE & false for all mstSet
    for (int i = 0; i < V; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 

    // picking up the first vertex and assigning it to 0
    key[0] = 0; 
    parent[0] = -1; 

    // The Loop
    for (int count = 0; count < V - 1; count++)
    { 
        // checking and updating values wrt minimum key
        int u = minimum_key(key, mstSet); 
        mstSet[u] = true; 
        for (int v = 0; v < V; v++) 
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
                parent[v] = u, key[v] = graph[u][v]; 
    } 
    vector<vector<int> > v;
    v = MST(parent, graph);
    return v; 
} 

// getting the preorder walk of the MST using DFS
void DFS(int** edges_list,int num_nodes,int starting_vertex,bool* visited_nodes)
{
    // adding the node to final answer
    final_ans.push_back(starting_vertex);

    // checking the visited status 
    visited_nodes[starting_vertex] = true;

    // using a recursive call
    for(int i=0;i<num_nodes;i++)
    {
        if(i==starting_vertex)
        {
            continue;
        }
        if(edges_list[starting_vertex][i]==1)
        {
            if(visited_nodes[i])
            {
                continue;
            }
            DFS(edges_list,num_nodes,i,visited_nodes);
        }
    }
}
int main() 
{ 
    // initial graph
    int graph[V][V] = { { 0, 3, 4, 2, 7 }, 
                        { 3, 0, 4, 6, 3 }, 
                        { 4, 4, 0, 5, 8 }, 
                        { 2, 6, 5, 0, 6 },
                        { 7, 3, 8, 6, 0 } }; 
 
    vector<vector<int> > v;

    // getting the output as MST 
    v = primMST(graph);

    // creating a dynamic matrix
    int** edges_list = new int*[V];
    for(int i=0;i<V;i++)
    {
        edges_list[i] = new int[V];
        for(int j=0;j<V;j++)
        {
            edges_list[i][j] = 0;
        }
    }

    // setting up MST as adjacency matrix
    for(int i=0;i<v.size();i++)
    {
        int first_node = v[i][0];
        int second_node = v[i][1];
        edges_list[first_node][second_node] = 1;
        edges_list[second_node][first_node] = 1;
    }

    // a checker function for the DFS
    bool* visited_nodes = new bool[V];
    for(int i=0;i<V;i++)
    {
        bool visited_node;
        visited_nodes[i] = false;
    }

    //performing DFS
    DFS(edges_list,V,0,visited_nodes);

    // adding the source node to the path
    final_ans.push_back(final_ans[0]);

    // printing the path
    int cost = 0;
    for(int i=0;i<final_ans.size();i++)
    {
        cout << final_ans[i] + 1 << "-";
        if( i != 0) cost += graph[final_ans[i-1]][final_ans[i]];
    }
    cout << "\n";
    cout << cost << endl;
    return 0; 
} 