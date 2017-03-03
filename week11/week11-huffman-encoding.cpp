#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef struct node{
	node* left;
	node* right;
	char letter;
	int freq;
}node;

typedef vector<node> node_queue;
// static var for encoding
vector<pair<char, string> > output_pair;

string print_codes(node* n, string code){	
	if(n->letter != '-' && n->left == NULL && n->right == NULL){
		printf("[%c:%d] ", n->letter, n->freq);
		cout << "code : " << code << endl;
		output_pair.push_back(make_pair(n->letter, code));
		return code;
	}else{
		print_codes(n->left, code + "0");
		print_codes(n->right, code + "1");
	}
	return "";
}

// push, keep ascending order
void push_orderly(node_queue* queue, node* n){
	if(queue->empty()){
		queue->push_back(*n);
		return;
	}
	node_queue::iterator it = queue->begin();
	while((*it).freq < n->freq && it != queue->end()){
		it++;
	}
	queue->insert(it, *n);
}
node* extract_min(node_queue* queue){
	node_queue::iterator it = queue->begin();
	node* extracted_node = new node;
	*extracted_node = (*it);
	queue->erase(it);
	return extracted_node;
}

void load_inputs(node_queue* queue, int* letter_count){
	freopen("sample_huffman.txt", "r", stdin);
	scanf("%d", letter_count);
	for(int i = 0; i < *letter_count; i++){
		char letter;
		int freq;
		scanf(" %c %d", &letter, &freq);
		node *n = new node;
		n->left = NULL;
		n->right = NULL;
		n->letter = letter;
		n->freq = freq;
		push_orderly(queue, n);
	}
}
node* huffman(node_queue* queue){
	int letter_count = queue->size();
	for(int i = 0; i < letter_count - 1; i++){
		node *x, *y;
		node *z = new node;
		
		// extract least frequent character, form to left child
		x = extract_min(queue);
		z->left = x;

		// extract least frequent character, form to right child
		y = extract_min(queue);
		z->right = y;

		// form freq of parent node.
		z->freq = x->freq + y->freq;
		z->letter = '-';

		// push to original queue
		push_orderly(queue, z);
	}
	return extract_min(queue);
}
void encode_string(string s){
	for(int s_index = 0 ; s_index < s.length(); s_index++){
		for(int i = 0; i < output_pair.size(); i++){
			if(s[s_index]==output_pair[i].first){
				cout << output_pair[i].second << " ";
				break;
			}
		}
	}
}
int main(void){
	node_queue priority_queue;
	int letter_count;
	load_inputs(&priority_queue, &letter_count);
	node* result_node = huffman(&priority_queue);
	print_codes(result_node, "");
	encode_string("baaeabda");
	return 0;
}


