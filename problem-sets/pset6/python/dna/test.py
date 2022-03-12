import sys
import csv


def Seq(DNA,STR):
    y=0
    x=0
    INDEX=[]
    STR_len=len(STR)

    for x in range(len(DNA)):
        y = DNA.find(STR, x, len(DNA))
        if y>0 and y not in INDEX:
            INDEX.append(y)
    INDEX.append(0)
    #print(INDEX)

    counter=1
    Index_len=len(INDEX)
    STR_array = []

    for i in range(0, Index_len-1,1):
        if (INDEX[i])+STR_len==(INDEX[i+1]):
            counter = counter + 1
        else:
            STR_array.append(counter)
            counter=1

    #print(STR_array)
    #print(max(STR_array))
    return(max(STR_array))

    

if len(sys.argv) != 3:
    print("missing argument")
    sys.exit(1)






dna=open(sys.argv[2], "r")
DNA=dna.read()
print(DNA)


# open people file
with open(sys.argv[1], "r") as infile:
    reader = csv.reader(infile)
    people = list(reader)
#print(people)

#extract STRs row
STRs=people[0]

output=["name"]

print(STRs)
for i in range(1, len(STRs), 1):
    print(STRs[i])
    z=Seq(DNA, STRs[i])
    print(z)
    output.append(z)
    
print(output)
    


    








