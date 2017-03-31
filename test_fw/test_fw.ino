// test_fw test firmware

// !!! Check your version !!!
// Uncomment your version  
//#define ArduinoLearningKitStarter_version_0.1
#define ArduinoLearningKitStarter_version_2.x

// You must install the toneAC library to your Arduino developer tools (e. g. Arduino IDE)
// https://bitbucket.org/teckel12/arduino-toneac/wiki/Home
#include <toneAC.h>

// You must install the DHT library to your Arduino developer tools 
// In Arduino IDE - open in Menu "Project" -> "Add library" -> "Library manager" ->
// -> write "DHT" to searching field
// -> and install the DHT library "DHT sensor library by Adafruit..." 
// (switch the version from the latest to 1.2.3)
// https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>

// Serial monitor speed (baud rate)
// You must set this baud rate in right corner in the serial monitor (in Arduino IDE)
#define SERIAL_BAUDRATE 57600

// Pinout define
#define L_RGB_R      5
#define L_RGB_G     11
#define L_RGB_B      6
  
#define L_R         12
#define L_Y         13
#define L_G          7
#define L_B          8

#define SW1          2
#define SW2          4
#define SW3          3

#define PIEZO_A      9
#define PIEZO_B     10

#define POT_RIGHT   A0
#define POT_LEFT    A1

#define PHOTO_SEN   A2

#define DHTPIN      A3
#define DHTTYPE  DHT11

#ifdef ArduinoLearningKitStarter_version_2.x
#define SW1          2
#define SW2          3
#define SW3          4

#define SERVOS_ON
#define S1           5
#define S2           6
#define S3           9
#define S4          10
#define S5          11
#endif

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // RGB led
  pinMode(L_RGB_R, OUTPUT);
  pinMode(L_RGB_G, OUTPUT);
  pinMode(L_RGB_B, OUTPUT);
  pinMode(L_R, OUTPUT);
  pinMode(L_Y, OUTPUT);
  pinMode(L_G, OUTPUT);
  pinMode(L_B, OUTPUT);
  pinMode(PIEZO_A, OUTPUT);
  pinMode(PIEZO_B, OUTPUT);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW1, INPUT_PULLUP);
  Serial.begin(SERIAL_BAUDRATE);
  dht.begin();
  Serial.print("Arduino learning kit starter hardware test firmware\n");  
}

unsigned long t_inc = 0;
unsigned long t_meas = 0;
uint8_t cnt = 0;
bool beeping = false;

void loop() {
//  digitalWrite(L_RGB_R, HIGH);
//  delay(500);
//  digitalWrite(L_RGB_R, LOW);
//  digitalWrite(L_RGB_G, HIGH);
//  delay(500);
//  digitalWrite(L_RGB_G, LOW);
//  digitalWrite(L_RGB_B, HIGH);
//  delay(500);
//  digitalWrite(L_RGB_B, LOW);
//  delay(500);
  if((millis() - t_inc) >= 500)
  {
    t_inc = millis();
    ++cnt;
    digitalWrite(L_R , cnt & 1 ? HIGH : LOW);
    digitalWrite(L_Y , cnt & 2 ? HIGH : LOW);
    digitalWrite(L_G , cnt & 4 ? HIGH : LOW);
    digitalWrite(L_B , cnt & 8 ? HIGH : LOW);
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
    Serial.print(analogRead(PHOTO_SEN));
    Serial.print("\tleft pot: ");
    Serial.print(analogRead(POT_LEFT));
    Serial.print("\tright pot: ");
    Serial.print(analogRead(POT_RIGHT));
    Serial.print("\n");
  }
  
  digitalWrite(L_RGB_R, digitalRead(SW3)   == HIGH ? LOW : HIGH);
  digitalWrite(L_RGB_G, digitalRead(SW2) == HIGH ? LOW : HIGH);
  //digitalWrite(L_RGB_G, !beeping ? LOW : HIGH);
  digitalWrite(L_RGB_B, digitalRead(SW1)  == HIGH ? LOW : HIGH);

  if(digitalRead(SW1) == LOW && digitalRead(SW3) == LOW)
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
