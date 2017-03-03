#include <list>
#include <cstdio>
#include <iostream>
using namespace std;
int func(int *arr){
    list<int> mess(arr, arr+10);
    for(list<int>::iterator it = mess.begin(); it != mess.end(); ++it){
        printf("%d ", *it);
    }
    return 0;
}
int main(int argc, char const *argv[]) {
    int arr[10] = {3, 6, 2, 3, 6, 1, 9, 22, 1, 69};
    sort(arr, arr+5);
    func(arr);
    return 0;
}
