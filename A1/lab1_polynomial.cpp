#include <iostream> //for console i/o
#include <fstream> //for file i/o
#include <cstdlib> //for everything
#include <cmath> //for math operations
#include <iomanip> //output formatting
#include "polynomial.h"
#include <fstream>

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
		Polynomial(){
			int rand = 123;//insert rng here
			data = new int [rand];
			data_size = rand;
			for (int index = 0; index < rand; index++){
				data[index] = 123//insert rng here
			}
		}

		Polynomial(string fileName){
			ifstream fin(fileName);
			//check for failure
			if (!fin.fail()){

			}

			fin.close();
			//my_ifstream.open(filename.c_str)
		}

        ~Polynomial(){
			delete[]data;
		}
};

int main()
{
	return EXIT_SUCCESS;
}
