// W1C. Single Source Shortest Paths problem
// For weighted, directed graphs with non-negative edge weights
// Dijkstra's algo.
// v2.0: using priority queue, keyed by edge weights
#include <iostream>
#include <stack>
#include <list>
// #include <cstdlib> // rand(), abs()
#include <fstream> // file
//#include <queue>
#include <climits>
#include <queue>

using namespace std;

struct weightedEdge{
    int src_vertex; // source vertex
    int des_vertex; // destination vertex
    int weight;
    bool operator < (weightedEdge &e1, weightedEdge &e2) const {
        return e1.weight < e2.weight;
    }
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
    // import data from a txt file
    int numVertex, numEdge, srcVertex;
    ifstream infile("in30.txt");
    infile >> numVertex >> numEdge >> srcVertex;
    Graph myGraph(numVertex, srcVertex);
    int a, b, c;
    while (infile >> a >> b >> c){
        myGraph.addEdge(a, b, c);
    }
    infile.close();

//    //import data from command line
//    int numVertex, numEdge, srcVertex;
//    cin >> numVertex >> numEdge >> srcVertex;
//    Graph myGraph(numVertex, srcVertex);
//    int a, b, c;
//    for (int i = 0; i < numEdge; i++) {
//        cin >> a >> b >> c;
//        myGraph.addEdge(a, b, c);
//    }

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

//void Graph::SSSP_Dijkstra() { // version 1
//   int *dis; //save the shortest-path estimate from the source vertex to each vertex
//   int *pi; // save the predecessor (parent) vertex of each vertex in the shortest paths
//   dis = new int[V];
//   pi = new int[V];
//
//   // initialize the graph
//   for (int v = 0; v < V; v++) {
//       dis[v] = INT_MAX;
//       pi[v] = -1; // predecessor vertex = NIL
//   }
//   dis[srcVer] = 0;
//
//   bool isDetermined[V];
//   for (int i = 0; i < V; i++){isDetermined[i] = false;}
//   int v_ref, d_ref;
//   for (int i = 0; i < V; i++) {
//       // find the vertex with a minimum of shortest-path estimate
//       v_ref = 0; d_ref = INT_MAX;
//       for (int vid = 0; vid < V; vid++) {
//           if ((isDetermined[vid]==false) && (dis[vid]) < d_ref) {
//               d_ref = dis[vid];
//               v_ref = vid;
//           }
//       }
//       isDetermined[v_ref] = true; // mark the vertex "v_ref" as determined with a shortest-path distance
//
//       // relax each edge terminating from v_ref
//       //list<weightedEdge>::iterator it;
//       for (it = adj[v_ref].begin(); it != adj[v_ref].end(); ++it) {
//           if (dis[it->src_vertex] != INT_MAX) {
//               if (dis[it->des_vertex] > dis[it->src_vertex] + it->weight) {
//                   dis[it->des_vertex] = dis[it->src_vertex] + it->weight;
//                   pi[it->des_vertex] = it->src_vertex; // note: it->src_vertex = v_ref
//               }
//           }
//       }
//   }
//
//   // print out the shortest-paths distance
//   for (int i = 0; i < V; i++) {
//       if (dis[i] < INT_MAX) {cout << dis[i] << endl;} else {cout << "INF\n";}
//   }
//}

// void Graph::SSSP_Dijkstra() { // version 2
//     int *dis; //save the shortest-path estimate from the source vertex to each vertex
//     int *pi; // save the predecessor (parent) vertex of each vertex in the shortest paths
//     dis = new int[V];
//     pi = new int[V];
//
//     // initialize the graph
//     for (int v = 0; v < V; v++) {
//         dis[v] = INT_MAX;
//         pi[v] = -1; // predecessor vertex = NIL
//     }
//     dis[srcVer] = 0;
//
//     list<int> listOfNotYetDeterimined;
//     int v_ref, d_ref;
//     for (int i = 0; i < V; i++) {listOfNotYetDeterimined.push_back(i);}
//     list<int>::iterator it1, it2;
//     while (!listOfNotYetDeterimined.empty()) {
//         // find the vertex with a minimum of shortest-path estimate
//         v_ref = listOfNotYetDeterimined.front(); d_ref = INT_MAX;
//         for (int i = 0; i < listOfNotYetDeterimined.size(); i++){
//             it1 = it2 = listOfNotYetDeterimined.begin();
//             advance(it2,i);
//             if ((dis[*it2]) < d_ref) {
//                 d_ref = dis[*it2];
//                 v_ref = *it2;
//                 advance(it1, i);
//             }
//         }
//
//         //listOfNotYetDeterimined.erase(it1);
//         listOfNotYetDeterimined.remove(v_ref);
//
//         // relax each edge terminating from v_ref
//         //list<weightedEdge>::iterator it;
//         for (it = adj[v_ref].begin(); it != adj[v_ref].end(); ++it) {
//             if (dis[it->src_vertex] != INT_MAX) {
//                 if (dis[it->des_vertex] > dis[it->src_vertex] + it->weight) {
//                     dis[it->des_vertex] = dis[it->src_vertex] + it->weight;
//                     pi[it->des_vertex] = it->src_vertex; // note: it->src_vertex = v_ref
//                 }
//             }
//         }
//     }
//
//     // print out the shortest-paths distance
//     for (int i = 0; i < V; i++) {
//         if (dis[i] < INT_MAX) {cout << dis[i] << endl;} else {cout << "INF\n";}
//     }
// }


void Graph::SSSP_Dijkstra() { // version 3
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

     list<int> listOfNotYetDeterimined;
     list<int>::iterator it2;
     int v_ref, d_ref;
     for (int i = 0; i < V; i++) {listOfNotYetDeterimined.push_back(i);}
     while (!listOfNotYetDeterimined.empty()) {
         // find the vertex with a minimum of shortest-path estimate
         v_ref = listOfNotYetDeterimined.front(); d_ref = INT_MAX;
         for (it2 = listOfNotYetDeterimined.begin(); it2 != listOfNotYetDeterimined.end(); ++it2){
             if ((dis[*it2]) < d_ref) {
                 d_ref = dis[*it2];
                 v_ref = *it2;
             }
         }
         listOfNotYetDeterimined.remove(v_ref);

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
