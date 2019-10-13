import tkinter
import serial
import tkinter.font

def stop():
	ser.write(b'0')

def up():
	ser.write(b'1')

def down():
	ser.write(b'2')

def left():
	ser.write(b'3')

def right():
	ser.write(b'4')

def speed():
	ser.write(b'5')
	c = Speedentry.get()
	ser.write(c.encode())
	
def steps():
	ser.write(b'6')
	d = Stepsentry.get()
	ser.write((str(len(d))+'\n').encode())
	for i in range(len(d)):
		ser.write((d[i]+'\n').encode())
	#ser.write(d.encode())
	
def zup():
	ser.write(b'7')
	
def zown():
	ser.write(b'8')

def drawlines(w,NoLinesentry,SepLinesentry,LenLinesentry,RepLinesentry):
	ser.write(b'9')
	nl = NoLinesentry.get()
	sep = SepLinesentry.get()
	leng = LenLinesentry.get()
	rep = RepLinesentry.get()
	w.destroy()
	ser.write((nl+'\n').encode())
	ser.write((sep+'\n').encode())
	ser.write((str(len(leng))+'\n').encode())
	ser.write((rep+'\n').encode())
	for i in range(len(leng)):
		ser.write((leng[i]+'\n').encode())
	


def lines():
	w = tkinter.Toplevel()
	NoLines = tkinter.Label(w, text = 'Number of Lines').grid(row =2 ,column = 2)
	NoLinesentry = tkinter.Entry(w)
	NoLinesentry.grid(row = 3, column = 2)
	SepLines = tkinter.Label(w, text='Separation of Lines').grid(row=5,column=2)
	SepLinesentry = tkinter.Entry(w)
	SepLinesentry.grid(row=6,column=2)
	LenLines = tkinter.Label(w, text='Length of Lines').grid(row=8,column='2')
	LenLinesentry = tkinter.Entry(w)
	LenLinesentry.grid(row=9,column=2)
	RepLines = tkinter.Label(w, text='Repetitions per Line').grid(row=11,column=2)
	RepLinesentry = tkinter.Entry(w)
	RepLinesentry.grid(row=12,column=2)
	SetNoLines = tkinter.Button(w, text = 'Set', command = lambda: drawlines(w,NoLinesentry,
	SepLinesentry,LenLinesentry,RepLinesentry)).grid(row=14,column=2)

def drawlinesho(who,NoLinesentryho,SepLinesentryho,LenLinesentryho,RepLinesentryho):
	ser.write(b'e')
	nlho = NoLinesentryho.get()
	sepho = SepLinesentryho.get()
	lengho = LenLinesentryho.get()
	repho = RepLinesentryho.get()
	who.destroy()
	ser.write((nlho+'\n').encode())
	ser.write((sepho+'\n').encode())
	ser.write((str(len(lengho))+'\n').encode())
	ser.write((repho+'\n').encode())
	for i in range(len(lengho)):
		ser.write((lengho[i]+'\n').encode())

def linesho():
	who = tkinter.Toplevel()
	NoLinesho = tkinter.Label(who, text = 'Number of Lines').grid(row =2 ,column = 2)
	NoLinesentryho = tkinter.Entry(who)
	NoLinesentryho.grid(row = 3, column = 2)
	SepLinesho = tkinter.Label(who, text='Separation of Lines').grid(row=5,column=2)
	SepLinesentryho = tkinter.Entry(who)
	SepLinesentryho.grid(row=6,column=2)
	LenLinesho = tkinter.Label(who, text='Length of Lines').grid(row=8,column=2)
	LenLinesentryho = tkinter.Entry(who)
	LenLinesentryho.grid(row=9,column=2)
	RepLinesho = tkinter.Label(who,text='Repetitions per Line').grid(row=11,column=2)
	RepLinesentryho = tkinter.Entry(who)
	RepLinesentryho.grid(row=12,column=2)
	SetNoLinesho = tkinter.Button(who,text='Set',command=lambda:drawlinesho(who,NoLinesentryho,
	SepLinesentryho,LenLinesentryho,RepLinesentryho)).grid(row=14,column=2)



def drawsquare(r,Sideentry,Repsquareentry):
	ser.write(b'a')
	sid = Sideentry.get()
	repsq = Repsquareentry.get()
	r.destroy()
	ser.write((str(len(sid))+'\n').encode())
	ser.write((repsq+'\n').encode())
	for i in range(len(sid)):
		ser.write((sid[i]+'\n').encode())



def square():
	r = tkinter.Toplevel()
	Side = tkinter.Label(r,text='Length of side').grid(row=2,column=2)
	Sideentry = tkinter.Entry(r)
	Sideentry.grid(row=3,column=2)
	Repsquare = tkinter.Label(r,text='Repetitions').grid(row=5,column=2)
	Repsquareentry = tkinter.Entry(r)
	Repsquareentry.grid(row=6,column=2)
	Setsquare = tkinter.Button(r,text='Set',command=lambda: drawsquare(r,Sideentry,
	Repsquareentry)).grid(row=8,column=2)


def drawrect(q,Widthentry,Lengrectentry,Reprectentry):
	ser.write(b'b')	
	wid = Widthentry.get()
	lerect = Lengrectentry.get()
	reprect = Reprectentry.get()
	q.destroy()
	ser.write((reprect+'\n').encode())
	ser.write((str(len(wid))+'\n').encode())
	ser.write((str(len(lerect))+'\n').encode())
	for i in range(len(wid)):
		ser.write((wid[i]+'\n').encode())
	for j in range(len(lerect)):
		ser.write((lerect[j]+'\n').encode())

