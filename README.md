# Step-Counter
A Step-Counter built using the NodeMCU 
This project uses an MPU6050 accelerometer to measure acceleration along the three axes. This data is then processed by the NodeMCU using the peak-finding algorithm to determine if a step has been made

The NodeMCU sends the clock pulse to the MPU6050 establishing master-slave connection. THe MPU6050 in turn transmits the data regarding acceleration in terms of voltage to the NodeMCU

![image](https://user-images.githubusercontent.com/78297958/143433958-78d4cc39-177d-4fe4-b6fb-934eab1ac7d1.png)

![image](https://user-images.githubusercontent.com/78297958/143434306-2211ab71-9276-4b01-97e9-886bf57e0b79.png)

The NodeMCU peridocially pushes the data to Blynk. We view this data using a virtual pin.

![image](https://user-images.githubusercontent.com/78297958/143437485-30417f68-ae37-4afd-8ac1-1170a83cd888.png)
