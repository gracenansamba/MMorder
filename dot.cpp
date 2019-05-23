#include <stdio.h>


int main()
{
int size =4;
int A [size] ={1,1,1,2};
int B [size] ={1,2,3,2};
int C [size] ={0,0,0,0};

		int temp=0;
		for (int i=0; i<size; i++){
			//printf("i= %d",i);printf("\n");
			//temp += A[i]*B[i];
			C[i] =  A[i]*B[i];
			printf( "Ci = %d",C[i]);printf("\n");
			temp += C[i];
		}
		printf( "The dot product = %d", temp);printf("\n");
	return 0;
}	

