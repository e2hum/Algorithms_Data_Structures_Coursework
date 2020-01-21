#pragma once

#ifndef polynomial
#define polynomial

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
        void print();
};
#endif
