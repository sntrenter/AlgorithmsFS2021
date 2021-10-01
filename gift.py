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
            #print(i.split())
            children.append(Children(i.split()[0],i.split()[2]))
        elif re.search(r'G[1-9][0-9]*\s[1-9][0-9]*\s[0-9][0-9]*.[0-9][0-9]*\s([1-9][0-9]*-[1-9][0-9]*|any)',i):
            #print(i.split())
            gifts.append(Gifts(i.split()[0],i.split()[1],i.split()[2],i.split()[3]))
    return (children,gifts)

def canReceiveGift(gift,child):
    #TODO: Fill in logic for not enough gifts left + avg gifts per kid
    if gift.ages == "any":
        #print("true")
        return True
    
    (low,high) = gift.ages.split("-")
    #print(low,high,child.age)
    if int(child.age) < int(low):
        #print("false")
        return False
    if int(child.age) > int(high):
        #print("false")
        return False
        #if (child.age < low or child.age > high):
        #    return False
    #print("True")
    return True


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

class Node: #TODO: make it so entry is two variables
    hist = []
    def __init__(self,gift,child,prev = []):#,entry,prev = []):
        self.hist.append((gift,child))
        if prev != []:
            for i in prev:
                self.hist.append(i)
    def __str__(self):
        s = ""
        for i in self.hist:
            s += str(i[0]) + str(i[1]) + "\n"
        return s
def main():
    print("start")
    #read in file(regex?)
    filename = "ex1_3child_6gifts" #turn this to a list
    (children,gifts) = getProblem(filename)
    print(children[0])
    print(gifts[0])
    print(canReceiveGift(gifts[0],children[0]))

    #bad implementation attempt
    #load nodes for first gift then move on
    print("#######")
    nodes = []
    for c in children:
        if canReceiveGift(gifts[0],c):
            nodes.append(Node(gifts[0],c))
    print(nodes[0])
    for g in gifts[1:]:
        #print(g)
        newNodes = []
        for n in nodes:
            for c in children:
                #print(c)
                if canReceiveGift(g,c):
                    newNodes.append(Node((g,c),n.hist))
                    #print("added node")
        #print(nodes)
        #print(newNodes)
        nodes = newNodes

    print(nodes)
    print(len(nodes))
    print(nodes[0].hist)

    print("end")

main()