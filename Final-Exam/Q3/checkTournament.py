N,M = open("INPUT_Tournament.txt").readlines()
N,M=int(N),int(M)
print (N)
print (M)
assert N%2 == 0
outputFile = open("op.out").read().strip().split("\n")

if len(outputFile)!=((N/2)*(M)):
    print ("Length of output file does not match the requirements!")
    exit(0)

allMatches=[]
for day in range(M):
    dailyPlayers = []
    for match in range(N/2):
        p1, p2 = outputFile[day*N/2+match].split()
        p1 = int(p1); p2 = int(p2)
        #print p1,p2
        if p1 not in dailyPlayers:
            dailyPlayers.append(p1)
        else:
            print ("Failed because player", p1, "in more than one match on day ", day)
            exit(0)
        if p2 not in dailyPlayers:
            dailyPlayers.append(p2)
        else:
            print ("Failed because player", p2, "in more than one match on day ", day)
            exit(0)

        if p1<p2:
            if (p1,p2) not in allMatches:
                allMatches.append((p1,p2))
            else:
                print ("Match", (p1,p2), "being replayed")
                exit(0)
        else:
            if (p2,p1) not in allMatches:
                allMatches.append((p2,p1))
            else:
                print ("Match", (p2,p1), "being replayed")
                exit(0)

for item in range(N):
    if allMatches.count(item)>N-1:
        print ("Failed because player", item, "exceeds the number of matches allowed.")
        exit(0)

print ("Success.")