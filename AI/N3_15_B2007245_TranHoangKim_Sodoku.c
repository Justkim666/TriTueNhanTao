#include<stdio.h>
#include<stdlib.h>
#define MAX_VALUE 10
#define EMPTY 0
#define AREA_SQUARE_SIZE 3
#define INF 999999
#define MaxLength 100
#define NB_ROWS 9
#define NB_COL 9
#define EMPTY 0
#define MAX_VALUE 10

/*-----------------------------Cau Truc Danh Sach-----------------------------*/

//Khai bao cau truc danh sach
typedef struct{
	int Elements[MaxLength];
	int size;
}List;

//Khoi tao danh sach rong
void makeNullList(List *list){
	list->size = 0;
}

//Them phan tu vao cuoi danh sach
void appendList(int x, List *list){
	list->Elements[list->size++] = x;
}

/*-----------------------------Cau Truc Danh Sach-----------------------------*/


/*-----------------------------Cau Truc Toa Do-----------------------------*/

//Khai bao cau truc toa do
typedef struct{
	int x, y;
}Coord;

//Cau truc danh sach toa do
typedef struct{
	Coord data[MaxLength];
	int size;
}ListCoord;

//Khoi tao danh sach
void initListCoord(ListCoord *list){
	list->size = 0;
}

//Them phan tu vao cuoi danh sach
void appendListCoord(Coord coord, ListCoord *listcoord){
	listcoord->data[listcoord->size++] = coord;
}

/*-----------------------------Cau Truc Rang Buoc-----------------------------*/

//Khai bao cau truc rang buoc
typedef struct{
	int data[NB_ROWS*NB_COL][NB_ROWS*NB_COL];
	int n;
}Constrains;

//Khoi tao rang buoc rong
void initConstrains(Constrains *constrains){
	int i, j;
	for(i = 0; i < NB_ROWS*NB_COL; i++){
		for(j = 0; j < NB_ROWS*NB_COL; j++){
			constrains->data[i][j] = 0;
		}
	}
	constrains->n = NB_ROWS*NB_COL;
}

//Chuyen doi gia tri

//Toa do -> dinh
int indexOf(Coord coord){
	return (NB_ROWS*coord.x + coord.y);
}

//Dinh -> Toa do
Coord positionOfVertex(int vertex){
	Coord coord;
	coord.x = vertex / NB_ROWS;
	coord.y = vertex % NB_COL;
	return coord;
}

//Them rang buoc
int addConstrains(Constrains *constrains, Coord source, Coord target){
	int u = indexOf(source);
	int v = indexOf(target);
	if(constrains->data[u][v] == 0){
		constrains->data[u][v] = 1;
		constrains->data[v][u] = 1;
		return 1;
	}
	return 0;
}

//Tap rang buoc cua 1 dinh
ListCoord getConstrains(Constrains constrains, Coord coord){
	int i;
	int v = indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	for(i = 0; i < constrains.n; i++){
		if(constrains.data[v][i] == 1){
			appendListCoord(positionOfVertex(i), &result);
		}
	}
	return result;
}

/*-----------------------------Cau Truc Bang Sudoku-----------------------------*/

//Khai bao cau truc Sudoku
typedef struct{
	int cells[NB_ROWS][NB_COL];
	Constrains constrains;
}Sudoku;

//Khoi tao Sudoku rong
void initSudoku(Sudoku *sudoku){
	int i, j;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COL; j++){
			sudoku->cells[i][j] = EMPTY;
		}
	}
	initConstrains(&sudoku->constrains); 
}

//Khoi tao bang Sudoku co gia tri
void initSudokuWithValue(Sudoku *sudoku, int inputs[NB_ROWS][NB_COL]){
	int i, j;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COL; j++){
			sudoku->cells[i][j] = inputs[i][j];
		}
	}
	initConstrains(&sudoku->constrains);
}

//In bang Sudoku
void printSudoku(Sudoku sudoku){
	
	int i, j;
	printf("Sudoku:\n");
	for(i = 0; i < NB_ROWS; i++){
		if(i % AREA_SQUARE_SIZE == 0)printf("-------------------------\n");
		for(j = 0; j < NB_COL; j++){
			if(j % AREA_SQUARE_SIZE == 0) printf("| ");
			printf("%d ", sudoku.cells[i][j]);
		}
		printf("|\n");
	}
	printf("-------------------------\n");
}

//Kiem tra trang thai ket thuc
int isFilledSudoku(Sudoku sudoku){
	int i, j;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COL; j++){
			if(sudoku.cells[i][j] == EMPTY) return 0;
		}
	}
	return 1;
}

