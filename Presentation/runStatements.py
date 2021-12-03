import glob
import re
import subprocess
textfiles = glob.glob("examples/*txt")
textfiles.reverse()

for i in textfiles:#[:1]:
    #print(i)
    
    c_g = re.match(r'examples\\ex1_([1-9]*[0-9])[_]?child_([1-9]*[0-9])gifts.txt',i)
    #print(c_g[2])

    print("./giftingWithClasses_timed "+i+" writefile "+c_g[1] + " " + c_g[2])
    #x = subprocess.check_output(["./giftingWithClasses_timed ",i," writefile ",c_g[1] , " " , c_g[2]])
    #print(x)
    #text = open("outputs/" + i.replace("/","_"),"w")
    #text.write(x)
    #text.close()
    print("./giftingWithClasses_timed "+i.replace("examples","optimized_examples")+" writefile "+c_g[1] + " " + c_g[2])

