#Sam Trenter
#algorithms gift giving

from os import name
import re
import copy

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

class Node:
    #dist = {}
    def __init__(self,gift,child,prev):
        if prev != {}:
            self.dist = prev
        else:
            self.dist = {}
        if child.name in self.dist:
            self.dist[child.name].append(gift)
        else:
            self.dist[child.name] = [gift]
    def __str__(self):
        s = ""
        for key,values in self.dist.items():
            s += str(key) + "\n"
            for i in values:
                s += "-" + str(i) + "\n"
        return s      

def canReceiveGift(gift,child):
    #TODO: Fill in logic for not enough gifts left + avg gifts per kid
    return True
    if gift.ages == "any":
        return True
    
    (low,high) = gift.ages.split("-")
    if int(child.age) < int(low):
        return False
    if int(child.age) > int(high):
        return False
    return True


def main():
    #print("start")
    filename = "ex1_3child_6gifts" 
    (children,gifts) = getProblem(filename)
    nodes = []
    for c in children:
        print(c)
        if canReceiveGift(gifts[0],c):
            nodes.append(Node(gifts[0],c,{}))

    for g in gifts[1:]:
        newNodes = []
        print(len(nodes))
        for n in nodes:
            for c in children:
                if canReceiveGift(g,c):
                    newNodes.append(Node(g,c,copy.deepcopy(n.dist)))

        nodes = newNodes

    print(len(nodes))
    for i in nodes:
        c = 0
        for key in i.dist:
            if len(i.dist[key]) == 2:
                c += 1
        if c == 3:
            print(i)
                
                

main()