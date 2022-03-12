import sys
import csv

# Check cmd arguments
if len(sys.argv) != 3:
    print("missing argument")
    sys.exit(1)
    
dna=open(sys.argv[2], "r")

def seq(DNA,STR):
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


#dna="AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATTAAAGGAGATCAGATCAGATCAGATCTATCTATCTATCTATCTATCAGAAAAGAGTAAATAGTTAAAGAGTAAGATATTGAATTAATGGAAAATATTGTTGGGGAAAGGAGGGATAGAAGG"
STR="AGATC"
x=seq(dna, STR)
print(x)