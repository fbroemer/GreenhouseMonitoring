#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>

dht DHT;

#define DHT11_PIN 7

//LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define SensorPin A1 
//float sensorValue = 0; 
int mode=0;

void waterdetection(){
int sensor=analogRead(A0);
int water=sensor/4;


  if(water>50){
    digitalWrite(9, HIGH);
    lcd.print("Water detected");
    lcd.setCursor(0,1);
    lcd.print("with value: ");
    lcd.print(water);
  }
  else{
    digitalWrite(9, LOW);
    lcd.print("No water");
    lcd.setCursor(0,1);
    lcd.print("with value: ");
    lcd.print(water);
  }
  return;
}

void moisturesensor(){
  int sensorValue =0;
  
  sensorValue=analogRead(SensorPin);
  float moist = 0;
  moist = sensorValue*0.1;
  
  lcd.print("Soil Moisture:");
  lcd.setCursor(0,1);
  lcd.print(moist);
  lcd.print("%");
  return;
}

void tempHumidity(){
  int chk = DHT.read11(DHT11_PIN);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  return;
}

void setup() {

 
  pinMode(9, OUTPUT);
  lcd.begin(16,2);               // initialize the lcd 

  lcd.clear();                   // go home
  lcd.print("Initializing");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("complete");   
  delay(1000);
  lcd.home();
  lcd.clear();    

}

void loop() {

  if (mode==0){
    waterdetection();
    mode++;
  }
  else if(mode==1){
    moisturesensor();
    mode++;
  }
  else{
    tempHumidity();
    mode=0;
  }


   delay(4000);
   lcd.home();
   lcd.clear(); 


}
