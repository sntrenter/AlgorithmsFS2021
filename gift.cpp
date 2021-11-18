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
    //bool isEqual(Node lhs)
    //{
    //    if(dist == lhs.dist)
    //    {
    //        return true;
    //    }
    //    return false;
    //}
};

list<Child> children = {};
list<Child>::iterator cit = children.begin();
list<Gift> gifts = {};
list<Gift>::iterator git = gifts.begin();

list<Node> DebugNodes = {};
list<Node>::iterator dnit = DebugNodes.begin();

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
    int i = 2;
    for (auto g : gifts)
    {
        list<Node> newNodes = {};
        list<Node>::iterator nNit = newNodes.begin();
        for (auto n : nodes)
        {
            for (auto c : children)
            {
                if (canRecieveGift(g, c))// || (i>8) )
                {
                    multimap<string, Gift> newMap = n.dist;
                    Node n = Node(g, c, newMap);
                    //if (inGiftRange(n, maxGifts))
                    //{
                    //bool found = (find(DebugNodes.begin(),DebugNodes.end(),n)!=DebugNodes.end());
                    //if(found){ cout << "found!"<<endl;}

                    newNodes.insert(nNit, n);
                    //}
                }
            }
        }
        i++;
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


void DEBUGTEST()
{
    getProblem("ex1_5child_14gifts");
    cout << "--------------------------------------------START Testing" << endl;
    cit = children.begin();
    Child c1 = *cit;
    c1.print();
    advance(cit,1);
    Child c2 = *cit;
    c2.print();
    advance(cit,1);
    Child c3 = *cit;
    c3.print();
    advance(cit,1);
    Child c4 = *cit;
    c4.print();
    advance(cit,1);
    Child c5 = *cit;
    c5.print();
    advance(cit,1);

    git = gifts.begin();
    Gift g1 = *git;
    g1.print();
    advance(git,1);
    Gift g2 = *git;
    g2.print();
    advance(git,1);
    Gift g3 = *git;
    g3.print();
    advance(git,1);
    Gift g4 = *git;
    g4.print();
    advance(git,1);
    Gift g5 = *git;
    g5.print();
    advance(git,1);
    Gift g6 = *git;
    g6.print();
    advance(git,1);
    Gift g7 = *git;
    g7.print();
    advance(git,1);
    Gift g8 = *git;
    g8.print();
    advance(git,1);
    Gift g9 = *git;
    g9.print();
    advance(git,1);
    Gift g10 = *git;
    g10.print();
    advance(git,1);
    Gift g11 = *git;
    g11.print();
    advance(git,1);
    Gift g12 = *git;
    g12.print();
    advance(git,1);
    Gift g13 = *git;
    g13.print();
    advance(git,1);
    Gift g14 = *git;
    g14.print();

    cout << canRecieveGift(g7,c1) << canRecieveGift(g8,c1) << canRecieveGift(g9,c1) << endl;
    cout << canRecieveGift(g4,c2) << canRecieveGift(g5,c2) << canRecieveGift(g12,c2) << endl;
    cout << canRecieveGift(g10,c3) << canRecieveGift(g13,c3) << endl;
    cout << canRecieveGift(g2,c4) << canRecieveGift(g6,c4) << canRecieveGift(g11,c4) << canRecieveGift(g14,c4) << endl;
    cout << canRecieveGift(g1,c5) << canRecieveGift(g3,c5) <<  endl;
    //multimap<string, Gift> emptymap;
    //Node n = Node(g, c, newMap);
    //multimap<string, Gift> newMap = n.dist;
    int P = 0;
    for (auto g : gifts)
    {
        P = P + g.price;
    }
    cout << P << endl;
    //Total number of children
    int N = children.size();
    cout << N << endl;
    cout << "------------ manual"<< endl;
    cout << "---1" << endl;
    multimap<string, Gift> emptymap;
    Node n1 = Node(g1,c5,emptymap);
    n1.print();
    cout << "---2" << endl;
    multimap<string, Gift> newMap = n1.dist;
    Node n2 = Node(g2,c4,newMap);
    n2.print();
    cout << "---3" << endl;
    newMap = n2.dist;
    Node n3 = Node(g3,c5,newMap);
    n3.print();
    cout << "---4" << endl;
    newMap = n3.dist;
    Node n4 = Node(g4,c2,newMap);
    n4.print();
    cout << "---5" << endl;
    newMap = n4.dist;
    Node n5 = Node(g5,c2,newMap);
    n5.print();
    cout << "---6" << endl;
    newMap = n5.dist;
    Node n6 = Node(g6,c4,newMap);
    n6.print();
    cout << "---7" << endl;
    newMap = n6.dist;
    Node n7 = Node(g7,c1,newMap);
    n7.print();
    cout << "---8" << endl;
    newMap = n7.dist;
    Node n8 = Node(g8,c1,newMap);
    n8.print();
    cout << "---9" << endl;
    newMap = n8.dist;
    Node n9 = Node(g9,c1,newMap);
    n9.print();
    cout << "---10" << endl;
    newMap = n9.dist;
    Node n10 = Node(g10,c3,newMap);
    n10.print();
    cout << "---11" << endl;
    newMap = n10.dist;
    Node n11 = Node(g11,c4,newMap);
    n11.print();
    cout << "---12" << endl;
    newMap = n11.dist;
    Node n12 = Node(g12,c2,newMap);
    n12.print();
    cout << "---13" << endl;
    newMap = n12.dist;
    Node n13 = Node(g13,c3,newMap);
    n13.print();
    cout << "---14" << endl;
    newMap = n13.dist;
    Node n14 = Node(g14,c4,newMap);
    n14.print();
    
    cout << calculateE(n14,P,N) << endl;

    children.clear();
    gifts.clear();
    cit = children.begin();
    git = gifts.begin();
    cout << "--------------------------------------------END Testing" << endl;

    for(auto c:children)
    {
        cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<< endl;
        c.print();
        for(auto g : gifts)
        {
            g.print();
            cout << boolalpha<< "can recieve: " <<canRecieveGift(g,c) << endl;
        }
    }
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<< endl;
    DebugNodes = {n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12,n13,n14};
    int maxGifts = round((double)gifts.size() / (double)children.size()) + 1;
    //mingifts = round(gifts/children) - 1
    int minGifts = round((double)gifts.size() / (double)children.size()) - 1;

    bool x = isNodeValid(n14,maxGifts,minGifts);
}



int main(int argc, char *argv[])
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

    //cout << "There are " << argc << " arguments:\n";
    //for (int count{ 0 }; count < argc; ++count)
    //{
    //    cout << count << ' ' << argv[count] << '\n';
    //}

    //TODO: get problem 5children 14gifts working

    //getProblem("ex1_5child_14gifts");
    //cout << "--------------------------------------------START Testing" << endl;
    //cit = children.begin();
    //Child c1 = *cit;
    //c1.print();
    //advance(cit,1);
    //Child c2 = *cit;
    //c2.print();
    //advance(cit,1);
    //Child c3 = *cit;
    //c3.print();
    //advance(cit,1);
    //Child c4 = *cit;
    //c4.print();
    //advance(cit,1);
    //Child c5 = *cit;
    //c5.print();
    //advance(cit,1);
//
    //git = gifts.begin();
    //Gift g1 = *git;
    //g1.print();
    //advance(git,1);
    //Gift g2 = *git;
    //g2.print();
    //advance(git,1);
    //Gift g3 = *git;
    //g3.print();
    //advance(git,1);
    //Gift g4 = *git;
    //g4.print();
    //advance(git,1);
    //Gift g5 = *git;
    //g5.print();
    //advance(git,1);
    //Gift g6 = *git;
    //g6.print();
    //advance(git,1);
    //Gift g7 = *git;
    //g7.print();
    //advance(git,1);
    //Gift g8 = *git;
    //g8.print();
    //advance(git,1);
    //Gift g9 = *git;
    //g9.print();
    //advance(git,1);
    //Gift g10 = *git;
    //g10.print();
    //advance(git,1);
    //Gift g11 = *git;
    //g11.print();
    //advance(git,1);
    //Gift g12 = *git;
    //g12.print();
    //advance(git,1);
    //Gift g13 = *git;
    //g13.print();
    //advance(git,1);
    //Gift g14 = *git;
    //g14.print();
//
    //cout << canRecieveGift(g7,c1) << canRecieveGift(g8,c1) << canRecieveGift(g9,c1) << endl;
    //cout << canRecieveGift(g4,c2) << canRecieveGift(g5,c2) << canRecieveGift(g12,c2) << endl;
    //cout << canRecieveGift(g10,c3) << canRecieveGift(g13,c3) << endl;
    //cout << canRecieveGift(g2,c4) << canRecieveGift(g6,c4) << canRecieveGift(g11,c4) << canRecieveGift(g14,c4) << endl;
    //cout << canRecieveGift(g1,c5) << canRecieveGift(g3,c5) <<  endl;
    ////multimap<string, Gift> emptymap;
    ////Node n = Node(g, c, newMap);
    ////multimap<string, Gift> newMap = n.dist;
    //int P = 0;
    //for (auto g : gifts)
    //{
    //    P = P + g.price;
    //}
    //cout << P << endl;
    ////Total number of children
    //int N = children.size();
    //cout << N << endl;
    //cout << "------------ manual"<< endl;
    //cout << "---1" << endl;
    //multimap<string, Gift> emptymap;
    //Node n1 = Node(g1,c5,emptymap);
    //n1.print();
    //cout << "---2" << endl;
    //multimap<string, Gift> newMap = n1.dist;
    //Node n2 = Node(g2,c4,newMap);
    //n2.print();
    //cout << "---3" << endl;
    //newMap = n2.dist;
    //Node n3 = Node(g2,c5,newMap);
    //n3.print();
    //cout << "---4" << endl;
    //newMap = n3.dist;
    //Node n4 = Node(g4,c2,newMap);
    //n4.print();
    //cout << "---5" << endl;
    //newMap = n4.dist;
    //Node n5 = Node(g5,c2,newMap);
    //n5.print();
    //cout << "---6" << endl;
    //newMap = n5.dist;
    //Node n6 = Node(g6,c4,newMap);
    //n6.print();
    //cout << "---7" << endl;
    //newMap = n6.dist;
    //Node n7 = Node(g7,c1,newMap);
    //n7.print();
    //cout << "---8" << endl;
    //newMap = n7.dist;
    //Node n8 = Node(g8,c1,newMap);
    //n8.print();
    //cout << "---9" << endl;
    //newMap = n8.dist;
    //Node n9 = Node(g9,c1,newMap);
    //n9.print();
    //cout << "---10" << endl;
    //newMap = n9.dist;
    //Node n10 = Node(g10,c3,newMap);
    //n10.print();
    //cout << "---11" << endl;
    //newMap = n10.dist;
    //Node n11 = Node(g11,c4,newMap);
    //n11.print();
    //cout << "---12" << endl;
    //newMap = n11.dist;
    //Node n12 = Node(g12,c2,newMap);
    //n12.print();
    //cout << "---13" << endl;
    //newMap = n12.dist;
    //Node n13 = Node(g13,c3,newMap);
    //n13.print();
    //cout << "---14" << endl;
    //newMap = n13.dist;
    //Node n14 = Node(g14,c4,newMap);
    //n14.print();
    //
    //cout << calculateE(n14,P,N) << endl;
//
    //cit = children.begin();
    //git = gifts.begin();
    //cout << "--------------------------------------------END Testing" << endl;
    
    //DEBUGTEST();

    //cout << "Start\n";
    //string problem = "ex1_3child_6gifts";
    getProblem("ex1_5child_14gifts"); //problem);
    distGifts();
    //cout << "End\n";
    return 0;
}