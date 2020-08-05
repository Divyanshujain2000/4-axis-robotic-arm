import math
import serial
import time
ser = serial.Serial('COM5',9600)
L1 = 30
no=0
L2 = 30
factor = 180/math.pi
def lawOfCosines(a, b, c):
	return math.acos((a*a + b*b - c*c) / (2 * a * b))

def distance(x, y):
	return math.sqrt(x*x + y*y)

def inversecal(x,y):
    #x=int(x)
    #y=int(y)
    #r=math.sqrt(x*x + y*y + z*z)
    #if(r <= L1+L2 and r >= L1-L2):
    dist=distance(x,y)
    d1 = math.atan(y/x) * factor
    d2 = lawOfCosines(dist,L1,L2) * factor
    
    elbow=lawOfCosines(L1,L2,dist)
    return elbow*factor, d1+d2

again=1
while (again==1):
    x=float(input("intial x(m)="))
    y=float(input("intial y(m)="))
    z=float(input("intial z(m)="))
    theta=math.atan(y/x)
    X=x/(math.cos(theta))
    Y=z
    elbow, shoulder = inversecal(X,Y)
    base = theta*factor

    if(base<0):
        base=base+180
    if(elbow<0):
        elbow=elbow+180
    if(shoulder<0):
        shoulder=shoulder+180

    if(base>180):
        base=180
    if(elbow>180):
        elbow=180
    if(shoulder>180):
        shoulder=180

    a=str(int(elbow))
    b=str(int(base))
    c=str(int(shoulder))

    if(elbow<10):
        a="00"+a
    elif(elbow<100):
        a="0"+a
    if(base<10):
        b="00"+b
    elif(base<100):
        b="0"+b
    if(shoulder<10):
        c="00"+c
    elif(shoulder<100):
        c="0"+c

    msg=a+b+c
    print(msg)# to debug
    
    ser.write(msg.encode())
    ser.close()
        
    
    time.sleep(2)  #    wait so that angle data starts to receive 
    again=0
    while (ser.available()==0  and again==0):
        ang1=ser.read()
        ang2=ser.read()
        ang3=ser.read()
        print(ang1*360/1024)
        print(ang2*360/1024)
        print(ang3*360/1024)
        again=int(input("need next postion press 1 else 0"))
    

