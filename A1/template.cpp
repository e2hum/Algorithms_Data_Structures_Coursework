#include <iostream> //for console i/o
#include <fstream> //for file i/o
#include <cstdlib> //for everything
#include <cmath> //for math operations
#include <iomanip> //output formatting
#include "polynomial.h"

using namespace std; //set std namespace

int main()
{
	int a = 7, b = -1, c = 4;
	int* p1 = &a;
	*p1 = 2;
	int *p2 = &b;
	*p2 = *p1 * c;
	int* p3 = p1;
	p1 = p2;
	cout << a << " " << b << " " << c << endl<< *p1 << " " << *p2 <<" " << *p3 <<endl;
	return EXIT_SUCCESS;
}
