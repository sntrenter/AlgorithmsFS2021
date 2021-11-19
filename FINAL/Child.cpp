#include <string.h>
#include <iostream>
#include "Child.h"
using namespace std;

//string Child:: name;
//int Child:: age;

Child::Child(string n, int a)
    : name(n),age(a)
{
    //name = n;
    //age = a;
}
void Child::print()
{
    cout << "CHILD|name:" << name << " age:" << age << endl;
}
