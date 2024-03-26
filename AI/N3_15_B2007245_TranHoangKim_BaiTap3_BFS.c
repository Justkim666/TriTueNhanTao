#include<stdio.h>
#include<stdlib.h>

#define tankcapacity_X 9 // Suc chua binh X
#define tankcapacity_Y 4 // Suc chua binh Y
#define empty 0
#define goal 6 // Muc tieu luong nuoc can dong duoc
#define MaxLength 100 // Su dung cai dat Ngan xep (Stack)

//Hang chuoi de in ra ten hanh donh
const char* action[] = {"First State", "pour Water Full X", "pour Water Full Y", 
                        "pour Water Empty X", "pour Water Empty Y","pour Water X to Y",
						"pour Water Y to X"};

// Khai bao cau truc trang thai
typedef struct{
	int x; // Luong nuoc trong binh x
	int y; // Luong nuoc trong binh y
}State;

//Khoi tao trang thai binh X = 0, Y= 0
void makeNullState(State *state){
	state->x = 0;
	state->y = 0;
}

//In trang thai
void print_State(State state){
	printf("\n    X: %d --- Y: %d", state.x, state.y);
}

//Ham kiem tra trang thai muc tieu
int goalcheck(State state){
	return (state.x == goal || state.y == goal);
}

//Lam day binh nuoc X
int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X){
		result->x = tankcapacity_X;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

//Lam day binh nuoc Y
int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y < tankcapacity_Y){
		result->x = cur_state.x;
		result->y = tankcapacity_Y;
	}
}

//Lam rong binh nuoc X
int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x>0){
		result->x = empty;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}

//Lam rong binh nuoc Y
int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y>0){
		result->x = cur_state.x;
		result->y = empty;
		return 1;
	}
	return 0;
}

//ham max
int max(int x, int y){
	return (x > y) ? x : y;
}

//ham min
int min(int x, int y){
	return (x < y) ? x : y;
}

//Chuyen tu binh X sang binh Y
int pourWaterXY(State cur_state, State *result){
	if(cur_state.x>0 && cur_state.y < tankcapacity_Y){
		result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y), empty);
		result->y = min(cur_state.x+cur_state.y, tankcapacity_Y);
		return 1;
	}
	return 0;
}

//Chuyen tu binh Y sang binh X
int pourWaterYX(State cur_state, State *result){
	if(cur_state.y>0 && cur_state.x < tankcapacity_X){
		result->x = min(cur_state.y+cur_state.x, tankcapacity_X);
		result->y = max(cur_state.y - (tankcapacity_X - cur_state.x), empty);
		return 1;
	}
	return 0;
}

//Goi cac phep toan tren trang thai
int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return pourWaterFullX(cur_state, result);
		case 2: return pourWaterFullY(cur_state, result);
		case 3: return pourWaterEmptyX(cur_state, result);
		case 4: return pourWaterEmptyY(cur_state, result);
		case 5: return pourWaterXY(cur_state, result);
		case 6: return pourWaterYX(cur_state, result);
		default: printf("Error calls operators");
		    return 0;
	}
}

//Khai bao cau truc nut (dinh) de dung cay tim kiem 
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;

//Khai bao cau truc hang doi
typedef struct{
	Node* Elements[MaxLength];
	int Front, Rear;
}Queue;

//Khoi tao hang doi rong
void makeNullQueue(Queue *Q){
	Q->Front = -1;
	Q->Rear = -1;
}

//Kiem tra hang doi day
int fullQueue(Queue Q){
	return Q.Rear - Q.Front + 1 == MaxLength;
}

//Kiem tra hang doi rong
int emptyQueue(Queue Q){
	return Q.Front == -1;
}

//Dua 1 phan tu vao hang doi
void enQueue(Node* node, Queue *Q){
	if(!fullQueue(*Q)){
		if(emptyQueue(*Q)){
			Q->Front = 0;
		}
		Q->Rear += 1;
		Q->Elements[Q->Rear] = node;
	}
}

//Xoa 1 phan tu ra khoi hang doi
void deQueue(Queue *Q){
	if(!emptyQueue(*Q)){
		Q->Front += 1;
		if(Q->Front > Q->Rear){
			makeNullQueue(Q);
		}
	}
}
//Tra ve phan tu dau cua hang doi
Node* front(Queue Q){
	return Q.Elements[Q.Front];
}

//Ham so sanh 2 trang thai
int compareStates(State a, State b){
	if((a.x == b.x) && (a.y == b.y)){
		return 1;
	}
	return 0;
}

//Tim trang thai trong Queue Open/Close
int find_State(State state, Queue Q){
	while(!emptyQueue(Q)){
		if(compareStates(front(Q)->state, state)){
			return 1;
		}
		deQueue(&Q);
	}
	return 0;
}
//Tuat toan duyet theo chieu rong
Node* BFS_Algorithm(State state){
	//Khai bao 2 hang doi Open va Close
	Queue Open; makeNullQueue(&Open);
	Queue Close; makeNullQueue(&Close);
	//Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	enQueue(root, &Open);
	while(!emptyQueue(Open)){
		//Lay front cua Open
		Node* node = front(Open);
		deQueue(&Open);
		enQueue(node, &Close);
		//Check Goal
		if(goalcheck(node->state)){
			return node;
		}
		int opt;
		//Goi cac phep toan tren trang thai
		for(opt = 1; opt <= 6; opt++){
			State newState;
			makeNullState(&newState);
			if(call_operator(node->state, &newState, opt)){
				//Neu trang thai moi sinh ra da ton tai thi bo qua
				if(find_State(newState, Open) || find_State(newState, Close)){
					continue;
				}
				//Neu trang thai chua ton tai
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newState;
				newNode->Parent = node;
				newNode->no_function = opt;
				enQueue(newNode, &Open);
			}
		}
	}
	return NULL;
}

//In ket qua chuyen nuoc
void print_WaystoGetGoal(Node* node){
	Queue QueuePrint; makeNullQueue(&QueuePrint);
	//duyet nguoc ve nut Parent
	while(node->Parent != NULL){
		enQueue(node, &QueuePrint);
		node = node->Parent;
	}
	enQueue(node, &QueuePrint);
	//In ra thu tu hanh dong chuyen nuoc
	int no_action = 0;
	for(int i = QueuePrint.Rear; i >= QueuePrint.Front; i--){
		Node* node = QueuePrint.Elements[i];
		printf("\nAction %d: %s", no_action, action[node->no_function]);
		print_State(node->state);
		no_action++;
	}
}
int main(){
	State cur_state = {0, 0};
	Node* p = BFS_Algorithm(cur_state);
	print_WaystoGetGoal(p);
	return 0;
}













