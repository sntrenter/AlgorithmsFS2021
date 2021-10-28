#include <iostream>
#include <list>
#include <fstream>
#include <regex>
#include <map>
using namespace std;

class Child
{
public:
    string name;
    int age;
    Child(string n, int a)
    {
        name = n;
        age = a;
    }
    void print()
    {
        cout << "CHILD|name:" << name << " age:" << age << endl;
    }
};
class Gift
{
public:
    string name;
    int price;
    double size;
    bool any;
    int ageLower;
    int ageHigher;
    Gift(string n, int p, double s, bool a, int al, int ah)
    {
        name = n;
        price = p;
        size = s;
        any = a;
        ageLower = al;
        ageHigher = ah;
    }
    void print()
    {
        if (any)
        {
            cout << "GIFT|name:" << name << " price:" << price << " size:" << size << " ageRange:"
                 << "any" << endl; //any<< endl;//TODO: add more stuff
        }
        else
        {
            cout << "GIFT|name:" << name << " price:" << price << " size:" << size << " ageRange:" << ageLower << "-" << ageHigher << endl; //TODO: add more stuff
        }
    }
};
class Node
{
public:
    multimap<string, Gift> dist;
    Node(Gift g, Child c, multimap<string, Gift> prev)
    {
        dist = prev;
        dist.insert({c.name, g});
    }
    void print()
    {
        for (multimap<string, Gift, less<string>>::const_iterator iter = dist.begin();
             iter != dist.end(); ++iter)
        {
            Gift g = iter->second;
            cout << iter->first << "|||";
            g.print();
        }
    }
};

list<Child> children = {};
list<Child>::iterator cit = children.begin();
list<Gift> gifts = {};
list<Gift>::iterator git = gifts.begin();
list<Node> nodes = {};
list<Node>::iterator nit = nodes.begin();

void getProblem(string filename)
{
    ifstream file;
    regex crgx("(Child[0-9]+)	age	([0-9]+)");
    regex grgx("(G[0-9]+)	([0-9]+)	([0-9]+.[0-9]+)	([0-9]+-[0-9]+|any)");
    regex ageRangergx("([0-9]+)-([0-9]+)");
    smatch match;
    smatch match2;

    cout << filename << "\n";
    filename = "examples/" + filename + ".txt";
    file.open(filename.c_str());
    string lntxt;
    while (getline(file, lntxt))
    {
        cout << lntxt << endl;
        if (regex_search(lntxt, match, crgx))
        {
            children.insert(cit, Child(match[1], stoi(match[2])));
        }
        if (regex_search(lntxt, match, grgx))
        {
            if (match[4].str() == "any")
            {
                gifts.insert(git, Gift(match[1], stoi(match[2]), stod(match[3]), true, 0, 0));
            }
            else
            {
                string ageRange = match[4].str();
                regex_search(ageRange, match2, ageRangergx);
                gifts.insert(git, Gift(match[1], stoi(match[2]), stod(match[3]), false, stoi(match2[1]), stoi(match2[2])));
            }
        }
    }
    cout << "CHILDREN:" << endl;
    for (auto c : children)
    {
        c.print();
    }
    cout << "GIFTS:" << endl;
    for (auto g : gifts)
    {
        g.print();
    }
}



bool canRecieveGift(Gift g, Child c)
{
    //return true;
    if (g.any || (c.age > g.ageLower && c.age < g.ageHigher))
    {
        //c.print();
        //cout << "can recieve" << endl;
        //g.print();
        //cout << "###########################" << endl;
        return true;
    }

    //c.print();
    //cout << "can't recieve" << endl;
    //g.print();
    //cout << "###########################" << endl;
    return false;
}

void distGifts()
{

    //for (auto c : children)
    //{
    //    c.print();
    //}
    //Fill in first layer
    Gift firstGift = gifts.front();
    gifts.pop_front();
    for (auto c : children)
    {
        if (canRecieveGift(firstGift,c))
        {
            multimap<string,Gift> emptymap;
            Node n = Node(firstGift,c,emptymap);
            nodes.insert(nit,n);
        }
    }
    //move through the rest of the layers
    for (auto g : gifts)
    {
        list<Node> newNodes = {};
        list<Node>::iterator nNit = newNodes.begin();
        for (auto n : nodes)
        {
            for (auto c : children)
            {
                if(canRecieveGift(g,c))
                {
                    multimap<string,Gift> newMap = n.dist;
                    Node n = Node(g,c,newMap);
                    newNodes.insert(nNit,n);
                }
            }
        }
        nodes.swap(newNodes);
        nit = nodes.begin();
        newNodes.clear();
        nNit = newNodes.begin();
        cout << nodes.size() << endl;
        
    }
    //print nodes
    cout << "##########" << endl;
    for (auto n : nodes)
    {
        n.print();
        cout << "##########" << endl;
    }


}

int main()
{
    Child c1 = Child("c1", 10);
    Child c2 = Child("c2", 15);
    Child c3 = Child("c3", 20);
    Gift g1 = Gift("g1", 10, 1.1, false, 9, 11);
    Gift g2 = Gift("g2", 10, 1.1, false, 14, 16);
    Gift g3 = Gift("g3", 10, 1.1, true, 0, 0);

    //canRecieveGift(g3, c1);
    //canRecieveGift(g3, c2);
    //canRecieveGift(g3, c3);

    //Node n1 = Node(g1,c1,{});
    //n1.print();
    //cout << "##############################" << endl;
    //Node n2 = Node(g2,c2,n1.dist);
    //n2.print();
    //cout << "##############################" << endl;
    //Node n3 = Node(g3,c3,n2.dist);
    //n3.print();
    //cout << "##############################" << endl;
    //Node n4 = Node(g1,c3,n3.dist);
    //n4.print();
    //cout << "##############################" << endl;

    cout << "Start\n";
    getProblem("ex1_3child_6gifts");
    distGifts();
    cout << "End\n";
    return 0;
}