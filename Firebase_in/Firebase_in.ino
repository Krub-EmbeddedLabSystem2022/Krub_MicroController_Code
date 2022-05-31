//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>

SoftwareSerial NodeSerial(D7, D8);

// Set these to run example.
#define FIREBASE_HOST "krub-embed-boooom-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "z6t3JDdQVoCHSJpUlO1SzH86INbhHyUOWRw2N8c7"
#define WIFI_SSID "sunsTorm"
#define WIFI_PASSWORD "fukupuku"



int n;
int ledPin = 2;
int digitalPin = D1;
int val = 0;
//int count = 0;

int state;

void setup() {

  pinMode(D7, INPUT); //RX
  pinMode(D8, OUTPUT); // TX

  pinMode(ledPin, OUTPUT); //sets the pin as output
  pinMode(digitalPin, INPUT); // sets the pin as input

  Serial.begin(9600);
  NodeSerial.begin(9600);
  
//  pinMode(LED_BUILTIN, OUTPUT);

  
  
//
//  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
//  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  state = 0;
}


void loop() {

  val = digitalRead(digitalPin);
  Serial.print("val = ");
  Serial.println(val);
  if (val == 0) {

    state = 1;
    
    Serial.println("bye Mother fuckerrr");
//    Firebase.setFloat("people_out", 0);
    
    digitalWrite(ledPin, 1);
    Serial.println("Detect object");
    NodeSerial.write("0");
    
  } else {
    if(state == 1){
      state = 0;
      // what if i move this bit of code here, so it doesn't have to wait for firebase ?
      digitalWrite(ledPin, 0); //LED low  
      NodeSerial.write("1");  // must come before the firebase command
      Serial.println("No Object");
      int total = Firebase.getFloat("total_in_room");
      Firebase.setFloat("total_in_room", total+1);
      
    }
    
  }
   delay(100);  

//  if (Firebase.failed()) {
//      Serial.print("setting /number failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }

  Serial.println(n);
}
