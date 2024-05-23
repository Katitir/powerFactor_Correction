#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>


#define RX 12
#define TX 11

int relay1 = 4;
int relay2 = 5;
int relay3 = 6;
int relay4 = 7;
int relay5 = 8;
int relay6 = 9;
int relay7 = 10;

float voltage;
float current;
float power;
float energy;
float frequency;
float pf;
float Capacitance;
float pot;

LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial pzemSerial(RX, TX);
PZEM004Tv30 pzem(pzemSerial);

void updateDisplay();
void conditions();
void electricParam();

void setup() {

Serial.begin(9600);

lcd.init();
lcd.backlight();
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("System On!!");
delay(2000); // wait for 2 seconds
lcd.setCursor(0, 1);
lcd.print("A Project Study Of");
delay(2000); // wait for 2 seconds
lcd.setCursor(0, 2);
lcd.print("AUTO PF CORRECTION");
delay(2000); // wait for 2 seconds
lcd.setCursor(0, 3);
lcd.print("Initializing...");
delay(3000); // wait for 2 seconds
lcd.clear();
delay(500);

digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);
digitalWrite(relay4, HIGH);
digitalWrite(relay5, HIGH);
digitalWrite(relay6, HIGH);
digitalWrite(relay7, HIGH);
delay(3000);

pinMode(relay1, OUTPUT);  //relay1
pinMode(relay2, OUTPUT);  //relay2
pinMode(relay3, OUTPUT);  //relay3
pinMode(relay4, OUTPUT);  //relay4
pinMode(relay5, OUTPUT);  //relay5
pinMode(relay5, OUTPUT);  //relay6
pinMode(relay7, OUTPUT); //relay7

}

void loop() {

 electricParam();
 Capacitance = round(((current*sqrt(1-(pf*pf)))/(6.2832*frequency*voltage))*(1000000));

 Serial.println(Capacitance);

 conditions();
 updateDisplay();


}

void electricParam(){

         
    Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);

    // Read the data from the sensor
     voltage = pzem.voltage();
     current = pzem.current();
     power = pzem.power();
     energy = pzem.energy();
     frequency = pzem.frequency();
     pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);
    }

    Serial.println();
    delay(2000);
}

void updateDisplay(){

  lcd.setCursor(0, 0);
  lcd.print("VOLTAGE     :");
  lcd.setCursor(13, 0);
  lcd.print(voltage, 3); // Print voltage with 3 decimal places
  lcd.print("V");

  lcd.setCursor(0, 1);
  lcd.print("CURRENT     :");
  lcd.setCursor(13, 1);
  lcd.print(current);
  lcd.print("A   ");

  lcd.setCursor(0, 2);
  lcd.print("FREQUENCY   :");
  lcd.setCursor(13, 2);
  lcd.print(frequency);
  lcd.print("HZ");

  lcd.setCursor(0, 3);
  lcd.print("CORRECTED PF:");
  lcd.setCursor(13, 3);
  lcd.print(pf);
  lcd.print("   ");

}

void conditions(){

  
 if(Capacitance == 1){

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 2){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 3){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 4){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 5){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 6){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 7){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 8){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 9){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 10){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 11){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 12){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 12){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 13){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 14){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 15){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 16){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 17){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 18){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 19){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 20){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 21){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 21){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 22){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 23){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 24){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 25){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 26){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 27){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 28){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 29){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 30){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 31){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 32){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 33){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 34){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 35){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 36){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 37){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 38){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 39){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 40){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 41){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 42){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 43){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 44){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 45){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 46){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 47){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 48){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 49){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 50){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 51){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 52){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 53){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 54){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 55){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 56){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 57){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 58){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 59){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 60){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 61){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 62){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 63){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, HIGH);
  delay(200);
} else if(Capacitance == 64){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 65){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 66){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 67){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 68){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 69){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 70){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 71){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 72){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 73){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 74){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 75){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 76){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 77){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 78){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 79){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 80){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 81){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 82){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 83){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 84){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 85){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 86){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 87){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 88){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 89){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 90){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 91){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 92){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 93){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 94){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 95){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 96){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 97){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 98){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 99){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 100){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 101){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 102){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 103){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 104){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 105){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 106){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 107){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 108){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 109){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 110){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 111){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
}  else if(Capacitance == 112){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
}  else if(Capacitance == 113){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 114){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 115){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 116){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 117){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 118){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 119){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 120){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 121){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 122){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 123){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 124){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 125){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 126){
   
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else if(Capacitance == 127){
   
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  delay(200);
} else {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
} 



}