#include <SoftwareSerial.h>
#define sensorPin1 A1
#define ECHOPIN 5
#define TRIGPIN 6
int sensorPin = A0;
SoftwareSerial mySerial(3,2); // SIM800L Tx & Rx is connected to Arduino
#3 & #2
void setup()
{
Serial.begin(115200);
pinMode(sensorPin, INPUT);
pinMode(ECHOPIN, INPUT_PULLUP);
pinMode(TRIGPIN, OUTPUT);
digitalWrite(ECHOPIN, HIGH);
mySerial.begin(9600);
delay(1000);
}
void loop()
{
int tiltSensorValue = analogRead(sensorPin1);
int distance = getDistance();
int gasSensorValue = analogRead(A0);
Serial.println(tiltSensorValue);
if (tiltSensorValue > 450 )
{
sendMessage("Alert: Manhole Tilt Detected");
Serial.println("tilt detected");
}
if (gasSensorValue > 80 )
{
sendMessage("Alert: Poisonous Gas Detected");
Serial.println(" Poisonous Gas detected");
}
if (distance < 30 )
{
sendMessage("Alert: Water level Reached");
Serial.println(" Water level Reached");
}
delay(1000);
}
int getDistance()
{
digitalWrite(TRIGPIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIGPIN, HIGH);
delayMicroseconds(15);
digitalWrite(TRIGPIN, LOW);
int pulseDuration = pulseIn(ECHOPIN, HIGH, 26000);
int distance = pulseDuration / 58;
Serial.println(distance);
Serial.println(" cm");
return distance;
}
void sendMessage(const char *message)
{
mySerial.println("AT"); // Once the handshake test is successful, it
will back to OK
updateSerial();
mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
updateSerial();
mySerial.println("AT+CMGS=\"+919495074331\""); // Change ZZ with country
code and xxxxxxxxxxx with phone number to SMS
updateSerial();
mySerial.print(message); // Text content
updateSerial();
mySerial.write(26);
}
void updateSerial()
{
delay(500);
while (Serial.available())
{
mySerial.write(Serial.read()); // Forward what Serial received to
Software Serial Port
}
while (mySerial.available())
{
Serial.write(mySerial.read()); // Forward what Software Serial
received to Serial Port
}
}