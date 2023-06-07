#include <LiquidCrystal.h>

int seconds = 0;
const int analogIn = A0;
int humiditysensorOutput = 0;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

const int ldrPin = 2; // LDR no pino analógico 2
const int ledVerde = 8;
const int ledVermelho = 10;
int ldrValue = 0; // Valor lido do LDR

void setup()
{
  lcd_1.begin(16, 2);
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledVermelho,OUTPUT);
}

void loop()
{
  
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  delay(2000);
  //Simulam um Sensor de Umidade e Temperatura DHT11 com essa parte do código
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; 
  tempC = (Voltage-500) * 0.1; 
  Serial.print("Raw Value = " );                  
  Serial.print(RawValue);      
  Serial.print("\t milli volts = ");
  Serial.print(Voltage,0);
  Serial.print("\t Temperature in C = ");
  Serial.print(tempC,1);
  humiditysensorOutput = analogRead(A1);
  Serial.print("Humidity: "); 
  Serial.print(map(humiditysensorOutput, 0, 1023, 10, 70));
  Serial.println("%");

  //Luminosidade aceitavel deve estar entre 570 e 200 ()
 
  //Luminosidade Alta
  if (ldrValue > 570){
    digitalWrite(ledVermelho,HIGH);
    digitalWrite(ledVerde,LOW);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Luminosidade");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Alta");
    delay(2000);
  }
  //Luminosidade Média.
  if (ldrValue >= 200 && ldrValue <= 570) {
    digitalWrite(ledVermelho,LOW);
    digitalWrite(ledVerde,HIGH);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Luminosidade");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Media");
    delay(2000);
  }
  //Luminosidade Baixa.
  if (ldrValue < 200) {
    digitalWrite(ledVermelho,LOW);
    digitalWrite(ledVerde,HIGH);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Luminosidade");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Baixa");
    delay(2000);
  }

  //Temperatura aceitavel deve estar entre 1ºC e 10ºC
  
  //temperatura OK.
  if (1 < tempC && tempC < 10) {
    digitalWrite(ledVermelho,LOW);
    digitalWrite(ledVerde,HIGH);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Temperatura OK");
    lcd_1.setCursor(0, 1);
    lcd_1.print(tempC,1);
    delay(2000);
  }

  //temperatura Alta.
  if (tempC > 10) {
    digitalWrite(ledVermelho,HIGH);
    digitalWrite(ledVerde,LOW);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Temperatura Alta");
    lcd_1.setCursor(0, 1);
    lcd_1.print(tempC,1);
    delay(2000);
  }

  //temperatura Baixa.
  if (tempC < 1) {
    digitalWrite(ledVermelho,LOW);
    digitalWrite(ledVerde,HIGH);
   	lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Temperatura Baixa");
    lcd_1.setCursor(0, 1);
    lcd_1.print(tempC,1);
    delay(2000);
  }

    //Umidade aceitavel deve estar entre 55% e 65% (Valores reais são entre 85% e 95%)

  
  //Umidade ok.
  if (55 < (map(humiditysensorOutput, 0, 1023, 10, 70))&& (map(humiditysensorOutput, 0, 1023, 10, 70)) < 65) {
    digitalWrite(ledVermelho,LOW);
    digitalWrite(ledVerde,HIGH);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Umidade OK");
    lcd_1.setCursor(0, 1);
    lcd_1.print(map(humiditysensorOutput, 0, 1023, 10, 70));
    lcd_1.print("%");
    delay(2000);
  }

  //Umidade Baixa.
  if (map(humiditysensorOutput, 0, 1023, 10, 70) < 55) {
    digitalWrite(ledVermelho,HIGH);
    digitalWrite(ledVerde,LOW);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Umidade Baixa");
    lcd_1.setCursor(0, 1);
    lcd_1.print(map(humiditysensorOutput, 0, 1023, 10, 70));
    lcd_1.print("%");
    delay(2000);
  }

  //Umidade Alta.
  if (map(humiditysensorOutput, 0, 1023, 10, 70) >= 65) {
    digitalWrite(ledVermelho,HIGH);
    digitalWrite(ledVerde,LOW);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Umidade Alta");
    lcd_1.setCursor(0, 1);
    lcd_1.print(map(humiditysensorOutput, 0, 1023, 10, 70));
    lcd_1.print("%");
    delay(2000);
  }
}
