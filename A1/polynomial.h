// Evan Hum and Jeremy Antonio Phy
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
        Polynomial operator+(const Polynomial & target) const;
        Polynomial operator-(const Polynomial & target) const;
        Polynomial operator*(const Polynomial & target) const;
        Polynomial derivative();
        friend class PolynomialTest;
};

class PolynomialTest
{
    public:
    bool test_constructors1();
    bool test_constructors2();
    bool test_constructors3();
    bool test_constructors4();
    bool test_operator_equals();
    bool test_operator_addition();
    bool test_operator_subtraction();
    bool test_operator_multiply();
    bool test_derivative();
    void run();
};
#endif
