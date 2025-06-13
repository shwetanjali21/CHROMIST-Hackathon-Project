# 🌫 CHROMIST

"Mist Managed"  -Click. Sync. Breathe.  
Smart humidity control from your browser using embedded hardware, mobile Bluetooth, and a Web Bluetooth–ready design.
## 🔧 What It Does
- Simulates a smart ultrasonic humidifier using ATmega328P
- Bluetooth ON/OFF control via MIT App Inventor (HC-05)
- Full circuit simulation with Wokwi
- PCB designed in KiCad
- BLE upgrade proposed (ESP32) for Web Bluetooth API support

## 🧰 Tech Stack
- ATmega328P (firmware in Embedded C)
- KiCad (PCB design)
- MIT App Inventor (mobile control)
- Wokwi (circuit simulation)
- Web Bluetooth API (planned with ESP32)

## 🌐 Web Upgrade
Switching HC-05 → ESP32 enables:
- BLE scan & connect via Chrome
- Browser sends ON/OFF commands using GATT
- App-free control in future versions

## 📄 Files Included
- main.c – Embedded code
- CHROMIST_Report.pdf – 9:16 stylish hackathon report
- CHROMIST_app.aia – Bluetooth app file
- Screenshots & circuit schematic

## 🔗 Live Wokwi Simulation
  -  https://wokwi.com/projects/432915125333736449

