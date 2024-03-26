#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<queue>
#define MaxLength 100
using namespace std;

//Khai bao cau truc trang thai
typedef struct{
	int ly[6];
}State;

//Khoi tao trang thai
void makeNullState(State *state){
	int i;
	for(i = 0; i <= 5; i++){
		state->ly[i] = 9999;
	}
}

//In trang thai
void printState(State state){
	printf("\n[%d, %d, %d, %d, %d, %d]",  state.ly[0], state.ly[1],
	                                      state.ly[2], state.ly[3],
										  state.ly[4], state.ly[5]);
}

//Kiem tra muc tieu
int goal(State state){
	int i;
	for(i = 0; i <= 5; i++){
		if(state.ly[i] != 1){
			return 0;
		}
	}
	return 1;
}

//cac phep toan

void nguaUp_UpNgua(State state, int start, int end, State *result){
	int i;
	for(i = start; i <= end; i++){
		if(state.ly[i] == 0){
			state.ly[i] = 1;
		}
		else if(state.ly[i] == 1){
			state.ly[i] = 0;
		}
	}
	*result = state;
}

//Khai bao cau truc Node
typedef struct Node{
	State state;
	struct Node* Parent;
}Node;

//So sanh 2 trang thai
int compareStates(State ly1, State ly2){
	int i;
	for(i = 0; i <= 5; i++){
		if(ly1.ly[i] != ly2.ly[i]){
			return 0;
		}
	}
	return 1;
}

//Tim trang thai trong 2 Queue Open/Close
int find_State(State state, queue<Node*> Q){
	while(!Q.empty()){
		if(compareStates(state, Q.front()->state)){
			return 1;
		}
		Q.pop();
	}
	return 0;
}

//Thuat toan duyet theo chieu rong
Node* BFS_Algorithm(State state){
	//Khai bao 2 Stack Open/Close
	queue<Node*> Open;
	queue<Node*> Close;
	//Khai bao nut cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->Parent = NULL;
	root->state = state;
	Open.push(root);
	while(!Open.empty()){
		//Lay Node trong Open ra
		Node* node = Open.front();
		Open.pop();
		Close.push(node);
		//Kiem tra muc tieu
		if(goal(node->state)){
			return node;
		}
		int i, head, tail;
		for(i = 0; i <= 3; i++){
			State newstate; makeNullState(&newstate);
			head = i; tail = head + 2;
			nguaUp_UpNgua(node->state, head, tail, &newstate);
			//Neu trang thai da ton tai
			if(find_State(newstate, Open) || find_State(newstate, Close)){
				continue;
			}
			//Neu trang thai chua ton tai
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->state = newstate;
			newNode->Parent = node;
			Open.push(newNode);
		}
	}
	return NULL;
}

//In ket qua
void print_WaystoGetGoal(Node* node){
	stack<Node*> queuePrint;
	//Duyet nguoc
	while(node->Parent != NULL){
		queuePrint.push(node);
		node = node->Parent;
	}
	queuePrint.push(node);
	while(!queuePrint.empty()){
		printState(queuePrint.top()->state);
		queuePrint.pop();
	}
}

int main(){
	State cur_state = {1, 0, 1, 0, 1, 0};
	Node* p = BFS_Algorithm(cur_state);
	print_WaystoGetGoal(p);
	return 0;
}


