#Sam Trenter
#algorithms gift giving

from os import name
import re

def getProblem(file):
    with open("examples/" + file + ".txt") as f:
        lines = f.readlines()
    children = []
    gifts = []
    for i in lines:
        if re.search(r'Child[1-9]\sage\s*[1-9][0-9]*',i):
            print(i.split())
            children.append(Children(i.split()[0],i.split()[2]))
        elif re.search(r'G[1-9][0-9]*\s[1-9][0-9]*\s[0-9][0-9]*.[0-9][0-9]*\s([1-9][0-9]*-[1-9][0-9]*|any)',i):
            print(i.split())
            gifts.append(Gifts(i.split()[0],i.split()[1],i.split()[2],i.split()[3]))
    return (children,gifts)

class Children:
    def __init__(self,name,age):
        self.name = name
        self.age = age
    def __str__(self):
        return "name: " + self.name + " age: " + self.age

class Gifts:
    def __init__(self,name,price,size,ages):
        self.name = name
        self.price = price
        self.size = size
        self.ages = ages
    def __str__(self):
        return "name: " + self.name + " price: " + self.price + " size: " + self.size + " ages: " + self.ages


def main():
    print("start")
    #read in file(regex?)
    filename = "ex1_3child_6gifts" #turn this to a list
    (children,gifts) = getProblem(filename)
    print(children[0])
    print(gifts[0])
    print("end")

main()