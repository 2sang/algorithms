#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

void load_inputs(int* v_c, int* e_c, vector<vector<pair<int, int> > >* adj_list){

	int vertex_count, edge_count;
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &vertex_count, &edge_count);
	*v_c = vertex_count; *e_c = edge_count;
	for(int i = 0; i < vertex_count; i++){
		vector<pair<int, int> > vec;
		adj_list->push_back(vec);
	}

	int from, to, weight;
	for(int i = 0; i < edge_count; i++){
		scanf("%d %d %d", &from, &to, &weight);
		(*adj_list)[from].push_back(make_pair(to, weight));
		(*adj_list)[to].push_back(make_pair(from, weight));
	}

}

// Typedef ((v1, v2), weight) pairs to 'edge'
typedef pair<pair<int, int>, int> edge;

edge make_edge(int v1, int v2, int weight){
	return make_pair(make_pair(v1, v2), weight);
}

void swap_edge(edge *x, edge *y){
    edge temp = *x;
    *x = *y;
    *y = temp;
}

void min_heapify(vector<edge> *vec, int parent_index){
	int last_index = vec->size() - 1;
    while (parent_index*2 + 1 < last_index) {
		// left child = 2*k + 1, right child : 2*k + 2
        int l_child_index = 2*parent_index + 1;
        int r_child_index = l_child_index + 1;
 		int c_child_index = l_child_index;
		int parent_value = (*vec)[parent_index].second;
		int l_child_value = (*vec)[l_child_index].second;
		int r_child_value = (*vec)[r_child_index].second;
		int c_child_value = l_child_value;

		if((r_child_index < last_index) &&
			(l_child_value > r_child_value)){
            c_child_index = r_child_index;
        }
		if(parent_value > c_child_value) {
			swap_edge( &((*vec)[c_child_index]), &((*vec)[parent_index]) );
			parent_index = c_child_index;
		}else
			return;
	}
}

void insert_edge_in_heap(vector<edge>* vec, edge* inserting_edge){
	vec->push_back(*inserting_edge);
	int parent_index = ((vec->size())-1)/2;
	while(1){
		min_heapify(vec, parent_index);
		if(parent_index == 0) break;
		parent_index /= 2;
	}
	printf("inserted edge ((%d, %d), %d)\n", inserting_edge->first.first, inserting_edge->first.second, inserting_edge->second);
}

edge extract_min_edge_in_heap(vector<edge> *vec){
	/* Swap root value with last index, so that
	 last element of array remains sorted sequently.
	 then min_heapify rest values*/
	edge ret = (*vec)[0];
	swap_edge(&((*vec)[0]), &((*vec)[vec->size()-1]));
	vec->erase(vec->end() - 1);
	min_heapify(vec, 0);
	return ret;
}

// Node's weight belongs to child, respectively. 
struct node{
	node* parent;
	vector<node *> children;
	int vertex_number;
	int weight;
};

// assign weight, pointer operations between two nodes
void connect_nodes(node* par, node* cur, int w){
	par->children.push_back(cur);
	cur->parent = par;
	cur->weight = w;
}

int main(){

	// Graph definitions using adjacency list with initializing
	vector<vector<pair<int, int> > > adj_list;
	vector<edge> edge_vector;
	vector<node> result_nodes;
	int vertex_count, edge_count;
	// Load inputs from file 'input.txt'
	load_inputs(&vertex_count, &edge_count, &adj_list);

	// Init result nodes vector. 
	node parent_of_root;
	parent_of_root.vertex_number = -1;
	for(int i = 0; i < vertex_count; i++){
		node n;
		n.vertex_number = i;
		n.parent = &parent_of_root;
		result_nodes.push_back(n);
	}
		
	bool* check = new bool[vertex_count];
	memset(check, false, sizeof(bool)*vertex_count);

	for(int i = 0; i < adj_list[0].size(); i++){
		pair<int, int> p = adj_list[0][i];
		edge derived_edge = make_edge(0, p.first, p.second); 
		insert_edge_in_heap(&edge_vector, &derived_edge);
	}
	check[0] = true;

	// Main prim's algorithm logic
	int connected_edge_count = 0;
	while(connected_edge_count < vertex_count - 1){
		edge min_edge = extract_min_edge_in_heap(&edge_vector);

		// If popped edge makes cycle, re-pop.
		while(check[min_edge.first.first] && check[min_edge.first.second]){
			if(!edge_vector.empty()){
				min_edge = extract_min_edge_in_heap(&edge_vector);
			}
		}

		// Connect two node, with parent-child realations(tree)
		connect_nodes(&result_nodes[min_edge.first.first], &result_nodes[min_edge.first.second], 
				min_edge.second);
		printf("connect (%d, %d)\n", min_edge.first.first, min_edge.first.second);
		connected_edge_count++;
		check[min_edge.first.second] = true;

		// Add new edges from newly connected vertex
		int new_node_index = min_edge.first.second;
		for(int i = 0; i < adj_list[new_node_index].size(); i++){
			pair<int, int> p = adj_list[new_node_index][i];
			if(!check[p.first]){
				edge derived_edge = make_edge(new_node_index, p.first, p.second); 
				insert_edge_in_heap(&edge_vector, &derived_edge);
			}
		}
	}
	printf("\nprint tree : start from root : 0\n");
	for(int i = 0; i < result_nodes.size(); i++){
		node *current_node = &result_nodes[i];
		printf("node #%d:\nparent : %d, children :", i, (current_node->parent)->vertex_number);
		for(auto it = current_node->children.begin(); it != current_node->children.end(); ++it ){
			printf("%d ", (**it).vertex_number);
		}
		printf("\n");
	}

	

	
	return 0;

}
