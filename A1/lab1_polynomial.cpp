#include <iostream> //for console i/o
#include <fstream> //for file i/o
#include <cstdlib> //for everything
#include <cmath> //for math operations
#include <iomanip> //output formatting
#include <ctime>
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
			int randomNum = rand() %1001;
			data = new int [randomNum];
			data_size = randomNum;
			for (int index = 0; index < randomNum; index++){
				data[index] = rand() % 2001 + (-1000);
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
	srand(time(0));
	return EXIT_SUCCESS;
}
