#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int tc;
	int test_count = 1;
	freopen("frog_input.txt", "r", stdin);
	scanf("%d", &tc);
	while(tc--){
		int stone_count;
		vector<int> stone_location_list;
		scanf("%d", &stone_count);
		int max_jump_value;
		int jump_count = 0;
		int current_frog_location = 0;
		int dist_btwin_stone = 0;
		bool unreachable = false;

		// input stone, frog status
		for(int i = 0; i < stone_count; i++){
			int stone_location;
			scanf("%d", &stone_location);
			stone_location_list.push_back(stone_location);
		}
		scanf("%d", &max_jump_value);
		// Jump while frog reaches the last stone.
		while(current_frog_location != stone_location_list[stone_count-1] && !unreachable){
			int max_reachable_location = current_frog_location + max_jump_value;
			while(find(stone_location_list.begin(), stone_location_list.end(), max_reachable_location) 
				== stone_location_list.end()){
				max_reachable_location--;
				if(max_reachable_location == current_frog_location){
					unreachable = true;
					break;
				}
			}
			current_frog_location = max_reachable_location;
			jump_count++;
		}
		printf("Case #%d\n", test_count++);
		if(unreachable) printf("-1\n");
		else printf("%d\n", jump_count);
	}
	return 0;
}
