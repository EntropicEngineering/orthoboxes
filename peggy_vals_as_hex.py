#!/opt/local/bin/python

his = [837, 702, 708, 693, 679, 582]
los = [37, 33, 32, 33, 36, 30]
mids = [0,0,0,0,0,0]
for i in range(0,6):
    mids[i] = (his[i]+4*los[i]) / 5

def swizzle(x):
    return x[2:4] + " " + x[0:2]

print(" ".join([("%d" % x) for x in mids]))
