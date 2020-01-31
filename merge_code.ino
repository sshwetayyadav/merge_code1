#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
#include <CurieBLE.h>
#include <Ultrasonic.h>

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "kX65NZxXrTBmynioVhkKgm0_fui_p-G2";
 
/* WiFi credentials */
char ssid[] = "go";
char pass[] = "shwetayadav20";
 
SimpleTimer timer;
//BLEPeripheral  blePeripheral;
WidgetLED green(V1);
WidgetLED orange(V2);
WidgetLED red(V3);


Ultrasonic ultrasonic(7);
int distance = 0;
int thresh [3] = {20,12,4};
 
int mq135 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0; 
void setup() 
{
  Serial.begin(115200);//setting the baud rate at 9600
  delay(1000);        //delay 1000
  blePeripheral.setLocalName("garbage");
  blePeripheral.setDeviceName("garbage");
  blePeripheral.setAppearance(384);
  Blynk.begin(blePeripheral, auth);
  blePeripheral.begin();
  Serial.println("Waiting for connections...");//printing on serial monitor
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
distance = ultrasonic.distanceRead();  //calculating distance
Serial.print(distance);
Blynk.run();
  if(distance<=thresh[0]&&distance>=thresh[1]&&distance>=thresh[2]){  //when trash is 10% full green led will on
    green.on();
    Serial.println(1);
    }
  else if(distance<=thresh[0]&&distance<=thresh[1]&&distance>=thresh[2]){  //when trash is 50% full orange led is on
    green.on();
    orange.on();
    Serial.println(2);
  }
  else if(distance<=thresh[0]&&distance<=thresh[1]&&distance<=thresh[2]){  //when trash is 80% full red led is on
    green.on();
    orange.on();
    red.on();
    Serial.println(3);
  }
  else{
    green.off();    //else led are off
    orange.off();
    red.off();
    Serial.println(0);
  }
  delay(100);

}
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}
 
/***************************************************
 * Send Sensor data to Blynk
 **************************************************/
void getSendData()
{
data = analogRead(mq135); 
  Blynk.virtualWrite(V2, data); //virtual pin V2
 
  if (data > 600 )
  {
    Blynk.notify("Smoke Detected!!!"); 
  }
 
}
