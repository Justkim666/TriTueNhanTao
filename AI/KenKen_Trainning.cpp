#include<stdio.h>
#include<stdlib.h>
#define NB_COL 4
#define NB_ROW 4
#define EMPTY 0
#define MAXLENGTH 100
#define DOMAINVALUE 4
#define INF 999999
#include<math.h>

/*                     Khai bao cau truc danh sach               */

//Khai bao cau truc danh sach
typedef struct{
	int data[MAXLENGTH];
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

/*                    Khai bao danh sach toa do                  */
//Khai bao cau truc toa do
typedef struct{
	int x, y;
}Coord;

//Khai bao cau truc danh sach toa do
typedef struct{
	Coord P[];
	int n;
}ListCoord;

//Khoi tao danh sach toa do
void initListCoord(ListCoord *list){
	list->n = 0;
}

//Them phan tu vao cuoi danh sach
void appendListCoord(Coord coord, ListCoord *listcoord){
	listcoord->P[listcoord->n] = coord;
	listcoord->n++;
}
/*                    Khai bao danh sach toa do                  */

/*                   Chuyen doi gia tri                          */

//Toa do -> Dinh
int coordToVertex(Coord coord){
	return (NB_ROW * coord.x + coord.y);
}

//Dinh -> Toa do
Coord vertexToCoord(int vertex){
	Coord coord;
	coord.x = vertex / NB_ROW;
	coord.y = vertex % NB_COL;
	return coord;
}

/*                   Chuyen doi gia tri                          */


/*                    Khai bao cau truc rang buoc                */

//Cau truc rang buoc
typedef struct{
	int C[NB_COL*NB_ROW][NB_COL*NB_ROW];
	int n;
}Constrains;

//Khoi tao cau truc rang buoc
void initConstrains(Constrains *constrains){
	int i, j;
	for(i = 0; i < NB_COL*NB_ROW; i++){
		for(j = 0; j < NB_COL*NB_ROW; j++){
			constrains->C[i][j] = 0;
		}
	}
	constrains->n = NB_COL*NB_ROW;
}

//Them rang buoc
int addConstrains(Constrains *constrains, Coord source, Coord target){
	int u = coordToVertex(source);
	int v = coordToVertex(target);
	if(constrains->C[u][v] == 0){
		constrains->C[u][v] = 1;
		constrains->C[v][u] = 1;
		return 1;
	}
	return 0;
}

//Tap rang buoc cua 1 dinh
ListCoord getConstrains(Constrains constrains, Coord coord){
	int i;
	int v = coordToVertex(coord);
	ListCoord result;
	initListCoord(&result);
	for(i = 0; i < constrains.n; i++){
		if(constrains.C[v][i] == 1){
			appendListCoord(vertexToCoord(i), &result);
		}
	}
	return result;
}

/*                        Khai bao cau truc KenKen                  */

//Khai bao cau truc cua 1 chuong
typedef struct{
	ListCoord dsToaDoChuong;
	char oper;
	int value;
}Chuong;

//Khai bao cau truc KenKen
typedef struct{
	int Matrix[NB_ROW][NB_COL];
	Chuong chuong[]; //khi doc file se la vi tri dau tien
	Constrains constrains;
	int n; //giu vi tri dau tien do
}KenKen;

/*                        Khai bao cau truc KenKen                  */

/*                        Lan truyen rang buoc                      */

void spreadConstrains(Chuong chuong1, Coord coord, Constrains *constrains, ListCoord *changes){
	int row = coord.x, col = coord.y;
	int i;
	//Tao rang buoc theo cot
	for(i = 0; i < NB_ROW; i++){
		if(i != row){
			Coord pos = {i, col};
			if(addConstrains(constrains, coord, pos)){
				//Them vao danh sach cac toa do changes neu co the them rang buoc
				appendListCoord(pos, changes);
			}
		}
	}
	//Tao rang buoc theo hang
	for(i = 0; i < NB_COL; i++){
		if(i != col){
			Coord pos = {row, i};
			if(addConstrains(constrains, coord, pos)){
				appendListCoord(pos, changes);
			}
		}
	}
	//Tao rang buoc theo chuong
	for(i = 0; i < chuong1.dsToaDoChuong.n; i++){
		Coord a = chuong1.dsToaDoChuong.P[i];
		if(a.x != coord.x && a.y != coord.y){
			if(addConstrains(constrains, coord, a)){
				appendListCoord(a, changes);
			}
		}
	}
}

//Tim mien gia tri cua o trong
List getAvailableValues(Chuong chuong1, Coord coord, KenKen kenken){
	ListCoord posList = getConstrains(kenken.constrains, coord); //Lay tap cac toa do cua rang buoc
	int availables[DOMAINVALUE]; // 1->4
	int i, j, k;
	for(i = 1; i <= DOMAINVALUE; i++) availables[i] = 1;
	for(i = 0; i < posList.n; i++){
		Coord b = posList.P[i];
		if(kenken.Matrix[b.x][b.y] != EMPTY){
			//VD Matrix[(1,2)] = 3 => 3 da co nen availables[3] = 0 
			availables[kenken.Matrix[b.x][b.y]] = 0;
		}
	}
	//Xu ly tren chuong
	int checkValue = 0;
	bool stop = false;
	for(i = 1; i <= DOMAINVALUE; i++){
		if(availables[i] != 0){
			stop = false;
			for(j = 0; j < chuong1.dsToaDoChuong.n; i++){
				if(stop == true) break;
				if(kenken.Matrix[chuong1.dsToaDoChuong.P[i-1].x][chuong1.dsToaDoChuong.P[i-1].y] != 0){
					switch(chuong1.oper){
						case '+':
							checkValue = i + kenken.Matrix[chuong1.dsToaDoChuong.P[i-1].x][chuong1.dsToaDoChuong.P[i-1].y];
							if(checkValue > chuong1.value){
								availables[i] = 0;
								stop = true;
							}
							break;
						case '-':
							checkValue = abs(i - kenken.Matrix[chuong1.dsToaDoChuong.P[i-1].x][chuong1.dsToaDoChuong.P[i-1].y]);
							if(checkValue < chuong1.value){
								availables[i] = 0;
								stop = true;
							}
							break;
						case 'x':
							checkValue =i + kenken.Matrix[chuong1.dsToaDoChuong.P[i-1].x][chuong1.dsToaDoChuong.P[i-1].y];
							if(checkValue > chuong1.value){
								availables[i] = 0;
								stop = true;
							}
							break;
						case '/':
							checkValue /= kenken.Matrix[chuong1.dsToaDoChuong.P[i-1].x][chuong1.dsToaDoChuong.P[i-1].y];
							if(checkValue < chuong1.value){
								availables[i] = 0;
								stop = true;
							}
							break;
					}
				}
			}
		}
	}
	List result;
	makeNullList(&result);
	for(i = 1; i <= DOMAINVALUE; i++){
		if(availables[i]){
			appendList(&result, i);
		}
	}
	return result;
}
//xac dinh 1 toa do thuoc chuong nao
Chuong defineChuongFromCoord(KenKen kenken, Coord coord){
	int i, j;
	for(i = 0; i < kenken.n; i++){
		for(j = 0; j < kenken.chuong[i].dsToaDoChuong.n; j++){
			if(kenken.chuong[i].dsToaDoChuong.P[j].x = coord.x && kenken.chuong[i].dsToaDoChuong.P[j].y == coord.y){
				return kenken.chuong[i];
			}
		}
	}
}
//Xac dinh o duoc uu tien dien truoc
Coord getNextMinDomainCell(KenKen kenken){
	int minLength = INF;
	int i, j;
	Coord result;
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			if(kenken.Matrix[i][j] == EMPTY){
				Coord pos = {i, j};
				Chuong box = defineChuongFromCoord(kenken, pos);
				int availablesLength = getAvailableValues(box, pos, kenken).n;
				if(availablesLength < minLength){
					minLength = availablesLength;
					result = pos;
				}
			}
		}
	}
	return result;
}

