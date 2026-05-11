Smart Plug Pro Dashboard
ระบบ Smart Plug สำหรับตรวจวัดการใช้พลังงานไฟฟ้าด้วย ESP32 และแสดงผลแบบ Real-time ผ่าน Dashboard บนเว็บ โดยใช้ MQTT Protocol ในการสื่อสารข้อมูล

คุณสมบัติของระบบ


วัดค่ากระแสไฟฟ้า (Ampere)


คำนวณกำลังไฟฟ้า (Watt)


คำนวณพลังงานสะสม (kWh)


คำนวณค่าไฟฟ้า (THB)


วิเคราะห์ระดับการใช้พลังงาน


แสดงผลแบบ Real-time ผ่าน MQTT


บันทึกประวัติการใช้พลังงานใน LocalStorage


รองรับการเชื่อมต่อใหม่อัตโนมัติ (Auto Reconnect)



โครงสร้างโปรเจกต์
smartplug-project/│├── esp32/│   └── smartplug.ino│├── dashboard/│   └── index.html│└── README.md

เทคโนโลยีที่ใช้
ESP32 Side


ESP32


Arduino Framework


WiFi.h


PubSubClient.h


Dashboard Side


HTML5


CSS3


JavaScript


MQTT.js


HiveMQ Broker



การทำงานของระบบ
ESP32
ESP32 จะ:


เชื่อมต่อ WiFi


เชื่อมต่อ MQTT Broker


อ่านค่า Analog จาก GPIO34


คำนวณ:


กระแสไฟ (Amp)


กำลังไฟ (Watt)


พลังงานสะสม (kWh)


ค่าไฟ




ส่งข้อมูลแบบ JSON ไปยัง MQTT Topic ทุก 5 วินาที


ตัวอย่าง JSON Payload:
{  "watt": 352.4,  "amp": 1.60,  "level": "Low",  "kwh": 0.0241,  "cost": 0.11,  "max_watt": 502.0,  "max_level": "Medium"}

Dashboard
Dashboard จะ:


Subscribe MQTT Topic


รับข้อมูลแบบ Real-time


แสดงข้อมูลผ่าน Card UI


แสดงระดับการใช้พลังงาน


บันทึกประวัติลง LocalStorage


แสดงสถิติย้อนหลัง



MQTT Configuration
Broker
broker.hivemq.com
Topic
cs423/smartplug/petch_1660702588

วิธีใช้งาน
Upload Code ลง ESP32
ติดตั้ง Library:


PubSubClient


WiFi


จากนั้น Upload ไฟล์:
smartplug.ino

เปิด Dashboard
เปิดไฟล์:
index.html
ผ่าน Browser

การคำนวณพลังงาน
กำลังไฟฟ้า
Watt = Amp × 220V
พลังงานสะสม
kWh += (Watt / 1000) × เวลา(ชั่วโมง)
ค่าไฟ
Cost = kWh × 4.5 บาท

ระดับการใช้พลังงาน
WattLevel< 100WStandby100 - 499WLow500 - 999WMedium1000 - 1999WHigh≥ 2000WVeryHigh

ตัวอย่างหน้าจอ Dashboard
ฟีเจอร์หลัก:


Real-time Power Monitoring


Animated Progress Bar


Power Trend Analysis


Historical Usage Table


Highest Usage Detection



การเชื่อมต่อ MQTT
Dashboard ใช้ WebSocket:
wss://broker.hivemq.com:8884/mqtt
ESP32 ใช้ TCP MQTT:
broker.hivemq.com:1883

จุดเด่นของโปรเจกต์


ใช้งานง่าย


Real-time Monitoring


Responsive UI


รองรับมือถือ


ไม่มี Backend Server


ใช้ Public MQTT Broker



อนาคตที่สามารถพัฒนาเพิ่มได้


เพิ่ม Relay เปิด/ปิดปลั๊กไฟ


แจ้งเตือนเมื่อใช้ไฟเกินกำหนด


บันทึกข้อมูลลง Database


สร้างกราฟการใช้พลังงาน


Login Authentication


Mobile Application


เชื่อมต่อ Firebase หรือ Node-RED



ผู้พัฒนา


ชื่อ: Petch


วิชา: CS423 IoT Project



License
This project is for educational purposes.
