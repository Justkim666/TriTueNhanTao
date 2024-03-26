#include<stdio.h>
#include<math.h>
#define SIZE 8

int a[20];
char Queens[SIZE][SIZE];
bool canPutQueen(int x2, int y2){
	//Kiem tra cach dat co thoa man hay khong
	for(int i = 1; i < x2; i++){
		if(a[i] == y2 || abs(i-x2) == abs(a[i]-y2)){
			return false;
		}
	}
	//Neu kiem tra het cac truong hop van khong sai thi tra ve true
	return true;
}

void from1Dto2D(int n, int result[]){
	//In ra mot ket qua
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(result[i] == j){
				Queens[i][j] = '$';
			}
			else Queens[i][j] = '-';
		}
	}
	printf("\n");
}

void printStateQueens(char stateQueens[][SIZE], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%c ", stateQueens[i][j]);
		}
		printf("\n");
	}
}

int countState = 1;
void PutQueens(int i, int n){
	for(int j = 1; j <= n; j++){
		//Thu dat quan hau vao cac cot tu 1 den n
		if(canPutQueen(i, j)){
			//Neu cach dat nay thoa man thi luu lai vi tri
			a[i] = j;
			//Neu dat xong quan hat thu n thi xuat ra mot ket qua
			if(i == n){
				from1Dto2D(n, a);
				printf("State suitable Queens %d\n", countState);
				printStateQueens(Queens, n);
				countState++;
			}
			PutQueens(i+1, n);
		}
	}
}

int main(){
	int n = 8; // Bai toan 8 quan hau
	PutQueens(1, 8);
	return 0;
}














