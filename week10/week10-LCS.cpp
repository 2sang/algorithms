#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

void load_inputs(vector<char>* l_chars, vector<char>* r_chars, int* l_c, int* r_c){
	freopen("inputs/sample_lcs1.txt", "r", stdin);
	scanf("%d", l_c);
	char char_in_use;
	for(int i = 0; i < *l_c; i++){
		scanf(" %c", &char_in_use);
		l_chars->push_back(char_in_use);
	}
	scanf("%d", r_c);
	for(int i = 0; i < *r_c; i++){
		scanf(" %c", &char_in_use);
		r_chars->push_back(char_in_use);
	}
}

int** initialized_matrix(int m, int n){
	int** matrix = new int*[m+1];
	for(int i = 0; i <= m; i++){
		matrix[i] = new int[n+1];
	}
	return matrix;
}

void print_lcs(int** b, vector<char> x, int i, int j){
	if(i == 0 || j == 0){
		return;
	}
	if(b[i][j] == 2){
		print_lcs(b, x, i-1, j-1);
		printf("[%c] ", x[i-1]);
	}else if(b[i][j] == 3){
		print_lcs(b, x, i-1, j);
	}else{
		print_lcs(b, x, i, j-1);
	}
}


int main(void){
	int l_c, r_c;
	vector<char> l_chars, r_chars;
	load_inputs(&l_chars, &r_chars, &l_c, &r_c);
	int m = l_chars.size(); // x.length
	int n = r_chars.size(); // y.length
	int **b = initialized_matrix(m, n);
	int **c = initialized_matrix(m, n);
	for(int i = 1; i <= m; i++){
		c[i][0] = 0;
		b[i][0] = 0;
	}
	for(int j = 0; j <= n; j++){
		c[0][j] = 0;
		b[0][j] = 0;
	}
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			if(l_chars[i-1] == r_chars[j-1]){
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j] = 2;
			}else if(c[i-1][j] >= c[i][j-1]){
				c[i][j] = c[i-1][j];
				b[i][j] = 3;
			}else{
				c[i][j] = c[i][j-1];
				b[i][j] = 1;
			}
		}
	}
	// Printing c[x][y]
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= m; j++){
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// Printing b[x][y]
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= m; j++){
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}

	print_lcs(b, l_chars, m, n);

	return 0;
}
