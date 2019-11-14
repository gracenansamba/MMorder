#include <iostream>
#include <stdio.h>
using namespace std;

#define MAXROW 4
#define MAXCOL 4

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

	//--------------------MAKING A "MATRIX" IN A SINGLE ARRAY----------------------
	double* A = new double [MAXROW*MAXCOL];
	double* B = new double [MAXROW*MAXCOL];
	
	//enter values of A
	for(int i(0); i < MAXROW; ++i){
	   for(int j(0); j < MAXCOL; ++j){
			cout << "A[" << i << "][" << j <<  "]: ";
			cin >> A[(i * MAXCOL) + j];
		 }
	}
	
	//enter value of B
	for(int i(0); i < MAXROW; ++i){
		for(int j(0); j < MAXCOL; ++j){
			cout << "B[" << i << "][" << j <<  "]: ";
			cin >> B[(i * MAXCOL) + j];
		}
	}
	//----------------------MAKING 2D ARRAYS--------------------------------
	//Making 2-D arrays with variable sizes is a little odd in C++
	// see https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	// for my source on this
	
	//Create first dimension
	double ** A_PRIME = new double*[MAXROW];
	double ** B_PRIME = new double*[MAXROW];
	
	//This next step is to setup the second dimension
	for(int z = 0; z < MAXROW; ++z)
	{
		A_PRIME[z] = new double[MAXCOL];
		B_PRIME[z] = new double[MAXCOL];
	}
	
	
	//copy the numbers over to fill 2-D array
	//This is just me being lazy since we already have
	// the other matrix setup :)
	for(int i = 0; i < MAXROW; ++i)
	{
		for(int j = 0; j < MAXCOL; ++j)
		{
			A_PRIME[i][j] = A[(i*MAXROW) + j];
			B_PRIME[i][j] = B[(i*MAXROW) + j];
		}
	}
	
	//-------------------USING BOTH METHODS TO show how to print them--------------------
	//to print out the matrix
	print_array(A, MAXCOL, MAXROW);
	print_array(B, MAXCOL, MAXROW);
	print_2D_array(A_PRIME, MAXCOL, MAXROW);
	print_2D_array(B_PRIME, MAXCOL, MAXROW);
	
	return 0;
}

