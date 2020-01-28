

#ifndef polynomial
#define polynomial

#include <string>
using namespace std;

class Polynomial
{
    // private attributes
    int* data;
    int data_size;

    public:
        Polynomial(int A[], int size);
        Polynomial();
        Polynomial(string fileName);
        ~Polynomial();
        int get_data_size();
        void print();
        bool operator==(const Polynomial & target) const;
        Polynomial operator+(const Polynomial & target);
        Polynomial derivative();
};
#endif
