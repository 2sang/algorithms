#include <stdio.h>
#include <string.h>

#define MAX_SUBLIST_SIZE 4

// Memory swap function.
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

/*
 Merge [first, mid] with [mid+1, first].
 permanently manipulate memories with memcpy()
*/
void merge(int *arr, int first, int mid, int last){
    printf("merging(%d, %d, %d)\n", first, mid, last);
    int arr_temp[100];
    int sublist_size = last - first;
    int r_index = mid, l_index = first, result_index = 0;
    while(l_index < mid || r_index < last){

        // End condition : if left or right array reached end of each arr.
        if (l_index == mid){
            while(r_index != last){
                arr_temp[result_index++] = arr[r_index++];
            }
            memcpy(arr+first, arr_temp, sizeof(int)*sublist_size);
            return;
        }
        if (r_index == last){
            while(l_index != mid){
                arr_temp[result_index++] = arr[l_index++];
            }
            memcpy(arr+first, arr_temp, sizeof(int)*sublist_size);
            return;
        }

        // Sorting through comparing left and right array.
        if(arr[l_index] <= arr[r_index]){
            arr_temp[result_index++] = arr[l_index++];
        }else{
            arr_temp[result_index++] = arr[r_index++];
        }
    }
    memcpy(arr+first, arr_temp, sizeof(int)*sublist_size);
    return;
}

// Insertion sort using swap(). up to (arr + arr_size)
void insertion_sort(int * arr, int arr_size){
    int i, j;
    for(int i = 1; i < arr_size; i++){
        for(int j = i; j > 0; j--){
            if(arr[j-1] > arr[j]){
                swap(&arr[j-1], &arr[j]);
            }
        }
    }
}

// Selection sort. up to (arr + last_index)
void selection_sort(int *arr, int last_index){
    int i, j, min_index;
    for(i = 0; i < last_index-1; i++){
        min_index = i;
        for(j = i + 1; j < last_index; j++){
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        swap(&arr[min_index], &arr[i]);
    }
}

// Binary search recursively.
int recursive_binary_search(int *arr, int item, int first, int last){
    printf("in range [%d to %d], finding %d\n", first, last, item);
    int mid, i;
    if (first > last){
        return -1;
    }
    mid = (first + last) / 2;
    if(arr[mid] == item){
        printf("item found. at index %d\n", mid);
        return mid;
    }else if(arr[mid] > item){
        printf("arr[mid]>item, searching left.\n");
        recursive_binary_search(arr, item, first, mid - 1);
    }else{
        printf("arr[mid]<item, searching right.\n");
        recursive_binary_search(arr, item, mid + 1, last);
    }
    return 0;
}

/*
Insertion sort with merge sort :
1. Split until sublist_size <= 4,
2. Sort sublists using insertion sort
3. merge sublists into one final list recursively.
*/
void insertion_with_merge_sort(int *arr, int first, int last){
    int sublist_size = last - first;
    if (sublist_size <= MAX_SUBLIST_SIZE){
        insertion_sort(&arr[first], sublist_size);
        return;
    }else{
        int mid = (first + last) / 2;// ex) 0 ~ 7 index -> mid == 3
        insertion_with_merge_sort(arr, first, mid+1);
        insertion_with_merge_sort(arr, mid+1, last);
        merge(arr, first, mid+1, last);
    }
}
