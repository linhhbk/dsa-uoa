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

struct weightedEdge{
    int src_vertex; // source vertex
    int des_vertex; // destination vertex
    int weight;
};

class Graph{
public:
    Graph(int nv, int s);
    void addEdge(int u, int v, int d);
    void printGraph();
    bool isCyclic();
    void SSSP_Dijkstra(); // return the distance of shortest paths saved in the attribute "dis"
protected:
private:
    int V; //number of vertexes
    // int E; //number of edges
    int srcVer; // the source vertex
    list<weightedEdge>* adj; //pointer to save adjacent vertexes of each vertex
    list<int>* wei; // save the weight of each edge
    weightedEdge myEdge;  // a temporary edge
    list<weightedEdge>::iterator it; // the iterator used to access each element of the "adj" list
};


int main()
{
//    // import data from a txt file
//    int numVertex = 4;
//    //int numEdge = 3;
//    int srcVertex = 0;
//    Graph myGraph(numVertex, srcVertex);
//    ifstream infile("input.txt");
//    int a, b, c;
//    while (infile >> a >> b >> c){
//        myGraph.addEdge(a, b, c);
//    }
//    infile.close();

    //import data from command line
    int numVertex = 0;
    int numEdge = 0;
    int srcVertex = 0;
    cin >> numVertex >> numEdge >> srcVertex;
    Graph myGraph(numVertex, srcVertex);
    int a, b, c;
    for (int i = 0; i < numEdge; i++) {
        cin >> a >> b >> c;
        myGraph.addEdge(a, b, c);
    }

    // test : print out the graph
    // myGraph.printGraph();

//    // test for cycle detection function
//    if (myGraph.isCyclic()) {cout << "1\n";} else {cout << "0\n";}

    // test on single source shortest-path algo.
    myGraph.SSSP_Dijkstra();

    return 0;
}


Graph::Graph(int nv, int s) {
    V = nv; // number of vertices in the graph
    srcVer = s; // the source vertex
    adj = new list<weightedEdge>[nv];
}

void Graph::addEdge(int u, int v, int d) {
    myEdge.src_vertex = u;
    myEdge.des_vertex = v;
    myEdge.weight = d;
    adj[u].push_back(myEdge);
    //wei[u].push_back(d);
}

void Graph::printGraph() {
    cout << "my graph:\n";
    for (int i = 0; i < V; i++) {
        cout <<  "adj[" << i << "]: ";
        //list<weightedEdge>::iterator it;
        for(it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << "(" << it->des_vertex << ", " << it->weight << ") ";
        }
        cout << "\n";
    }
};

//bool Graph::isCyclic() {
//    bool isCycleDetected = false;
//    //DFS: repeat until a cycle is detected
//    stack<int> myStack;
//    bool isDiscovered[V];
//    for (int i = 0; i < V; i++){isDiscovered[i] = false;}
//    for (int iVertex = 0; iVertex < V; iVertex++) {
//		myStack.push(iVertex);
//		// reset all elements to zero
//		for (int i = 0; i < V; i++){isDiscovered[i] = false;}
//		int v; //a temporary vertex
//		while (!myStack.empty() && !isCycleDetected) {
//			v = myStack.top();
//			myStack.pop();
//			if (!isDiscovered[v]) {
//				isDiscovered[v] = true;
//				list<int>::iterator it;
//				for (it = adj[v].begin(); it != adj[v].end(); ++it) {
//					if (*it == iVertex) {
//						isCycleDetected = true;
//						break;
//					} else {
//						myStack.push(*it);
//					}
//				}
//			}
//		}
//		if (isCycleDetected) {break;}
//    }
//
//    if (isCycleDetected) {return true;} else {return false;}
//}

void Graph::SSSP_Dijkstra() {
    int *dis; //save the shortest-path estimate from the source vertex to each vertex
    int *pi; // save the predecessor (parent) vertex of each vertex in the shortest paths
    dis = new int[V];
    pi = new int[V];

    // initialize the graph
    for (int v = 0; v < V; v++) {
        dis[v] = INT_MAX;
        pi[v] = -1; // predecessor vertex = NIL
    }
    dis[srcVer] = 0;

    bool isDetermined[V];
    for (int i = 0; i < V; i++){isDetermined[i] = false;}
    int v_ref, d_ref;
    for (int i = 0; i < V; i++) {
        // find the vertex with a minimum of shortest-path estimate
        v_ref = 0; d_ref = INT_MAX;
        for (int vid = 0; vid < V; vid++) {
            if ((isDetermined[vid]==false) && (dis[vid])<d_ref) {
                d_ref = dis[vid];
                v_ref = vid;
            }
        }
        isDetermined[v_ref] = true; // mark the vertex "v_ref" as determined with a shortest-path distance

        // relax each edge terminating from v_ref
        //list<weightedEdge>::iterator it;
        for (it = adj[v_ref].begin(); it != adj[v_ref].end(); ++it) {
            if (dis[it->src_vertex] != INT_MAX) {
                if (dis[it->des_vertex] > dis[it->src_vertex] + it->weight) {
                    dis[it->des_vertex] = dis[it->src_vertex] + it->weight;
                    pi[it->des_vertex] = it->src_vertex; // note: it->src_vertex = v_ref
                }
            }
        }
    }

    // print out the shortest-paths distance
    for (int i = 0; i < V; i++) {
        if (dis[i] < INT_MAX) {cout << dis[i] << endl;} else {cout << "INF\n";}
    }
}
