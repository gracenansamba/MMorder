// this is recursive.cpp + printing info the subproblems, to illustrate the recursion:
#include <stdio.h>
#include <iostream>
#include<omp.h>
#include <time.h>
using namespace std;

#define PRINT_INFO // print out the trace of operations as you recurse.
//#pragma omp parallel
//{ 
//the traditional ijk
template <typename T>
void matmul_ijk(T *C1, T *A, T *B, int M, int K, int N, int RS) // row major, shape C:MxN, A:MxK, B:KxN let M=K=N :square
{
#ifdef PRINT_INFO
	 cout << "matmul_ijk(" << M << ", " << K << "," << N << ")" << endl;
#endif
   for(int i = 0; i < M; ++i)
 	for(int j = 0; j < N; ++j)
	 {
	   T tmp = (T)0;
	    for(int k = 0; k < K; ++k)
	    	tmp += A[i*RS+k] * B[k*RS+j];    // A(i,k)*B(k,j)
		     C1[i*RS+j] += tmp;
	 }
}
//}

template <typename T, int N>
void simple_matmul(T *C, T *A, T *B, int RS) // row major, fixed NxN, need not be a power of 2, but square 
{
#ifdef PRINT_INFO
  cout << "simple_matmul(" << N << ")" << endl;
#endif
  
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
    {
      T tmp = (T)0;
      for(int k = 0; k < N; ++k)
	tmp += A[i*RS+k] * B[k*RS+j];       // A(i,k)*B(k,j)

      C[i*RS+j] += tmp;
    }
}

template <typename T>
void recursive_matmul_PO2(T *C, T *A, T *B, int M, int RS, int level) // SQUARE, Power of 2 only; row major; C zero or preinitialized.
{
  // assume A and B and C are square, powers of 2, all the same

#ifdef PRINT_INFO
  cout << "recursive_matmul_PO2(M = " << M << ", RS = " << RS << ", level = " << level <<")" << endl;
#endif

  if(M == 16)  // base cases
  {
    simple_matmul<T,16>(C, A, B, RS);
  }
  else if(M == 8)
  {
    simple_matmul<T,8>(C, A, B, RS);
  }
  else if(M == 4)
  {
    simple_matmul<T,4>(C, A, B, RS);
  }
  else if(M == 2)
  {
    simple_matmul<T,2>(C, A, B, RS);
  }
  else if(M == 1)
  {
#ifdef PRINT_INFO
    cout << "recursive_matmul_PO2(basecase M = 1: RS = " << RS << ")" << endl;
#endif

    //simple_matmul<T,1>(C, A, B);
    C[0] = A[0] * B[0];
  }
  else
  {
    // 4 blocks

    //C00 = A00 * B00 + A01 * B10 
    T *C00_ptr = &C[0];
    T *A00_ptr = &A[0];
    T *B00_ptr = &B[0];
    T *A01_ptr = &A[0*RS + M/2];   /* row 0, col M/2 */
    T *B10_ptr = &B[(M/2)*RS + 0]; /* row M/2, col 0 */

#ifdef PRINT_INFO
    cout << "C00 computations: for M=" << M << ", level = " << level << endl;
#endif    
    recursive_matmul_PO2(C00_ptr, A00_ptr, B00_ptr, M/2, RS, level+1); // C00 += A00*B00 
    recursive_matmul_PO2(C00_ptr, A01_ptr, B10_ptr, M/2, RS, level+1); // C00 += A01*B10 

    //C01 = A00 * B01 + A01 * B11
    T *C01_ptr = &C[0];
    T *B01_ptr = &B[0*RS + M/2];    // row 0, col M/2 
    T *B11_ptr = &B[(M/2)*RS+ M/2]; // row M/2, col M/2 

#ifdef PRINT_INFO
    cout << "C01 computations: for M=" << M << ", level = " << level << endl;
#endif    
    recursive_matmul_PO2(C01_ptr, A00_ptr, B01_ptr, M/2, RS, level+1); // C00 += A00*B00
    recursive_matmul_PO2(C01_ptr, A01_ptr, B11_ptr, M/2, RS, level+1); // C00 += A01*B10

    //C10 = A10 * B00 + A11 * B10
    T *C10_ptr = &C[(M/2)*RS + 0];
    T *A10_ptr = &A[(M/2)*RS + 0];
    T *A11_ptr = &A[(M/2)*RS + M/2];	    
    
#ifdef PRINT_INFO
    cout << "C10 computations: for M=" << M << ", level = " << level << endl;
#endif    
    recursive_matmul_PO2(C10_ptr, A10_ptr, B00_ptr, M/2, RS, level+1); // C00 += A00*B00 
    recursive_matmul_PO2(C10_ptr, A11_ptr, B10_ptr, M/2, RS, level+1); // C00 += A01*B10 

    //C11 = A10 * B01 + A11 * B11
    T *C11_ptr = &C[(M/2)*M + M/2];
    
#ifdef PRINT_INFO
    cout << "C11 computations: for M=" << M << ", level = " << level << endl;
#endif    
    recursive_matmul_PO2(C11_ptr, A10_ptr, B01_ptr, M/2, RS, level+1); // C00 += A00*B00 
    recursive_matmul_PO2(C11_ptr, A11_ptr, B11_ptr, M/2, RS, level+1); // C00 += A01*B10 
  }

}

