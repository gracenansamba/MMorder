// this is recursive1.cpp + printing info the subproblems, to illustrate the recursion:

#include <iostream>
using namespace std;

#define PRINT_INFO // print out the trace of operations as you recurse.

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
  recursive_matmul_PO2(C, A, B, M, RS, 0);
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


#define MMAX 64
int main(void)
{
   double *C = new double[MMAX*MMAX];
   double *A = new double[MMAX*MMAX];
   double *B = new double[MMAX*MMAX];

   // zero out C:
   for(int i = 0; i < MMAX; ++i)
     for(int j = 0; j < MMAX; ++j)
     {
       A[i*MMAX+j] = B[i*MMAX+j] = C[i*MMAX+j] = 0.0; // C is all zeros
       if(i==j)
       {
	 A[i*MMAX+j] = i+1;
         B[i*MMAX+j] = 100.0;
       }
     }

   // A and B contain random stuff right now...
   matmul_PO2(C, A, B, MMAX /* SHAPE : MMAXxMMAX matrices */, MMAX /* ROW STRIDE */ );

   print_mat(C, MMAX, MMAX, MMAX);

   delete[] C;
   delete[] A;
   delete[] B;


   return 0;
}



