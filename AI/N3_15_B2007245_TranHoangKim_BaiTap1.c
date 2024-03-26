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

int main(){
	State cur_state= {5, 4}, result;
	printf("Trang thai bat dau");
	print_State(cur_state);
	int opt;
	for(opt = 1; opt <= 6; opt++){
		int thuchien = call_operator(cur_state, &result, opt);
		if(thuchien == 1){ //thuc hien thanh cong
			printf("\nHanh dong %s thanh cong", action[opt]);
			print_State(result);
		}
		else
		   printf("\nHanh dong %s KHONG thanh cong", action[opt]);
	}
	return 0;
}
