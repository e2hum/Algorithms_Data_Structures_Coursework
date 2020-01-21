#include <iostream> //for console i/o
#include <fstream> //for file i/o
#include <cstdlib> //for everything
#include <cmath> //for math operations
#include <iomanip> //output formatting
#include <ctime>
#include "polynomial.h"

using namespace std; //set std namespace


Polynomial::Polynomial(int A[], int size){
	data = new int [size];
	data_size = size;
	for (int index = size; index > 0; index--){
		data[index] = A[index];
	}
}
Polynomial::Polynomial(){
	int randomNum = rand() %1001;
	data = new int [randomNum];
	data_size = randomNum;
	for (int index = 0; index < randomNum; index++){
		data[index] = rand() % 2001 + (-1000);
	}
}

void Polynomial::print()
{
	for (int index = 0; index < data_size; index++)
	{
		if (index == 0)
			cout << data[index] << "x^" << index;
		else
			cout << " + " << data[index] << "x^" << index;
	}
}

Polynomial::~Polynomial(){
	delete[]data;
}

int main()
{
	srand(time(0));
	Polynomial test;
	test.print();
	return EXIT_SUCCESS;
}
