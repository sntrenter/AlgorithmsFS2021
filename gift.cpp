#include <iostream>
#include <list>
#include <fstream>
#include <regex>
#include <map>
#include <math.h>
#include <iomanip>
//#include <format>
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
                 << "any" << endl; //any<< endl;
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
    if (g.any || (c.age >= g.ageLower && c.age <= g.ageHigher))
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

double calculateE(Node n, int P, int N)
{
    list<double> e = {};
    list<double>::iterator eit = e.begin();
    for (auto c : children)
    {
        pair<multimap<string, Gift>::iterator, multimap<string, Gift>::iterator> ret;
        ret = n.dist.equal_range(c.name);
        //cout << c.name << endl;
        double eValue = 0;
        for (multimap<string, Gift>::iterator it = ret.first; it != ret.second; ++it)
        {
            Gift g = it->second;
            eValue = eValue + double(g.price);
            //cout << g.price << endl;
        }
        e.insert(eit, abs((double(P) / double(N)) - eValue));
    }
    //for (auto e : e)
    //{
    //    cout << setprecision(2) << e << ",";
    //}
    //cout << endl;
    double sum = 0;
    for (std::list<double>::iterator it = e.begin(); it != e.end(); ++it)
    {
        sum += *it;
    }
    //cout << setprecision(6) << sum << endl;
    return sum;
}

bool inGiftRange(Node n, int maxGifts)
{
    for (auto c : children)
    {
        //c.print();
        pair<multimap<string, Gift>::iterator, multimap<string, Gift>::iterator> ret;
        ret = n.dist.equal_range(c.name);
        int numGifts = 0;
        for (multimap<string, Gift>::iterator it = ret.first; it != ret.second; ++it)
        {
            Gift g = it->second;
            numGifts = numGifts + 1;
        }
        if (numGifts > maxGifts)
        {
            cout << "Child given too many gifts!" << endl;
            return false;
        }
    }
    return true;
}

bool isNodeValid(Node n, int maxGifts, int minGifts)
{
    for (auto c : children)
    {
        //c.print();
        pair<multimap<string, Gift>::iterator, multimap<string, Gift>::iterator> ret;
        ret = n.dist.equal_range(c.name);
        int numGifts = 0;
        bool large = false;
        bool medium = false;
        for (multimap<string, Gift>::iterator it = ret.first; it != ret.second; ++it)
        {
            Gift g = it->second;
            if (g.size >= 1.0 && g.size <= 2.0)
            {
                medium = true;
                //cout << "medium" << endl;
            }
            if (g.size > 2.0)
            {
                large = true;
                //cout << "large" << endl;
            }
            numGifts = numGifts + 1;
        }
        //cout << "numgifts: " << numGifts << endl;
        if (large == false || medium == false)
        {
            //cout << "didn't have both types of gifts" << endl;
            return false;
        }
        if (numGifts > maxGifts || numGifts < minGifts)
        {
            //cout << "too few gifts" << endl;
            return false;
        }
    }
    return true;
}

void distGifts()
{

    //maxgifts = round(gifts/children) + 1
    int maxGifts = round(gifts.size() / children.size()) + 1;
    //mingifts = round(gifts/children) - 1
    int minGifts = round(gifts.size() / children.size()) - 1;
    //sum of retial price for each gift
    int P = 0;
    for (auto g : gifts)
    {
        P = P + g.price;
    }
    cout << P << endl;
    //Total number of children
    int N = children.size();
    cout << N << endl;
    cout << "------" << endl;
    //Fill in first layer
    Gift firstGift = gifts.front();
    gifts.pop_front();
    for (auto c : children)
    {
        if (canRecieveGift(firstGift, c))
        {
            multimap<string, Gift> emptymap;
            Node n = Node(firstGift, c, emptymap);
            nodes.insert(nit, n);
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
                if (canRecieveGift(g, c))
                {
                    multimap<string, Gift> newMap = n.dist;
                    Node n = Node(g, c, newMap);
                    //if (inGiftRange(n, maxGifts))
                    //{
                    newNodes.insert(nNit, n);
                    //}
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
    Node lowestNode = nodes.front();
    double lowestE = calculateE(lowestNode, P, N);
    cout << "##########" << endl;
    //DEBUG
    list<Node> DEBUGnodes = {};
    list<Node>::iterator DEBUGnit = DEBUGnodes.begin();
    for (auto n : nodes) //go over the first one again TODO:Fix
    {
        //n.print();
        //cout << setprecision(8) << calculateE(n, P, N) << endl;
        //cout << "##########" << endl;
        if(isNodeValid(n, maxGifts, minGifts) && calculateE(n, P, N) < 12.0)
        {
            DEBUGnodes.insert(DEBUGnit,n);
        }
        if (isNodeValid(n, maxGifts, minGifts) && calculateE(n, P, N) < lowestE)
        {
            lowestNode = n;
            lowestE = calculateE(n, P, N);
        }
    }
    for (auto n : DEBUGnodes)
    {
        cout << "#######" << endl;
        cout << setprecision(5) << calculateE(n,P,N) << endl;
        n.print();
        cout << "#######" << endl;
    }
    cout << "Lowest Node:" << endl;
    lowestNode.print();
    cout << "Lowest E: " << lowestE << endl;
}

int main()
{
    //Child c1 = Child("c1", 10);
    //Child c2 = Child("c2", 15);
    //Child c3 = Child("c3", 20);
    //Gift g1 = Gift("g1", 10, 1.1, false, 9, 11);
    //Gift g2 = Gift("g2", 10, 1.1, false, 14, 16);
    //Gift g3 = Gift("g3", 10, 2.1, true, 0, 0);
    //Gift g4 = Gift("g3", 10, 2.1, true, 0, 0);
    //canRecieveGift(g3, c1);
    //canRecieveGift(g3, c2);
    //canRecieveGift(g3, c3);

    //Node n1 = Node(g1, c1, {});
    //n1.print();
    //cout << "##############################" << endl;
    //Node n2 = Node(g2, c2, n1.dist);
    //n2.print();
    //cout << "##############################" << endl;
    //Node n3 = Node(g3, c1, n2.dist);
    //n3.print();
    //cout << "##############################" << endl;
    //Node n4 = Node(g4, c2, n3.dist);
    //n4.print();
    //cout << "##############################" << endl;
    //children.insert(cit, c1);
    //children.insert(cit, c2);
    //children.insert(cit,c3);
    //bool temp = inGiftRange(n4, 1);
    //cout << boolalpha << "in gift range?: " << temp << endl;

    cout << "Start\n";
    string problem = "ex1_3child_6gifts";
    getProblem("ex1_5child_14gifts"); //problem);
    distGifts();
    cout << "End\n";
    return 0;
}