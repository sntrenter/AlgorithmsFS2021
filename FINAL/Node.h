#ifndef NODE_H
#define NODE_H
#include <string.h>
#include <iostream>
#include <map>
#include "Gift.h"
#include "Child.h"
using namespace std;

class Node
{

     public :
        multimap<string, Gift> dist;
        int age;
        Node(Gift g, Child c, multimap<string, Gift> prev);
        void print();

};
 
#endif