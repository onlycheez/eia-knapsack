#!/usr/bin/python
# -*- coding: utf-8 -*-

v = []
w = []
x = []
it = 0
maxi = 0
s = ""

def countRest(f, cap, orig):
	temp = orig
	for i in range(f, it):
		#print w[i] 
		#print cap
		if cap - w[i] < 0:
			#print w[i], v[i]
			if temp == orig:
				return temp
			temp += float(v[i])/float(w[i])*float(cap)
			return temp
		else:
			temp += v[i]
			cap -= w[i]
	#print temp
	return temp
	


def solve(item, cap, val, est, sol):
	global maxi,s
	#print "item " + str(item)
	#print "cap " + str(cap)
	#print "val " + str(val)
	#print "est " + str(est)
	#print "amxi " + str(maxi)
	#print ""
	
    	
	if cap < 0:
		return
	elif est <= maxi:
		return
	elif item == it-1:
		if val > maxi:
			maxi = val
			s = sol
			return
		else:
			return
	else :
		if cap-w[item+1] >= 0:
			solve(item+1,cap-w[item+1],val+v[item+1],countRest(item+1, cap-w[item+1], val+v[item+1]),sol + " 1")
		solve(item+1,cap,val,countRest(item+1, cap, val),sol + " 0")
		return
	

def solveIt(inputData):
    # Modify this code to run your optimization algorithm
    global maxi,v,w,s,it,x
    # parse the input
    lines = inputData.split('\n')

    firstLine = lines[0].split()
    items = int(firstLine[0])
    capacity = int(firstLine[1])

    values = []
    weights = []
    x = []
    maxi = 0
    s = ""
    
    for i in range(1, items+1):
        line = lines[i]
        parts = line.split()
        x.append((int(parts[0]), int(parts[1]), float(parts[0]) / float(parts[1])))
        
    x = sorted(x, key=lambda st: st[2])
    x.reverse()
    
    #print x
    
    
    for i in x:
        v.append(i[0])
        values.append(i[0])
        weights.append(i[1])
        w.append(i[1])
        
    it = items = len(values)
    

    value = 0
    weight = 0
    taken = []
    sys.setrecursionlimit(10100)

    sv = countRest(0,capacity,0)
    solve(0,capacity - weights[0],values[0],sv,"1")
    solve(0,capacity,0,sv,"0")

    value = maxi
    
    # prepare the solution in the specified output format
    outputData = str(value) + ' ' + str(0) + '\n'
    outputData += s#' '.join(map(str, taken))
    return outputData




import sys

if __name__ == '__main__':
    if len(sys.argv) > 1:
        fileLocation = sys.argv[1].strip()
        inputDataFile = open(fileLocation, 'r')
        inputData = ''.join(inputDataFile.readlines())
        inputDataFile.close()
        print solveIt(inputData)
    else:
        print 'This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)'

