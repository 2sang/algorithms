#include <iostream>
#include <dirent.h>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <ctime>
using namespace std;
vector<string> input_file_listing();
pair<string, int> file_info_define(vector<string> dirlist);
void import_files(pair<string, int> file_info);
void read_inputs(vector<int> array, int cnt);
void swap(int *x, int *y);
void heapsort_measurement();
void heap_sort(int *a, int i);
void heapify(int *a, int k, int n);
void randomized_quicksort();
double time_elapsed[4];
pair<string, int> *file_info;
vector<int> arrays[4];
pair<const char*, int> define_inputfile(const char* filename, int items){
    return make_pair(filename, items);
}


//////////////////// Main() ////////////////////////
int main(int argc, char const *argv[]) {
    // Read all files into vector arrays
    file_info = &file_info_define(input_file_listing());
    import_files(file_info);

    // heapsort with time measurement
    //heapsort_measurement();

    // Re-initialize global arrays
    //import_files();
    //quicksort_measurement();

    return 0;
}
/////////////////////////////////////////////////////
vector<string> input_file_listing(){
    DIR *d;
    vector<string> dirlist;
    struct dirent *dir;
    int i = 0;
    d = opendir("input/");
    if (d){
        while ((dir = readdir(d)) != NULL){
            i++;
            dirlist.push_back(dir->d_name);
        }
        for(int i = 0; i < dirlist.size(); i++){
            cout << dirlist[i] << endl;
        }
        closedir(d);
    }
    return dirlist;
}

pair<string, int> file_info_define(vector<string> dirlist){
    file_info = new pair<string, int>[dirlist.size()];
    for(int i = 0; i < dirlist.size(); i++){
        file_info[i].first = dirlist[i];
        file_info[i].second = 50;
    }
    return *file_info;
}

void import_files(pair<string, int> file_info){
    for(int i = 0; i < 4; i++){
        freopen(file_info[i].first.c_str(), "r", stdin);
        read_inputs(arrays[i], file_info[i].second);
    }
}

void read_inputs(vector<int> array, int cnt){
    int number;
    for(int i = 0; i < cnt; i++){
        scanf("%d", &number);
        array.push_back(number);
    }
}
/*
void heapsort_measurement(){
    clock_t start, end;
    for(int i = 0; i < 4; i++){
        start = clock();
        heap_sort(arrays[i], file_info[i].second);
        end = clock();
        time_elapsed[i] = (end - start)/(double)CLOCKS_PER_SEC;
        printf("time elapsed : %2.7lf\n", time_elapsed[0]);
    }
}
*/
