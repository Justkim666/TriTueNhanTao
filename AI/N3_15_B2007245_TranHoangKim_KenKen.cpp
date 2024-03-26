#include<stdio.h>
#include<stdlib.h>
#define NB_COL 4
#define NB_ROW 4
#define EMPTY 0
#define domainValue 4
#define INF 999999
#define MaxLength 100

/*                     Khai bao cau can thiet co cau truc KenKen                  */

//Khai bao cau truc toa do
typedef struct{
	int x, y;
}Point;

/*---------Khai bao cau truc danh sach cac toa do---------*/
typedef struct{
	Point A[];
	int n;
}ListCoord;

//Khoi tao danh sach toa do
void initListCoord(ListCoord *list){
	list->n = 0;
}
/*---------Khai bao cau truc danh sach cac toa do---------*/

//Them phan tu vao cuoi danh sach
void appendListCoord(Point point, ListCoord *listcoord){
	listcoord->A[listcoord->n++] = point;
}
//Cau truc 1 chuong
typedef struct{
	int value;
	char oper;
	ListCoord L;
}Box;

/*                     Khai bao cau can thiet cho cau truc KenKen                  */

/*                     Khai bao cau truc danh sach               */

//Khai bao cau truc danh sach
typedef struct{
	int data[MaxLength];
	int n;
}List;


//Khoi tao danh sach
void makeNullList(List *list){
	list->n = 0;
}

//Them phan tu vao cuoi danh sach
void appendList(List *list, int x){
	list->data[list->n++] = x;
}

/*                     Khai bao cau truc danh sach               */

/*                     Cau truc rang buoc                        */

//Khai bao cau truc rang buoc
typedef struct{
	int data[NB_COL*NB_ROW][NB_COL*NB_ROW];
	int n;
}Constrains;

//Khoi tao cau truc rang buoc
void initConstrains(Constrains *constrains){
	int i, j;
	for(i = 0; i < NB_COL*NB_ROW; i++){
		for(j = 0; j < NB_COL*NB_ROW; j++){
			constrains->data[i][j] = 0;
		}
	}
	constrains->n = NB_COL*NB_ROW;
}

//Chuyen doi gia tri

//Toa do -> dinh
int indexOf(Point point){
	return (NB_ROW*point.x + point.y);
}

//Dinh -> Toa do
Point positionOfVertex(int vertex){
	Point point;
	point.x = vertex / NB_ROW;
	point.y = vertex % NB_COL;
	return point;
}

//Them rang buoc
int addConstrains(Constrains *constrains, Point source, Point target){
	int u = indexOf(source);
	int v = indexOf(target);
	if(constrains->data[u][v] == 0){
		constrains->data[u][v] = 1;
		constrains->data[v][u] = 1;
		return 1;
	}
	return 0;
}

//Tap rang buoc cua 1 dinh (Liet ke cac rang buoc cua 1 dinh)
ListCoord getConstrains(Constrains constrains, Point point){
	int i;
	int v = indexOf(point);
	ListCoord result;
	initListCoord(&result);
	for(i = 0; i < constrains.n; i++){
		if(constrains.data[v][i] == 1){
			appendListCoord(positionOfVertex(i), &result);
		}
	}
	return result;
}

/*                                   Cau truc KenKen                               */

//Khai bao cau truc KenKen
typedef struct{
	int cells[NB_ROW][NB_COL];
	Box boxCells[];
	int size;
	Constrains constrains;
}KenKen;

//Khoi tao KenKen rong
void initKenKen(KenKen *kenken){
	int i, j;
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			kenken->cells[i][j] = EMPTY;
		}
	}
	initConstrains(&kenken->constrains);
}

//Doc du lieu cua KenKen (Chu yeu doc vao Oper va Value va xac dinh danh sach toa do cua tung chuong)
void readKenKen(KenKen *kenken){
	freopen("kenken.txt", "r", stdin);
	int numberBox;
	scanf("%d", &numberBox);
	kenken->size = numberBox;
	int i, j = 0, val, x, y, endln, privious;
	char oper;
	for(i = 0; i < numberBox; i++){
		endln = false;
		while(!endln){
			//Kiem tra operation neu = 0 thi nhan luon value va thoat
			if(j == 0){
				scanf("%c", &oper);
				printf("%c", oper);
				kenken->boxCells[j].oper = oper;
				if(oper == '0'){
					//Nhan vao value
					scanf("%d", &val);
					kenken->boxCells[j].value = val;
					printf("%d\n", val);
					//Thoat
					endln = true;
					continue;
				}
				j++;
			}
			//Nhan vao value
			else if(j == 1){
				scanf("%d", &val);
				printf("%d\n", val);
				kenken->boxCells[j].value = val;
				j++;
		    }
			//Kiem tra vi tri cuoi hang
			scanf("%d", &privious);
			if(privious == 9999){
				endln = true;
			}
			}else{
				scanf("%d%d", &x, &y);
				Point point; 
				point.x = x; 
				point.y = y;
				printf("(%d, %d)\n", x, y);
				//Trich 1 chuong tu mang chuong va tu 1 cai chuong do them vao toa do
				kenken->boxCells[j].L.A[j] = point;
			}
		}
	}
}

