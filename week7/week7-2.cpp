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
		vector<pair<int, int>> vec;
		adj_list->push_back(vec);
	}

	int from, to, weight;
	for(int i = 0; i < edge_count; i++){
		scanf("%d %d %d", &from, &to, &weight);
		(*adj_list)[from].push_back(make_pair(to, weight));
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
	if(parent_index*2 + 1 == last_index){
		int l_child_index = 2*parent_index + 1;
		if((*vec)[l_child_index].second < (*vec)[parent_index].second){
			swap_edge( &((*vec)[l_child_index]), &(*vec)[parent_index]);
		}
		return;
	}
    while (parent_index*2 + 1 < last_index) {
		// left child = 2*k + 1, right child : 2*k + 2
        int l_child_index = 2*parent_index + 1;
        int r_child_index = l_child_index + 1;
 		int c_child_index = l_child_index;
		int parent_value = (*vec)[parent_index].second;
		int l_child_value = (*vec)[l_child_index].second;
		int r_child_value = (*vec)[r_child_index].second;
		int c_child_value = l_child_value;

		if((r_child_index <= last_index) &&
			(l_child_value > r_child_value)){
            c_child_index = r_child_index;
			c_child_value = (*vec)[c_child_index].second;
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
	if(vec->size() == 1) return;
	int parent_index = ((vec->size())-2)/2;
	while(1){
		min_heapify(vec, parent_index);
		if(parent_index == 0) break;
		parent_index = (parent_index - 1)/2;
	}
	printf("Insert into heap, status : ");
	for(auto it = vec->begin(); it != vec->end(); ++it){
		printf("%d ", (*it).second);	
	}
	printf("\n");
}

edge extract_min_edge_in_heap(vector<edge> *vec){
	/* Swap root value with last index, so that
	 last element of array remains sorted sequently.
	 then min_heapify rest values*/
	edge ret = (*vec)[0];
	swap_edge(&((*vec)[0]), &((*vec)[vec->size()-1]));
	vec->erase(vec->end() - 1);
	min_heapify(vec, 0);
	printf("Extract from heap, heap status : ");
	for(auto it = vec->begin(); it != vec->end(); ++it){
		printf("%d ", (*it).second);	
	}
	printf("\n");
	printf("returning edge ((%d, %d), %d)\n", ret.first.first, ret.first.second, ret.second);
	return ret;
}

// Node's weight belongs to child, respectively. 
struct node{
	node* parent;
	vector<node *> children;
	int vertex_number;
	int weight;
	int rank;
};

// Returns uppermost node's vertex value(root)
// == FIND()
int root_value_of(node *child){
	node temp = *child;
	while(child->parent){
		child = child->parent;
	}
	return child->vertex_number;

}
// assign weight, pointer operations between two nodes
void connect_nodes(node* par, node* cur, int w){
	if(par->rank >= cur->rank){
		par->children.push_back(cur);
		cur->parent = par;
		cur->weight = w;
		cur->rank = par->rank + 1;
	}else{
		cur->children.push_back(par);
		par->parent = cur;
		par->weight = w;
		par->rank = cur->rank + 1;
	}

}

int main(){

	// Graph definitions using adjacency list with initializing
	vector<vector<pair<int, int>>> adj_list;
	vector<edge> edge_vector;
	vector<node> result_nodes;
	int vertex_count, edge_count;
	// Load inputs from file 'input.txt'
	load_inputs(&vertex_count, &edge_count, &adj_list);

	// Init result nodes vector. 
	for(int i = 0; i < vertex_count; i++){
		node n;
		n.vertex_number = i;
		n.parent = 0;
		n.rank = 0;
		result_nodes.push_back(n);
	}
		
	bool* check = new bool[vertex_count];
	memset(check, false, sizeof(bool)*vertex_count);

	// Input all edge structs into heap, while avoiding duplicated edge(non-directed edge)
	for(int i = 0; i < adj_list.size(); i++){
		for(int j = 0; j < adj_list[i].size(); j++){
			pair<int, int> p = adj_list[i][j];
			edge derived_edge = make_edge(i, p.first, p.second); 
			insert_edge_in_heap(&edge_vector, &derived_edge);
		}
	}

	// Main kruskal's algorithm logic
	int connected_edge_count = 0;
	while(connected_edge_count < vertex_count - 1){
		edge min_edge = extract_min_edge_in_heap(&edge_vector);

		// If popped edge makes cycle, re-pop.
		while(root_value_of(&result_nodes[min_edge.first.first]) == root_value_of(&result_nodes[min_edge.first.second])){
			if(!edge_vector.empty()){
				min_edge = extract_min_edge_in_heap(&edge_vector);
			}
		}

		// Connect two node, with parent-child realations(tree)
		connect_nodes(&result_nodes[min_edge.first.first], &result_nodes[min_edge.first.second], 
				min_edge.second);
		printf("found non-cycle edge, connect (%d, %d)\n", min_edge.first.first, min_edge.first.second);
		connected_edge_count++;
	}
	return 0;

}
