#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <ctime>

using namespace std;

// Function prototypes
void import_files();
void print_arrays();
void swap(int *x, int *y);
void min_heap_sort(int *arr, int last);
void max_heap_sort(int *arr, int last);
void build_max_heap(int *arr, int last);
void build_min_heap(int *arr, int last);
void build_max_d_array_heap(int *arr, int last, int d);
void min_heapify(int *arr, int parent_node, int last);
void max_heapify(int *arr, int parent_node, int last);
void max_heapify_recursively(int *arr, int parent_node, int last);
void d_array_max_sort(int *arr, int last, int d);
void d_array_max_heapify(int *arr, int parent_node, int last, int d);
void randomized_quicksort();
int randomized_partition(int *arr, int first, int last);
void min_heapsort_measurement();
void max_heapsort_measurement();
void max_heapsort_recursively_measurement();
void randomized_quicksort_measurement();
void d_array_max_heapsort_measurement();

// Global variables.
int arr0[51], arr1[501], arr2[5001], arr3[10001];
double time_elapsed[4];


/////////////////////// Main() //////////////////////////
int main(int argc, char const *argv[]) {
    import_files();
    printf("///min_heapsort///\n");
    min_heapsort_measurement();
    print_arrays();
    printf("********************************\n");

    import_files();
    printf("///max_heapsort///\n");
    max_heapsort_measurement();
    print_arrays();
    printf("********************************\n");

    import_files();
    printf("///randomized_quicksort///\n");
    randomized_quicksort_measurement();
    print_arrays();
    printf("********************************\n");

    import_files();
    printf("///max_heapsort_recursively///\n");
    max_heapsort_recursively_measurement();
    print_arrays();
    printf("********************************\n");

    import_files();
    printf("///d_array_max_sort///\n");
    d_array_max_heapsort_measurement();
    print_arrays();
    printf("********************************\n");

    return 0;
}
//////////////////////////////////////////////////////////



void import_files(){
    freopen("input/input50.txt", "r", stdin);
    for(int i = 0; i < 50; i++){
        scanf("%d", &arr0[i]);
    }
    freopen("input/input500.txt", "r", stdin);
    for(int i = 0; i < 500; i++){
        scanf("%d", &arr1[i]);
    }
    freopen("input/input5000.txt", "r", stdin);
    for(int i = 0; i < 5000; i++){
        scanf("%d", &arr2[i]);
    }
    freopen("input/input10000.txt", "r", stdin);
    for(int i = 0; i < 10000; i++){
        scanf("%d",  &arr3[i]);
    }
}

