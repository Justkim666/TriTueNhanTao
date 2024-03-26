#include<stdio.h>
#include<stack>
#include<stdlib.h>
#define MaxLength 100
using namespace std;
/*-----------------------------------------Khai Bao-----------------------------------------*/

//Hang chuoi de in ra ten hanh dong
const char* action[] = {"First State", "Di chuyen 1 tu si",
                        "Di chuyen 2 tu si", "Di chuyen 1 quy",
						"Di chuyen 2 quy", "Di chuyen 1 quy 1 tu si"};
// Khai bao cau truc trang thai
typedef struct{
	int a;     //[0, 0, 3, 3]
	int b;
	int c;
	int d;
}State;

// Khoi tao trang thai
void makeNullState(State *state){
	state->a = 0;
	state->b = 0;
	state->c = 0;
	state->d = 0;
}

// In trang thai
void printState(State state){
	printf("\n [%d, %d, %d, %d]", state.a, state.b, state.c, state.d);
}

// Kiem tra goal
int goal(State state){
	if(state.a == 3 && state.b == 3 && state.c == 0 && state.d == 0){
		return 1;
	}
	return 0;
}

/*-----------------------------------------Khai Bao-----------------------------------------*/


/*-----------------------------------------Cac Phep Toan-----------------------------------------*/

// 1. Di chuyen 1 tu si
int diChuyen1TuSi(State state, State *result){
	if(state.c > 0){
		result->a = state.a + 1;
		result->b = state.b;
		result->c = state.c - 1;
		result->d = state.d;
		return 1;
	}
	return 0;
}

// 2. Di chuyen 2 tu si
int diChuyen2TuSi(State state, State *result){
	if(state.c > 1){
		result->a = state.a + 2;
		result->b = state.b;
		result->c = state.c - 2;
		result->d = state.d;
		return 1;
	}
	return 0;
}

// 3. Di chuyen 1 quy
int diChuyen1Quy(State state, State *result){
	if(state.d > 0){
		result->a = state.a;
		result->b = state.b + 1;
		result->c = state.c;
		result->d = state.d - 1;
		return 1;
	}
	return 0;
}

// 4. Di chuyen 2 quy
int diChuyen2Quy(State state, State *result){
	if(state.d > 1){
		result->a = state.a;
		result->b = state.b + 2;
		result->c = state.c;
		result->d = state.d - 2;
		return 1;
	}
	return 0;
}

// 5. Di chuyen 1 quy, 1 tu si
int diChuyen1Quy1TuSi(State state, State *result){
	if(state.c > 0 && state.d > 0){
		result->a = state.a + 1;
		result->b = state.b + 1;
		result->c = state.c - 1;
		result->d = state.d - 1;
		return 1;
	}
	return 0;
}


/*-----------------------------------------Cac Phep Toan-----------------------------------------*/


// Goi cac phep toan tren trang thai
int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return diChuyen1TuSi(cur_state, result);
		case 2: return diChuyen2TuSi(cur_state, result);
		case 3: return diChuyen1Quy(cur_state, result);
		case 4: return diChuyen2Quy(cur_state, result);
		case 5: return diChuyen1Quy1TuSi(cur_state, result);
		default: printf("Error call operators");
		return 0;
	}
}

// Dung cay khong gian trang thai

// Khai bao cau truc 1 node
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

// Ham so sanh 2 trang thai
int compareStates(State a, State b){
	if((a.a == b.a) && (a.b == b.b) && (a.c == b.c) && (a.d == b.d)){
		return 1;
	}
	return 0;
}

//Tim trang thai trong Stack 
int find_State(State state, stack<Node*> Open){
	while(!Open.empty()){
		if(compareStates(Open.top()->state, state)){
			return 1;
		}
		Open.pop();
	}
	return 0;
}

//Kiem tra dieu kien
int checkCondition(State state){
	if((state.b > state.a) || (state.d > state.c)){
		return 1;
	}
	return 0;
}

// Thuat toan duyet theo chieu sau
Node* DFS_Algorithm(State state){
	//Khai bao 2 ngan xep Open/Close
	stack<Node*> Open; 
	stack<Node*> Close;
	//Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	Open.push(root);
	while(!Open.empty()){
		//Lay 1 dinh trong ngan xep ra
		Node* node = Open.top();
		Open.pop();
		Close.push(node);
		//Kiem tra dinh lay ra co phai la goal ?
		if(goal(node->state)){
			return node;
		}
		int opt;
		//Goi cac phep toan tren trang thai
		for(opt = 1; opt <= 5; opt++){
			State newstate;
			makeNullState(&newstate);
			if(call_operator(node->state, &newstate, opt)){
				//Neu trang thai moi sinh ra da ton tai or sai dieu kien
				if((find_State(newstate, Open) || find_State(newstate, Close)) || checkCondition(newstate)){
					continue;
				}
				//Neu trang thai moi chua ton tai
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->Parent = node;
				newNode->no_function = opt;
				Open.push(newNode);
			}
		}
	}
	return NULL;
}

//In ket qua
void print_WaystoGetGoal(Node* node){
	stack<Node*> printStack;
	while(node->Parent != NULL){
		printStack.push(node);
		node = node->Parent;
	}
	printStack.push(node);
	int no_action = 0;
	while(!printStack.empty()){
		printf("\nAction %d: %s", no_action, action[printStack.top()->no_function]);
		printState(printStack.top()->state);
		printStack.pop();
		no_action++;
	}
}

int main(){
	State cur_state = {0, 0, 3, 3};
	Node* p = DFS_Algorithm(cur_state);
	print_WaystoGetGoal(p);
	return 0;
}







