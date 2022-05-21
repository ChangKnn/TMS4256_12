from audioop import add
from os import fdopen

from sympy import Add
# Write
#  ADDR1          (1111111111XX111) 
#  ADDR1           (1111111111XX010) 
#  ADDR2           (0000000001XX010) 
#  ADDR2           (0000000000XX010) 
#  ADDR2           (0000000000XX000) 
#  INC             (0000000000XX010) 
#  INC             (0000000001XX010) 
#  INC             (0000000001XX011) 
#  INC             (1111111111XX111) 
#  ADDR1           (1111111111XX111)


def write(row,col,d,f):
    brow = '{:09b}'.format(row)
    bcol = '{:09b}'.format(col)
    sq = str(d)
    buf = " INC   ("+ brow+ "1XX111)\n"
    buf += " INC   ("+ brow+ "1XX" + sq+ "10)\n"
    buf += " INC   ("+ bcol+ "1XX" + sq+ "10)\n"
    buf += " INC   ("+ bcol+ "0XX" + sq+ "10)\n"
    buf += " INC   ("+ bcol+ "0XX" + sq+ "00)\n"
    buf += " INC   (0000000000XX" + sq+ "10)\n"
    buf += " INC   (0000000001XX" + sq+ "10)\n"
    buf += " INC   (0000000001XX" + sq+ "11)\n"
    buf += " INC   (1111111111XX111)\n"
    buf += " INC   ("+ brow+ "1XX111)\n"
    f.write(buf)
    # print("Write " + str(q) + " To " + str(row) + "," + str(col))
    return

# Read
#  ADDR1           (1111111111XX111) 
#  ADDR1           (1111111111XX110) 
#  ADDR2           (0000000001XX110) 
#  ADDR2           (0000000000XX110) 
#  ADDR2           (0000000000XX110) 
#  INC             (0000000000HX110) 
#  INC             (0000000001XX110) 
#  INC             (0000000001XX111) 
#  INCAR2          (1111111111XX111) 
def read(row,col,q,f):
    brow = '{:09b}'.format(row)
    bcol = '{:09b}'.format(col)
    if q == 1:
        sq = "H"
    else:
        sq = "L"
    buf = " INC   ("+ brow+ "1XX111)\n"
    buf += " INC   ("+ brow+ "1XX110)\n"
    buf += " INC   ("+ bcol+ "1XX110)\n"
    buf += " INC   ("+ bcol+ "0XX110)\n"
    buf += " INC   ("+ bcol+ "0XX110)\n"
    buf += " INC   (0000000000"+ sq +"X110)\n"
    buf += " INC   (0000000001XX110)\n"
    buf += " INC   (0000000001XX011)\n"
    buf += " INC   (0000000001XX111)\n"
    buf += " INC   ("+ brow+ "1XX111)\n"
    f.write(buf)
    # print("From" + str(row) + "," + str(col) + " Read " + str(d))
    return

print("Start")
col = 0
row = 0
curCol = 0
addrNum = int(pow(2,9))
f = open("C:/Users/Chang/Desktop/信诺达/FUN.mdc","w")
# Write All 0
# for x in range(addrNum):
#     for y in range(addrNum):
#         write(x, y, 0)

for col in range(addrNum):
    

for x in range(addrNum):
    col = x       # Start Col
    # Write Diagonal 1
    for r in range(addrNum):
        curCol = col + r
        if curCol > addrNum :
            curCol = curCol - addrNum
        # write(r, curCol, 1, f)
    
    # Read Mem
    for r in range(addrNum):
        curCol = col + r
        if curCol > addrNum:
            curCol = curCol - addrNum
        for c in range(addrNum):
            if c == curCol:
                read(r, c, 1 ,f)
            else:
                read(r, c, 0, f)

f.close()
