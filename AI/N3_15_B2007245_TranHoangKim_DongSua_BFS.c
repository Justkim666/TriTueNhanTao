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
	if(a.X == b.X && a.Y == b.Y && a.Z == b.Z){
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
		if(Goal(node->state)){
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

//In ket qua
void print_WaystoGetGoal(Node* node){
	Queue QueuePrint; makeNullQueue(&QueuePrint);
	//duyet nguoc ve nut Parent
	while(node->Parent != NULL){
		enQueue(node, &QueuePrint);
		node = node->Parent;
	}
	enQueue(node, &QueuePrint);
	//In ra thu tu hanh dong chuyen nuoc
	int no_action = 0, i;
	for(i = QueuePrint.Rear; i >= QueuePrint.Front; i--){
		Node* node = QueuePrint.Elements[i];
		printf("\nAction %d: %s", no_action, action[node->no_function]);
		printState(node->state);
		no_action++;
	}
}

int main(){
	State cur_state = {10, 0, 0};
	Node* p = BFS_Algorithm(cur_state);
	print_WaystoGetGoal(p);
	return 0;
}
