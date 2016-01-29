#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Graph notes 
* Degree: The # of edges incident on it
* Connected: there is a path from any vertex to any other vertex
* Formal: A path exists between nodes i, j for all i && j, i != j
* Fully Connected: 
* Formal: A edge exists between nodes i, j for all i && j, i != j
* Weighted:
* Formal: edges have cost associated with them
* Directed:
* Edges have a direction
* Minimum Spanning Tree:
* Finding fewest # of edges to connect components of a graph
* MST on Weighted Graph
* Connect all nodes in such a way that total sum of path costs
* is minimized. ````````
* DFS
* 1) Pick a start node, mark it as visited
* 2) Push on stack S
* 3) For any adjacent unvisited node, mark as visited, push on stack
* 4) Continually do 3 until unable too anymore
* 5) if cant do 3, pop, then try 3 again
* 6) if unable to do 3 or 4, you're finished
*
* BFS
* For number 2 in DFS change to queue
*
* Greedy Algorithms
* 
* Prim's algorithm
* Kruskal's algorithm
* Single-source shortest path
* starting from a given vertex what's the cheapest path to every other vertex
* shortest path tree
* 
* Dikstras
* Track path costs
* 1) start at node, a
* 2) branch out to neighbor, n
* 3) branch out to n's neighbor n'
* 4) if cost(a, n') = cost (a, n) + cost(n, n')
*    then update when see a cheaper path from a, n'
* 
* Input: Start node, a
* 1) Set cost (a, n) = inf for all n != a
*    Set cost (a, a) = 0
* 2) Mark all nodes as unvisited, current node = a
* 3) For current node, c
* -  look at all unvisted neighbors, N 
*    for each n in N:
*    cost (a, n) = cost (a, c) + cost (c, n)
*    if cost(a, n) is cheaper than what we have seen before, save it
* 4) mark C as visited
* 5) current = unvisited neighbor w/ smallest distance from a
* 6) go to step 3
*/
template <typename T>
class Graph{
	private:
		int** adjacency_matrix;
		int vertex_counter;
		int* getEdges(int key);
		int square_size;
	public:
		Graph();
		Graph(int size);
		Graph(int** x, int size);
		~Graph();
		void primsMSTAlgorithm(int start_vertex);
		void kruskalsAlgorithm();
		int* getMinIndex(int* currentVertices, bool* visitedSet, int* hold_min);
		bool contains(int* x, int j);
		int DFS(int vertex);
		int BFS(int vertex);
		bool addEdge(int v1, int v2, int value);
};

template<typename T>
Graph<T>::Graph(){
	square_size=5;
	adjacency_matrix = new int*[5];
	for (int j = 0; j < 5; ++j){
		adjacency_matrix[j] = new int[5];
		for (int i = 0; i < 5; ++i){
			adjacency_matrix[j][i] = 0;
		}
	}
}
template<typename T>
Graph<T>::Graph(int size){
	square_size=size;
	adjacency_matrix = new int*[size];
	for (int j = 0; j < size; ++j){
		adjacency_matrix[j] = new int[size];
		for (int i = 0; i < size; ++i){
			adjacency_matrix[j][i] = 0;
		}
	}
}
template<typename T>
Graph<T>::Graph(int** x, int size){
	square_size=size;
	adjacency_matrix = new int*[size];
	for (int i = 0; i < size; ++i){
		adjacency_matrix[i] = new int[size];
		for (int j = 0; j < size; ++j){
			adjacency_matrix[i][j] = x[i][j];
		}
	}
}	
template<typename T>
Graph<T>::~Graph(){
	for (int i = 0; i < square_size; ++i){
		delete[] adjacency_matrix[i];
	}
	delete[] adjacency_matrix;
}
template<typename T>
bool Graph<T>::addEdge(int v1, int v2, int value){
	bool ret = true;
	if (v1 > square_size || v2 > square_size || v1 == v2){
		ret = false;
	}
	else{
		adjacency_matrix[v1][v2] = value;
		adjacency_matrix[v2][v1] = value;
	}
	return ret;
}
template <typename T>
int Graph<T>::DFS(int vertex){
	int count = 0;
	bool visited[square_size];
	stack<int> x;
	x.push(vertex);
	while (!x.empty()){
		vertex = x.top();
		x.pop();
		if (visited[vertex] != true){
			visited[vertex] = true;
			//cout << "Visited: " << vertex << endl;
			count++;			
			for (int i = 0; i < square_size; ++i){
				if (adjacency_matrix[vertex][i] != 0){
					x.push(i);
				}
			}
		}
	}
	return count;
}

template<typename T>
int Graph<T>::BFS(int vertex){
	int count = 0;
	bool visited[square_size];
	queue<int> x;
	x.push(vertex);
	while (!x.empty()){
		vertex = x.front();
		x.pop();
		if (visited[vertex] != true){
			visited[vertex] = true;
			count++;
			//cout << "Visited: " << vertex << endl;
			for (int i = 0; i < square_size; ++i){
				if (adjacency_matrix[vertex][i] != 0){
					x.push(i);
				}
			}
		}
	}
	return count;
}

template<typename T>
void Graph<T>::primsMSTAlgorithm(int start_vertex){
	int hold_stuff[2];
	int weightedMST[square_size];
	int holdSet[square_size];
	bool visitedSet[square_size];
	for (int i = 0; i < square_size; ++i){
		weightedMST[i]=0;visitedSet[i]=false;
	}
	int count = 0;
	holdSet[count] = start_vertex;
	weightedMST[count] = -1;
	visitedSet[start_vertex] = true;
	++count;
	for (int i = 0; i < square_size; ++i){
		int* hold_array = getMinIndex(weightedMST, visitedSet, hold_stuff);
		visitedSet[hold_array[0]] = true;
		holdSet[count] = hold_array[0];
		weightedMST[count] = hold_array[1];
		++count;
	}
	count = 0;;
	for (int i = 0; i < square_size; ++i){
		cout << "Vertex: " << holdSet[i] << " Edge: " << weightedMST[i] << endl;
		++count;
	}
	cout << count << endl;
}

template <typename T>
int* Graph<T>::getMinIndex(int* currentVertices, bool* visitedSet, int* hold_min){
	hold_min[0] = 0 ; hold_min[1] = INT_MAX;
	for (int i = 0; i < square_size; ++i){
		if (visitedSet[i] == true){
			for (int j = 0; j < square_size; ++j){
				if (visitedSet[j] == true){}
				else if(adjacency_matrix[i][j] < hold_min[1] && adjacency_matrix[i][j] != 0){
					hold_min[1] = adjacency_matrix[i][j];
					hold_min[0] = j;
				}
			}
		}	
	}
	return hold_min;
}

template <typename T>
void Graph<T>::kruskalsAlgorithm(){

}


template <typename T>
bool Graph<T>::contains(int* x, int j){
	bool ret = false;
	for (int i = 0; i < square_size; ++i){
		if (x[i] == j){
			ret = true;
			break;
		}
	}
	return ret;
}

#endif
