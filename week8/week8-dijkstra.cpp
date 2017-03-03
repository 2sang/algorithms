#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <queue>
#define INF 9999
using namespace std;

void load_inputs(int* v_c, int* e_c, vector<vector<pair<int, int>>>* adj_list){

	int vertex_count, edge_count;
	freopen("graph_sample_dijkstra.txt", "r", stdin);
	scanf("%d %d", &vertex_count, &edge_count);
	*v_c = vertex_count; *e_c = edge_count;
	for(int i = 0; i < vertex_count; i++){
		vector<pair<int, int>> vec;
		adj_list->push_back(vec);
	}

	int from, to, weight;
	for(int i = 0; i < edge_count; i++){
		scanf("%d %d %d", &from, &to, &weight);
		(*adj_list)[from].push_back(make_pair(to, weight));
	}

}

// Node's weight belongs to child, respectively. 
struct node{
	node* pred;
	int vertex_number;
	int cost;
};

// When compare pair in priority_queue, choose second item.
class Prioritize {
public:
     int operator() ( const pair<int, int>& p1,
                      const pair<int, int>& p2 ) {
         return p1.second > p2.second;
     }
};

int main(){

	// Graph definitions using adjacency list with initializing
	vector<vector<pair<int, int>>> adj_list;
	priority_queue<pair<int, int>, vector<pair<int, int>>, Prioritize> vertex_queue;
	vector<node> result_nodes;
	int vertex_count, edge_count;
	// Load inputs from file 'input.txt'
	load_inputs(&vertex_count, &edge_count, &adj_list);

	bool *visit = new bool[vertex_count];
	memset(visit, false, sizeof(bool)*vertex_count);
	node root_node;
	root_node.vertex_number = 0;
	// Init result nodes vector. 
	for(int i = 0; i < vertex_count; i++){
		node n;
		n.vertex_number = i;
		n.pred = &root_node;
		n.cost = INF;
		result_nodes.push_back(n);
	}
		
	// Dijkstra's algorithm
	result_nodes[0].cost = 0;
	// push(vertex_number, vertex_cost) pair
	vertex_queue.push(make_pair(0, 0));
	while(!vertex_queue.empty()){
		int current_vertex = vertex_queue.top().first;
		vertex_queue.pop();
		if(!visit[current_vertex]){
			visit[current_vertex] = true;
			for(int i = 0; i < adj_list[current_vertex].size(); i++){
				int point_to = adj_list[current_vertex][i].first;
				int edge_weight = adj_list[current_vertex][i].second;
				if(result_nodes[current_vertex].cost + edge_weight < result_nodes[point_to].cost ){
					result_nodes[point_to].cost = result_nodes[current_vertex].cost + edge_weight;
					result_nodes[point_to].pred = &result_nodes[current_vertex];
					vertex_queue.push(make_pair(point_to, result_nodes[point_to].cost));
				}
			}	
		}
	}
	for(int i = 0; i < result_nodes.size(); i++){
		printf("result_nodes[%d].d=%d, pre:%d\n", i, result_nodes[i].cost, result_nodes[i].pred->vertex_number);
	}
	return 0;

}
