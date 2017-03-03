#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define MAXINT 999999
using namespace std;

void load_inputs(vector<int>* input_vector, int* matrix_count){
	freopen("inputs/sample_mat2.txt", "r", stdin);
	scanf("%d", matrix_count);
	for(int i = 0; i <= *matrix_count; i++){
		int amount;
		scanf("%d ", &amount);
		input_vector->push_back(amount);
	}
}

int** initialized_matrix(int matrix_count){
	int** m = new int*[matrix_count];
	for(int i = 0; i < matrix_count; i++){
		m[i] = new int[matrix_count];
		for(int j = 0; j < matrix_count; j++){
			m[i][j] = -1;
		}
	}
	return m;

}
void print_optimal_parenthesis(int** s, int i, int j){
	if(i == j){
		printf("A[%d]", i);
	}else{
		printf("(");
		print_optimal_parenthesis(s, i, s[i][j]);
		print_optimal_parenthesis(s, s[i][j]+1, j);
		printf(")");
	}
}
int main(){
	vector<int> matrix_degrees;
	int matrix_count;
	int** m; int** s; 
	load_inputs(&matrix_degrees, &matrix_count);
	m = initialized_matrix(matrix_count);
	s = initialized_matrix(matrix_count);
	for(int i = 0; i < matrix_count; i++){
		m[i][i] = 0;
	}
	for(int chain_length = 1; chain_length < matrix_count; chain_length++){
		for(int i = 0; i < matrix_count - chain_length; i++){
			int j = i + chain_length;
			m[i][j] = MAXINT;
			for(int k = i; k < j; k++){
				int q = (m[i][k] + m[k+1][j] +
					matrix_degrees[i]*matrix_degrees[k+1]*matrix_degrees[j+1]);
				if (q < m[i][j]){
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
		printf("\n");
	}

	printf("::::::::::::::::: m :::::::::::::::::\n");
	for(int i = 0; i < matrix_count; i++){
		for(int j = 0; j < matrix_count; j++){
			printf("%5d ", m[i][j]);
		}
		printf("\n");
	}
	
	printf("::::::::::::::::: s :::::::::::::::::\n");
	for(int i = 0; i < matrix_count; i++){
		for(int j = 0; j < matrix_count; j++){
			printf("%5d ", s[i][j]);
		}
		printf("\n");
	}
	printf("RESULT : ");
	print_optimal_parenthesis(s, 0, matrix_count-1);
	return 0;
}

