# 🚗 Self-Stopping Car (Arduino Project)

A simple Arduino-based system that helps your car avoid collisions while **driving or parking** using ultrasonic sensors, LCDs, and a buzzer.

---

## 🧠 How It Works

When the car starts, choose a mode from the Serial Monitor:

1. **Driving Mode**  
   - Front sensor detects obstacles.  
   - If anything is closer than **10 cm**, LCD (front) shows a warning.  
   - If it’s under **4 cm**, the car **stops automatically**.  
   - Rear sensor shows warnings on the back LCD if a vehicle is too close.

2. **Parking Mode**  
   - Rear sensor checks for obstacles while reversing.  
   - Distance is shown on the front LCD.  
   - If an object is closer than **4 cm**, the car **stops**.

---

## 🔧 Hardware Used

- Arduino UNO  
- 2x HC-SR04 Ultrasonic Sensors  
- 2x 16x2 I2C LCDs  
- Buzzer  
- DC Motors + Motor Driver  

---

## 📌 Pin Setup

| Component        | Pin     |
|------------------|---------|
| Front Sensor     | trig: 6, echo: 7 |
| Rear Sensor      | trig: 12, echo: 11 |
| Buzzer           | 10      |
| Motors           | 8, 9    |
| LCD Front        | I2C 0x27 |
| LCD Back         | I2C 0x26 |

---

## 🚀 Getting Started

1. Upload the `.ino` file via Arduino IDE.  
2. Open Serial Monitor → Enter `1` (Parking) or `2` (Driving).  
3. Watch the car react based on sensor input — warnings + auto stop.

---

## 🛑 Safety First!

- **< 10 cm** → Visual warning  
- **< 4 cm** → Motors turn off automatically  

---

