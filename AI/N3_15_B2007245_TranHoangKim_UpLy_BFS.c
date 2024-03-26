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

/*-----------------------------------------Queue-----------------------------------------*/
//Khai bao cau truc hang doi
typedef struct{
	Node* Elements[MaxLength];
	int Front, Rear;
}Queue;

//Khoi tao hang doi
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

//Tra ve phan tu dau cua hang doi
Node* front(Queue Q){
	return Q.Elements[Q.Front];
}

//Dua 1 phan tu vao hang doi
void enQueue(Node* node, Queue *Q){
	if(!fullQueue(*Q)){
		if(emptyQueue(*Q)){
			Q->Front = 0;
		}
		Q->Rear = Q->Rear + 1;
		Q->Elements[Q->Rear] = node;
	}
}

//Xoa 1 phan tu ra khoi hand doi
void deQueue(Queue *Q){
	if(!emptyQueue(*Q)){
		Q->Front = Q->Front + 1;
		if(Q->Front > Q->Rear){
			makeNullQueue(Q);
		}
	}
}

//So sanh 2 trang thai
int comparesState(State ly1, State ly2){
	int i;
	for(i = 0; i <= 5; i++){
		if(ly1.ly[i] != ly2.ly[i]){
			return 0;
		}
	}
	return 1;
}

//Tim trang thai trong 2 Queue Open/Close
int find_State(State state, Queue Q){
	while(!emptyQueue(Q)){
		if(comparesState(state, front(Q)->state)){
			return 1;
		}
		deQueue(&Q);
	}
	return 0;
}

//Thuat toan duyet theo chieu rong
Node* BFS_Algorithm(State state){
	//Khai bao 2 Queue Open/Close
	Queue Open; makeNullQueue(&Open);
	Queue Close; makeNullQueue(&Close);
	//Khai bao nut cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->Parent = NULL;
	root->state = state;
	enQueue(root, &Open);
	while(!emptyQueue(Open)){
		//Lay trong Open ra
		Node* node = front(Open);
		deQueue(&Open);
		enQueue(node, &Close);
		//Kiem tra goal
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
			newNode->Parent = node;
			newNode->state = newstate;
			enQueue(newNode, &Open);
		}
	}
	return NULL;
}

//In ket qua
void print_WaystoGetGoal(Node* node){
	Queue queuePrint; makeNullQueue(&queuePrint);
	//Duyet nguoc
	while(node->Parent != NULL){
		enQueue(node, &queuePrint);
		node = node->Parent;
	}
	enQueue(node, &queuePrint);
	int i;
	for(i = queuePrint.Rear; i >= queuePrint.Front; i--){
		printState(queuePrint.Elements[i]->state);
	}
}

int main(){
	State cur_state = {1, 0, 1, 0, 1, 0};
	Node* p = BFS_Algorithm(cur_state);
	print_WaystoGetGoal(p);
	return 0;
}