void print_arrays(){
    for(int i = 47; i < 50; i++){
        printf("arr0[%d] = %d, ", i, arr0[i]);
    }
    printf("\n");
    for(int i = 497; i < 500; i++){
        printf("arr1[%d] = %d, ", i, arr1[i]);
    }
    printf("\n");
    for(int i = 4997; i < 5000; i++){
        printf("arr2[%d] = %d, ", i, arr2[i]);
    }
    printf("\n");
    for(int i = 9997; i < 10000; i++){
        printf("arr3[%d] = %d, ", i, arr3[i]);
    }
    printf("\n");
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void min_heap_sort(int *arr, int last){
    build_min_heap(arr, last);
    while ((last - 1) > 0) {
        /* Swap root value with last index, so that
         last element of array remains sorted sequently.
         then min_heapify rest values*/
        swap(arr[last - 1], arr[0]);
        min_heapify(arr, 0, last - 1);
        last--;
    }
}

void max_heap_sort(int *arr, int last){
    build_max_heap(arr, last);
    while ((last - 1) > 0) {
        /* Swap root value with last index, so that
         last element of array remains sorted sequently.
         then max_heapify rest values*/
        swap(arr[last - 1], arr[0]);
        last--;
        max_heapify(arr, 0, last);
    }
}

void randomized_quicksort(int *arr, int first, int last){
    if(first < last){
        int pivot = randomized_partition(arr, first, last);
        randomized_quicksort(arr, first, (pivot - 1));
        randomized_quicksort(arr, (pivot + 1), last);
    }
}

void max_heap_sort_recursively(int *arr, int last){
    build_max_heap(arr, last);
    while ((last - 1) > 0) {
        /* Swap root value with last index, so that
         last element of array remains sorted sequently.
         then max_heapify rest values*/
        swap(arr[last-1], arr[0]);
        last--;
        max_heapify_recursively(arr, 0, last);
    }
}

void d_array_max_sort(int *arr, int last, int d){
    build_max_d_array_heap(arr, last, d);
    /* Swap root value with last index, so that
     last element of array remains sorted sequently.
     then d_array_max_heapify rest values*/
    while((last - 1) > 0){
        swap(arr[last - 1], arr[0]);
        d_array_max_heapify(arr, 0, last - 1, d);
        last--;
    }
}



void build_max_heap(int *arr, int last){
    for (int k = last/2; k >= 0; k--) {
        max_heapify(arr, k, last);
    }
}

void build_min_heap(int *arr, int last){
    for (int k = last/2; k >= 0; k--) {
        min_heapify(arr, k, last);
    }
}

void build_max_d_array_heap(int *arr, int last, int d){
    for (int k = last/d; k >= 0; k--) {
        d_array_max_heapify(arr, k, last, d);
    }
}

void min_heapify(int *arr, int parent_node, int last){
    while (parent_node*2 + 1 < last) {
		// left child = 2*k + 1, right child : 2*k + 2
        int left_child = 2*parent_node + 1;
        int right_child = left_child + 1;
 		int current_child = left_child;

		if((right_child < last) && (arr[left_child] > arr[right_child])){
            current_child = right_child;
        }
		if(arr[parent_node] > arr[current_child]) {
			swap(arr[current_child], arr[parent_node]);
			parent_node = current_child;
		}else
			return;
	}
}

void max_heapify(int *arr, int parent_node, int last){
    // Top-down flow while parent_node reaches leaf.
    // Iterate while parent node has its left child
    while (parent_node*2 + 1 < last) {
		// left child = 2*parent + 1, right child : 2*parent + 2
        int left_child = 2*parent_node + 1;
        int right_child = left_child + 1;
 		int current_child = left_child;

		if((right_child < last) && (arr[left_child] < arr[right_child])){
            current_child = right_child;
        }
        // If parent node and current node are existed reversed order
		if(arr[parent_node] < arr[current_child]) {
			swap(arr[current_child], arr[parent_node]);
            // Switch pointer to its current child
			parent_node = current_child;
        // Collect order
		}else
			return;
	}
}

void max_heapify_recursively(int *arr, int parent_node, int last){
	// left child = 2*k + 1, right child : 2*k + 2
    int left_child = 2*parent_node + 1;
    int right_child = 2*parent_node + 2;
    int max_index = parent_node;
    if((left_child < last) && (arr[left_child] > arr[right_child])) {
        max_index = left_child;
    }
	if((right_child < last) && (arr[left_child] < arr[right_child])){
        max_index = right_child;
    }
    if(max_index != parent_node){
        swap(arr[parent_node], arr[max_index]);
        max_heapify_recursively(arr, max_index, last);
    }
}

void d_array_max_heapify(int *arr, int parent_node, int last, int d){
    // Top-down flow while parent_node reaches leaf.
    // Iterate while parent node has its left child
    while (parent_node*d + 1 < last) {
        // leftmost child to rightmost : 5*parent + 1 ~ 5*parent + 5
        int leftmost_child = d*parent_node + 1;
 		int current_child = leftmost_child;
        int largest_child = leftmost_child;

        // Iterate through leftmost_child to rightmost_child
        while(current_child < (leftmost_child + d) && current_child < last){
            if(arr[largest_child] < arr[current_child]){
                largest_child = current_child;
            }
            current_child++;
        }
        if(arr[parent_node] < arr[largest_child]){
            swap(arr[parent_node], arr[largest_child]);
            parent_node = largest_child;
        }else{
            return;
        }
    }
}



int randomized_partition(int *arr, int first, int last){
    srand(time(NULL));
    int random_pivot, iteration_index, pivot_value;

    // 1. Select randomized pivot.
    random_pivot = rand()%(last - first + 1) + first;

    // 2. Swap pivot item with last item.
    swap(arr[random_pivot], arr[last]);

    // 3. store random value in pivot_value
    pivot_value = arr[last];

    // 4. Set iteration index to first - 1
    iteration_index = first - 1;
    for(int i = first; i < last; i++){
        // Check if arr[i] value is less than arr[pivot]
        if(arr[i] <= pivot_value){
            iteration_index++;
            swap(arr[iteration_index], arr[i]);
        }
    }
    swap(arr[iteration_index + 1], arr[last]);
    return (iteration_index + 1);
}

void min_heapsort_measurement(){
    clock_t start, end;
    start = clock();
    min_heap_sort(arr0, 50);
    end = clock();
    time_elapsed[0] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[0]);

    start = clock();
    min_heap_sort(arr1, 500);
    end = clock();
    time_elapsed[1] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[1]);

    start = clock();
    min_heap_sort(arr2, 5000);
    end = clock();
    time_elapsed[2] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[2]);

    start = clock();
    min_heap_sort(arr3, 10000);
    end = clock();
    time_elapsed[3] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[3]);
}

