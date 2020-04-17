// W1C. Single Source Shortest Paths problem
// For weighted, directed graphs with non-negative edge weights
// Dijkstra's algo.
#include <iostream>
#include <stack>
#include <list>
// #include <cstdlib> // rand(), abs()
#include <fstream> // file
//#include <queue>
#include <climits>


using namespace std;

class Graph{
public:
    Graph(int nv, int s);
    void addEdge(int u, int v, int d);
    void printGraph();
    bool isCyclic();
    void Dijkstra(); // return the distance of shortest paths saved in the attribute dis
protected:
private:
    int V; //number of vertexes
    // int E; //number of edges
    int srcVer; // the source vertex
    list<int>* adj; //pointer to save adjacent vertexes of each vertex
    list<int>* wei; // save the weight of each edge
    int* dis; //save the shortest-path estimate from the source vertex to each vertex
    int* pi; // save the predecessor (parent) vertex of each vertex in the shortest paths
};


int main()
{
    // import data from a txt file
    int numVertex = 4;
    //int numEdge = 3;
    int srcVertex = 0;
    Graph myGraph(numVertex, srcVertex);
    ifstream infile("input.txt");
    int a, b, c;
    while (infile >> a >> b >> c){
        myGraph.addEdge(a, b, c);
    }
    infile.close();

    //import data from command line
//    int numVertex = 0;
//    int numEdge = 0;
//    cin >> numVertex >> numEdge;
//    Graph myGraph(numVertex);
//    int a, b;
//    for (int i = 0; i < numEdge; i++) {
//        cin >> a >> b;
//        myGraph.addEdge(a, b);
//    }

    // test : print out the graph
    myGraph.printGraph();

//    // test for cycle detection function
//    if (myGraph.isCyclic()) {cout << "1\n";} else {cout << "0\n";}

//    int* dis2;
//    dis2 = new int[10];
//    cout << dis2[0] << " " << dis2[1] << " " << dis2[2] << endl;
//
//    int myLimit = INT_MAX;
//    cout << myLimit;

    return 0;
}


Graph::Graph(int nv, int s) {
    V = nv; // no. of vertices in the graph
    srcVer = s; // the source vertex
    adj = new list<int>[nv];
    wei = new list<int>[nv];
    dis = new int[nv];
    pi = new int[nv];
    // initialize the graph
    for (int v = 0; v < V; v++) {
        dis[v] = INT_MAX;
        pi[v] = -1; // predecessor vertex = NIL
    }
    dis[srcVer] = 0;
}

void Graph::addEdge(int u, int v, int d) {
    adj[u].push_back(v);
    wei[u].push_back(d);
}

void Graph::printGraph() {
    cout << "adjacent lists:\n";
    for (int i = 0; i < V; i++) {
        cout <<  "adj[" << i << "]: ";
        list<int>::iterator it;
        for(it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << "\n";
    }

    cout << "edge weights:\n";
    for (int i =0; i < V; i++) {
        cout <<  "adj[" << i << "]: ";
        list<int>::iterator it;
        for (it = wei[i].begin(); it != wei[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << "\n";
    }
}

bool Graph::isCyclic() {
    bool isCycleDetected = false;
    //DFS: repeat until a cycle is detected
    stack<int> myStack;
    bool isDiscovered[V];
    for (int i = 0; i < V; i++){isDiscovered[i] = false;}
    for (int iVertex = 0; iVertex < V; iVertex++) {
		myStack.push(iVertex);
		// reset all elements to zero
		for (int i = 0; i < V; i++){isDiscovered[i] = false;}
		int v; //a temporary vertex
		while (!myStack.empty() && !isCycleDetected) {
			v = myStack.top();
			myStack.pop();
			if (!isDiscovered[v]) {
				isDiscovered[v] = true;
				list<int>::iterator it;
				for (it = adj[v].begin(); it != adj[v].end(); ++it) {
					if (*it == iVertex) {
						isCycleDetected = true;
						break;
					} else {
						myStack.push(*it);
					}
				}
			}
		}
		if (isCycleDetected) {break;}
    }

    if (isCycleDetected) {return true;} else {return false;}
}

Graph
