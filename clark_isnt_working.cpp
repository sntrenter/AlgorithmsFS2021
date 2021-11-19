//Sam Trenter
//Algorithms FS2020
//Makefile is not mine but used with permission
//
//I use "trees" to reduce the number of nodes I have to test, at the cost of memory
//example of how to run:
// make;./gifting examples/ex1_3child_6gifts.txt writeme.sol 3 6
#include <iostream>
#include <list>
#include <fstream>
#include <regex>
#include <map>
#include <math.h>
#include <iomanip>
#include <string.h>

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
        dist.insert(pair<string, Gift>(c.name, g));
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

list<Child> children;
list<Child>::iterator cit = children.begin();
list<Gift> gifts;
list<Gift>::iterator git = gifts.begin();
list<Node> nodes;
list<Node>::iterator nit = nodes.begin();

void getProblem(string filename, int numChild, int numGift)
{
    /* Def: Reads problem into children and gifts globals*/
    ifstream inputFile;

    inputFile.open(filename);
    string tempStrng;
    for (int i = 0; i < numChild; i++)
    { // read in numchild rows
        string tempString;
        string childName;
        int childAge;
        inputFile >> childName;  // child IDs in first column
        inputFile >> tempString; // throw away second column
        inputFile >> childAge;   // child ages in third column
        Child c = Child(childName, childAge);
        children.insert(cit, c);
    }
    inputFile >> tempStrng;
    inputFile >> tempStrng;
    inputFile >> tempStrng;
    inputFile >> tempStrng;
    //gift BS
    for (int i = 0; i < numGift; i++)
    {
        string tempStrng;
        int tempInt;
        string name;
        int price;
        double size;
        bool any = false;
        int ageLower;
        int ageHigher;

        inputFile >> name;  // read in gift ID
        inputFile >> price; // read in price
        inputFile >> size;  // read in size

        // read in suitable ages
        inputFile >> tempStrng;
        if (tempStrng == "any")
        { // suitable for any age
            //suitableAges[i][0] = 0; // designate age range as 0 to 21
            //suitableAges[i][1] = 21;
            any = true;
        }
        else
        {
            // determine if ages are single or double digits
            int numChars = 0; // count number of chars in string
            while (tempStrng[numChars] != '\0')
                numChars++;

            switch (numChars)
            {

            case 3:
            {                                      // both ages are single digit
                ageLower = (int)tempStrng[0] - 48; // subtract 30 from ASCII value to get correct int
                ageHigher = (int)tempStrng[2] - 48;
                break;
            }

            case 4:
            { // first age single digit, second is double digit
                ageLower = (int)tempStrng[0] - 48;
                tempInt = (int)tempStrng[2] - 48; // first digit of second age
                tempInt *= 10;
                tempInt += (int)tempStrng[3] - 48; // convert to double digit age
                ageHigher = tempInt;
                break;
            }

            case 5:
            {                                     // both ages are double digit
                tempInt = (int)tempStrng[0] - 48; // first digit of first age
                tempInt *= 10;
                tempInt += (int)tempStrng[1] - 48; // convert to double digit age
                ageLower = tempInt;

                tempInt = (int)tempStrng[3] - 48; // first digit of second age
                tempInt *= 10;
                tempInt += (int)tempStrng[4] - 48; // convert to double digit age
                ageHigher = tempInt;
                break;
            }

            default:
            {
                cout << numChars << " chars" << endl;
            }
            }
        }
        Gift g = Gift(name, price, size, any, ageLower, ageHigher);
        gifts.insert(git, g);
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
    inputFile.close();
}

bool canRecieveGift(Gift g, Child c)
{
    /* Def: Checks if a child c is eligable to recive gift g*/
    if (g.any || (c.age >= g.ageLower && c.age <= g.ageHigher))
    {
        return true;
    }
    return false;
}

double calculateE(Node n, int P, int N)
{
    /* Def: Calculates a nodes e value with a given P and N value*/
    list<double> e = {};
    list<double>::iterator eit = e.begin();
    for (auto c : children)
    {
        pair<multimap<string, Gift>::iterator, multimap<string, Gift>::iterator> ret;
        ret = n.dist.equal_range(c.name);
        double eValue = 0;
        for (multimap<string, Gift>::iterator it = ret.first; it != ret.second; ++it)
        {
            Gift g = it->second;
            eValue = eValue + double(g.price);
        }
        e.insert(eit, abs((double(P) / double(N)) - eValue));
    }
    double sum = 0;
    for (std::list<double>::iterator it = e.begin(); it != e.end(); ++it)
    {
        sum += *it;
    }
    return sum;
}

bool inGiftRange(Node n, int maxGifts)
{
    /* Def: does node n have a child with too many gifts?*/
    for (auto c : children)
    {
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
    /* 
        Def: Checks if a node is valid, we already check that eachchild can recieve gift so we 
        don't need to do it here
    */
    for (auto c : children)
    {
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
            }
            if (g.size > 2.0)
            {
                large = true;
            }
            numGifts = numGifts + 1;
        }
        if (large == false || medium == false)
        {
            return false;
        }
        if (numGifts > maxGifts || numGifts < minGifts)
        {
            return false;
        }
    }
    return true;
}

