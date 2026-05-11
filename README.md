# Smart Plug Pro Dashboard

ระบบ Smart Plug สำหรับตรวจวัดการใช้พลังงานไฟฟ้าด้วย ESP32 และแสดงผลแบบ Real-time ผ่าน Dashboard บนเว็บ โดยใช้ MQTT Protocol ในการสื่อสารข้อมูล

---

## Features

- วัดค่ากระแสไฟฟ้า (Ampere)
- คำนวณกำลังไฟฟ้า (Watt)
- คำนวณพลังงานสะสม (kWh)
- คำนวณค่าไฟฟ้า (THB)
- วิเคราะห์ระดับการใช้พลังงาน
- แสดงผลแบบ Real-time ผ่าน MQTT
- บันทึกประวัติการใช้พลังงานใน LocalStorage
- รองรับการเชื่อมต่อใหม่อัตโนมัติ (Auto Reconnect)

---

# Project Structure

```bash
smartplug-project/
│
├── esp32/
│   └── smartplug.ino
│
├── dashboard/
│   └── index.html
│
└── README.md
```

---

# Technologies Used

## ESP32 Side

- ESP32
- Arduino Framework
- WiFi.h
- PubSubClient.h

## Dashboard Side

- HTML5
- CSS3
- JavaScript
- MQTT.js
- HiveMQ Broker

---

# System Workflow

## ESP32

ESP32 จะทำงานดังนี้:

1. เชื่อมต่อ WiFi
2. เชื่อมต่อ MQTT Broker
3. อ่านค่า Analog จาก GPIO34
4. คำนวณ:
   - กระแสไฟฟ้า (Amp)
   - กำลังไฟฟ้า (Watt)
   - พลังงานสะสม (kWh)
   - ค่าไฟฟ้า (THB)
5. ส่งข้อมูลแบบ JSON ทุก 5 วินาที

---

# Example JSON Payload

```json
{
  "watt": 352.4,
  "amp": 1.60,
  "level": "Low",
  "kwh": 0.0241,
  "cost": 0.11,
  "max_watt": 502.0,
  "max_level": "Medium"
}
```

---

# Dashboard Features

Dashboard สามารถ:

- Subscribe MQTT Topic
- รับข้อมูลแบบ Real-time
- แสดงข้อมูลผ่าน Card UI
- วิเคราะห์ระดับการใช้พลังงาน
- บันทึกข้อมูลลง LocalStorage
- แสดงสถิติย้อนหลัง
- ตรวจจับค่าการใช้ไฟสูงสุด

---

# MQTT Configuration

## Broker

```text
broker.hivemq.com
```

## Topic

```text
cs423/smartplug/petch_1660702588
```

---

# Installation Guide

## 1. Upload Code ลง ESP32

ติดตั้ง Library:

- WiFi
- PubSubClient

จากนั้น Upload:

```text
smartplug.ino
```

---

## 2. เปิด Dashboard

เปิดไฟล์:

```text
index.html
```

ผ่าน Browser

---

# Power Calculation

## Power Formula

:contentReference[oaicite:0]{index=0}

## Energy Consumption

:contentReference[oaicite:1]{index=1}

## Electricity Cost

:contentReference[oaicite:2]{index=2}

---

# Power Usage Levels

| Watt Range | Level |
|---|---|
| < 100W | Standby |
| 100 - 499W | Low |
| 500 - 999W | Medium |
| 1000 - 1999W | High |
| ≥ 2000W | Very High |

---

# MQTT Connection

## Dashboard (WebSocket)

```text
wss://broker.hivemq.com:8884/mqtt
```

## ESP32 (TCP MQTT)

```text
broker.hivemq.com:1883
```

---

# Main Features

- Real-time Power Monitoring
- Animated Progress Bar
- Power Trend Analysis
- Historical Usage Table
- Highest Usage Detection

---

# Advantages

- ใช้งานง่าย
- Real-time Monitoring
- Responsive UI
- รองรับมือถือ
- ไม่มี Backend Server
- ใช้ Public MQTT Broker

---

# Future Improvements

- เพิ่ม Relay เปิด/ปิดปลั๊กไฟ
- แจ้งเตือนเมื่อใช้ไฟเกินกำหนด
- บันทึกข้อมูลลง Database
- สร้างกราฟการใช้พลังงาน
- Login Authentication
- Mobile Application
- เชื่อมต่อ Firebase
- เชื่อมต่อ Node-RED

---

# Developer

- Name: Petch
- Course: CS423 IoT Project

---

# License

This project is for educational purposes only.
