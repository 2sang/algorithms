#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
#define ITER vector<int>::iterator
#define R_ITER vector<int>::reverse_iterator
#define FOR_EACH_FORWARD(iter, vec) for(iter = vec.begin(); iter != vec.end(); ++iter)
#define FOR_EACH_BACKWARD(iter, vec) for(iter = vec.rbegin(); iter != vec.rend(); ++iter)

using namespace std;

string file_names[4] = {"input50.txt", "input500.txt", "input5000.txt", "input10000.txt"};
int file_count = (int)sizeof(file_names)/sizeof(file_names[0]);
vector<vector<int>> arr;

void banner(const char* string){
    printf("\n***********%s*************\n", string);
}

// Printing vector values using iterator
void printing_vector(vector<int> vec){
    ITER it;
    FOR_EACH_FORWARD(it, vec){
        printf("%d ", *it);
    }
}

// Printing array values
void printing_array(int *arr, int size){
    for(int i = 1; i <= size; i++){
        printf("%d ", arr[i-1]);
        if(i % 10 == 0) printf("\n");
    }
    printf("\n");
}

// Find max value in vector<int>
int find_max(vector<int> vec){
    int max = 0;
    ITER it;
    FOR_EACH_FORWARD(it, vec){
        if(*it > max) max = *it;
    }
    return max;
}

// return number of digits (degree)
int find_degree(int number){
    int degree = 0;
    for(int i = 1; i < 1000000; i*=10){
        if (number/i != 0) degree++;
    }
    return degree;
}

// ex) number_at(1523, 3) returns 5 which located third place from rightmost character
int number_at(int original, int location){
    int power = (int)pow(10, location);
    return (original%power)/(power/10);
}



void load_inputs(){
    int unit_number;

    // For each files
    for(int i = 0; i < file_count; i++){

        vector<int> numbers;
        string input_path = "input/" + file_names[i];

        // Refresh file buffer with changed "input_path" file
        freopen(input_path.c_str(), "r", stdin);

        // Iterate until EOF
        int scan_ret = scanf("%d", &unit_number);
        while(scan_ret == 1){
            numbers.push_back(unit_number);
            scan_ret = scanf("%d", &unit_number);
        }
        // push_back each 'numbers' vector into 'arr' vector
        // which owns type vector<int> as element.
        arr.push_back(numbers);
    }
}

void counting_sort(vector<int> array){
    // Find max value in original array.
    int maxvalue_in_array = find_max(array);

    // Declare counting_array, result_array dynamically.
    int *counting_array = new int[maxvalue_in_array+1];
    int *result_array = new int[array.size()];

    // Initialize counting_array by 0
    memset(counting_array, 0, sizeof(int)*(maxvalue_in_array+1));

    // 1. Apply frequencies of elemenets into counting_array
    ITER it;
    FOR_EACH_FORWARD(it, array){
        counting_array[*it]++;
    }

    // 2. Accumulate counting_array values consecutively for index use
    for(int i = 0; i < maxvalue_in_array; i++){
        counting_array[i+1] += counting_array[i];
    }

    // 3. Sort original values using accumulated counting_array
    R_ITER r_it;
    FOR_EACH_BACKWARD(r_it, array){
        result_array[--counting_array[*r_it]] = *r_it;
    }

    // Printing result array of input50.txt
    if(array.size() == 50) printing_array(result_array, 50);

    // Delete dynamically allocated memory.
    delete[] counting_array;
    delete[] result_array;
}

void radix_sort(vector<int> array){
    // Find max value in original array.
    int degree = find_degree(find_max(array));

    // Declare counting_array, result_array dynamically.
    int *source_array = new int[array.size()];
    int *radix_array = new int[10];
    int *result_array = new int[array.size()];

    // Init source_array synchronize with parameter vecter 'array'
    copy(array.begin(), array.end(), source_array);

    // For all single figures in each number
    for(int d = 1; d <= degree; d++){

        // 1. Initialize radix_array all by 0
        memset(radix_array, 0, sizeof(int)*10);

        // 2. Apply frequencies of elemenets into radix_array
        for(int i = 0; i < array.size(); i++){
            radix_array[number_at(source_array[i], d)]++;
        }

        // 3. Accumulate radix_array values consecutively for index use
        for(int i = 0; i < 9; i++){
            radix_array[i+1] += radix_array[i];
        }

        // 4. Sort by one single figure using accumulated counting_array
        for(int i = array.size() - 1; i >= 0; i--){
            int single_figure = number_at(source_array[i], d);
            result_array[--radix_array[single_figure]] = source_array[i];
        }
        // 5. Copy dest array to source array, iterate through all number figures
        if(d != degree) memcpy(source_array, result_array, sizeof(int)*array.size());
    }
    if(array.size() == 50) printing_array(result_array, 50);

    // Delete dynamically allocated memory.
    delete[] source_array;
    delete[] radix_array;
    delete[] result_array;
}

