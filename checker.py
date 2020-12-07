import random as rd
import subprocess


while True:
    print("create/check/quit?")
    req = input()
    if req == "create":
        fin = open("in.txt", 'w')
        fin.write("800\n")
        for i in range(800):
            fin.write("300\n")
            fin.write(' '.join([str(rd.randint(0, 1000)) for i in range(300)]) + '\n')
        fin.close()
    elif req == "check":
        bfs = ['2', '2', '-1', '4', '1']
        srt = ''
        while srt not in ["shell", "heap", "quick", "intro", "bfs"]:
            srt = input("shell/heap/quick/intro/bfs?\n").lower()
        subprocess.run([srt + '.exe', '-o', srt + '.o'])
        if srt == 'bfs':
            fot = open("outbfs.txt", 'r')
            # print([k[:-1] for k in fot.readlines()], bfs)
            if [k[:-1] for k in fot.readlines()] == bfs:
                print("CORRECT!")
                continue
            print("WRONG!")
            continue
        fot = open("out.txt", 'r')
        orig = []
        arr = []
        time = []
        flag = 0
        i = 0
        for line in fot:
            if line == '-\n':
                if list(sorted(orig)) != arr:
                    print("WRONG, FAILED AT LINE", str(i))
                    print("CORRECT WOULD BE:", *list(sorted(orig)))
                    print("GOT:", *arr)
                    break
                flag = 0
                continue
            if flag == 0:
                orig = list(map(int, line.split()))
                flag = 1
                i += 1
            elif flag == 1:
                arr = list(map(int, line.split()))
                flag = 2
            else:
                time.append(float(line))
        else:
            print("SORTED CORRECTLY, AVERAGE TIME SPENT: " + str(sum(time) / len(time)))
        fot.close()
    elif req == "quit":
        break
