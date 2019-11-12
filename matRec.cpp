#include <stdio.h>
using namespace std;

const int M=4;const int N=4;const int K=4;
//int A[M][K]; int B[K][N]; int C[M][N];// int M, int K, int N ;
void matmul(int A[M][K], int B[K][N], int C[M][N], int M, int K, int N ){
    for (int i=0; i<M; i++){
//	printf("i= %d", i);printf("\n");
	    for (int j=0; j<N; j++){
		//printf("j= %d", j);printf("\n");
		    C[i][j]=0;
		//int temp = 0;
		//printf("temp= %d", temp);printf("\n");
		    for (int k=0; k<K; k++){
			//printf("k= %d", k);printf("\n");
			//temp += A[i][k] * B[k][j]; //C is fixed while A is rowWise and B is columnWise
			C[i][j] += A[i][k] * B[k][j];  //C is updated rowWise
			//printf("Cij= %d", temp);printf("\n");
		    }	
	    }
    }
    
}
 
//void kernel16x16(Cl,Bl,Al){Cl+=Al+Bl;}

void display(int C[M][N], int M, int N){
    for (int i=0; i<M; i++){
	    for (int j=0; j<N; j++)
		{
		printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
}
 void blocks(){
     
     
 }
int main()
{
//int row, col, col1=3;
int A [M][K] ={{1,2,3,1},{4,5,6,1},{7,8,9,1},{1,1,1,1}};
int B [K][N] ={{1,2,3,1},{4,5,6,1},{7,8,9,1},{1,1,1,1}};
int C [M][N] ={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

  matmul(A, B, C, M, K, N); 
  display(C,M,N);
  printf("\n");
int A00[M/2][K/2] ={{1,2},{4,5}};
int B00[K/2][N/2] ={{1,2},{4,5}};
int C00[M/2][N/2] ={{0,0},{0,0}};
matmul(A00, B00, C00, M/2, K/2, N/2); 
display(C,M,N);
  
    return 0; 

}

	