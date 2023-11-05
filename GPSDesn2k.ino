#include <TinyGPS++.h>
#include <SoftwareSerial.h>


// Choose two Arduino pins to use for software serial
int GPSRXPin = 2;
int GPSTXPin = 3;
int BTRXPin = 6;
int BTTXPin = 7;

int BTBaud = 9600;
int GPSBaud = 115200;

// Create a TinyGPS++ object
TinyGPSPlus gps;


// Create a software serial port called "gpsSerial" and "BTSerial"
SoftwareSerial gpsSerial(GPSRXPin, GPSTXPin);
SoftwareSerial BTSerial(BTRXPin, BTTXPin); //


// Helper Funcs
void displaySerial();
void displayBTSerial();

void setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  // Start the software serial port at the BT Module's default baud
  BTSerial.begin(BTBaud); 

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      displayInfo();
    }
  }

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void displayInfo()
{
  displaySerial();
  if (BTSerial.available()) {
    displayBTSerial();
  }
}



void displaySerial() {
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);

}


void displayBTSerial() {
    if (gps.location.isValid())
    {
        BTSerial.print("Latitude: ");
        BTSerial.println(gps.location.lat(), 6);
        BTSerial.print("Longitude: ");
        BTSerial.println(gps.location.lng(), 6);
        BTSerial.print("Altitude: ");
        BTSerial.println(gps.altitude.meters());
    }
    else
    {
        BTSerial.println("Location: Not Available");
    }

    BTSerial.print("Date: ");
    if (gps.date.isValid())
    {
        BTSerial.print(gps.date.month());
        BTSerial.print("/");
        BTSerial.print(gps.date.day());
        BTSerial.print("/");
        BTSerial.println(gps.date.year());
    }
    else
    {
        BTSerial.println("Not Available");
    }

    BTSerial.print("Time: ");
    if (gps.time.isValid())
    {
        if (gps.time.hour() < 10) BTSerial.print(F("0"));
        BTSerial.print(gps.time.hour());
        BTSerial.print(":");
        if (gps.time.minute() < 10) BTSerial.print(F("0"));
        BTSerial.print(gps.time.minute());
        BTSerial.print(":");
        if (gps.time.second() < 10) BTSerial.print(F("0"));
        BTSerial.print(gps.time.second());
        BTSerial.print(".");
        if (gps.time.centisecond() < 10) BTSerial.print(F("0"));
        BTSerial.println(gps.time.centisecond());
    }
    else
    {
        BTSerial.println("Not Available");
    }

    BTSerial.println();
    BTSerial.println();
    delay(1000);

}
