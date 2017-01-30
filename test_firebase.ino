#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "test-iot-24619.firebaseio.com"
#define FIREBASE_AUTH "m74FpxeBCMqS8RoJe4ypglib1rjiQ60B2pg8TVzJ"

#define WIFI_SSID "WebAnt"
#define WIFI_PASS "ABCABC1819"


int greenPin = 4;
int redPin = 5;
int bluePin = 16;

void connectWifi() {

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }

  Serial.println();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println();
  Serial.println("Firebase host: ");
  Serial.println(FIREBASE_HOST);
}


void setup() {
    Serial.begin(9600);
    
    connectWifi();
    setupFirebase();
    
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void loop() {
    getDataFirebanse();
}


void getDataFirebanse(){
  String path = "led";
  
  FirebaseObject object = Firebase.get(path);

  int red = object.getInt("red");
  int green = object.getInt("green");
  int blue = object.getInt("blue");
  setColor(red,green,blue);
}

void setColor(int red, int green, int blue)
{
    #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
    #endif

    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}

