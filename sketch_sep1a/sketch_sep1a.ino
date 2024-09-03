#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6LlPqZzhg"
#define BLYNK_TEMPLATE_NAME "StepMotor"
#define BLYNK_AUTH_TOKEN "WOox8k0f7TyWCVPhmxmCrC94fAH0sHwZ"



#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

Adafruit_SSD1306 display(128,64,&Wire,-1);
volatile float Step = 0 , StepVar = 0 ;
int check;
char arr[10];
char ssid[] = "Hoang Phuc";
char pass[] = "0906382269";
volatile int save[3] = {0,0,0};

#define LED_PIN1 D5
#define LED_PIN2 D6
#define LED_PIN3 D7
#define LED_PIN4 D8


void tien ();
void lui  ();



BLYNK_WRITE(V1) { // This function is called every time Virtual Pin 1 state changes in Blynk app
  if(param.asInt())
  {
    Step = (Step + 1.6);
    tien();    
  }
  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  if(Step > 358.4)
  {
    Step = 0;
  }
  sprintf(arr , "STEP: %0.1f",Step);
  display.println(arr);
  display.display();
}
BLYNK_WRITE(V2) { // This function is called every time Virtual Pin 1 state changes in Blynk app
  int pinValue = param.asInt(); // Get the value sent from Blynk app
  digitalWrite(LED_PIN2, pinValue); // Turn LED on or off based on the value
  display.clearDisplay();
  if(param.asInt())
  {
    save[check] = Step / 1.6;
    check++;
  }
  Serial.println("NHAN DUOC");
  Serial.println(save[0]);
  Serial.println(save[1]);
  Serial.println(save[2]);
}
BLYNK_WRITE(V3) { // This function is called every time Virtual Pin 1 state changes in Blynk app
  int pinValue = param.asInt(); // Get the value sent from Blynk app
  digitalWrite(LED_PIN3, pinValue); // Turn LED on or off based on the value
}
BLYNK_WRITE(V4) { // This function is called every time Virtual Pin 1 state changes in Blynk app
  if(param.asInt())
  {
    Step = (Step - 1.6);
    lui();
  }
  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  if(Step <= 0)
  {
    Step = 358;
  }
  sprintf(arr , "STEP: %0.1f",Step);
  display.println(arr);
  display.display();
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    for(;;);

  }
  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  sprintf(arr , "STEP: %0.1f",Step);
  display.println(arr);
  display.display();
}

void loop()
{
  Blynk.run();
  if(save[2] != 0)
  {
    display.setFont(&FreeSerif9pt7b);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    sprintf(arr , "STEP: %0.1f",Step);
    display.println(arr);
    display.display();
    display.setFont(&FreeSerif9pt7b);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,40);
    display.println("Memory Full ");
    display.display();
  }
  else
  {
    display.setFont(&FreeSerif9pt7b);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    sprintf(arr , "STEP: %0.1f",Step);
    display.println(arr);
    display.display();
    display.setFont(&FreeSerif9pt7b);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,40);
    display.println("Memory Empty");
    display.display();
  }
}


void tien()
{
  digitalWrite(LED_PIN4  , HIGH);
  digitalWrite(LED_PIN1 , HIGH);
  delay(2);
  digitalWrite(LED_PIN1 , LOW);
  delay(2);
}


void lui()
{
  digitalWrite(LED_PIN4  , LOW);
  digitalWrite(LED_PIN1 , HIGH);
  delay(2);
  digitalWrite(LED_PIN1 , LOW);
  delay(2);
}