#!/usr/bin/python3
from time import sleep
from tkinter import *
import serial
import re
import time
import os

# ============================= #
# Cấu hình serial & đường dẫn   #
# ============================= #
BASE_DIR = "/home/pi/Desktop/Firmware-Over-The-Air/Script_On_Raspberry_Pi"
UPDATE_HEX_PATH = os.path.join(BASE_DIR, "Update.hex")
PORT = "/dev/ttyS0"
BAUD_RATE = 115200                  # Đã đổi lên 115200 cho ổn định

if os.environ.get("DISPLAY", "") == "":
    os.environ.__setitem__("DISPLAY", ":0.0")

print("Opening serial port...")
ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
time.sleep(2)                       # Chờ STM32 ổn định

# ============================= #
# Hàm flash hex                 #
# ============================= #
def flash():
    with open(UPDATE_HEX_PATH, "rb") as file:
        for line in file:
            for byte in line:
                ser.write(bytes([byte]))
            ser.write(b"\n")
            while True:
                ack = ser.read(1)
                if ack == b"o":
                    break

# ============================= #
# GUI                           #
# ============================= #
root = Tk()
root.title("Firmware Update")
root.geometry("560x360")
root.resizable(False, False)
root.configure(bg="#f4f6f9")

# Main frame
main = Frame(root, bg="#f4f6f9")
main.pack(expand=True, fill=BOTH, padx=30, pady=30)

# Title
Label(main, text="New Firmware Available", font=("Segoe UI", 20, "bold"), 
      bg="#f4f6f9", fg="#1a73e8").pack(pady=(0,15))

Label(main, text="The new version is ready. Please select an action:",
      font=("Segoe UI", 11), bg="#f4f6f9", fg="#555").pack(pady=(0,30))

# Buttons frame
btn_frame = Frame(main, bg="#f4f6f9")
btn_frame.pack(pady=20)

Button(btn_frame, text="Update Now", font=("Segoe UI", 12, "bold"),
       bg="#1a73e8", fg="white", activebackground="#1557b0",
       width=18, height=2, relief="flat", command=lambda: Update()).pack(side=LEFT, padx=15)

Button(btn_frame, text="Snooze 10s", font=("Segoe UI", 12, "bold"),
       bg="#fbbc05", fg="black", activebackground="#e8a600",
       width=18, height=2, relief="flat", command=lambda: Snooze()).pack(side=LEFT, padx=15)

# ============================= #
# Top window - Switch check     #
# ============================= #
Top = Toplevel(root)
Top.title("Update Confirmation")
Top.geometry("560x420")
Top.resizable(False, False)
Top.configure(bg="#ffffff")
Top.withdraw()

top_main = Frame(Top, bg="#ffffff")
top_main.pack(expand=True, fill=BOTH, padx=40, pady=40)

Label(top_main, text="Switch 1 must be OFF", font=("Segoe UI", 18, "bold"),
      bg="#ffffff", fg="#d93025").pack(pady=(0,30))

label_OK = Label(top_main, text="✓ Switch 1 off - Available update", 
                 font=("Segoe UI", 14, "bold"), bg="#ffffff", fg="#34a853")

label_progress = Label(top_main, text="Loading firmware...", 
                       font=("Segoe UI", 14, "bold"), bg="#ffffff", fg="#1a73e8")

label_done = Label(top_main, text="Successfull !", 
                   font=("Segoe UI", 18, "bold"), bg="#ffffff", fg="#34a853")

# Nút trong Top
btn_container = Frame(top_main, bg="#ffffff")
btn_container.pack(pady=30)

bt_back = Button(btn_container, text="Back", font=("Segoe UI", 11, "bold"),
                 bg="#ea4335", fg="white", width=15, height=2, relief="flat",
                 command=lambda: back())

bt_update_now = Button(btn_container, text="Proceed Update", font=("Segoe UI", 12, "bold"),
                       bg="#34a853", fg="white", activebackground="#2e8b57",
                       width=20, height=2, relief="flat", command=lambda: Reset_Request_then_flash())

# ============================= #
# Functions                     #
# ============================= #
def Update():
    Top.deiconify()
    root.withdraw()
    ser.reset_input_buffer()
    ser.write(b"NEW")
    ser.flush()
    time.sleep(0.3)

    response = ser.readline().decode('utf-8', errors='ignore').strip()
    print("STM32 says:", response)

    if "Switch 1" in response:
        switch1 = ser.read(1)
        print("Switch1 value:", switch1)
        if switch1 == b'0':
            label_OK.pack(pady=20)
            bt_update_now.pack(pady=15)
            bt_back.pack(pady=10)
        else:
            label_OK.pack_forget()
            bt_update_now.pack_forget()
            bt_back.pack(pady=20)
    else:
        bt_back.pack(pady=20)

def Snooze():
    root.withdraw()
    sleep(10)
    root.deiconify()

def back():
    Top.withdraw()
    ser.write(b"B")
    root.deiconify()
    ser.reset_input_buffer()

def Reset_Request_then_flash():
    ser.write(b"1")
    label_progress.pack(pady=30)
    bt_update_now.destroy()
    bt_back.destroy()
    Top.update()
    sleep(3)
    flash()
    label_progress.pack_forget()
    label_done.pack(pady=40)
    Top.update()
    sleep(5)
    root.destroy()

# ============================= #
# Start GUI                     #
# ============================= #
root.mainloop()