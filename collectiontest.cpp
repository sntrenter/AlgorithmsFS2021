#include <iostream>
#include <list>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;

class Node
{
public:
    string name = "Test";
};

int main()
{
    cout << "Start\n";
    vector<int> test;
    test.assign(1, 7);

    for (std::vector<int>::iterator it = test.begin(); it != test.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    test.clear();
    test.assign(1, 3);
    test.assign(1, 4);
    test.assign(1, 5);
    test.assign(1, 6);

    for (std::vector<int>::iterator it = test.begin(); it != test.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    cout << "End\n";
    return 0;
}