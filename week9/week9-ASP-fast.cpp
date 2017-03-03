#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#define INF 9999
using namespace std;

int min(int x, int y){return (x < y) ? x : y;}

int** new_INF_matrix(int matrix_size){
	// Initialize adjacent matrix [vertex_count][vertex_count]
	int **new_matrix = new int*[matrix_size];
	for(int i = 0; i < matrix_size; i++){
		new_matrix[i] = new int[matrix_size];
		for(int j = 0; j < matrix_size; j++){
			if(i == j){
				new_matrix[i][j] = 0;
			}else{
				new_matrix[i][j] = INF;
			}
		}
	}
	return new_matrix;
}

void print_matrix(int vertex_size, int **adj_matrix){
	// printing method
	for(int i = -1; i < vertex_size; i++){
		for(int j = -1; j < vertex_size; j++){
			if(i == -1 && j == -1) printf("     ");
			else{
				if(i == -1){
					printf("[%02d] ", j);
				}else if(j == -1){
					printf("[%02d] ", i);
				}else{
					printf("%4d ", adj_matrix[i][j]);
				}
			}
		}
		printf("\n");
	}
	printf("\n");

}

int** load_inputs(int* v_c, int* e_c){

	int vertex_count, edge_count;
	freopen("graph_sample_directed.txt", "r", stdin);
	scanf("%d %d", &vertex_count, &edge_count);
	*v_c = vertex_count; *e_c = edge_count;
	int** adj_matrix = new_INF_matrix(vertex_count);
	int from, to, weight;
	for(int i = 0; i < edge_count; i++){
		scanf("%d %d %d", &from, &to, &weight);
		adj_matrix[from][to] = weight;
	}
	return adj_matrix;

}

int** extend_shortest_paths(int vertex_count, int** l, int** w){

	int** result_matrix = new_INF_matrix(vertex_count);
	for(int i = 0; i < vertex_count; i++){
	for(int j = 0; j < vertex_count; j++){
		result_matrix[i][j] = l[i][j];
		for(int k = 0; k < vertex_count; k++){
			// If relaxable, modify value.
			if((l[i][k] != INF && w[k][j] != INF)
				 &&(l[i][k] + w[k][j]) < l[i][j]){
				result_matrix[i][j] = ((l[i][k] + w[k][j]));
			}
		}
	}
	}
	return result_matrix;
}

int main(){

	// Graph definitions using adjacency list with initializing
	int vertex_count, edge_count;

	// Load inputs from file 'input.txt'
	int **adj_matrix = load_inputs(&vertex_count, &edge_count);
	printf("INITIAL MATRIX : \n");
	print_matrix(vertex_count, adj_matrix);

	for(int i = 1; i < vertex_count*2; i = i*2){
		printf("EXTEND_SHORTEST_PATH #%d\n", i);
		adj_matrix = extend_shortest_paths(vertex_count, adj_matrix, adj_matrix);
		print_matrix(vertex_count, adj_matrix);
	}

	return 0;
}