void saveNode(Node n, double e, string filename)
{
    /* Def: Saves node n with it's e value in the given filename*/
    ofstream writefile;
    writefile.open(filename);
    writefile << "Sum_e_i " << e;
    string name = "";
    for (auto itr = n.dist.begin(); itr != n.dist.end(); itr++)
    {
        if (itr->first != name)
        {
            name = itr->first;
            writefile << "\n"
                      << itr->first;
        }
        writefile << " " << itr->second.name;
    }

    writefile.close();
}

void distGifts(string writeFile)
{
    /* 
        Def: "meat and potatos of out algorithm, uses children,gifts, and nodes
        to create layers of our tree. Then it will find the node in the last layer 
        with the lowest e value.
    */

    //maxgifts = round(gifts/children) + 1
    int maxGifts = round((double)gifts.size() / (double)children.size()) + 1;
    //mingifts = round(gifts/children) - 1
    int minGifts = round((double)gifts.size() / (double)children.size()) - 1;
    //sum of retial price for each gift
    int P = 0;
    for (auto g : gifts)
    {
        P = P + g.price;
    }
    cout << "------" << endl;
    cout <<"sum of retial price for each gift P: "<< P << endl;
    //Total number of children
    int N = children.size();
    cout << "Total number of children N: " << N << endl;
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
    cout << "Size of the Nodes:" << endl;
    cout << nodes.size() << endl;
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
                if (canRecieveGift(g, c)) // || (i>8) )
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
        i++;
        nodes.swap(newNodes);
        nit = nodes.begin();
        newNodes.clear();
        nNit = newNodes.begin();
        cout << nodes.size() << endl;
    }
    cout << "------" << endl;

    Node lowestNode = nodes.front();
    double lowestE = calculateE(lowestNode, P, N);
    for (auto n : nodes) 
    {
        if (isNodeValid(n, maxGifts, minGifts) && calculateE(n, P, N) < lowestE)
        {
            lowestNode = n;
            lowestE = calculateE(n, P, N);
        }
    }
    cout << "Lowest Node:" << endl;
    lowestNode.print();
    cout << "Lowest E: " << lowestE << endl;
    saveNode(lowestNode, lowestE, writeFile);
}

int main(int argc, char *argv[])
{

    cout << "There are " << argc << " arguments:\n";
    for (int count{0}; count < argc; ++count)
    {
        cout << count << ' ' << argv[count] << '\n';
    }
    cout << "Start\n";
    string filename = "examples/ex1_3child_6gifts.txt";
    string writeFile = "writefile";
    int numChild = 3;
    int numGift = 6;

    getProblem(filename, numChild, numGift);
    distGifts(writeFile);
    cout << "End\n";
    return 0;
}
