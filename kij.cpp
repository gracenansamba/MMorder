#include <stdio.h>

int main()
{

int A [2][3] ={{1,2,3},{4,5,6}};
int B [3][3] ={{1,2,3},{4,5,6},{7,8,9}};
int C [2][3] ={{0,0,0},{0,0,0}};


for (int k=0; k<3; k++){
	printf("k= %d", k);printf("\n");
	for (int i=0; i<2; i++){
		printf("i= %d",i);printf("\n");
		int temp = A[i][k]; //here A is fixed and then B and C are operated on rowwise
		printf("temp = %d",temp);printf("\n");
		for (int j=0; j<3; j++){
		printf("j= %d",j);printf("\n");
		C[i][j] +=temp * B[k][j];
		printf( " Cij = %d",C[i][j]);printf("\n");
		}	
	}
}

for (int i=0; i<2; i++){
	for (int j=0; j<3; j++)
		{
		printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
	return 0;
}	