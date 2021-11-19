#ifndef CHILD_H
#define CHILD_H
#include <string.h>
#include <iostream>
using namespace std;

class Child
{

     public :
        string name;
        int age;
        Child(string n,int a);
        void print();

};
 
#endif