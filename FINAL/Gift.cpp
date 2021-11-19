#include <string.h>
#include <iostream>
#include "Gift.h"
using namespace std;



Gift::Gift(string n, int p, double s, bool a, int al, int ah)
    : name(n),price(p),size(s),any(a),ageLower(al),ageHigher(ah)
{}
void Gift::print()
   {
       if (any)
       {
           cout << "GIFT|name:" << name << " price:" << price << " size:" << size << " ageRange:"
                << "any" << endl; //any<< endl;
       }
       else
       {
           cout << "GIFT|name:" << name << " price:" << price << " size:" << size << " ageRange:" << ageLower << "-" << ageHigher << endl; //TODO: add more stuff
       }
   }