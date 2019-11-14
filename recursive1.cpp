#include <iostream>
using namespace std;

template <typename T, int N>
void simple_matmul(T *C, T *A, T *B, int RS) // row major, fixed NxN, need not be a power of 2, but square 
{
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
void matmul_PO2(T *C, T *A, T *B, int M, int RS) // SQUARE, Power of 2 only; row major; C zero or preinitialized.
{
  // assume A and B and C are square, powers of 2, all the same

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
    
    matmul_PO2(C00_ptr, A00_ptr, B00_ptr, M/2, RS); // C00 += A00*B00 
    matmul_PO2(C00_ptr, A01_ptr, B10_ptr, M/2, RS); // C00 += A01*B10 

    //C01 = A00 * B01 + A01 * B11
    T *C01_ptr = &C[0];
    T *B01_ptr = &B[0*RS + M/2];    // row 0, col M/2 
    T *B11_ptr = &B[(M/2)*RS+ M/2]; // row M/2, col M/2 
    
    matmul_PO2(C01_ptr, A00_ptr, B01_ptr, M/2, RS); // C00 += A00*B00
    matmul_PO2(C01_ptr, A01_ptr, B11_ptr, M/2, RS); // C00 += A01*B10

    //C10 = A10 * B00 + A11 * B10
    T *C10_ptr = &C[(M/2)*RS + 0];
    T *A10_ptr = &A[(M/2)*RS + 0];
    T *A11_ptr = &A[(M/2)*RS + M/2];	    
    
    matmul_PO2(C10_ptr, A10_ptr, B00_ptr, M/2, RS); // C00 += A00*B00 
    matmul_PO2(C10_ptr, A11_ptr, B10_ptr, M/2, RS); // C00 += A01*B10 

    //C11 = A10 * B01 + A11 * B11
    T *C11_ptr = &C[(M/2)*M + M/2];
    
    matmul_PO2(C11_ptr, A10_ptr, B01_ptr, M/2, RS); // C00 += A00*B00 
    matmul_PO2(C11_ptr, A11_ptr, B11_ptr, M/2, RS); // C00 += A01*B10 
  }

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


#define MMAX 32
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

   return 0;
}



