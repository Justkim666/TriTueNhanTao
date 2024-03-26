#include<stdio.h>
#include<stdlib.h>
#define MaxLength 100
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

//Tim trang thai trong 2 Stack Open/Close
int find_State(State state, Stack S){
	while(!emptyStack(S)){
		if(compareStates(state, top(S)->state)){
			return 1;
		}
		pop(&S);
	}
	return 0;
}

//Thuat toan duyet theo chieu sau
Node* DFS_Algorithm(State state){
	//Khai bao 2 Stack Open/Close
	Stack Open; makeNullStack(&Open);
	Stack Close; makeNullStack(&Close);
	//Khai bao nut cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->Parent = NULL;
	root->state = state;
	push(root, &Open);
	while(!emptyStack(Open)){
		//Lay 1 Node trong Open
		Node* node = top(Open);
		pop(&Open);
		push(node, &Close);
		//Kiem tra muc tieu
		if(goal(node->state)){
			return node;
		}
		int i, head, tail;
		for(i = 0; i <= 3; i++){
			State newstate;
			makeNullState(&newstate);
			head = i; 
			tail = head + 2;
			nguaUp_UpNgua(node->state, head, tail, &newstate);
			//Neu trang thai da ton tai
			if(find_State(newstate, Open) || find_State(newstate, Close)){
				continue;
			}
			//Neu trang thai chua ton tai
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->state = newstate;
			newNode->Parent = node;
			push(newNode, &Open);
		}
	}
	return NULL;
}

//In ket qua
void print_WaystoGetGoal(Node* node){
	Stack stackPrint; makeNullStack(&stackPrint);
	//Duyet nguoc
	while(node->Parent != NULL){
		push(node, &stackPrint);
		node = node->Parent;
	}
	push(node, &stackPrint);
	while(!emptyStack(stackPrint)){
		printState(top(stackPrint)->state);
		pop(&stackPrint);
	}
}

int main(){
	State cur_state = {1, 0, 1, 0, 1, 0};
	Node* p = DFS_Algorithm(cur_state);
	print_WaystoGetGoal(p);
	return 0;
}
