/* 
 * File:   butter.cpp
 * Author: ant
 *
 * Created on November 2, 2012, 11:00 AM
 */

#include <cstdlib>
#include <map>
#include <utility>
#include <fstream>
#include <limits.h>
#include <queue>
#include <list>
#include <iostream>

using namespace std;

struct node
{
    int cost;
    int at;
    
    node(int cost, int at)
    {
        this->cost = cost;
        this->at   = at;
    }
    
};

class graphAdjMap
{
public:
    //adjacency map. given an edge connection, find the cost associated with it.
    //-1 means no connection yet exists.
    //the graph is undirected, so only store and lookup connections where a < b
    map<pair<short, short>, int> adj;
    
    void addEdge(short a, short b, int cost)
    {
        adj[pair<short,short>(a,b)] = cost;
    }
    int getEdgeCost(short a, short b)
    {
        if(b > a)
        {
            short temp = a;
            a = b;
            b = temp;
        }
        pair<short,short> edge(a,b);
        map<pair<short, short>, int>::iterator result = adj.find(edge);
        if(result == adj.end())
        {
            return -1;
        }
        else
        {
            return result->second;
        }
    }
};

class graphAdjList
{
public:
    //adjacency map. given an edge connection, find the cost associated with it.
    //-1 means no connection yet exists.
    //the graph is undirected, so only store and lookup connections where a < b
    list<node> * adj;
    int numVertices;
    
    graphAdjList(int v)
    {
        numVertices = v;
        adj = new list<node>[v];
    }
    ~graphAdjList()
    {
        delete [] adj;
    }
    
    void addEdge(short a, short b, int cost)
    {
        if(b > a)
        {
            short temp = a;
            a = b;
            b = temp;
        }
        adj[a].push_front(node(cost, b));
    }
    int getEdgeCost(short a, short b)
    {
        if(b > a)
        {
            short temp = a;
            a = b;
            b = temp;
        }

        for(list<node>::iterator it = adj[a].begin(); it != adj[a].end(); ++it)
        {
            if(it->at == b)
                return it->cost;
        }
        return -1;        
    }
};


//the number of cows at each node. will be needed
//to find the total cost of having cows move
short nodeWeight[501];



bool operator<(const node &leftNode, const node &rightNode) {
 if (leftNode.cost != rightNode.cost) return leftNode.cost < rightNode.cost;
 if (leftNode.at != rightNode.at) return leftNode.at < rightNode.at;
 return false;
}

int* dijkstra(int numVerticies, short start, graphAdjList g)
{
    int dist[numVerticies+1];
    bool visited[numVerticies+1];
    priority_queue<node> q;
    
    for(int i=0;i<numVerticies+1; ++i)
        dist[i] = INT_MAX;
    
    node startNode(0, start);
    
    q.push(startNode);
    
    while(!q.empty())
    {

        node crnt = q.top();
        q.pop();

        if(visited[crnt.at]) continue;
        
        dist[crnt.at]    = crnt.cost;
        visited[crnt.at] = true;
        
        list<node>& adj = g.adj[crnt.at];
        
        for(list<node>::iterator it = adj.begin(); it != adj.end(); ++it)
        {
            node &adjNode = *it;
            if(!visited[it->at])
            {
                node entry(crnt.cost + adjNode.cost, adjNode.at);
                q.push(entry);
            }
        }
        
    }
    
}

int main(int argc, char** argv)
{
    int n,p,c;
    ifstream fin("butter.in");
    ofstream fout("butter.out");
    
    fin >> n >> p >> c;
    
    graphAdjList g(p);

    
    for(int i=0;i<n; ++i)
    {
        int location;
        fin >> location;
        ++nodeWeight[location-1];
    }
    for(int i=0; i < c; ++i)
    {
        short a, b, cost;
        fin >> a >> b >> cost;
        g.addEdge(a-1,b-1,cost);
    }
    
    //find the total cost that would be associated with each possible vertex
    //as the destination node
    
    for(int i=1; i <= p; ++i)
    {
        int * costs = dijkstra(p, i, g);
        for(int j=0; j < p; ++j)
        {
            fout << costs[j] << endl;
        }
        fout << endl;
    }
    
    return 0;
}

