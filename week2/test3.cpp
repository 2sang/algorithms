#include <dirent.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
int main(void)
{
    DIR *d;
    struct dirent *dir;
    vector<string> dirlist;
    int i=0;
    d = opendir("input/");
    if (d){
        while ((dir = readdir(d)) != NULL){
            i++;
            //cout<<dir->d_name<<endl;
            dirlist.push_back(dir->d_name);
        }
        for(int i = 0; i < dirlist.size(); i++){
            cout << dirlist[i] << endl;
        }
        closedir(d);
    }

    return(0);
}
