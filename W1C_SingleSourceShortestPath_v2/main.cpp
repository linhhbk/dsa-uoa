// W1C. Single Source Shortest Paths problem
// For weighted, directed graphs with non-negative edge weights (-> Dijkstra's algorithm)
// v2.0: using priority queue, keyed by edge weights
#include <iostream>
#include <stack>
#include <list>
#include <fstream>
#include <climits>
#include <queue>
#include <string>

using namespace std;

struct Edge{
    int des_vertex; // destination vertex
    int weight;
    Edge(int des, int wei) : des_vertex(des), weight(wei) {}
};

struct Node{
    int id; // identity: the index of this node in range [0; (V-1)]
    int sp_est; // estimate of shortest-path distance
    Node(int id_, int sp_est_) : id(id_), sp_est(sp_est_) {}
    void update(int id_, int sp_est_) {this->id = id_; this -> sp_est = sp_est_;}
    bool operator < (const Node &ref_node) const {
        return this-> sp_est > ref_node.sp_est;
    }
};

class Graph{
public:
    int V; //number of vertexes
    int srcVer; // the source vertex
    list<Edge>* adj; //pointer to save adjacent vertexes of each vertex
    Graph(int nv, int s);
    void addEdge(int u, int v, int d);
    void printGraph();
    void dijkstra(); // Single Source Shortest Path
};

/*import data from a txt file*/
Graph in_file (string filename) {
    int numVertex, numEdge, srcVertex;
    ifstream infile(filename);
    infile >> numVertex >> numEdge >> srcVertex;
    Graph myGraph(numVertex, srcVertex);
    int a, b, c;
    while (infile >> a >> b >> c){
        myGraph.addEdge(a, b, c);
    }
    infile.close();
    return myGraph;
}

/*get input from cmd line*/
Graph in_cmd () {
   int numVertex, numEdge, srcVertex;
   cin >> numVertex >> numEdge >> srcVertex;
   Graph myGraph(numVertex, srcVertex);
   int a, b, c;
   for (int i = 0; i < numEdge; i++) {
       cin >> a >> b >> c;
       myGraph.addEdge(a, b, c);
   }
   return myGraph;
}

int main()
{
    //Graph myGraph = in_file("in30.txt");
    Graph myGraph = in_cmd();
    myGraph.dijkstra();
    return 0;
}


Graph::Graph(int nv, int s) {
    V = nv; // number of vertices in the graph
    srcVer = s; // the source vertex
    adj = new list<Edge>[nv];
}

void Graph::addEdge(int u, int v, int d) {
    Edge myEdge(v, d);
    adj[u].push_back(myEdge);
}

void Graph::printGraph() {
    cout << "my graph:\n";
    for (int i = 0; i < V; i++) {
        cout <<  "adj[" << i << "]: ";
        list<Edge>::iterator it;
        for(it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << "(" << it->des_vertex << ", " << it->weight << ") ";
        }
        cout << "\n";
    }
};

 void Graph::dijkstra() { // version 4: using priority_queue in Cpp
     /* initiation */
     int dis[V]; //save the shortest-path estimate from the source vertex to each vertex
     int pi[V]; // save the predecessor (parent) vertex of each vertex in the shortest paths
     bool isDetermined[V]; // whether the shortest path of one node is determined
     for (int i = 0; i < V; i++) {
        dis[i] = INT_MAX; pi[i] = -1; isDetermined[i] = false;
     }
     dis[srcVer] = 0; // for source vertex
     isDetermined[srcVer] = true;

     /*initiate priority_queue, which maintains all nodes whose shortest paths are not yet determined*/
     priority_queue<Node> prique;
     Node node(srcVer, 0);
     prique.push(node);

     while (!prique.empty()) {
         // find the vertex with a minimum of shortest-path estimate
         node = prique.top(); prique.pop();
         int u = node.id; // vertex u has the smallest shortest-path estimate
         isDetermined[u] = true;

         // relax each edge terminating from u
         list<Edge>::iterator it;
         for(it = adj[u].begin(); it != adj[u].end(); ++it) {
             if (!isDetermined[it->des_vertex]) {
                 if (dis[it->des_vertex] > dis[u] + it->weight) {
                     dis[it->des_vertex] = dis[u] + it->weight;
                     pi[it->des_vertex] = u; // for printing the shortest paths later
                     node.update(it -> des_vertex, dis[it->des_vertex]);
                     prique.push(node);
                 }
             }
         }
     }

     // print out the shortest-paths distance
     for (int i = 0; i < V; i++) {
         if (dis[i] < INT_MAX) {cout << dis[i] << endl;} else {cout << "INF\n";}
     }
 }
