#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>
#define INF 9999
using namespace std;

void load_inputs(int* v_c, int* e_c, vector<vector<pair<int, int> > >* adj_list){

	int vertex_count, edge_count;
	freopen("graph_sample_DAG.txt", "r", stdin);
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

int main(){

	// Graph definitions using adjacency list with initializing
	vector<vector<pair<int, int>>> adj_list;
	vector<node> result_nodes;
	int vertex_count, edge_count;
	// Load inputs from file 'input.txt'
	load_inputs(&vertex_count, &edge_count, &adj_list);

	node root_node;
	root_node.vertex_number = -1;
	// Init result nodes vector. 
	for(int i = 0; i < vertex_count; i++){
		node n;
		n.vertex_number = i;
		n.pred = &root_node;
		n.cost = INF;
		result_nodes.push_back(n);
	}
		
	// DAG algorithm. assume that graph adj_list is sorted in topological order.
	result_nodes[1].cost = 0;
	for(int i = 0; i < adj_list.size(); i++){
		for(int j = 0; j < adj_list[i].size(); j++){
			int point_to = adj_list[i][j].first;
			int edge_weight = adj_list[i][j].second;
			if(result_nodes[i].cost + edge_weight < result_nodes[point_to].cost){
				result_nodes[point_to].cost = result_nodes[i].cost + edge_weight;
				result_nodes[point_to].pred = &result_nodes[i];
			}
		}
	}
	for(int i = 0; i < result_nodes.size(); i++){
		printf("result_nodes[%d].d=%d, pre:%d\n", i, result_nodes[i].cost, result_nodes[i].pred->vertex_number);
	}
	return 0;

}
