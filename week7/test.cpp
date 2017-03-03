#include <iostream>
#include <vector>
using namespace std;
struct node{
	int value;
	node* parent;
};
void swap(node *x, node *y){
	node temp = *x;
	*x = *y;
	*y = temp;
}

int func(node* child){
	while(child->parent){
		child = child->parent;
	}
	printf("%d", child->value);
	return 0;
}
int main(){

	node root;
	root.value =  3;
	root.parent = 0;
	node sample;
	sample.value = 4;
	sample.parent = &root;
	func(&sample);

	return 0;
}
