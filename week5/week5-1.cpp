#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <vector>
using namespace std;
int arr0[51], arr1[501], arr2[5001], arr3[10001];

void load_50(){
    freopen("input/input50.txt", "r", stdin);
    for(int i = 0; i < 50; i++){
        scanf("%d", &arr0[i]);
    }
}
void load_500(){
    freopen("input/input500.txt", "r", stdin);
    for(int i = 0; i < 500; i++){
        scanf("%d", &arr1[i]);
    }
}
void load_5000(){
    freopen("input/input5000.txt", "r", stdin);
    for(int i = 0; i < 5000; i++){
        scanf("%d", &arr2[i]);
    }
}
void load_10000(){
    freopen("input/input10000.txt", "r", stdin);
    for(int i = 0; i < 10000; i++){
        scanf("%d",  &arr3[i]);
    }
}

void load_inputs(){
    load_50();
    load_500();
    load_5000();
    load_10000();
}

void printing_result(int find, int source, int result, double time_elapsed){
    printf("select %dth in input %d : (%5d), time: %.7lf\n", find, source, result, time_elapsed);
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int randomized_partition(int *arr, int first_index, int last_index){
    srand(time(NULL));
    int random_pivot, iteration_index, pivot_value;

    // 1. Select randomized pivot. from rand()%number, expected result will be (0 to (number-1))
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

// If target = 5, find 5th smallest value.
int randomized_selection(int *arr, int first_index, int last_index, int target){

    // If array has only one value, return it.
    if(first_index == last_index){
        return arr[first_index];
    }

    // Choose random pivot with partitioning.
    int pivot = randomized_partition(arr, first_index, last_index);

    // Count the number of elements located left side from pivot
    int left_count = pivot - first_index;

    // If target(ith smallest number)==left_count+1,
    // conclude it's exactly pointing the target.
    if(target == left_count + 1){
        return arr[pivot];

    // There must be answer which we seeking inside left side, so drop the right_side.
    }else if(target < left_count + 1){
        return randomized_selection(arr, first_index, pivot - 1, target);

    // As we already know answer is nowhere in left_side, subtract left_count from target and
    // proceed pivot+1 to last_index.
    }else{//(pivot < target - 1)
        return randomized_selection(arr, pivot + 1, last_index, (target-pivot+first_index-1));
    }
}
double avg_time_5times(int *arr, int first, int last, int target){
    clock_t start, end;
    double time_elapsed = 0;
    for(int i = 0; i < 5; i++){
        switch (last) {
            case 49 :
                load_50();
                break;
            case 499 :
                load_500();
                break;
            case 4999 :
                load_5000();
                break;
            case 9999 :
                load_10000();
                break;
        }
        start = clock();
        randomized_selection(arr, first, last, target);
        end = clock();
        time_elapsed += (end - start)/(double)CLOCKS_PER_SEC;
    }
    time_elapsed /= 5;
    return time_elapsed;

}

void randomized_selection_measurement(){
    int result[4][5];
    double time_elapsed[4][5];

    // Select '10th smallest' in input50.txt
    result[0][0] = randomized_selection(arr0, 0, 49, 10);
    time_elapsed[0][0] = avg_time_5times(arr0, 0, 49, 10);
    printing_result(10, 50, result[0][0], time_elapsed[0][0]);

    // Select '25th smallest' in input50.txt
    result[0][1] = randomized_selection(arr0, 0, 49, 25);
    time_elapsed[0][1] = avg_time_5times(arr0, 0, 49, 25);
    printing_result(25, 50, result[0][1], time_elapsed[0][1]);

    // Select '30th smallest' in input50.txt
    result[0][2] = randomized_selection(arr0, 0, 49, 30);
    time_elapsed[0][2] = avg_time_5times(arr0, 0, 49, 30);
    printing_result(30, 50, result[0][2], time_elapsed[0][2]);


    // Select '100th smallest' in input500.txt
    result[1][0] = randomized_selection(arr1, 0, 499, 100);
    time_elapsed[1][0] = avg_time_5times(arr1, 0, 499, 100);
    printing_result(100, 500, result[1][0], time_elapsed[1][0]);

    // Select '250th smallest' in input500.txt
    result[1][1] = randomized_selection(arr1, 0, 499, 250);
    time_elapsed[1][1] = avg_time_5times(arr1, 0, 499, 250);
    printing_result(250, 500, result[1][1], time_elapsed[1][1]);

    // Select '300th smallest' in input500.txt
    result[1][2] = randomized_selection(arr1, 0, 499, 300);
    time_elapsed[1][2] = avg_time_5times(arr1, 0, 499, 300);
    printing_result(300, 500, result[1][2], time_elapsed[1][2]);


    // Select '1000th smallest' in input5000.txt
    result[2][0] = randomized_selection(arr2, 0, 4999, 1000);
    time_elapsed[2][0] = avg_time_5times(arr2, 0, 4999, 1000);
    printing_result(1000, 5000, result[2][0], time_elapsed[2][0]);

    // Select '2500th smallest' in input5000.txt
    result[2][1] = randomized_selection(arr2, 0, 4999, 2500);
    time_elapsed[2][1] = avg_time_5times(arr2, 0, 4999, 2500);
    printing_result(2500, 5000, result[2][1], time_elapsed[2][1]);

    // Select '3000th smallest' in input5000.txt
    result[2][2] = randomized_selection(arr2, 0, 4999, 3000);
    time_elapsed[2][2] = avg_time_5times(arr2, 0, 4999, 3000);
    printing_result(3000, 5000, result[2][2], time_elapsed[2][2]);


    // Select '1000th smallest' in input10000.txt
    result[3][0] = randomized_selection(arr3, 0, 9999, 1000);
    time_elapsed[3][0] = avg_time_5times(arr3, 0, 9999, 1000);
    printing_result(1000, 10000, result[3][0], time_elapsed[3][0]);

    // Select '2500th smallest' in input10000.txt
    result[3][1] = randomized_selection(arr3, 0, 9999, 2500);
    time_elapsed[3][1] = avg_time_5times(arr3, 0, 9999, 2500);
    printing_result(2500, 10000, result[3][1], time_elapsed[3][1]);

    // Select '5000th smallest' in input10000.txt
    result[3][2] = randomized_selection(arr3, 0, 9999, 5000);
    time_elapsed[3][2] = avg_time_5times(arr3, 0, 9999, 5000);
    printing_result(5000, 10000, result[3][2], time_elapsed[3][2]);

    // Select '7000th smallest' in input10000.txt
    result[3][3] = randomized_selection(arr3, 0, 9999, 7000);
    time_elapsed[3][3] = avg_time_5times(arr3, 0, 9999, 7000);
    printing_result(7000, 10000, result[3][3], time_elapsed[3][3]);

    // Select '9000th smallest' in input10000.txt
    result[3][4] = randomized_selection(arr3, 0, 9999, 9000);
    time_elapsed[3][4] = avg_time_5times(arr3, 0, 9999, 9000);
    printing_result(9000, 10000, result[3][4], time_elapsed[3][4]);


}

int main(int argc, char const *argv[]) {
    load_inputs();
    randomized_selection_measurement();
    return 0;
}
