#include<bits/stdc++.h>
using namespace std;

#define N 6 //number of nodes in my network
#define INF 100000   //represents a very large value for this program.

// for every node i, graph(vector of pairs) will store the information {neighbor, i->neighbor_linkCost}
vector<pair<int, int> > graph[N];

//for every node i, rTab(vector of pairs) will store the information {i->j_linkCost, through_this_node}
vector<pair<int, int> > rTab[N];

//this function is to build a network randomly, although the number of nodes is taken as 6.
// the number of neighbors and their corresponding costs are set randomly.
void build()
{
    srand(time(NULL));	//set the seed value.
    set<int> s[N];		// neighbor list for every node.
    for(int i=0; i<N; i++)
    {
        int neighCount = 1+rand()%(N/2);  // why N/2 ? eh, just like that :P.
        neighCount -= s[i].size();// say node 2 has neighbor 3, 4. So s[3] and s[4] already has 2. See the 11th line of code starting from now.
        s[i].insert(i);		// just to ensure we don't end up having say node 2 as neighbor to node 2. Well that would be wrong.
        for(int j=0; j<neighCount; j++)
        {
            int neigh = rand()%N;
            if(s[i].find(neigh) == s[i].end())  // if the number neigh is not in set s[i]
            {
                int linkCost = 1+rand()%20;
                graph[i].push_back(make_pair(neigh, linkCost));
                graph[neigh].push_back(make_pair(i, linkCost));
                s[i].insert(neigh);
                s[neigh].insert(i);
            }
            else	// this means we might already have neigh in our set s[i], time to choose once again.
                j--;
        }
    }
}

// this function basically initializes the whole routing tables .
void init()
{
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            rTab[i].push_back(make_pair(INF, INF));  //initially all the neighbors and their linkCosts will be INF.
            
    for(int i=0; i<N; i++)
    {
        rTab[i][i] = make_pair(0, i);	// Cost to reach itself is 0.
        for(int j=0; j<graph[i].size(); j++)
        {
            int neigh = graph[i][j].first;
            rTab[i][neigh].first = graph[i][j].second;
            rTab[i][neigh].second = i;
        }
    } 
}

// this function is to calculate the cost required to reach node-e from node-a 
//   after learning the shortest path and updating the same info in the routing table.
void calcCost(int s, int e)
{
    int curr = s;
    int total = 0;
    cout << curr << " -> ";
    total += rTab[curr][ rTab[curr][e].second ].first;
    while(rTab[curr][e].second != curr)
    {
        curr = rTab[curr][e].second;
        cout << curr << " -> ";
        total += rTab[curr][ rTab[curr][e].second ].first;
    }
    total += rTab[curr][e].first;
    cout << e << endl;
    cout << "The shortest path from " << s << " to " << e << " is " << total << endl;
}

// simple implementaion of bellman Ford algorithm.
void bellmanFord()
{
    bool isUpdating = true;
    int noOfUpdates = 0;
    while(isUpdating)
    {
        noOfUpdates = 0;
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<graph[i].size(); j++)
            {
                int neigh = graph[i][j].first;
                int cost = graph[i][j].second;
                for(int k=0; k<rTab[i].size(); k++)
                {
                    if(cost+rTab[i][k].first < rTab[neigh][k].first)
                    {
                        rTab[neigh][k].first = cost + rTab[i][k].first;
                        rTab[neigh][k].second = i;
                        noOfUpdates++;
                    }
                }
            }
        }
        if(noOfUpdates == 0)
        {
            isUpdating = false;
            cout << endl << endl; 
        }
    } 
    
    // print the routing tables.
    for(int i=0; i<N; i++)
    {
        cout << "RTab for Node " << i << ":\n";
        cout << "\tcost\tpath\n";
        for(int j=0; j<rTab[i].size(); j++)
        {
            cout << j << ":\t" << rTab[i][j].first << "\t" << rTab[i][j].second << endl;
        }
        cout << endl << endl;
    }
}
int main()
{
    build();
    init();
    
    // this distMatrix stores the network topology information in matrix form.
    int distMatrix[N][N];
    memset(distMatrix, 0, sizeof(distMatrix));
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<graph[i].size(); j++)
        {
            int neigh = graph[i][j].first;
            distMatrix[i][neigh] = graph[i][j].second;
        }
    }
    // print the matrix.
    cout << "\nDistance Matrix: \n";
    for(int i=0; i<N; i++)
    {
        cout << "\t";
        for(int j=0; j<N; j++)
        {
            cout << distMatrix[i][j] << " ";
        }
        cout << endl;
    }
    
    bellmanFord();
    
    int testCases, source, dest;
    cout << "Numbr of test cases: \n";
    cin >> testCases;
    while(testCases--)
    {
        cout << "Source: " << endl;
        cin >> source;
        
        cout << "Destination: " << endl;
        cin >> dest;
        
        calcCost(source, dest);
        cout << endl;
    }
    return 0;
}
