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

Polynomial Polynomial::operator+(const Polynomial &target){
	int smaller_size = 0;
	
	Polynomial result;
	if (target.data_size>data_size){
		//saves size of smaller as the number of overlappinng
		smaller_size = (*this).get_data_size();
		//saves larger of the two into result
		result = target;
	}else{
		smaller_size = target.data_size;
		result = (*this);
	}

	//rewrites overlapping data with sum of two, non-overlapping stays
	for (int index = 0; index < smaller_size; index++){
		result.data[index] = (*this).data[index] + target.data[index];
	}
	return result;
	
}

Polynomial Polynomial::derivative(){
	//multiplies every coefficient with power
	for (int  index = 0; index < data_size; index++){
		data[index] *= index;
	}
	//removes last term and shifts array
	for (int  index = 0; index < data_size-1; index++){
		data[index] = data[index+1];
	}
	data[data_size-1] = 0;
}
int main()
{
	srand(time(0));
	int A[3] = {1,2,3};
	int B[3] = {4,5,6};
	Polynomial test1(A,3);
	Polynomial test2(B,3);
	//test1.print();
	Polynomial add = test1+test2;
	add.print();
	cout<<endl;
	add.derivative();
	add.print();
	/*
	cout << (test1 == test2);
	cout << (test1 == test1);
	*/return EXIT_SUCCESS;
}
