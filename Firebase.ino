#include <WiFi.h>
#include <Servo.h>
#include "DHT.h"
#define DHTTYPE DHT11
#include "FirebaseESP32.h"

#define FIREBASE_HOST "https://miniproject-fb647-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "Sls8XR4cmpLxG3Ezk6Ew6LJl1uSAYtXeBmqE9orq"
#define WIFI_SSID "Matiaj kamu"
#define WIFI_PASSWORD "matiajakamu"



#define DHTPIN 22
#define servoPin 23
DHT dht(DHTPIN,DHTTYPE);
FirebaseData firebaseData;
Servo myServo;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  
  dht.begin();
  myServo.attach(servoPin);
  initWifi();
  }

void loop() {
  // put your main code here, to run repeatedly:
   // put your main code here, to run repeatedly:
  
  float failed=0;
  float t=dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if(Firebase.getInt(firebaseData,"/data/switch")){
    
    if(firebaseData.intData() == 1){
      Firebase.setFloat(firebaseData ,"/data/temperature" , t);
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.println(F("°C "));
      Firebase.setFloat(firebaseData ,"/data/humidity" , h);
      Serial.print(F("%  Humadity: "));
      Serial.println(h);
      
      int posDegrees1= 0;
      int posDegrees2= 45;
      int posDegrees3= 90;
      int posDegrees4= 135;
      int posDegrees5= 180;
      int posDegrees6= 225;
      int posDegrees7= 270;
      int posDegrees8= 315;
      int posDegrees9= 360;
           
      myServo.write(posDegrees1);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees1);
      delay(10);
      myServo.write(posDegrees2);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees2);
      delay(10);
      myServo.write(posDegrees3);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees3);
      delay(10);
      myServo.write(posDegrees4);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees4);
      delay(10);
      myServo.write(posDegrees5);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees5);
      delay(10);
      myServo.write(posDegrees6);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees6);
      delay(10);
      myServo.write(posDegrees7);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees7);
      delay(10);
      myServo.write(posDegrees8);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees8);
      delay(10);
      myServo.write(posDegrees9);
      Firebase.setFloat(firebaseData ,"/data/Servo" , posDegrees9);
      delay(10);
      
    }else{
      Firebase.setFloat(firebaseData ,"/data/temperature" , failed);
      Firebase.setFloat(firebaseData ,"/data/humidity" , failed);
      Firebase.setFloat(firebaseData ,"/data/Servo" , failed);
    }
   
  }  
  delay(500);
}

void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
