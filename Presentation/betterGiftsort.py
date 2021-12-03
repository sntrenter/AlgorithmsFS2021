#Sam Trenter
#sorting gifts

from os import name
import re

def getProblem(file):
    with open("examples/" + file + ".txt") as f:
        lines = f.readlines()
    children = []
    gifts = []
    for i in lines:
        if re.search(r'Child[1-9]\sage\s*[0-9]*',i):
            #print(i.split())
            children.append(Children(i.split()[0],i.split()[2]))
        elif re.search(r'G[1-9][0-9]*\s[1-9][0-9]*\s[0-9][0-9]*.[0-9][0-9]*\s([0-9]*-[0-9]*|any)',i):
            #print(i.split())
            gifts.append(Gifts(i.split()[0],i.split()[1],i.split()[2],i.split()[3]))
    return (children,gifts)


def canReceiveGift(g,c):
    if g.ages == "any":
        return True
    al = int(g.ages.split("-")[0])
    ah = int(g.ages.split("-")[1])
    if int(c.age) >= al and int(c.age) <= ah:
        return True

    return False



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
        self.numchildren = 0
    def __str__(self):
        return "name: " + self.name + " price: " + self.price + " size: " + self.size + " ages: " + self.ages + "|" + str(self.numchildren)
    def __lt__(self,other):
        return self.numchildren < other.numchildren

def main():
    print("start")
    #read in file(regex?)
    filename = "ex1_20_child_40gifts" #turn this to a list
    (children,gifts) = getProblem(filename)
    for c in children:
        print(c)
    for g in gifts:
        print(g)
    print(len(children))
    print(len(gifts))
    #print(canReceiveGift(gifts[0],children[2]))
    #print(canReceiveGift(gifts[1],children[2]))
    #print(canReceiveGift(gifts[2],children[2]))
    #print(canReceiveGift(gifts[3],children[2]))
    #print(canReceiveGift(gifts[4],children[2]))
    for g in gifts:
        for c in children:
            if canReceiveGift(g,c):
                g.numchildren += 1
    gifts.sort()
    for g in gifts:
        print(g)
        
    for g in gifts:
        #print(g)
        print(g.name + "	" + g.price + "	" + g.size + "	" + g.ages)


main()








