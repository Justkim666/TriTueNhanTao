#include<stdio.h>
#include<stdlib.h>

#define tankcapacity_X 10 // Suc chua binh 10 lit (day)
#define tankcapacity_Y 6 // Suc chua binh 5 lit (rong)
#define tankcapacity_Z 5 // Suc chua binh 6 lit (rong)
#define empty 0
#define goal 8
#define MaxLength 100 // Ngan Xep

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
		result->X = max(cur_state.X - (tankcapacity_Y-cur_state.Y), empty);
		result->Y = min(cur_state.X+cur_state.Y, tankcapacity_Y);
		result->Z = cur_state.Z;
		return 1;
	}
	return 0;
}


//Do tu X->Z
int pourWaterX_Z(State cur_state, State *result){
	if(cur_state.X > 0 && cur_state.Z < tankcapacity_Z){
		result->X = max(cur_state.X - (tankcapacity_Z-cur_state.Z), empty);
		result->Y = cur_state.Y;
		result->Z = min(cur_state.X+cur_state.Z, tankcapacity_Z);
		return 1;
	}
	return 0;
}

//Do tu Y->X
int pourWaterY_X(State cur_state, State *result){
	if(cur_state.Y > 0 && cur_state.X < tankcapacity_X){
		result->Y = max(cur_state.Y - (tankcapacity_X-cur_state.X), empty);
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
		result->Y = max(cur_state.Y-(tankcapacity_Z-cur_state.Z), empty);
		result->Z = min(cur_state.Y+cur_state.Z, tankcapacity_Z);
		return 1;
	}
	return 0;
}

//Do tu Z->X
int pourWaterZ_X(State cur_state, State *result){
	if(cur_state.Z > 0 && cur_state.X < tankcapacity_X){
		result->Z = max(cur_state.Z-(tankcapacity_X-cur_state.X), empty);
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
		result->Z = max(cur_state.Z-(tankcapacity_Y-cur_state.Y), empty);
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

//*----------------------------------------------*//
//Khai bao cau truc Stack
typedef struct{
	Node* Elements[MaxLength];
	int Top_idx;
}Stack;

//kiem tra ngan xep day
int fullStack(Stack stack){
	return stack.Top_idx == 0;
}
//Dua 1 phan tu vao ngan xep
void push(Node* x, Stack *stack){
	if(fullStack(*stack)){
		printf("Error! Stack is full");
	}
	else{
		stack->Top_idx -= 1;
		stack->Elements[stack->Top_idx] = x;
	}
}

//Khoi tao ngan xep rong
void makeNullStack(Stack *stack){
	stack->Top_idx = MaxLength;
}

//Kiem tra ngan xep co rong hay khong
int emptyStack(Stack stack){
	return stack.Top_idx == MaxLength;
}

//Tra ve phan tu tren dinh ngan xep
Node* top(Stack stack){
	if(!emptyStack(stack)){
		return stack.Elements[stack.Top_idx];
	}
	return NULL;
}

//Xoa phan tu tai dinh ngan xep
void pop(Stack *stack){
	if(!emptyStack(*stack)){
		stack->Top_idx += 1;
	}
	else printf("Error! Stack is empty");
}

//Ham so sanh 2 trang thai
int comparesState(State a, State b){
	if(a.X == b.X && a.Y == b.Y && a.Z == b.Z){
		return 1;
	}
	return 0;
}

//Tim trang thai trong Stack Open/Close
int find_State(State state, Stack stack){
	while(!emptyStack(stack)){
		if(comparesState(state, top(stack)->state)){
			return 1;
		}
		pop(&stack);
	}
	return 0;
}

//Thuat toan duyet theo chieu sau
Node* DFS_Algorithm(State state){
	//Khai bao 2 ngan xep Open va Close
	Stack Open; makeNullStack(&Open);
	Stack Close; makeNullStack(&Close);
	//Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	push(root, &Open);
	while(!emptyStack(Open)){
		//Lay 1 dinh trong ngan xep
		Node* node = top(Open);
		pop(&Open);
		push(node, &Close);
		//Dinh lay ra la trang thai muc tieu ?
		if(Goal(node->state)){
			return node;
		}
		int opt;
		//Goi cac phep toan tren trang thai
		for(opt = 1; opt <= 6; opt++){
			State newState; makeNullState(&newState);
			if(call_operator(node->state, &newState, opt)){
				//Neu trang thai moi sinh ra da ton tai thi bo qua
				if(find_State(newState, Open) || find_State(newState, Close)){
					continue;
				}
				//Neu trang thai moi chua ton tai
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->Parent = node;
				newNode->no_function = opt;
				push(newNode, &Open);
			}		
		}
	}
	return NULL;
}

//In ket qua

void print_wayToGetGoal(Node *node){
	Stack stack; makeNullStack(&stack);
	while(node->Parent != NULL){
		push(node, &stack);
		node = node->Parent;
	}
	push(node, &stack);
	//in thu tu 
	int no_action;
	while(!emptyStack(stack)){
		printf("\nAction %d: %s", no_action, action[top(stack)->no_function]);
		printState(top(stack)->state);
		pop(&stack);
		no_action++;
	}
}

int main(){
	State cur_state = {10, 0, 0};
	Node *p = DFS_Algorithm(cur_state);
	print_wayToGetGoal(p);
	return 0;
}