int isFilledKenKen(KenKen kenken){
	int i, j;
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			if(kenken.Matrix[i][j] == 0){
				return 0;
			}
		}
	}
	return 1;
}
//Giai quyet bai toan
int exploredCounter = 0;
int KenKenBackTracking(KenKen *kenken){
	if(isFilledKenKen(*kenken)) return 1;
	Coord coord = getNextMinDomainCell(*kenken);
	Chuong chuong2 = defineChuongFromCoord(*kenken, coord);
	List availables = getAvailableValues(chuong2, coord, *kenken);
	if(availables.n == 0){
		return 0;
	}
	int j;
	for(j = 0; j < availables.n; j++){
		int value = availables.data[j];
		kenken->Matrix[coord.x][coord.y] = value;
		exploredCounter++;
		if(KenKenBackTracking(kenken)){
			return 1;
		}
		kenken->Matrix[coord.x][coord.y] = EMPTY;
	}
	return 0;
}

//Lan truyen rang buoc va ket thuc bai toan
KenKen solveKenKen(KenKen kenken){
	int i, j;
	//Clear constrains
	initConstrains(&kenken.constrains);
	for(i = 0; i < NB_ROW; i++){
		for(j = 0; j < NB_COL; j++){
			ListCoord history;
			initListCoord(&history);
			Coord pos = {i, j};
			Chuong chuong2 = defineChuongFromCoord(kenken, pos);
			spreadConstrains(chuong2, pos, &kenken.constrains, &history);
		}
	}
	exploredCounter = 0;
	if(KenKenBackTracking(&kenken)) printf("Solved\n");
	else printf("Can not solve\n");
	printf("Explored %d states\n", exploredCounter);
	return kenken;
}

//doc file
void readFile(KenKen *kenken){
	freopen("kenken.txt", "r", stdin);
	int i, n, value, x, y, j, index;
	char oper;
	scanf("%d", &n);
	bool endln;
	kenken->n = n;
	for(i = 0; i < n; i++){
		initListCoord(&kenken->chuong[i].dsToaDoChuong);
		index = 0;
		endln = false, j = 0;
		while(endln == false){
			if(j == 0){
				getchar();
				scanf("%c", &oper);
				scanf("%d", &value);
				printf("%c  %d ", oper, value);
 				kenken->chuong[i].oper = oper;
				kenken->chuong[i].value = value;
				j++;
			}
			scanf("%d", &x);
			if(x == 9999){
				endln = true;
				break;
			}
			printf("%d ", x);
			if(x != 9999){
				scanf("%d", &y);
				printf("%d ", y);
			}
			Coord t;
			t.x = x;
			t.y = y;
			appendListCoord(t, &kenken->chuong[i].dsToaDoChuong);
			printf("(%d, %d) ", kenken->chuong[i].dsToaDoChuong.P[index].x, kenken->chuong[i].dsToaDoChuong.P[index].y);
			index++;
			kenken->Matrix[x][y] = 0;
		}
		printf("\n");
	}
}

//In
void print(KenKen kenken){
	int i, j;
	printf("\n-----------------");
	for(i = 0; i < NB_ROW; i++){
		printf("\n|");
		for(j = 0; j < NB_COL; j++){
			printf(" %d |", kenken.Matrix[i][j]);
		}
		printf("\n-----------------");
	}
}

int main(){
	KenKen kenken;
	readFile(&kenken);
	print(kenken);
	KenKen result = solveKenKen(kenken);
	print(kenken);
	return 0;
}