void bucket_sort(vector<int> array){
    // Find max value in parameter array.
    int maxvalue_in_array = find_max(array);

    // Declare vector that has vector<int> as element.
    int *result_array = new int[array.size()];
    vector<vector<int>> result_list(array.size());
    vector<int> bucket;
    ITER it;

    // Initialize result_list vector - push all sub-vectors into it.
    FOR_EACH_FORWARD(it, array){
        result_list.push_back(bucket);
    }

    // Iterate through original array.
    FOR_EACH_FORWARD(it, array){

        // Calculate adjusted index, store into result_index
        int result_index = ((*it)*(array.size()) / (maxvalue_in_array+1));

        // Store pointers at unit_vector for comparison within sub-vectors
        vector<int> *unit_vector = &result_list[result_index];

        if(!unit_vector->empty()){

            // Start with beginning index of unit_vector
            ITER inner_it = unit_vector->begin();

            // If first element is larger than *it, insert to beginning index.
            if(*inner_it > *it){
                unit_vector->insert(inner_it, *it);

            }else{
                // Else, Search appropriate index
                while(inner_it != unit_vector->end() && (*inner_it < *it)){
                    ++inner_it;
                }

                // And insert
                unit_vector->insert(inner_it, *it);
            }

        // If unit_vector is empty, just push into it.
        }else{
            unit_vector->push_back(*it);
        }
    }

    // Printing with nested iteration.
    if(array.size() == 50){
        int count = 0;
        vector<vector<int>>::iterator it1;
        ITER it2;
        FOR_EACH_FORWARD(it1, result_list){
            for(it2 = it1->begin(); it2 != it1->end(); ++it2){
                if(count % 10 == 0) printf("\n");
                printf("%d ", * it2);
                count++;
            }
        }
        printf("\n");
    }


}
double avg_time_5times(vector<int> array, char c){
    double time_elapsed = 0;
    clock_t start, end;

    for(int i = 0; i < 5; i++){
        load_inputs();
        start = clock();
        switch (c) {
            case 'c' :
                counting_sort(array);
                break;
            case 'b' :
                bucket_sort(array);
                break;
            case 'r' :
                radix_sort(array);
                break;
        }
        end = clock();
        time_elapsed += (end - start)/(double)CLOCKS_PER_SEC;
        arr.clear();
    }
    time_elapsed /= 5;
    return time_elapsed;
}

void counting_sort_measurement(){
    banner("counting_sort");
    double time_elapsed[file_count];
    for(int i = 0; i < file_count; i++){
        load_inputs();
        time_elapsed[i] = avg_time_5times(arr[i], 'c');
        printf("elapsed time while %dth counting sort : %lf\n", i, time_elapsed[i]);
    }
}

void radix_sort_measurement(){
    load_inputs();
    banner("radix sort");
    double time_elapsed[file_count];
    for(int i = 0; i < file_count; i++){
        load_inputs();
        time_elapsed[i] = avg_time_5times(arr[i], 'r');
        printf("elapsed time while %dth radix sort : %lf\n", i, time_elapsed[i]);
    }
}

void bucket_sort_measurement(){
    load_inputs();
    banner("bucket sort");
    double time_elapsed[file_count];
    for(int i = 0; i < file_count; i++){
        load_inputs();
        time_elapsed[i] = avg_time_5times(arr[i], 'b');
        printf("elapsed time while %dth counting sort : %lf\n", i, time_elapsed[i]);
    }
    arr.clear();
}

int main(int argc, char const *argv[]) {
    load_inputs();
    counting_sort_measurement();
    radix_sort_measurement();
    bucket_sort_measurement();
    return 0;
}
