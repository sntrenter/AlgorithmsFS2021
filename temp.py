Class Node:
def canReceiveGift():
def findLowestNode():
    pass

def distributeGifts(gifts,children):
    nodes = []
    for c in children:
        if canReceiveGift(gifts[0],c): #can each child recieve the first gift
            nodes.append(Node(gifts[0],c,{})) #create a node for that child

    for g in gifts[1:]: #already distributed first gift, start at second
        newNodes = []
        for n in nodes: 
            for c in children: #Need to go over each child for each node
                if canReceiveGift(g,c): #goes over all requiremnts for gifting
                    newNodes.append(Node(g,c,n.dist)) #creates new node with previous nodes gift distrabution + new gift

        nodes = newNodes #get ready to move to next layer
    findLowestNode(nodes) #this will go over remaining nodes and print the one with the lowest e value


distributeGifts([],[]):