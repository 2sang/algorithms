#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef struct work{
	int start_point;
	int end_point;
} work;

typedef vector<work> works;

void load_inputs(works* activities, int* activity_count){
	freopen("sample_selection.txt", "r", stdin);
	scanf("%d", activity_count);
	// since both points starts from index 1, insert first dummy -1s.
	work dummy_work;
	dummy_work.start_point = -1;
	dummy_work.end_point = -1;
	activities->push_back(dummy_work);
	for(int i = 0; i < *activity_count; i++){
		work w;
		int start, end;
		scanf("%d %d", &start, &end);
		w.start_point = start;
		w.end_point = end;
		activities->push_back(w);
	}
}

works greedy_activity_selector(works* all_works, int activity_count){
	works activity_queue;
	activity_queue.push_back((*all_works)[1]);
	int k = 1;
	for(int m = 2; m <= activity_count; m++){
		if((*all_works)[m].start_point >= (*all_works)[k].end_point){
			activity_queue.push_back((*all_works)[m]);
			k = m;
		}
	}
	return activity_queue;
}
int main(void){
	works input_activities;
	works result_activities;
	int activity_count;
	load_inputs(&input_activities, &activity_count);
	result_activities = greedy_activity_selector(&input_activities, activity_count);
	for(int i = 0; i < result_activities.size(); i++){
		printf("%d %d\n", result_activities[i].start_point, result_activities[i].end_point);
	}
	return 0;
}
