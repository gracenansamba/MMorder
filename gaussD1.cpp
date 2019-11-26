#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

#define MAXROW 4
template <typename T>
void printGauss(T A[MAXROW][MAXROW+1]);


template<typename T>
T fwdElim(T A [MAXROW][MAXROW+1]){
	for(int k = 0; k < MAXROW; k++)
	{
		for(int i = k+1; i < MAXROW; i++)
		{
			double f = A[i][k]/A[k][k];
			for(int j=k+1; j<=MAXROW; j++){ //make the col traingular 0
				A[i][j] -= A[k][j] * f;
				A[i][k]=0;
			}
		}
		cout<< "Forward Elimination: step " << k+1 <<endl;
		printGauss(A);
	}
}

template <typename T>
void bkdSub(T A[MAXROW][MAXROW+1]){
	double x[MAXROW];
	for(int i=MAXROW-1; i>=0;i--)
	{
		x[i] = A[i][MAXROW];
		for( int j=i+1; j<MAXROW; j++)
		{
			x[i] -= A[i][j]*x[j];
		}
		x[i]= x[i]/A[i][i];
	}
	for(int i=0; i<MAXROW; i++)
		cout << setprecision(5) << "\n x"<< i+1 <<"= "<< x[i] << endl;
}


template <typename T>
void printGauss(T A[MAXROW][MAXROW+1])
{
	for(int i(0); i < MAXROW; ++i){
		for(int j(0); j < MAXROW+1; ++j){
			cout << A[i][j] << "\t";
		}
		cout <<endl;
	}
}

int main(){

	double A[MAXROW][MAXROW+1] ={
					{4,3,-2,5,26.6654},
					{8,1,0,6,37.7765},
					{2,4,5,6,54.4432},
					{3,1,7,2,37.7779}
					};
	/*
	//enter values of A
	for(int i(0); i < MAXROW; ++i){
	   for(int j(0); j < MAXROW+1; ++j){
			cout << "A[" << i << "][" << j <<  "]: ";
			cin >> A[i][j];
		 }
	}*/

	cout << "Augumented Matrix A" << endl;
	printGauss(A);
   	cout << "\n" << endl;
	fwdElim(A);
	
	cout << ""<<endl;
	cout << "Backward substitution : values of x" << endl;
	bkdSub(A);
	cout << "\n"<<endl;
	//cout << "New Matrix after Gausian ELimination"<< endl;
	//printGauss(A);
	return 0;
}

