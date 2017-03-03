#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

string file_names[1] = {"input_small.txt"};
int file_count = (int)sizeof(file_names)/sizeof(file_names[0]);
vector<vector<int>> arr;

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

// Struct 'node' declaration. it has integer value with its left, right child pointer.
struct node{
	int value;
	struct node *left;
	struct node *right;
}*root;

// Class 'BinarySearchTree' declaration. 
class BinarySearchTree{
	public :
		BinarySearchTree(){
			root = NULL;
		}

		void insert(node *, node *);
		void find_value(int, node **, node **);
		void move_rightmost(node **, node **);
		void move_leftmost(node **, node **);
		void remove(int);
		void remove_case_one(node *, node *);
		void remove_case_two(node *, node *);
		void remove_case_three(node *, node *);
		void printBST(node *);
};

// find_value function : find integer target from tree
// parameter as double pointer (parent, current), returned by address
void BinarySearchTree::find_value(int target, node **parent, node **current){
	node *point, *upper_point;
	if(root == NULL){
		*current = NULL;
		*parent = NULL;
		printf("root is null(while find_value)\n");
		return;
	}
	if(target == root->value){
		*current = root;
		*parent = NULL;
		return;
	}
	if(target < root->value){
		point = root->left;
	}
	else{
		point = root->right;
	}
	upper_point = root;

	// Find left when target value < current node value 
	// Find right when target value > current node value while
	// node reachs the bottom of tree
	while(point != NULL){
		if(target == point->value){
			*current = point;
			*parent = upper_point;
			return;
		}
		upper_point = point;
		if(target < point->value){
			point = point->left;
		}
		else{
			point = point->right;
		}
	}
	// In case that cannot found target value in tree :
	*current = NULL;
	*parent = upper_point;

}

void BinarySearchTree::insert(node *tree, node *input_node){
	// If root is NULL
	if(root == NULL){
		root = new node;
		root->value = input_node->value;
		root->left = NULL;
		root->right = NULL;
		printf("Root node %d added\n", root->value);
		return;
	}
	
	// Refusing insert while recursive call
	if(tree->value == input_node->value){
		printf("duplicated element. : %d\n", tree->value);
		return;
	}
	
	// If current node value > new node value, go left-down.
	if(tree->value > input_node->value){
		
		// When it has left child, call left child as tree recursively.
		if(tree->left != NULL){
			insert(tree->left, input_node);
		}

		// When it doesn't has left child, insert into it.
		else{
			tree->left = input_node;
			(tree->left)->left = NULL;
			(tree->left)->right = NULL;
			printf("input completed.: %d\n", input_node->value);
			return;
		}
	}
	// If current node value < new node value, go right-down.
	else{

		// When it has right child, call right child as tree recursively.
		if(tree->right != NULL){
			insert(tree->right, input_node);
		}	

		// When it doesn't has right child, insert into it.
		else{
			tree->right = input_node;
			(tree->right)->left = NULL;
			(tree->right)->right = NULL;
			printf("input completed.: %d\n", input_node->value);
			return;
		}
	}
}

// In case of remove, there're three cases about status of child,
// :only one child, both children, doesn't have child
void BinarySearchTree::remove(int wanted_value){
	node *parent, *current;
	if(root == NULL){
		printf("tree is empty.\n");
		return;
	}
	// Find wanted value, set address to pointer variable parent, current
	find_value(wanted_value, &parent, &current);
	if(current == NULL){
		printf("item doesn't exist in tree.");
		return;
	}
	// If current doesn't have any child
	if(current->left == NULL && current -> right == NULL) {
		remove_case_one(parent, current);
	}
	// If current has only one child
	else if(current->left != NULL && current->right != NULL){
		remove_case_two(parent, current);
	}
	// If current has both children
	else{
		remove_case_three(parent, current);
	}
	// deallocate current object in memory
	free(current);
	printf("[value %d removed successfully.]\n", wanted_value);
}

// Move current and its parent pointer to rightmost.
void BinarySearchTree::move_rightmost(node **parent, node **current){
	node *point_parent = *parent, *point = *current;
	while(point->right != NULL){
		point_parent = point;
		point = point->right;

	}
	*current = point;
	*parent = point_parent;
}


// Move current and its parent pointer to leftmost.
void BinarySearchTree::move_leftmost(node **parent, node **current){
	node *point_parent = *parent, *point = *current;
	while(point->left != NULL){
		point_parent = point;
		point = point->left;
	}
	*current = point;
	*parent = point_parent;
}

// case one : target node doesn't have any child
void BinarySearchTree::remove_case_one(node *parent, node *current){
	if(parent == NULL){
		root = NULL;
		return;
	}
	// if current node was left child of parent, 
	if(current == parent->left){
		parent->left = NULL;
	}
	// if current node was right child of parent,
	else{
		parent->right = NULL;
	}
}

// Case two : target node has both children
void BinarySearchTree::remove_case_two(node *parent, node *current){
	node *point, *point_parent, *temp, *temp_parent;
	point_parent = current;
	point = current->right;
	move_leftmost(&point_parent, &point);
	temp = point;
	temp_parent = point_parent;
	if(temp->left == NULL && temp->right == NULL){
		remove_case_one(temp_parent, temp);
	}
	else{
		remove_case_three(temp_parent, temp);
	}
	if(parent == NULL){
		root = temp;
	}
	else{
		if(current == parent->left){
			parent->left = temp;
		}
		else{
			parent->right = temp;
		}
	}
	temp->left = current->left;
	temp->right = current->right;
}

// Case three : target node has only one child
void BinarySearchTree::remove_case_three(node *parent, node *current){
	node *child;
	if(current->left != NULL){
		child = current->left;
	}
	else{
		child = current->right;
	}
	if(parent == NULL){
		root = child;
	}
	else{
		if(current == parent->left){
			parent->left = child;
		}
		else{
			parent->right = child;
		}
	}
}

void printBST(node *current){
	if(root == NULL){
		printf("Tree is empty\n");
		return;
	}
	if(current != NULL){
		printBST(current->left);
		printf("%d ", current->value);
		printBST(current->right);
	}
}

int main(){
	// Load inputs from ".input/small_inputs.txt"
	load_inputs();

	// Create BinarySearchTree object
	BinarySearchTree bst;

	// insert all elements in input vector 'arr'
			++inner_it){
			node *temp = new node;
			temp->value = *inner_it;
			bst.insert(root, temp);
		}
	}
	bst.remove(15);
	bst.remove(40);
	bst.remove(206);
	bst.remove(100);
	printBST(root);
	printf("\n");
}


