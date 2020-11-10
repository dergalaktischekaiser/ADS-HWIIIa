// THE PRIM'S ALGORITHM IS INTRODUCED TO SOLVE THE PROBLEM OF DESIGNING
// AN ENERGY NETWORK
/*
                                                                                            O _____ O                   Karimov R.
                                                                                            /\     /\                   DSBA191
                                                                                           /  \   /  \                  GitHub @dergalaktischekaiser
											  /    \ /    \
											 O----- O------O
											  \    / \    /
											   \  /   \  /
											    \/_____\/
											    O       O                                           
*/
#include <climits>                           
#include <cmath>                                  
#include <functional>                              
#include <iostream>
#include <list>
#include <queue>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::greater;
using std::list;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::sqrt;
using std::vector;

typedef pair<int, int> Pair;                                    // simplified definition of std::pair<int, int>
typedef list<Pair>::iterator Iter;                              // simplified definition to read iterators easier

double calculate_weight(double x1, double y1, double x2, double y2)
{                                                               // calculating weights of edges as
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); // described in the task
}

class Graph {
public:
	int V;                                                      // the number of vertices in a graph
	list <Pair>* adjacency_list;                                // in terms of this list we are going to describe a graph
	vector<vector<double>> weights;                             // a matrix which contains weights or every edge in our graph
	vector<pair<double, double>> coordinates;                   // thus all the nodes' coordinates are going to be stored

	Graph(int v)
	{
		this->V = v;
		adjacency_list = new list<Pair>[v];
		weights.resize(v);
		for (vector<double>& vec : weights)
			vec.resize(v);
		coordinates.resize(v);
	}

	void push_edge(int u, int v, double weight)                // a method which allows us to add a vertex to a graph
	{
		adjacency_list[u].push_back(make_pair(v, weight));
		adjacency_list[v].push_back(make_pair(u, weight));
	}

	void Prim()                                                // the algorithm itself
	{
		priority_queue<Pair, vector<Pair>, greater<Pair>> graph_base;
		vector<int> key(V, INT_MAX),                           // in terms of this vector we define keys for all vertices
		            parents(V, -42);                           // in terms of this vector we define any vertex's parent
		vector<bool> is_edge_in_MST(V, false);                 // in terms of this vec. we check if a vertex belongs to the MST
		graph_base.push(make_pair(0, 0));                      // assume that the 0th vertex has key = 0
		key[0] = 0;
		int u;                                                 // a variable we use to grab any vertex in the following cycle
		while (!graph_base.empty()) {
			u = graph_base.top().second;
			graph_base.pop();
			is_edge_in_MST[u] = true;
			for (Iter i = adjacency_list[u].begin(); i != adjacency_list[u].end(); ++i)
			{
				int v = (*i).first,
					_weight = (*i).second;
				if (!is_edge_in_MST[v] && key[v] > _weight)
				{
					key[v] = _weight;
					graph_base.push(make_pair(key[v], v));
					parents[v] = u;
				}
			}
		}
		                                                      // now, it follows the outout including the calculated weight and all MST vertices' coordinates
		double _weight_ = 0;
		for (int i = 1; i < V; ++i)
			_weight_ += weights[parents[i]][i];
		printf("%.7f\n", _weight_);
		for (int i = 1; i < V; ++i)
			cout << this->coordinates[parents[i]].first << " " << this->coordinates[parents[i]].second
			     << " " << this->coordinates[i].first << " " << this->coordinates[i].second << "\n";
	}
};

int main() {
	double _u, _v, weight;
	int N;
	cin >> N;
	Graph G(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> _u >> _v;
		G.coordinates[i] = make_pair(_u, _v);
	}
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
		{
			weight = calculate_weight(G.coordinates[i].first, G.coordinates[i].second,
				                      G.coordinates[j].first, G.coordinates[j].second);
			G.push_edge(i, j, weight);
			G.weights[i][j] = weight;
			G.weights[j][i] = weight;
		}
	G.Prim();
	return 0;
}