//In
void printKenKen(KenKen kenken){
	int i, j;
	printf("KenKen:\n");
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			printf("%d ", kenken.cells[i][j]);
		}
	}
	printf("\n");
}

//Kiem tra trang thai ket thuc
int isFilledKenKen(KenKen kenken){
	int i, j;
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			if(kenken.cells[i][j] == EMPTY){
				return 0;
			}
		}
	}
}

//Tao rang buoc tu vi tri cho truoc
void spreadConstrainsFrom(Box AREA, Point position, Constrains *constrains, ListCoord *changeds){
	int row = position.x, col = position.y;
	int i, j, k;
	//Tao rang buoc theo cot
	for(i = 0; i < NB_ROW; i++){
		if(i != row){
			Point pos = {i, col};
			if(addConstrains(constrains, position, pos)){
				appendListCoord(pos, changeds);
			}
		}
	}
	//Tao rang buoc theo hang
	for(i = 0; i < NB_COL; i++){
		if(i != col){
			Point pos = {row, i};
			if(addConstrains(constrains, position, pos)){
				appendListCoord(pos, changeds);
			}
		}
	}
	//Tao rang buoc theo chuong
	for(k = 0; k <AREA.L.n; k++){
		Point pos = AREA.L.A[k]; //Lay 1 toa do trong chuong ra
		if(pos.x != row || pos.y != col){
			if(addConstrains(constrains, position, pos)){
				appendListCoord(pos, changeds);
			}
		}
	}
}

bool failOperBox(KenKen kenken, Box box, int n){
	int i, check = 0;
	for(i = 0; i < box.L.n; i++){
		if(box.oper == '+'){
			int x = box.L.A[i].x;
			int y = box.L.A[i].y;
			check += kenken.cells[x][y];
		}
		else if(box.oper == '-'){
			int x = box.L.A[i].x;
			int y = box.L.A[i].y;
			check -= kenken.cells[x][y];
		}
		else if(box.oper == '*'){
			int x = box.L.A[i].x;
			int y = box.L.A[i].y;
			check *= kenken.cells[x][y];
		}
		else{
			int x = box.L.A[i].x;
			int y = box.L.A[i].y;
			check /= kenken.cells[x][y];
		}
	}
	if(n > box.value) return false;
	return true;
}
//Tim mien gia tri cua o trong
List getAvailableValues(Point position, KenKen kenken){
	ListCoord posList = getConstrains(kenken.constrains, position);
	int availables[domainValue]; // 1->4
	int i;
	for(i = 1; i < domainValue; i++) availables[i] = 1;
	for(i = 0; i < posList.n; i++){
		Point pos = posList.A[i];
		if(kenken.cells[pos.x][pos.y] != EMPTY || failOperBox(kenken, kenken.boxCells[i], kenken.boxCells[i].L.n == false)){ 
		//Dang mang gia tri
			availables[kenken.cells[pos.x][pos.y]] = 0;
		}
		
	}
	List result;
	makeNullList(&result);
	for(i = 1; i < domainValue; i++){
		if(availables[i]){
			appendList(&result, i);
		}
	}
	return result;
}

//Xac dinh o duoc uu tien dien truoc
Point getNextMinDomainCell(KenKen kenken){
	int minLength = INF;
	int i, j;
	Point result;
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			if(kenken.cells[i][j] == EMPTY){
				Point pos = {i, j};
				int availablesLength = getAvailableValues(pos, kenken).n;
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
int KenKenBackTracking(KenKen *kenken){
	if(isFilledKenKen(*kenken)) return 1;
	Point position = getNextMinDomainCell(*kenken);
	List availables = getAvailableValues(position, *kenken);
	if(availables.n == 0){
		return 0;
	}
	int j;
	for(j = 0; j < availables.n; j++){
		int value = availables.data[j];
		kenken->cells[position.x][position.y] = value;
		exploredCounter++;
		if(KenKenBackTracking(kenken)){
			return 1;
		}
		kenken->cells[position.x][position.y] = EMPTY;
	}
	return 0;
}

//Lan truyen rang buoc va ket thuc bai toan
KenKen solveKenken(KenKen kenken){
	int i, j;
	//clear Constrains
	initConstrains(&kenken.constrains);
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			ListCoord history; // Danh sach cac toa do rang buoc cua 1 dinh
			initListCoord(&history);
			Point pos = {i, j};
			spreadConstrainsFrom(kenken.boxCells[i], pos, &kenken.constrains, &history);
		}
	}
	exploredCounter = 0;
	if(KenKenBackTracking(&kenken)) printf("Solved\n");
	else printf("Can not solve\n");
	printf("Explored %d states\n", exploredCounter);
	return kenken;
}

int main(){
	KenKen kenken;
	initKenKen(&kenken);
	readKenKen(&kenken);
	solveKenken(kenken);
	printKenKen(kenken);
	return 0;
}
