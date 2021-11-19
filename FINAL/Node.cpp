#include <string.h>
#include <iostream>
#include <map>
#include "Gift.h"
#include "Child.h"
#include "Node.h"
using namespace std;

Node::Node(Gift g, Child c, multimap<string, Gift> prev)
{
    dist = prev;
    dist.insert(pair<string, Gift>(c.name, g));
}
void Node::print()
{
    for (multimap<string, Gift, less<string>>::const_iterator iter = dist.begin();
         iter != dist.end(); ++iter)
    {
        Gift g = iter->second;
        cout << iter->first << "|||";
        g.print();
    }
}