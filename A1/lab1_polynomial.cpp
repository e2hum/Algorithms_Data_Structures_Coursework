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

void Polynomial::print() {
	// skips all beginning zeros
	bool first = false;
	for (int index = data_size-1; index >= 0; index--) {
		if (data[index] != 0 && first == false) {
			cout << data[index] << "x^" << index;
			first = true;
		}
		else if (data[index] == 0 && data[index] !=0 && first == true)
			cout << " + " << index;
			
		else if (data[index] != 0 && first == true)
			cout << " + " << data[index] << "x^" << index;
		
	}
	cout << endl;
}

bool Polynomial::operator==(const Polynomial & target) const {
	for (int num = 0; num < (*this).data_size; num++)
	{
		if ((*this).data[num] != target.data[num])
			return false;
	}
	return true;
}

Polynomial Polynomial::operator*(const Polynomial & target) const {
	int size = ((*this).data_size - 1) * (target.data_size - 1) + 1;
	int A[size] = {0};
	Polynomial newPoly(A, size);
	for (int index = 0; index < (*this).data_size; index++) {
		for (int num = 0; num < target.data_size; num++) {
			newPoly.data[index + num] += (*this).data[index] * target.data[num];
		}
		newPoly.print();
	}

	return newPoly;
}
int main()
{
	srand(time(0));
	int A[4] = {1,1,1};
	int B[3] = {1,1,1};
	Polynomial test1(A,3);
	Polynomial test2(B,3);
	test1.print();
	cout << (test1 == test2) << endl;;
	cout << (test1 == test1) << endl;
	(test1 * test2).print();
	return EXIT_SUCCESS;
}
