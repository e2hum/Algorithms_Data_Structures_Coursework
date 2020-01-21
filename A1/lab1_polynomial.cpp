#include <iostream> //for console i/o
#include <fstream> //for file i/o
#include <cstdlib> //for everything
#include <cmath> //for math operations
#include <iomanip> //output formatting
#include "polynomial.h"

using namespace std; //set std namespace

class Polynomial
{
    // private attributes
    int* data;
    int data_size;

    public:
        Polynomial(int A[], int size){
			data = new int [size];
			data_size = size;
			for (int index = size; index > 0; index--){
				data[index] = A[index];
			}
		}
        ~Polynomial(){
			delete[]data;
		}
};

int main()
{
	return EXIT_SUCCESS;
}
