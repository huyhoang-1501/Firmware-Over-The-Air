# =========================================================== #
#  Imported Libraries                                         #
# =========================================================== #
import tkinter as tk
from tkinter import *
from tkinter import messagebox, filedialog
import pyrebase
import os
from PIL import Image, ImageTk

# =========================================================== #
#  Base directory                                             #
# =========================================================== #
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# =========================================================== #
#  Firebase configuration                                     #
# =========================================================== #
config = {
    "apiKey": "AIzaSyADvax54nso0DOMKLgT35pfedVbWUZU9YE",
    "authDomain": "firmwareovertheair-b8a90.firebaseapp.com",
    "databaseURL": "https://firmwareovertheair-b8a90-default-rtdb.firebaseio.com",
    "projectId": "firmwareovertheair-b8a90",
    "storageBucket": "",   
}

Firebase = pyrebase.initialize_app(config)
Database = Firebase.database()

# =========================================================== #
#  Browse file                                                #
# =========================================================== #
def Browse():
    filename = filedialog.askopenfilename(
        title="Browse HEX file",
        filetypes=(("HEX files", "*.hex"), ("All files", "*.*")),
    )
    if filename:
        Local_Path.set(filename)

# =========================================================== #
#  Upload: ghi version + URL GitHub lên Firebase              #
# =========================================================== #
def Upload():
    local_path = Local_Path.get()

    if not local_path or not os.path.isfile(local_path):
        messagebox.showerror("Error", "Chưa chọn file HEX hợp lệ trên máy tính.")
        return

    try:
        version = int(Version_Number.get())
    except ValueError:
        messagebox.showerror("Error", "Version phải là số nguyên")
        return

    firmware_url = Firmware_URL.get().strip()
    if not firmware_url:
        messagebox.showerror("Error", "Chưa nhập URL file Update.hex trên GitHub (RAW URL)")
        return

    try:
        data = {"version": version, "url": firmware_url}
        Database.set(data)

        label_Successful_Update.place(
            x=PANEL_X, y=PANEL_Y + 3 * ROW_GAP + 40
        )
        label_UnSuccessful_Update.place_forget()
    except Exception as e:
        label_UnSuccessful_Update.place(
            x=PANEL_X, y=PANEL_Y + 3 * ROW_GAP + 40
        )
        label_Successful_Update.place_forget()
        messagebox.showerror("Upload failed", str(e))

# =========================================================== #
#  Create GUI Window                                          #
# =========================================================== #
BG_WIDTH = 1053
BG_HEIGHT = 677

main_window = tk.Tk()
main_window.title("FOTA Cloud Server")
main_window.configure(bg="#f1f1f1")
main_window.geometry(f"{BG_WIDTH}x{BG_HEIGHT}+200+100")
main_window.resizable(False, False)
main_window.iconphoto(False, PhotoImage(file=os.path.join(BASE_DIR, "Upload.png")))

# =========================================================== #
#  Background Canvas                                          #
# =========================================================== #
Background = Canvas(
    main_window,
    bg="#f1f1f1",
    height=BG_HEIGHT,
    width=BG_WIDTH,
    bd=0,
    highlightthickness=0,
    relief="ridge",
)
Background.place(x=0, y=0)

bg_path = os.path.join(BASE_DIR, "Background.png")
bg_pil = Image.open(bg_path)
background_img = ImageTk.PhotoImage(bg_pil)
Background.create_image(BG_WIDTH / 2, BG_HEIGHT / 2, image=background_img)

# =========================================================== #
#  Gốc toạ độ cụm control (panel ở giữa bên phải)             #
# =========================================================== #
# Giảm PANEL_X để cụm control dịch vào giữa bớt
PANEL_X = 540      # lề trái cụm control (trước là 580)
PANEL_Y = 220      # hàng trên cùng
ROW_GAP = 70       # khoảng cách dọc giữa các hàng

# =========================================================== #
#  Status Labels                                              #
# =========================================================== #
label_Successful_Update = Label(
    Background,
    bg="#f1f1f1",
    fg="green",
    text="Version & URL uploaded successfully!",
    font=("Times New Roman", 13),
)

label_UnSuccessful_Update = Label(
    Background,
    bg="#f1f1f1",
    fg="red",
    text="Upload failed. Please try again.",
    font=("Times New Roman", 13),
)

# =========================================================== #
#  Hàng 1: Browse + File path                                 #
# =========================================================== #
Local_Path = tk.StringVar()

Browse_Button_Image = PhotoImage(file=os.path.join(BASE_DIR, "BrowseButton.png"))
Browse_Button = tk.Button(
    Background,
    image=Browse_Button_Image,
    borderwidth=0,
    highlightthickness=0,
    command=Browse,
    relief="flat",
)
Browse_Button.place(
    x=PANEL_X,
    y=PANEL_Y,
    width=150,
    height=60,
)

Path_Entry = tk.Entry(
    Background,
    bd=0,
    bg="#d4d4d4",
    textvariable=Local_Path,
    highlightthickness=0,
    font=("Arial", 11),
)
Path_Entry.place(
    x=PANEL_X + 170,
    y=PANEL_Y + 15,
    width=340,
    height=30,
)

# =========================================================== #
#  Hàng 2: Version + ô nhập + Upload                          #
# =========================================================== #
Version_Number = tk.StringVar()
row2_y = PANEL_Y + ROW_GAP

label_version = Label(
    Background,
    bg="#f1f1f1",
    text="Version:",
    font=("Times New Roman", 12, "bold"),
)
label_version.place(
    x=PANEL_X,
    y=row2_y,
)

Version_Entry = tk.Entry(
    Background,
    bd=0,
    bg="#d4d4d4",
    textvariable=Version_Number,
    highlightthickness=0,
    font=("Arial", 11),
)
Version_Entry.place(
    x=PANEL_X + 90,
    y=row2_y - 3,
    width=80,
    height=26,
)

Upload_Button_Image = PhotoImage(file=os.path.join(BASE_DIR, "UploadButton.png"))
Upload_Button = tk.Button(
    Background,
    image=Upload_Button_Image,
    borderwidth=0,
    highlightthickness=0,
    command=Upload,
    relief="flat",
)
Upload_Button.place(
    x=PANEL_X + 210,
    y=row2_y - 18,
    width=170,
    height=60,
)

# =========================================================== #
#  Hàng 3: GitHub RAW URL                                     #
# =========================================================== #
Firmware_URL = tk.StringVar()
row3_y = PANEL_Y + 2 * ROW_GAP

label_url = Label(
    Background,
    bg="#f1f1f1",
    text="RAW URL:",
    font=("Times New Roman", 12, "bold"),
)
label_url.place(
    x=PANEL_X,
    y=row3_y,
)

Url_Entry = tk.Entry(
    Background,
    bd=0,
    bg="#d4d4d4",
    textvariable=Firmware_URL,
    highlightthickness=0,
    font=("Arial", 11),
)
Url_Entry.place(
    x=PANEL_X + 130,
    y=row3_y - 3,
    width=350,
    height=28,
)

# =========================================================== #
#  Main loop                                                  #
# =========================================================== #
main_window.mainloop()  