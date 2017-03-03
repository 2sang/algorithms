#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#define INF 9999
using namespace std;

void load_inputs(int* v_c, int* e_c, vector<vector<pair<int, int>>>* adj_list){

	int vertex_count, edge_count;
	freopen("graph_sample_bellman.txt", "r", stdin);
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

// struct node has its parent's pointer, vertex number, cost
struct node{
	node* predecessor;
	int vertex_number;
	int cost;
};

// assign weight, pointer operations between two nodes
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
		n.predecessor = &root_node;
		n.cost = INF;
		result_nodes.push_back(n);
	}
		

	result_nodes[0].cost = 0;
	for(int count = 0; count < result_nodes.size(); count++){
		printf("\nrelaxing #%d\n", count);
		for(int i = 0; i < adj_list.size(); i++){
			for(int j = 0; j < adj_list[i].size(); j++){
				int point_to = adj_list[i][j].first;
				int edge_weight = adj_list[i][j].second;

				// iterate through all edges, vertex-1 times.
				if (count != result_nodes.size() - 1) {
					if (result_nodes[i].cost + edge_weight < result_nodes[point_to].cost) {
						result_nodes[point_to].predecessor = &result_nodes[i];
						result_nodes[point_to].cost = result_nodes[i].cost + edge_weight;
						printf("result_nodes[%d].d=%d, pre:%d\n"
								, point_to, result_nodes[point_to].cost,
								result_nodes[point_to].predecessor->vertex_number);
					}

				}else{ // Cycle recognition, return false if cycle detected.
					if(result_nodes[point_to].cost > result_nodes[i].cost + edge_weight){
						printf("cycle detected. return.");
						return false;
					} 
				}
			}
		}		
	}
	
	

	printf("\nprint nodes : start from 0\n");
	for(int i = 0; i < result_nodes.size(); i++){
		printf("result_nodes[%d].d=%d, pre:%d\n", 
				i, result_nodes[i].cost
				, result_nodes[i].predecessor->vertex_number);
	}

	return 0;

}
