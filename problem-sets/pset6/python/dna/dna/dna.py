import sys
import csv

# function to get number of consecutive repetitions


def Seq(DNA, STR):
    y = 0
    x = 0
    INDEX = []
    STR_len = len(STR)

    for x in range(len(DNA)):
        y = DNA.find(STR, x, len(DNA))
        if y > 0 and y not in INDEX:
            INDEX.append(y)
    INDEX.append(0)
    # print(INDEX)

    counter = 1
    Index_len = len(INDEX)
    STR_array = []

    for i in range(0, Index_len-1, 1):
        if (INDEX[i]) + STR_len == (INDEX[i + 1]):
            counter = counter + 1
        else:
            STR_array.append(counter)
            counter = 1

    # print(STR_array)
    # print(max(STR_array))
    if len(STR_array) > 0:
        return(max(STR_array))
    # print(max(STR_array))


# check command line arguments
if len(sys.argv) != 3:
    print("missing argument")
    sys.exit(1)

# parse from DNA sequence file to variable
dna = open(sys.argv[2], "r")
DNA = dna.read()
# print(DNA)

# open people file
with open(sys.argv[1], "r") as infile:
    reader = csv.reader(infile)
    people = list(reader)
# print(people)

# extract STRs row
STRs = people[0]

# create array for output
output = ["name"]

# print(STRs)
for i in range(1, len(STRs), 1):
    # print(STRs[i])
    z = Seq(DNA, STRs[i])
    # print(z)
    output.append(str(z))

# print(output)
# compare arrays
# print(len(people))
matches_needed = len(people[0])-2
match_array = []
match = False
final_match = False
match_count = 1
# print("matches needed", matches_needed)


if sys.argv[1] == 'databases/large.csv':
    # iterate over rows
    for j in range(1, len(people), 1):
     # print(people[j])
        # iterate over items in row
        for n in range(1, len(people[j])):
            if output[n] == people[j][n]:
                # print (output[n], "  ",people[j][n], "match", match_count)
                match_count = match_count + 1
            if match_count == matches_needed:
                print(people[j][0])
                final_match = True
                break
        if match_count == matches_needed - 1:
            # print(people[j][0])
            final_match = True
            break
        match_count = 1
        
elif sys.argv[1] == 'databases/small.csv':
    for j in range(1, len(people), 1):
        # print(people[j])
        # iterate over items in row
        for n in range(1, len(people[j])):
            if output[n] == people[j][n]:
                #print (output[n], "  ",people[j][n], "match", match_count)
                match_count = match_count + 1
            if match_count == matches_needed + 1:
                print(people[j][0])
                final_match = True
        match_count = 0


if final_match == False:
    print("No match")