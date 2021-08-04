 /*
 * 
 * All the resources for this project: https://www.hackster.io/Aritro
 * Modified by Aritro Mukherjee
 * 
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
 #include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() 
{
  pinMode(2,OUTPUT);
  lcd.noBacklight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(buttonPin, INPUT);
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin();
  lcd.noBacklight();
  lcd.setCursor(1,0);


}
void loop() 
{
  
  buttonState = digitalRead(buttonPin);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "CA 48 EF 81") //change here the UID of the card/cards that you want to give access
  {
    lcd.backlight();
    Serial.println("Authorized access");
    lcd.print("Hello Pedro");
    Serial.println();
    delay(3000);
    lcd.clear();
    lcd.print("GOLF CART: ON");
    digitalWrite(11,HIGH);

  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
  if (buttonState == HIGH) {
    Serial.println("Button Pressed");
    ;
  } else {
    // turn LED off:
    Serial.println("Button Rekeased");
  }
} 
