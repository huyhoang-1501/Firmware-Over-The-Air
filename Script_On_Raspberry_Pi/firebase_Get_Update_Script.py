#!/usr/bin/python3

from time import sleep
import pyrebase
import requests
import os

# ============================= #
#  Cau hinh duong dan           #
# ============================= #

BASE_DIR = "/home/pi/Desktop/Firmware-Over-The-Air/Script_On_Raspberry_Pi"
VERSION_FILE = os.path.join(BASE_DIR, "version.txt")
UPDATE_HEX_PATH = os.path.join(BASE_DIR, "Update.hex")
GUI_SCRIPT = os.path.join(BASE_DIR, "GUI_Update_Notification.py")
# Äá»c version hiá»‡n táº¡i lÆ°u trÃªn Pi
with open(VERSION_FILE, "r") as f:
    version_check = int(f.read().strip())

# ============================= #
#  Firebase config              #
# ============================= #
Config = {
    "apiKey": "AIzaSyADvax54nso0DOMKLgT35pfedVbWUZU9YE",
    "authDomain": "firmwareovertheair-b8a90.firebaseapp.com",
    "databaseURL": "https://firmwareovertheair-b8a90-default-rtdb.firebaseio.com",
    "projectId": "firmwareovertheair-b8a90",
    "storageBucket": "",
}

firebase = pyrebase.initialize_app(Config)
database = firebase.database()

while True:
    try:
        
        data = database.get().val()
        if not data:
            print("No data in DB")
            sleep(5)
            continue

        current_version = int(data.get("version", 0))
        update_url = data.get("url", "").strip()

        print("Current version on server:", current_version)
        print("Current version on Pi    :", version_check)

        if not update_url:
            print("No update URL in DB")
            sleep(5)
            continue

        if version_check != current_version:
            print("New firmware detected, downloading from:", update_url)

            # TTai file hex len 
            r = requests.get(update_url, timeout=30)
            r.raise_for_status()

            with open(UPDATE_HEX_PATH, "wb") as f:
                f.write(r.content)

            # Cap nhat version.txt
            with open(VERSION_FILE, "w") as f:
                f.write(str(current_version))

            version_check = current_version

            print("Download done, launching GUI_Update_Notification.py")
            # Cap nhat version
            exec(open(GUI_SCRIPT).read())

    except Exception as e:
        print("Error in update loop:", e)

    sleep(5)