from tkinter import *
import serial

ser = serial.Serial('COM5')
root = Tk()
lbl1 = Label(root, text="전압")
lbl1.pack()

value = StringVar()
value.set('')
lblvalue = Label(root, textvariable = value)
lblvalue.pack()

def readSerial():
    try:
        if ser.inWaiting():
            value.set(int(ser.readline()) * 0.0029296875)
            root.update_idletasks()
    finally:
        root.after(100, readSerial)

readSerial()
root.mainloop()

