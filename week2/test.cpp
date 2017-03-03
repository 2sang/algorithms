#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <ctime>
using namespace std;

int arr[199];

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int randomized_partition(int *arr, int first_index, int last_index){
    srand(time(NULL));
    int random_pivot, iteration_index, pivot_value;

    // 1. Select randomized pivot.
    random_pivot = rand()%(last_index - first_index + 1) + first_index;

    // 2. Swap pivot item with last item.
    swap(arr[random_pivot], arr[last_index]);

    // 3. store random value in pivot_value
    pivot_value = arr[last_index];

    // 4. Set iteration index to first_index - 1
    iteration_index = first_index - 1;
    for(int i = first_index; i < last_index; i++){
        // Check if arr[i] value is less than arr[pivot]
        if(arr[i] <= pivot_value){
            iteration_index++;
            swap(arr[iteration_index], arr[i]);
        }
    }
    swap(arr[iteration_index + 1], arr[last_index]);
    return (iteration_index + 1);
}

void randomized_quicksort(int *arr, int first_index, int last_index){
    if(first_index < last_index){
        int pivot = randomized_partition(arr, first_index, last_index);
        randomized_quicksort(arr, first_index, (pivot - 1));
        randomized_quicksort(arr, (pivot + 1), last_index);
    }
}

int main(int argc, char const *argv[]) {
    int arr[10] = {19, 32, 442, 42, 31,
                    85, 80, 2, 54, 10};
    for(int i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    randomized_quicksort(arr, 0, 9);
    for(int i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}
void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
void heapsort(vector<int> *arr, int last_index){
    for (int k = last_index/2; k >= 0; k--) {
        heapify(arr, k, last_index);
    }

    while ((last_index - 1) > 0) {
        /* Swap root value with last index, so that
         last element of array remains sorted sequently.
         then heapify rest values*/
        swap(arr[last_index - 1], arr[0]);
        heapify(arr, 0, last_index - 1);
        last_index--;
    }
}
void heapify(vector<int> *arr, int k, int n){
    while ( k*2 + 1 < n ) {
		// left child = 2*k + 1, right child : 2*k + 2
 		int child = 2*k + 1;
		if ((child + 1 < n) && (arr[child] < arr[child+1])){
            child++;
        }
		if (arr[k] < arr[child]) {
			swap(arr[child], arr[k]);
			k = child;
		}
		else
			return;
	}
}
