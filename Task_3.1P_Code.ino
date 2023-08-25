#include <WiFiNINA.h>   //For WiFi connection, incorporate the WiFiNINA library.
#include <ThingSpeak.h>   //For simplified ThingSpeak communication, include the ThingSpeak library.
#include <DHT.h>    //Utilise the DHT library for interfacing with DHT11 sensor.

#define DHTPIN 4    //Specify the digital pin attached to the DHT sensor.
#define DHTTYPE DHT11   //Specify the DHT sensor type being used (here, DHT11).

// Define WiFi credentials
char SSID[] ="tanya";   //WiFi SSID
char PASS[]="hello12345";   //WiFI Password

// Channel settings for ThingSpeak
unsigned long Channel = 2251600;    //ThingSpeak channel number
const char* API_Key = "7MOHI4E845IJQWOG";   //ThingSpeak API key

WiFiClient myclient;    //Initialize a WiFi client object and use it to communicate over a network.
DHT dht(4, DHT11);    //Initialize a DHT object with pin 4 for DHT11 sensor.

void setup() {
  Serial.begin(9600);   // Initialize the serial communication at 9600 baud rate.
  dht.begin();    // Initialize communication with the DHT sensor.

  //Establish WiFi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Establishing WiFi connection....");   //Show message for connection attempt
    //Serial.println(SSID);
    WiFi.begin(SSID, PASS);   //Configure a WiFi connection using the specified credentials.
    delay(2000);    //Prior to the subsequent connection attempt, wait for a moment
  }
  Serial.println("WiFi connection achieved..");   //Successful WiFi connection message.
  ThingSpeak.begin(myclient);   //Initialize ThingSpeak communication with WiFi client
 
}

void loop() {
  float temp = dht.readTemperature();   //Read the DHT sensor's temperature.

  // Display temperature data
  Serial.print("Temperature is: ");   //Print a label
  Serial.print(temp);  //Display the temperature value
  Serial.println("°C");   //Print its unit

  ThingSpeak.writeField(Channel, 1, temp, API_Key);   //send temperature information to ThingSpeak
  Serial.println("Data transfer was successfully completed");   //successful data transfer message

  // Display humidity data
  float humid = dht.readHumidity();   //Read the humidity data from DHT sensor.
  Serial.print("Humidity is: ");    //Print a label
  Serial.print(humid);    //Display the humidity value
  ThingSpeak.writeField(Channel, 2, humid, API_Key);    //send humidity information to ThingSpeak
  Serial.println("Data transfer was successfully completed");   //successful data transfer message

  delay(3000);    //Wait a while before taking further readings.
}
