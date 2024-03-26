#include<stdio.h>
#include<stdlib.h>
#include<vector>
#define ROWS 3
#define COLS 3
#define EMPTY 0
#define MAX_OPERATOR 4
#define Maxlength 500
#include<algorithm>
using namespace std;
const char* action[] = {"First State", "Move cell EMPTY to UP", "Move cell EMPTY to DOWN",
                        "Move cell EMPTY to LEFT", "Move cell EMPTY to RIGHT"};

//Khai bao cau truc trang thai cua 8_puzzel
typedef struct{
	int eightPuzzel[ROWS][COLS];
	int emptyRow;
	int emptyCol;
}State;

//In trang thai cua 8_Puzzel
void printState(State state){
	int row, col;
	printf("\n----------\n");
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			printf("|%d ", state.eightPuzzel[row][col]);
		}
		printf("\n");
	}
	printf("----------\n");
}

//So sanh trang thai state1 co giong voi trang thai state2
int compareStates(State state1, State state2){
	if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol){
		return 0;
	}
	int row, col;
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			if(state1.eightPuzzel[row][col] != state2.eightPuzzel[row][col]){
				return 0;
			}
		}
	}
	return 1;
}

//Ham kiem tra trang thai muc tieu
int goalcheck(State state, State goal){
	return compareStates(state, goal);
}

//Hanh dong chuyen o trong len tren
int upOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if(empRowCurrent > 0){
		result->emptyRow = empRowCurrent-1;
		result->emptyCol = empColCurrent;
		result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent-1][empColCurrent];
		result->eightPuzzel[empRowCurrent-1][empColCurrent] = EMPTY;
		return 1;
	}
	return 0;
}

//Hanh dong chuyen o trong xuong duoi
int downOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if(empRowCurrent < 2){
		result->emptyRow = empRowCurrent+1;
		result->emptyCol = empColCurrent;
		result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent+1][empColCurrent];
		result->eightPuzzel[empRowCurrent+1][empColCurrent] = EMPTY;
		return 1;
	}
	return 0;
}

//Hanh dong di chuyen o trong sang trai
int leftOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if(empColCurrent > 0){
		result->emptyRow = empRowCurrent;
		result->emptyCol = empColCurrent-1;
		result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent][empColCurrent-1];
		result->eightPuzzel[empRowCurrent][empColCurrent-1] = EMPTY;
		return 1;
	}
	return 0;
}

//Hanh dong di chuyen o trong sang phai
int rightOperator(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if(empColCurrent < 2){
		result->emptyRow = empRowCurrent;
		result->emptyCol = empColCurrent+1;
		result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent][empColCurrent+1];
		result->eightPuzzel[empRowCurrent][empColCurrent+1] = EMPTY;
		return 1;
	}
	return 0;
}

//Goi cac hanh dong chuyen o trong cho trang thai hien tai
int callOperator(State state, State *result, int opt){
	switch(opt){
		case 1: return upOperator(state, result);
		case 2: return downOperator(state, result);
		case 3: return leftOperator(state, result);
		case 4: return rightOperator(state, result);
		default: printf("Cannot call operators");
		    return 0;
	}
}

//Ham heuristic 1
//Dem so o sai khac voi trang thai muc tieu
int heuristic1(State state, State goal){
	int row, col, count = 0;
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			if(state.eightPuzzel[row][col] != goal.eightPuzzel[row][col]){
				count++;
			}
		}
	}
	return count;
}

//Ham heuristic 2
//Dem so buoc chuyen o sai ve o dung cua trang thai muc tieu
int heuristic2(State state, State goal){
	int count = 0;
	int row, col, row_g, col_g;
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			if(state.eightPuzzel[row][col] != EMPTY){
				for(row_g = 0; row_g < ROWS; row_g++){
					for(col_g = 0; col_g < COLS; col_g++){
						if(state.eightPuzzel[row][col] == goal.eightPuzzel[row_g][col_g]);
						count += abs(row - row_g) + abs(col - col_g);
						col_g = COLS; // break loop col_g
						row_g = ROWS; //break loop row_g
					}
				}
			}
		}
	}
	return count;
}

//Khai bao cau truc Node de dung cay tim kiem
typedef struct Node{
	State state;
	struct Node* parent;
	int no_function;
	int heuristic;
}Node;