def rectangle():
	q = tkinter.Toplevel()
	Width = tkinter.Label(q,text='Width').grid(row=2,column=2)
	Widthentry = tkinter.Entry(q)
	Widthentry.grid(row=3,column=2)
	Lengrect = tkinter.Label(q,text='Lenght').grid(row=5,column=2)
	Lengrectentry = tkinter.Entry(q)
	Lengrectentry.grid(row=6,column=2)
	Reprect = tkinter.Label(q,text='Repetitions').grid(row=8,column=2)
	Reprectentry = tkinter.Entry(q)
	Reprectentry.grid(row=9,column=2)
	Setrect = tkinter.Button(q,text='Set',command=lambda: drawrect(q,Widthentry,
	Lengrectentry,Reprectentry)).grid(row=11,column=2)

def close():
	ser.write(b'c')

def ope():
	ser.write(b'd')

def drawpoints(po,Hopointsentry,Vepointsentry,Timeentry,Hosepentry,Vesepentry):
	ser.write(b'f')
	hpo = Hopointsentry.get()
	vpo = Vepointsentry.get()
	tpo = Timeentry.get()
	hosep = Hosepentry.get()
	vesep = Vesepentry.get()
	po.destroy()
	ser.write((str(len(hpo))+'\n').encode())
	ser.write((str(len(vpo))+'\n').encode())
	ser.write((str(len(tpo))+'\n').encode())
	ser.write((str(len(hosep))+'\n').encode())
	ser.write((str(len(vesep))+'\n').encode())
	for i in range(len(hpo)):
		ser.write((hpo[i]+'\n').encode())
	for j in range(len(vpo)):
		ser.write((vpo[j]+'\n').encode())
	for k in range(len(tpo)):
		ser.write((tpo[k]+'\n').encode())
	for p in range(len(hosep)):
		ser.write((hosep[p]+'\n').encode())
	for q in range(len(vesep)):
		ser.write((vesep[q]+'\n').encode())



def points():
	po = tkinter.Toplevel()
	Hopoints = tkinter.Label(po,text='Horizontal Points').grid(row=2,column=2)
	Hopointsentry = tkinter.Entry(po)
	Hopointsentry.grid(row=3,column=2)
	Vepoints = tkinter.Label(po,text='Vertical points').grid(row=5,column=2)
	Vepointsentry = tkinter.Entry(po)
	Vepointsentry.grid(row=6,column=2)
	Time = tkinter.Label(po,text='Time per point').grid(row=8,column=2)
	Timeentry = tkinter.Entry(po)
	Timeentry.grid(row=9,column=2)
	Hosep = tkinter.Label(po,text='Horizontal Separation').grid(row=11,column=2)
	Hosepentry = tkinter.Entry(po)
	Hosepentry.grid(row=12,column=2)
	Vesep = tkinter.Label(po,text='Vertical Separation').grid(row=14,column=2)
	Vesepentry = tkinter.Entry(po)
	Vesepentry.grid(row=15,column=2)
	Setpoints = tkinter.Button(po,text='Set',command= lambda: drawpoints(po,Hopointsentry,
	Vepointsentry,Timeentry,Hosepentry,Vesepentry)).grid(row=17,column=2)



## Starts serial communication
ser = serial.Serial('COM10', 28800)
top = tkinter.Tk()
helv11 = tkinter.font.Font(family='Helvetica', size=7, weight='bold')

## Buttons to move freely any motor in te plane
A = tkinter.Button(top, text = 'UP', command = up, font = helv11)
A.grid(row = 1, column = 4)
B = tkinter.Button(top, text = 'DOWN', command = down, font = helv11)
B.grid(row = 5, column = 4)
C = tkinter.Button(top, text = 'LEFT', command = left, font = helv11)
C.grid(row = 4, column = 3)
D = tkinter.Button(top, text = 'RIGHT', command = right, font = helv11)
D.grid(row = 4, column =5)

## Buttons to adjust the height of the laser waist
E = tkinter.Button(top, text = 'ZUP', command = zup, font = helv11).grid(row = 1, column = 13)
F = tkinter.Button(top, text = 'ZOWN', command = zown, font = helv11).grid(row = 5, column = 13)

## Button to stop any motor
Stop = tkinter.Button(top, text = 'Stop', command = stop).grid(row = 1, column = 20)

## Label and entry to select speed
Speed = tkinter.Label(top, text = 'Speed').grid(row = 17, column = 20)
Speedentry = tkinter.Entry(top)
Speedentry.grid(row = 18, column = 20)
Setspeed = tkinter.Button(top, text = 'Set', command = speed).grid(row = 18, column = 22)

## Label and entry to select number of steps
Steps = tkinter.Label(top, text = 'Number of Steps').grid(row = 19, column = 20)
Stepsentry = tkinter.Entry(top)
Stepsentry.grid(row = 20, column = 20)
Setsteps = tkinter.Button(top, text = 'Set', command = steps).grid(row = 20, column =22)

## Button to open the draw line option
Lines = tkinter.Button(top, text = 'Lines', command = lines).grid(row = 18, column = 1 )

## Button to open the draw square option
Square = tkinter.Button(top, text='Square',command=square).grid(row=18, column=4)

## Button to open the draw rectangle option
Rectangle = tkinter.Button(top,text='Rectangle',command=rectangle).grid(row=18,column=6)

## Button to close shooter
Shootcl = tkinter.Button(top,text='Close',command=close).grid(row=15,column=7)

##Button to open shooter
Shootop = tkinter.Button(top,text='Open',command=ope).grid(row=14,column=7)

##Button to draw horizontal lines
LinesHor = tkinter.Button(top, text = 'LinesHO', command = linesho).grid(row = 18, column = 12)

##Button to draw points
Points = tkinter.Button(top,text='Points', command=points).grid(row=20,column=1)

top.mainloop()



