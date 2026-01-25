from tkinter import *
import os

# Nếu chưa cài, hãy chạy: pip install Pillow
from PIL import Image, ImageTk

# Lấy đường dẫn tuyệt đối đến thư mục chứa file window.py
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

def resource_path(name: str) -> str:
    """
    Trả về đường dẫn đầy đủ đến resource (ảnh, v.v...)
    dựa trên thư mục chứa file window.py
    """
    return os.path.join(BASE_DIR, name)

def btn_clicked():
    print("Button Clicked")

# Kích thước cửa sổ
WINDOW_WIDTH = 1000
WINDOW_HEIGHT = 600

# Tạo cửa sổ chính
window = Tk()
window.title("GUI FOTA")
window.geometry(f"{WINDOW_WIDTH}x{WINDOW_HEIGHT}")

# Background Stuff
window.configure(bg="#f1f1f1")
canvas = Canvas(
    window,
    bg="#f1f1f1",
    height=WINDOW_HEIGHT,
    width=WINDOW_WIDTH,
    bd=0,
    highlightthickness=0,
    relief="ridge"
)
canvas.place(x=0, y=0)

# ===== Load & scale background image =====
bg_path = resource_path("background.png")

# Dùng Pillow mở và resize ảnh cho vừa khung cửa sổ
bg_pil = Image.open(bg_path)
bg_pil = bg_pil.resize((WINDOW_WIDTH, WINDOW_HEIGHT), Image.LANCZOS)
background_img = ImageTk.PhotoImage(bg_pil)

background = canvas.create_image(
    WINDOW_WIDTH / 2,
    WINDOW_HEIGHT / 2,
    image=background_img
)

# ===== Entry Browse =====
entry0_img = PhotoImage(file=resource_path("img_textBox0.png"))
entry0_bg = canvas.create_image(
    744.0, 210.5,
    image=entry0_img
)

entry0 = Entry(
    bd=0,
    bg="#d4d4d4",
    highlightthickness=0
)
entry0.place(
    x=580.5, y=185,
    width=327.0,
    height=49
)

# ===== Entry Version Number =====
entry1_img = PhotoImage(file=resource_path("img_textBox1.png"))
entry1_bg = canvas.create_image(
    501.0, 325.5,
    image=entry1_img
)

entry1 = Entry(
    bd=0,
    bg="#d4d4d4",
    highlightthickness=0
)
entry1.place(
   x=440.5, y=300,
    width=121.0,
    height=49
)

# ===== Button Browse =====
img0 = PhotoImage(file=resource_path("btn_browse.png"))
b0 = Button(
    image=img0,
    borderwidth=0,
    highlightthickness=0,
    command=btn_clicked,
    relief="flat"
)
b0.place(
    x=405, y=171,
    width=143,
    height=79
)

# ===== Button Upload =====
img1 = PhotoImage(file=resource_path("btn_upload.png"))
b1 = Button(
    image=img1,
    borderwidth=0,
    highlightthickness=0,
    command=btn_clicked,
    relief="flat"
)
b1.place(
    #x=768, y=300,
    x=630, y=300,
    width=165,
    height=51
)

window.resizable(False, False)
window.mainloop()