//Tim trang thai state co thuoc Open hoac Close hay khong
//Luu vi tri tim duoc vao bien *position
Node* find_State(State state, vector<Node*> list, int *position){
	int i;
	for(i = 0; i < list.size(); i++){
		if(compareStates(list.at(i)->state, state)){
			*position = i;
			return list.at(i);
		}
	}
	return NULL;
}

//Thuat toan tim kiem tot nhat dau tien
//Ham f = h
Node* best_first_search(State state, State goal){
	vector<Node*> Open_BFS;
	vector<Node*> Close_BFS;
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_function = 0;
	root->heuristic = heuristic1(root->state, goal);
	Open_BFS.push_back(root);
	while(!Open_BFS.empty()){
		Node* node = Open_BFS.front();
		Open_BFS.erase(Open_BFS.begin()+0);
		Close_BFS.push_back(node);
		if(goalcheck(node->state, goal)){
			return node;
		}
		int opt;
		for(opt = 1; opt <= MAX_OPERATOR; opt++){
			State newstate;
			newstate = node->state;
			if(callOperator(node->state, &newstate, opt)){
				
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->parent = node;
				newNode->no_function = opt;
				newNode->heuristic = heuristic1(newstate, goal);
				//Kiem tra trang thai moi sinh ra
				int pos_Open, pos_Close;
				Node* nodeFoundOpen = find_State(newstate, Open_BFS, &pos_Open);
				Node* nodeFoundClose = find_State(newstate, Close_BFS, &pos_Close);
				if(nodeFoundOpen == NULL && nodeFoundClose == NULL){
					Open_BFS.push_back(newNode);
				}
				else if(nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic){
					Open_BFS.erase(Open_BFS.begin()+pos_Open);
					Open_BFS.push_back(newNode);
				}
				else if(nodeFoundClose != NULL && nodeFoundClose->heuristic > newNode->heuristic){
					Close_BFS.erase(Close_BFS.begin()+pos_Close);
					Open_BFS.push_back(newNode);
				}
				int i, j;
				for(i = 0; i < Open_BFS.size()-1; i++){
					for(j = i+1; j < Open_BFS.size(); j++){
						if(Open_BFS.at(i)->heuristic > Open_BFS.at(j)->heuristic){
							Node* temp = Open_BFS[i];
							Open_BFS[i] = Open_BFS[j];
							Open_BFS[j] = temp;
						}
					}
				}
			}
		}
	}
	return NULL;
}

//In ket qua
void print_WaysToGetGoal(Node* node){
	vector<Node*> listPrint;
	//Duyet nguoc ve nut parent
	while(node->parent != NULL){
		listPrint.push_back(node);
		node = node->parent;
	}
	listPrint.push_back(node);
	//In ra thu tu
	int no_action = 0, i;
	for(i = listPrint.size()-1; i >= 0; i--){
		printf("\nAction %d: %s", no_action, action[listPrint.at(i)->no_function]);
		printState(listPrint.at(i)->state);
		no_action++;
	}
}

int main(){
	State state; //, result;
	state.emptyRow = 1;
	state.emptyCol = 1;
	state.eightPuzzel[0][0] = 3;
	state.eightPuzzel[0][1] = 4;
	state.eightPuzzel[0][2] = 5;
	state.eightPuzzel[1][0] = 1;
	state.eightPuzzel[1][1] = 0;
	state.eightPuzzel[1][2] = 2;
	state.eightPuzzel[2][0] = 6;
	state.eightPuzzel[2][1] = 7;
	state.eightPuzzel[2][2] = 8;
	State goal;
	goal.emptyRow = 0;
	goal.emptyCol = 0;
	goal.eightPuzzel[0][0] = 0;
	goal.eightPuzzel[0][1] = 1;
	goal.eightPuzzel[0][2] = 2;
	goal.eightPuzzel[1][0] = 3;
	goal.eightPuzzel[1][1] = 4;
	goal.eightPuzzel[1][2] = 5;
	goal.eightPuzzel[2][0] = 6;
	goal.eightPuzzel[2][1] = 7;
	goal.eightPuzzel[2][2] = 8;
	Node* p = best_first_search(state, goal); 
	print_WaysToGetGoal(p);
	return 0;
}
