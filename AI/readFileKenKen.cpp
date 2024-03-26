#include<stdio.h>
void readFile(){
	freopen("kenken.txt", "r", stdin);
	int length, value, x = 0, y = 0, j = 0;
	bool endln;
	char oper;
	scanf("%d", &length);
	for(int i = 1; i <= length; i++){
		endln = false, j = 0;
		while(endln == false){
			if(j == 0){
				getchar();
				scanf("%c", &oper);
				scanf("%d", &value);
				printf("%c  %d", oper, value);
				j++;
			}
			scanf("%d", &x);
			if(x == 9999){
				endln = true;
				break;
			}
			printf(" %d", x);
			if(x != 9999){
				scanf("%d", &y);
				printf(" %d", y);
			}
		}
		printf("\n");
	}
}
int main(){
	readFile();
	return 0;
}
