#include <iostream>
#include <list>
#include <fstream>
#include <regex>
using namespace std;



class Child {
    public:
        string name;
        int age;
        Child(string n,int a)
        {
            name = n;
            age = a;
        }
        void print()
        {
            cout << "name:" << name << " age:" << age << endl;
        }
};
class Gift {
    public:
        string name;
        int price;
        double size;
        bool any;
        int ageLower;
        int ageHigher;

};
class Node {
    public:
        string name = "Test";
};

list <Child> children = {};
list<Child>::iterator cit = children.begin();
list <Gift> gifts = {};
list<Gift>::iterator git = gifts.begin();


void getProblem(string filename){
    ifstream file;
    regex crgx("(Child[0-9]+)	age	([0-9]+)");
    regex grgx("(G[0-9]+)	([0-9]+)	([0-9]+.[0-9]+)	([0-9]+-[0-9]+|any)");
    smatch match;

    cout << filename << "\n";
    filename = "examples/" + filename + ".txt";
    file.open(filename.c_str());
    string lntxt;
    while(getline(file,lntxt)){
        cout << lntxt << endl;
        if(regex_search(lntxt,match,crgx)){
            children.insert(cit,Child(match[1],stoi(match[2])));
        }
        if(regex_search(lntxt,match,grgx)){

        }
    }
    cout<<"CHILDREN:"<<endl;
    for (auto c: children){
        c.print();
    }
        

}


int main() {
  cout << "Start\n";
    getProblem("ex1_3child_6gifts");
    //Child test = Child("hello",10);
    //test.print();
  cout << "End\n";
  return 0;
}