#include <Wire.h>
#include<MPU6050.h> //For using the MPU

#include <ESP8266WiFi.h>

#include <FirebaseArduino.h>  
 #include <ArduinoJson.h> 
 #include <ESP8266HTTPClient.h>
// Set these to run example.  
#define FIREBASE_HOST "nodemcu-dbbc7-default-rtdb.firebaseio.com"  
#define FIREBASE_AUTH "fTJhLcfVqrJRe8TNuRQsTTSuTvbAMcwNBBMBcLqC"  
#define WIFI_SSID "KG"  
#define WIFI_PASSWORD "randomthoughts@..."  
float x,y,z,a,prev;
int count=0,steps=0,up2date=0,i=0;

MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
     //beginning the connection
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  checkSettings();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
}

void checkSettings() //basic hardware checking
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  
  calc();

}

void calc(){
  i++;
  Vector normAccel= mpu.readNormalizeAccel();
  x=normAccel.XAxis;
  y=normAccel.YAxis;
  a=sqrt(x*x+y*y);

  if(a>prev){
    
  }
  else if(a<(prev-0.3)){
    count++;
    if(count==4){
      count=0;
      steps++;
    }
  }
  Serial.println(steps);
  if(i==300){sendata();i=0;}
  prev=a;

  delay(100);
}

void sendata(){
    Firebase.setFloat("number", steps);  
  // handle error  
  if (Firebase.failed()) {  
      Serial.print("setting /number failed:");  
      Serial.println(Firebase.error());    
      return;  
  }  
}

