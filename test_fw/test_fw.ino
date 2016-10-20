#include <toneAC.h>
#include <DHT.h>

#define LED_RGB_R      5
#define LED_RGB_G     11
#define LED_RGB_B      6
  
#define LED_RED       12
#define LED_YELLOW    13
#define LED_GREEN      7
#define LED_BLUE       8

#define BUTTON_LEFT    3
#define BUTTON_MIDDLE  4
#define BUTTON_RIGHT   2

#define PIN_PIEZO_A    9
#define PIN_PIEZO_B   10

#define POT_RIGHT     A0
#define POT_LEFT      A1

#define LIGHT_SENSOR  A2

#define DHTPIN     A3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // RGB led
  pinMode(LED_RGB_R, OUTPUT);
  pinMode(LED_RGB_G, OUTPUT);
  pinMode(LED_RGB_B, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(PIN_PIEZO_A, OUTPUT);
  pinMode(PIN_PIEZO_B, OUTPUT);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_MIDDLE, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  Serial.begin(57600);
  dht.begin();
  Serial.print("Arduino learning kit starter hardware test firmware\n");
}

unsigned long t_inc = 0;
unsigned long t_meas = 0;
uint8_t cnt = 0;
bool beeping = false;

void loop() {
//  digitalWrite(LED_RGB_R, HIGH);
//  delay(500);
//  digitalWrite(LED_RGB_R, LOW);
//  digitalWrite(LED_RGB_G, HIGH);
//  delay(500);
//  digitalWrite(LED_RGB_G, LOW);
//  digitalWrite(LED_RGB_B, HIGH);
//  delay(500);
//  digitalWrite(LED_RGB_B, LOW);
//  delay(500);
  if((millis() - t_inc) >= 500)
  {
    t_inc = millis();
    ++cnt;
    digitalWrite(LED_RED   , cnt & 1 ? HIGH : LOW);
    digitalWrite(LED_YELLOW, cnt & 2 ? HIGH : LOW);
    digitalWrite(LED_GREEN , cnt & 4 ? HIGH : LOW);
    digitalWrite(LED_BLUE  , cnt & 8 ? HIGH : LOW);
  }

  if((millis() - t_meas) >= 500)
  {
    t_meas = millis();
    float t = dht.readTemperature();
    if(isnan(t))
    {
      Serial.println("TEMPERATURE ERROR");
    }
    else
    {
      Serial.print("Temperature: ");
      Serial.print(int(t));
    }
    Serial.print("\tlight: ");
    Serial.print(analogRead(LIGHT_SENSOR));
    Serial.print("\tleft pot: ");
    Serial.print(analogRead(POT_LEFT));
    Serial.print("\tright pot: ");
    Serial.print(analogRead(POT_RIGHT));
    Serial.print("\n");
  }
  
  digitalWrite(LED_RGB_R, digitalRead(BUTTON_LEFT)   == HIGH ? LOW : HIGH);
  digitalWrite(LED_RGB_G, digitalRead(BUTTON_MIDDLE) == HIGH ? LOW : HIGH);
  //digitalWrite(LED_RGB_G, !beeping ? LOW : HIGH);
  digitalWrite(LED_RGB_B, digitalRead(BUTTON_RIGHT)  == HIGH ? LOW : HIGH);

  if(digitalRead(BUTTON_RIGHT) == LOW && digitalRead(BUTTON_LEFT) == LOW)
  {
    if(!beeping)
    {
      beeping = true;
      toneAC(440);
    }
  }
  else
  {
    if(beeping)
    {
      beeping = false;
      toneAC(0);
    }
  }

  if(Serial.available())
  {
    char c = Serial.read();
    switch(c)
    {
      case '\r':
        Serial.write('\n');
        break;
      default:
        Serial.write(c + 1);
        Serial.write('\n');
        break;
    }
  }
}