// this is the API that the application uses:
template <typename T>
void matmul_PO2(T *C, T *A, T *B, int M, int RS) // SQUARE, Power of 2 only; row major; C zero or preinitialized.
{
  //double start1 = omp_get_wtime();
  recursive_matmul_PO2(C, A, B, M, RS, 0);
 // double end1 = omp_get_wtime();
 // printf("time for for recursive: %lf\n", (end1-start1)); //time to run the recursive function
}


template<typename T>
void print_mat(T *A, int M, int N, int RS) // row major, MxN in shape
{
  for(int i = 0; i < M; ++i) // each row
  {
    for(int j = 0; j < N; j++)
      cout << A[i*RS+j] << " ";

   cout << endl;
  }
}


#define MMAX 16 
int main(void)
{
   double *C = new double[MMAX*MMAX];
   double *C1 = new double[MMAX*MMAX];
   double *A = new double[MMAX*MMAX];
   double *B = new double[MMAX*MMAX];

   // zero out C:
   for(int i = 0; i < MMAX; ++i)
     for(int j = 0; j < MMAX; ++j)
     {
       A[i*MMAX+j] = B[i*MMAX+j] = C[i*MMAX+j] = 0.0; // C is all zeros
        A[i*MMAX+j] = B[i*MMAX+j] = C1[i*MMAX+j] = 0.0; // C1 is all zeros
       for (int i = 0; i<MMAX*MMAX; i++)
	  for (int j= 0; j<MMAX*MMAX; j++){
		 A[i]=rand ()%10;
	           B[i]=rand ()%10;}
      /* if (i==j)
	{
	  A[i*MMAX+j]=1;
	  B[i*MMAX+j]=2;
	}
       else if(i!=j)
       {
	 A[i*MMAX+j] = i;
         B[i*MMAX+j] = 1.0;
       }*/
     }

   // A and B contain random stuff right now...
   	    double start1 = omp_get_wtime();
   	  #pragma omp parallel
   	  {
		    //double start1 = omp_get_wtime();
   matmul_PO2(C, A, B, MMAX /* SHAPE : MMAXxMMAX matrices */, MMAX /* ROW STRIDE */ );
   		  //double end1 = omp_get_wtime();
		 // printf("time for for Recursive: %lf\n", (end1-start1)); //time to run the recursive function
   	}


	    cout << "Matrix A"<<endl;
	       print_mat(A, MMAX, MMAX, MMAX);  
	       cout << "Matrix B"<<endl;
	       cout << "" <<endl;
		 print_mat(B, MMAX, MMAX, MMAX);

	  double end1 = omp_get_wtime();
	  printf("*****time for for Recursive: %lf\n", (end1-start1)); //time to run the recursive function
   //cout << "Matrix A"<<endl;
   //print_mat(A, MMAX, MMAX, MMAX);   cout << "Matrix B"<<endl;
   //cout << "" <<endl;
  // print_mat(B, MMAX, MMAX, MMAX);  
  cout << "Matrix C for recursive" <<endl;
   print_mat(C, MMAX, MMAX, MMAX);
//check the ijk result
	cout << "" <<endl;
	  start1 = omp_get_wtime();
	 #pragma omp parallel
	{
		// double start1 = omp_get_wtime();
    matmul_ijk(C1, A, B, MMAX, MMAX, MMAX, MMAX);
    		//double end1 = omp_get_wtime();
		// printf("time for for ijk: %lf\n", (end1-start1)); //time to run the ijk function
    	}
	 end1 = omp_get_wtime(); 
	printf("****time for for ijk: %lf\n", (end1-start1)); //time to run the ijk function
    cout<< "MAtrix C1 for ijk"<<endl;
	print_mat(C1, MMAX, MMAX, MMAX); 		
   delete[] C;
   delete[] C1;
   delete[] A;
   delete[] B;
/*	#pragma omp parallel
   {
	   cout << "hello world"<<endl;
   }*/

   return 0;
}



