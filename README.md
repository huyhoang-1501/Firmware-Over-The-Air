# Firmware Over The Air (FOTA) Implementation

This project showcases a straightforward implementation of Firmware Over The Air (FOTA) updates, leveraging cloud services to send updates which are then parsed by a Raspberry Pi 4 client.

## Benefits of FOTA
- **Bug and Security Fixes:** Allows for the swift rectification of software vulnerabilities.
- **Functionality Improvements:** Enhances system functions over time without needing hardware adjustments.
- **Version Updates:** Seamlessly updates firmware versions without physical intervention.

## Overview

![Sequence Diagram](assets/Sequence_Diagram.png)

Updates can be uploaded to a cloud server (Firebase). The Raspberry Pi, acting as the main Microcontroller Unit (MCU), listens to real-time database changes. Upon detecting a valid update, a GUI notifies the user about the available update, providing options to either initiate the update immediately or postpone it. If the user chooses to proceed, the Raspberry Pi transfers the new hex file to the target microcontroller (STM32F103C8T6) via UART. The progress and status of the update are reflected in the Raspberry Pi's GUI.

Once the update process concludes, the new application activates on the target STMF10, and the GUI confirms the update's successful installation.

[**Demo Video**](https://www.youtube.com/watch?v=OATkTLVjR8Q)

<p align="center">
  <a href="https://www.youtube.com/watch?v=OATkTLVjR8Q">
    <img src="assets/DemoVideo.png" alt="Demo Video" width="500">
  </a>
</p>


## Components

1. **Cloud Server (Firebase)**:
   - Firebase is chosen for its real-time database, encryption capabilities, and Python integration.
   - Provides a platform for uploading hex files using a dedicated GUI.

2. **Desktop GUI**: 
   - Designed with Python and Tkinter.
   - Facilitates the upload of update files to the server.

        ![GUI Image](assets/GUI_Desktop.png)

3. **Raspberry Pi**:
   - Automatically polls the database for updates.
   - Fetches and parses new hex files from the server when detected.
   - Guides users through the update process, including safety checks and update status.

        ![GUI Image](assets/GUI_Desktop.png)

4. **Application**:
   - Manages UART-based update commands and user switch input, requesting a system reset to return control to the Bootloader when a firmware update is required.

        ![Application](assets/App.jpg)

5. **Bootloader**:
   - Responsible for memory management, featuring Bootloader (BL), Bank 1, and Bank 2 sections.
   - Manages update sequence, deciding between existing or new applications based on switch states and update availability.

        ![Bootloader](assets/Boot.jpg)

6. **Application (Update Handler)**:
    - Handles runtime communication with the update controller (Raspberry Pi) via UART.
    - Monitors user switch state and update commands to determine update requests.
    - Triggers a system reset to transfer execution back to the Bootloader when an update is requested.
    - Maintains normal application execution until a valid update condition is detected.

         ![Update](assets/Update.jpg)

<div align="center">

**© 2025 – Ho Chi Minh City University of Technology and Engineering (HCMUTE)**  
**Electronics & Communication Engineering Technology**

**Nguyễn Phạm Huy Hoàng**  

</div>