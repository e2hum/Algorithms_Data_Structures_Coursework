#include <iostream> //for console i/o
#include <fstream> //for file i/o
#include <cstdlib> //for everything
#include <cmath> //for math operations
#include <iomanip> //output formatting
#include <ctime>
#include "polynomial.h"
#include <fstream>


using namespace std; //set std namespace


Polynomial::Polynomial(int A[], int size){
	data = new int [size];
	data_size = size;
	for (int index = 0; index < size; index++){
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

Polynomial::Polynomial(string fileName){
	ifstream fin(fileName.c_str());
	int size = 0;
	if (!fin.fail()){ //check for failure
		fin>>size; //first variable is size
		data = new int [size];
		data_size = size;
		for(int index = 0; index < size; index++){
			fin>>data[index];
		}
		fin.close();
	}
	//my_ifstream.open(filename.c_str)
}

Polynomial::~Polynomial(){
	delete[]data;
}

int Polynomial::get_data_size()
{
	return (*this).data_size;
}

void Polynomial::print()
{
	for (int index = 0; index < data_size; index++)
	{
		if (index == 0 && data[index] != 0)
			cout << data[index] << "x^" << index;
		else if (data[index] != 0)
			cout << " + " << data[index] << "x^" << index;
	}
}

bool Polynomial::operator==(const Polynomial & target) const
{
	for (int num = 0; num < (*this).data_size; num++)
	{
		if (data[num] != target.data[num])
			return false;
	}
	return true;
}

int main()
{
	srand(time(0));
	int A[3] = {1,2,3};
	int B[3] = {4,5,6};
	Polynomial test1(A,3);
	Polynomial test2(B,3);
	test1.print();
	cout << (test1 == test2);
	cout << (test1 == test1);
	return EXIT_SUCCESS;
}
