#define BLYNK_TEMPLATE_ID "TMPL3yjlPOWMN"
#define BLYNK_TEMPLATE_NAME "Human Discomfort Indicator"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char auth[] = "VyXieXpjIoB9PYv9pqPV4fZcGrhRr7hs"; //here you can give your auth token
char ssid[] = "SAINIHHAAR 5426";//your hotspot ssid
char pass[] = "1234567890";//and its password

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
BlynkTimer timer;

void s(){
  float h = dht.readHumidity();
  float c = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hi = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(c, h, false);
  float di = c - (0.55 - 0.0055 * h) * (c - 14.5);

  String st;

  if(di < 24) st="Comfort";
  else st="Discomfort";

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(c);
  lcd.print(" H:");
  lcd.print(h);

  lcd.setCursor(0,1);
  lcd.print("HI:");
  lcd.print(hic);
  lcd.print(" ");
  lcd.print(st);

  Blynk.virtualWrite(V0,c);
  Blynk.virtualWrite(V1,h);
  Blynk.virtualWrite(V2,hic);
  Blynk.virtualWrite(V3,st);
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  lcd.init();
  lcd.backlight();
  timer.setInterval(2000L,s);
}

void loop(){
  Blynk.run();
  timer.run();
}