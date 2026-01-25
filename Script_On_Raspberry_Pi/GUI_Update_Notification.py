#!/usr/bin/python3
from time import sleep
from tkinter import *
import sys
import os
import serial
import re
import time

# ============================= #
#  Cau hinh duong dan / serial  #
# ============================= #
BASE_DIR = "/home/pi/Desktop/Firmware-Over-The-Air/Script_On_Raspberry_Pi"
UPDATE_HEX_PATH = os.path.join(BASE_DIR, "Update.hex")

PORT = "/dev/ttyS0"
BAUD_RATE = 9600


if os.environ.get("DISPLAY", "") == "":
    os.environ.__setitem__("DISPLAY", ":0.0")

# ============================= #
#  Khoi tao serial & flash()    #
# ============================= #

print("Opening serial port...")
ser = serial.Serial(PORT, BAUD_RATE)
time.sleep(1)

string_pattern = b"."
chunk = re.compile(string_pattern)

def flash():
    # Gá»­i toÃ n bá»™ file Update.hex sang STM32
    with open(UPDATE_HEX_PATH, "rb") as file:
        for line in file:
            result = chunk.findall(line)
            for x in range(len(result)):
                ser.write(result[x])
            ser.write("\n".encode("utf-8"))

            # Chá» MCU tráº£ 'o' Ä‘á»ƒ gá»­i tiáº¿p
            while True:
                data_rec = ser.read()
                if data_rec.decode("utf-8") == "o":
                    break

# ============================= #
#  GUI thong bao update         #
# ============================= #

switch1 = int()

root = Tk()
root.title("New Firmware Update")
root.geometry("450x200")
root.resizable(0, 0)

Top = Toplevel()
Top.withdraw()

# Label tren main window
label_update = Label(
    root,
    text="New update is available, please select an action:",
    font=("Arial", 15),
)
label_update.grid(row=0, column=0, columnspan=2, pady=10)

# Labels tren top Window
label_switch1 = Label(Top, text="Switch 1 must be off", font=("Arial", 15))
label_switch1.grid(row=0, column=0, columnspan=2, pady=10)

label_OK = Label(Top, text="OK", font=("Arial", 15))

label_update_in_progress = Label(
    Top, text="Update in progress", font=("Arial", 15)
)

label_update_finished = Label(
    Top, text="Update is done", font=("Arial", 15)
)

# ----------------------------- #
#  Cac ham xu ly nut            #
# ----------------------------- #
def Update():
    global Top, switch1

    Top.deiconify()
    Top.geometry("500x400")
    root.withdraw()

    # Gá»­i 'NEW' cho STM32
    for c in "NEW":
        ser.write(c.encode("utf-8"))
        sleep(0.1)

    Top.update()

    # Äá»c chuá»—i "Switch 1\n"
    string = ser.readline().decode("utf-8")
    print(string)

    if string == "Switch 1\n":
        switch1 = ser.read()
        print("switch1 =", switch1)

        if switch1 == b"0":
            label_OK.grid(row=1, column=0, pady=10)
            bt_update_now.grid(row=5, column=0, pady=20)
        else:
            label_OK.grid_forget()
            bt_update_now.grid_forget()

def Snooze():
    root.withdraw()
    sleep(10)
    root.deiconify()

def back():
    Top.withdraw()
    ser.write("B".encode("utf-8"))
    root.deiconify()
    ser.reset_input_buffer()

def Reset_Request_then_flash():
    ser.write("1".encode("utf-8"))
    label_update_in_progress.grid(row=3, column=0, pady=10)
    bt_update_now.destroy()
    bt_back.destroy()
    Top.update()
    sleep(5)
    flash()
    label_update_finished.grid(row=4, column=0, pady=10)
    Top.update()
    sleep(5)
    root.destroy()
    # Sau khi xong, quay lai vong lap firebase_Get_Update_Script 

# ----------------------------- #
#  Buttons                      #
# ----------------------------- #
bt_update = Button(
    root,
    text="Update now",
    font="Arial 10 bold",
    bg="lightyellow",
    height=3,
    width=15,
    command=Update,
)
bt_update.grid(row=1, column=0, padx=10, pady=10)

bt_snooze = Button(
    root,
    text="Snooze",
    font="Arial 10 bold",
    bg="light pink",
    height=3,
    width=15,
    command=Snooze,
)
bt_snooze.grid(row=2, column=0, padx=10, pady=10)

bt_back = Button(
    Top,
    text="Back",
    font="Arial 10 bold",
    bg="lightyellow",
    height=3,
    width=15,
    command=back,
)
bt_back.grid(row=5, column=1, padx=10, pady=20)

bt_update_now = Button(
    Top,
    text="Update now",
    font="Arial 10 bold",
    bg="lightyellow",
    height=3,
    width=15,
    command=Reset_Request_then_flash,
)

Top.update()
root.mainloop()