//Tao rang buoc tu vi tri cho truoc
void spreadConstrainsFrom(Coord position, Constrains* constrains, ListCoord* changeds){
	int row = position.x, col = position.y;
	int i, j;
	//Tao rang buoc theo cot
	for(i = 0; i < NB_ROWS; i++){
		if(i != row){
			Coord pos = {i, col};
			if(addConstrains(constrains, position, pos)){
				appendListCoord(pos, changeds);
			}
		}
	}
	//Tao rang buoc theo hang
	for(i = 0; i < NB_COL; i++){
		if(i != col){
			Coord pos = {row, i};
			if(addConstrains(constrains, position, pos)){
				appendListCoord(pos, changeds);
			}
		}
	}
	//Tao rang buoc theo khoi
	for(i = 0; i < AREA_SQUARE_SIZE; i++){
		for(j = 0; j < AREA_SQUARE_SIZE; j++){
			int areaX = (row/AREA_SQUARE_SIZE)*AREA_SQUARE_SIZE;
			int areaY = (col/AREA_SQUARE_SIZE)*AREA_SQUARE_SIZE;
			if(areaX+i != row || areaY+j != col){
				Coord pos = {areaX+i, areaY+j};
				if(addConstrains(constrains, position, pos)){
					appendListCoord(pos, changeds);
				}
			}
		}
	}
}


//Tim mien gia tri cua o trong
List getAvailableValues(Coord position, Sudoku sudoku){
	ListCoord posList = getConstrains(sudoku.constrains, position);
	int availables[MAX_VALUE]; //1->9
	int i;
	for(i = 1; i < MAX_VALUE; i++) availables[i] = 1;
	for(i = 0; i < posList.size; i++){
		Coord pos = posList.data[i];
		if(sudoku.cells[pos.x][pos.y] != EMPTY){ //dang mang gia tri
			availables[sudoku.cells[pos.x][pos.y]] = 0;
		}
	}
	List result;
	makeNullList(&result);
	for(i = 1; i < MAX_VALUE; i++){
		if(availables[i]) appendList(i, &result);
	}
	return result;
}

//Xac dinh o nao uu tien duoc dien truoc

//cach 1
Coord getNextEmptyCell(Sudoku sudoku){
	int i, j;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COL; j++){
			Coord pos = {i, j};
			if(sudoku.cells[i][j] == EMPTY) return pos;
		}
	}
}

//Cach 2
Coord getNextMinDomainCell(Sudoku sudoku){
	int minLength = INF;
	int i, j;
	Coord result;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COL; j++){
			if(sudoku.cells[i][j] == EMPTY){
				Coord pos ={i, j};
				int availablesLength = getAvailableValues(pos, sudoku).size;
				if(availablesLength < minLength){
					minLength = availablesLength;
					result = pos;
				}
			}
		}
	}
	return result;
}

//Giai quyet bai toan
int exploredCounter = 0;
int sudokuBackTracking(Sudoku *sudoku){
	if(isFilledSudoku(*sudoku)) return 1;
	Coord position = getNextMinDomainCell(*sudoku);
	List availables = getAvailableValues(position, *sudoku);
	if(availables.size == 0){
		//Mien gia tri van chua duoc dien
		return 0;
	}
	int j;
	for(j = 0; j < availables.size; j++){
		int value = availables.Elements[j]; 
		sudoku->cells[position.x][position.y] = value;
		exploredCounter++;
		if(sudokuBackTracking(sudoku)){
			return 1;
		}
		sudoku->cells[position.x][position.y] = EMPTY;
	}
	return 0;
}

//Lan truyen rang buoc va ket thuc bai toan
Sudoku solveSudoku(Sudoku sudoku){
	int i, j;
	//clearConstrains(&sudoku.constrains);
	initConstrains(&sudoku.constrains);
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COL; j++){
			ListCoord history;
			initListCoord(&history);
			Coord pos = {i, j};
			spreadConstrainsFrom(pos, &sudoku.constrains, &history);
		}
	}
	exploredCounter = 0;
	if(sudokuBackTracking(&sudoku)) printf("Solved\n");
	else printf("Can not solve\n");
	printf("Explored %d states\n", exploredCounter);
	return sudoku;
}

int main(){
	
int inputs1[9][9] = {
{5, 3, 0, 0, 7, 0, 0, 0, 0},
{6, 0, 0, 1, 9, 5, 0, 0, 0},
{0, 9, 8, 0, 0, 0, 0, 6, 0},
{8, 0, 0, 0, 6, 0, 0, 0, 3},
{4, 0, 0, 8, 0 , 3, 0, 0, 1},
{7, 0, 0, 0, 2, 0, 0, 0, 6},
{0, 6, 0, 0, 0, 0, 2, 8, 0},
{0, 0, 0, 4, 1, 9, 0, 0, 5},
{0, 0, 0, 0, 8, 0, 0, 7, 9},
};
	
	Sudoku sudoku;
	initSudokuWithValue(&sudoku, inputs1);
	printSudoku(sudoku);
	Sudoku result = solveSudoku(sudoku);
	printSudoku(result);
	return 0;
}
