void max_heapsort_measurement(){
    clock_t start, end;
    start = clock();
    max_heap_sort(arr0, 50);
    end = clock();
    time_elapsed[0] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[0]);

    start = clock();
    max_heap_sort(arr1, 500);
    end = clock();
    time_elapsed[1] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[1]);

    start = clock();
    max_heap_sort(arr2, 5000);
    end = clock();
    time_elapsed[2] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[2]);

    start = clock();
    max_heap_sort(arr3, 10000);
    end = clock();
    time_elapsed[3] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[3]);
}
void max_heapsort_recursively_measurement(){
    clock_t start, end;
    start = clock();
    max_heap_sort_recursively(arr0, 50);
    end = clock();
    time_elapsed[0] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[0]);

    start = clock();
    max_heap_sort_recursively(arr1, 500);
    end = clock();
    time_elapsed[1] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[1]);

    start = clock();
    max_heap_sort_recursively(arr2, 5000);
    end = clock();
    time_elapsed[2] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[2]);

    start = clock();
    max_heap_sort_recursively(arr3, 10000);
    end = clock();
    time_elapsed[3] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[3]);
}

void randomized_quicksort_measurement(){
    clock_t start, end;
    start = clock();
    randomized_quicksort(arr0, 0, 49);
    end = clock();
    time_elapsed[0] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[0]);

    start = clock();
    randomized_quicksort(arr1, 0, 499);
    end = clock();
    time_elapsed[1] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[1]);

    start = clock();
    randomized_quicksort(arr2, 0, 4999);
    end = clock();
    time_elapsed[2] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[2]);

    start = clock();
    randomized_quicksort(arr3, 0, 9999);
    end = clock();
    time_elapsed[3] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[3]);
}

void d_array_max_heapsort_measurement(){
    clock_t start, end;
    start = clock();
    d_array_max_sort(arr0, 50, 5);
    end = clock();
    time_elapsed[0] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[0]);
    for(int i = 1; i < 51; i++){
        if(i%15 == 0) printf("\n");
        printf("%d ", arr0[i-1]);
    }

    start = clock();
    d_array_max_sort(arr1, 500, 5);
    end = clock();
    time_elapsed[1] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[1]);

    start = clock();
    d_array_max_sort(arr2, 5000, 5);
    end = clock();
    time_elapsed[2] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[2]);

    start = clock();
    d_array_max_sort(arr3, 10000, 5);
    end = clock();
    time_elapsed[3] = (end - start)/(double)CLOCKS_PER_SEC;
    printf("time elapsed : %2.7lf\n", time_elapsed[3]);
}
