
filin = open(input("wordbank name: "),"r")
filout = open("wordbank.txt","w")

for line in filin:
    line = line.replace("%","")
    if len(line) <= 3: continue
    filout.write(line)
filout.write("")

filin.close()
filout.close()