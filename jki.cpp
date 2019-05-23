#include <stdio.h>

int main()
{
//int row, col, col1=3;
int A [3][3] ={{1,2,3},{4,5,6},{7,8,9}};
int B [3][3] ={{1,2,3},{4,5,6},{7,8,9}};
int C [3][3] ={{0,0,0},{0,0,0},{0,0,0}};


for (int j=0; j<3; j++){
	printf("j= %d", j);printf("\n");
	for (int k=0; k<3; k++){
		printf("k= %d", k);printf("\n");
		int temp = B[k][j]; //B is fixed , then A and C are columnwise
		printf("temp= %d", temp);printf("\n");
		for (int i=0; i<3; i++){
			printf("i= %d", i);printf("\n");
			C[i][j] += A[i][k] * temp ;
			printf("Cij= %d", C[i][j]);printf("\n");
		}	
	}
}

for (int i=0; i<3; i++){
	for (int j=0; j<3; j++)
		{
		printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
	return 0;
}	