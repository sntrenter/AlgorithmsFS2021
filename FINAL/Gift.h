#ifndef GIFT_H
#define GIFT_H
#include <string.h>
#include <iostream>
using namespace std;

class Gift
{

public:
    string name;
    int price;
    double size;
    bool any;
    int ageLower;
    int ageHigher;
    Gift(string n, int p, double s, bool a, int al, int ah);

    void print();
};

#endif