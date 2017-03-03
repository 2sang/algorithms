#include "algorithms.h"
#include <stdio.h>
void read_inputs(int *arr_small, int *arr_middle);
void print_array(int *arr, int last_index);
int arr_small[20];
int arr_middle[70];
int arr_small_count, arr_middle_count;

int main(int argc, char const *argv[]) {
    int alg_number;
    read_inputs(arr_small, arr_middle);
    printf("1. selection sort\n2. recursive binary search\n3. insertion with merge sort\nelse to quit, input the number...");
    scanf("%d", &alg_number);

    // After sorting or searching, print each arrays
    if (alg_number == 1) {
        selection_sort(arr_small, arr_small_count);
        print_array(arr_small, arr_small_count);
    }else if (alg_number == 2){
        selection_sort(arr_small, arr_small_count);
        recursive_binary_search(arr_small, 152, 0, arr_small_count-1);
        print_array(arr_small, arr_small_count);
    }else if (alg_number == 3){
        insertion_with_merge_sort(arr_middle, 0, arr_middle_count);
        print_array(arr_middle, arr_middle_count);
    }else {
        printf("end of program.\n");
    }
    return 0;
}


// Read inputs from file. - small arr, middle arr
void read_inputs(int *arr_small, int *arr_middle){
    FILE *file_small = fopen("input_small.txt", "r");
    FILE *file_middle = fopen("input_middle.txt", "r");
    int index_small = 0, index_middle = 0;

    while(!feof(file_small)){
        fscanf(file_small, "%d", &arr_small[index_small]);
        index_small++;
    }
    arr_small_count = index_small;

    while(!feof(file_middle)){
        fscanf(file_middle, "%d", &arr_middle[index_middle]);
        index_middle++;
    }
    arr_middle_count = index_middle;
}

// Print result array.
void print_array(int *arr, int last_index){
    int i;
    printf("printing array items :\n");
    for(i = 0; i < last_index; i++){
        printf("%d\n", arr[i]);
    }
    printf("\n");
}
