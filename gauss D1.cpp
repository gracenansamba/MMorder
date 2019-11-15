#include <iostream>
#include <stdio.h>
using namespace std;

#define MAXROW 4
#define MAXCOL 4


template<typename T>
void fwdElim(T **A, T *B, int M){
	int i,j,k;
	for(k = 1; k < M-1; k++)
	{
		for(i = k+1; i < M; i++)
		{
			for( j=k; j<M; j++) //make the col traingular 0
				A[i][j] = ((A[i][k])/ (A[k][k])) * (A[k][j]);
		}
		/* ####### HERE ######### */
		B[i] -= (A[i][j]/A[k][k]) * B[k];
	}
}

template <typename T>
T* bkdSub(T **A, T *B, int M){
	int i,j;
	T* X = new T();
	for( i=M-1; i>0;i--)
	{
		for( j=i+1; j<M+1; j++)
		{
			B[i]=B[i]-A[i][j]*X[j];
		}
		X[i]= B[i]/A[i][i];
		cout <<" X"<< i << " "<< X[i] << endl;
	}
	return X;
}
template<typename T>
void print_Gaus(T *A, T *B, int M){



}

//These methods show you how to pass the pointer around to a method
template <typename T>
void print_array(T *array, int number_of_columns, int number_of_rows)
{
	for(int i(0); i < number_of_rows; ++i){
		for(int j(0); j < number_of_columns; ++j){
			cout << array[i*number_of_columns+j] << ", ";
		}
		cout <<endl;
	}
}

template <typename T>
void print_2D_array(T **array, int number_of_columns, int number_of_rows)
{
	for(int i(0); i < number_of_rows; ++i){
		for(int j(0); j < number_of_columns; ++j){
			cout << array[i][j] << ", ";
		}
		cout <<endl;
	}
}

int main(){

	double ** A_PRIME = new double*[MAXROW];
	for(int z = 0; z < MAXROW; ++z)
	{
		A_PRIME[z] = new double[MAXCOL];
	}
	
	double* B = new double [MAXCOL];
	
	//enter values of A
	for(int i(0); i < MAXROW; ++i){
	   for(int j(0); j < MAXCOL; ++j){
			cout << "A[" << i << "][" << j <<  "]: ";
			cin >> A_PRIME[i][j];
		 }
	}
	
	//enter value of B
	for(int j(0); j < MAXCOL; ++j){
		cout << "B[" << j <<  "]: ";
		cin >> B[j];
	}
	
	print_2D_array(A_PRIME, MAXCOL, MAXROW);
	
	fwdElim(A_PRIME, B, 4);
	double* res = bkdSub(A_PRIME, B, 4);
	
	print_array(B, 1, MAXROW);
	print_array(res, 1, MAXROW);
	print_2D_array(A_PRIME, MAXCOL, MAXROW);
	
	return 0;
}

