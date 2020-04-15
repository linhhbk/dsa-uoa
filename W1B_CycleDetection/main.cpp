// cycle detection in a directed graph
#include <iostream>
#include <stack>
#include <list>
#include <cstdlib> // rand(), abs()
#include <fstream> // file

using namespace std;

const int numVertex_max = 100;
const int numEdge_max = 1000;

class Graph{
public:
    Graph(int v); //construction function
    void addEdge(int u, int v);
    void printGraph();
    bool isCyclic();
protected:
private:
    int V; //number of vertexes
    // int E; //number of edges
    list<int>* adj; //pointer to save adjacent vertexes of each vertex
};


int main()
{
    // import data from a txt file
    int numVertex = 5;
    // int numEdge = 3;
    Graph myGraph(numVertex);
    ifstream infile("input.txt");
    int a, b;
    while (infile >> a >> b){
        myGraph.addEdge(a, b);
    }
    infile.close();

//    //import data from command line
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

    // test for cycle detection function
    if (myGraph.isCyclic()) {cout << "1\n";} else {cout << "0\n";}

    return 0;
}


Graph::Graph(int v) {
    V = v;
    adj = new list<int>[v];
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void Graph::printGraph() {
    for (int i = 0; i < V; i++) {
        cout <<  "adj[" << i << "]: ";
        list<int>::iterator it;
        for(it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << "\n";
    }
}

bool Graph::isCyclic() {
    bool isCycleDetected = false;
    //DFS: repeat until a cycle is detected
    stack<int> myStack;
    bool isDiscovered[V] = {false};
    for (int iVertex = 0; iVertex < V; iVertex++) {
		myStack.push(iVertex);
		isDiscovered[V] = {false};
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
