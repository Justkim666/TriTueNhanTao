#include<stdio.h>
#include<stdlib.h>
#include<stack>
#define tankcapacity_X 10 // Suc chua binh 10 lit (day)
#define tankcapacity_Y 6 // Suc chua binh 5 lit (rong)
#define tankcapacity_Z 5 // Suc chua binh 6 lit (rong)
#define Empty 0
#define goal 8
#define MaxLength 100 // Ngan Xep
using namespace std;
//Hang chuoi in ra ten hanh dong
const char* action[] = {"First State", "pour Milk X to Y",
                         "pour Milk X to Z", "pour Milk Y to X",
                         "pour Milk Y to Z", "pour Milk Z to X",
                         "pour Milk Z to Y"
};
//Khai bao cau truc trang thai
typedef struct{
	int X;
	int Y;
	int Z;
}State;

//Khoi tao trang thai
void makeNullState(State *state){
	state->X = 0;
	state->Y = 0;
	state->Z = 0;
}

//In trang thai
void printState(State state){
	printf("\n(X---%d | Y---%d | X---%d)", state.X, state.Y, state.Z);
}

//Ham kiem tra muc tieu
int Goal(State state){
	return (state.X == goal || state.Y == goal || state.Z == goal);
}

/*--------------------------------Cac Phep Toan--------------------------------*/

//Ham max
int max(int a, int b){
	return (a > b) ? a : b;
}

//Ham min
int min(int a, int b){
	return (a < b) ? a : b;
}

//Do tu X->Y
int pourWaterX_Y(State cur_state, State *result){
	if(cur_state.X > 0 && cur_state.Y < tankcapacity_Y){
		result->X = max(cur_state.X - (tankcapacity_Y-cur_state.Y), Empty);
		result->Y = min(cur_state.X+cur_state.Y, tankcapacity_Y);
		result->Z = cur_state.Z;
		return 1;
	}
	return 0;
}


//Do tu X->Z
int pourWaterX_Z(State cur_state, State *result){
	if(cur_state.X > 0 && cur_state.Z < tankcapacity_Z){
		result->X = max(cur_state.X - (tankcapacity_Z-cur_state.Z), Empty);
		result->Y = cur_state.Y;
		result->Z = min(cur_state.X+cur_state.Z, tankcapacity_Z);
		return 1;
	}
	return 0;
}

//Do tu Y->X
int pourWaterY_X(State cur_state, State *result){
	if(cur_state.Y > 0 && cur_state.X < tankcapacity_X){
		result->Y = max(cur_state.Y - (tankcapacity_X-cur_state.X), Empty);
		result->X = min(cur_state.X+cur_state.Y, tankcapacity_X);
		result->Z = cur_state.Z;
		return 1;
	}
	return 0;
}

//Do tu Y->Z
int pourWaterY_Z(State cur_state, State *result){
	if(cur_state.Y > 0 && cur_state.Z < tankcapacity_Z){
		result->X = cur_state.X;
		result->Y = max(cur_state.Y-(tankcapacity_Z-cur_state.Z), Empty);
		result->Z = min(cur_state.Y+cur_state.Z, tankcapacity_Z);
		return 1;
	}
	return 0;
}

//Do tu Z->X
int pourWaterZ_X(State cur_state, State *result){
	if(cur_state.Z > 0 && cur_state.X < tankcapacity_X){
		result->Z = max(cur_state.Z-(tankcapacity_X-cur_state.X), Empty);
		result->X = min(cur_state.X+cur_state.Z, tankcapacity_X);
		result->Y = cur_state.Y;
		return 1;
	}
	return 0;
}

//Do tu Z->Y
int pourWaterZ_Y(State cur_state, State *result){
	if(cur_state.Z > 0 && cur_state.Y < tankcapacity_Y){
		result->X = cur_state.X;
		result->Z = max(cur_state.Z-(tankcapacity_Y-cur_state.Y), Empty);
		result->Y = min(cur_state.Y+cur_state.Z, tankcapacity_Y);
		return 1;
	}
	return 0;
}

//Goi cac phep toan tren trang thai
int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourWaterX_Y(cur_state, result);
		case 2: return pourWaterX_Z(cur_state, result);
		case 3: return pourWaterY_X(cur_state, result);
		case 4: return pourWaterY_Z(cur_state, result);
		case 5: return pourWaterZ_X(cur_state, result);
		case 6: return pourWaterZ_Y(cur_state, result);
		default:
			printf("Error call operators");
			return 0;
	}
}

//Khai bao cau truc nut dinh de dung cay tim kiem
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

//Ham so sanh 2 trang thai
int compareStates(State a, State b){
	if(a.X == b.X && a.Y == b.Y && a.Z == b.Z){
		return 1;
	}
	return 0;
}

//Ham kiem tra trang thi co nam trong Stack
int find_State(State state, stack<Node*> OpenStack){
	while(!OpenStack.empty()){
		if(compareStates(OpenStack.top()->state, state)){
			return 1;
		}
		OpenStack.pop();
	}
	return 0;
}

//Thuat toan duyet theo chieu su
Node* DFS_Algorithm(State state){
	//Khai bao hai ngan xep Open va Close
	stack<Node*> Open;
	stack<Node*> Close;
	//Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	Open.push(root);
	while(!Open.empty()){
		//Lay 1 dinh trong ngan xep
		Node* node = Open.top();
		Open.pop();
		Close.push(node);
		//Kiem tra goal
		if(Goal(node->state)){
			return node;
		}
		int opt;
		//Goi cac phep toan tren trang thai
		for(opt = 1; opt <= 6; opt++){
			State newState;
			makeNullState(&newState);
			if(call_operator(node->state, &newState, opt)){
				//Neu trang thai moi sinh ra da ton tai
				if(find_State(newState, Open) || find_State(newState, Close)){
					continue;
				}
			    //Neu trang thai chua ton tai
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->Parent = node;
				newNode->no_function = opt;
				Open.push(newNode);
			}
		}
	}
	return NULL;
}

//In ket qua chuyen nuoc de dat den trang thai muc tieu
void print_WaystoGetGoal(Node* node){
	stack<Node*> stackPrint;
	//duyet nguoc ve nut Parent
	while(node->Parent != NULL){
		stackPrint.push(node);
		node = node->Parent;
	}
	stackPrint.push(node);
	//In ra thu tu hanh dong chuyen nuoc
	int no_action = 0;
	while(!stackPrint.empty()){
		printf("\nAction %d: %s", no_action, action[stackPrint.top()->no_function]);
		printState(stackPrint.top()->state);
		stackPrint.pop();
		no_action++;
	}
}
int main(){
	State cur_state = {10, 0, 0};
	Node* p = DFS_Algorithm(cur_state);
	print_WaystoGetGoal(p);
	return 0;
}
