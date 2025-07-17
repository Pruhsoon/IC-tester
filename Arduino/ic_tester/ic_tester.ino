//TFT
#include <Adafruit_GFX.h>    // Core graphics library
#include <TouchScreen.h> //Touch Screen Library
#include <MCUFRIEND_kbv.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // LCD RESET goes to Analog 4

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

MCUFRIEND_kbv tft;

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//TFT initialization

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button buttons[12];

//SD CARD
#include <SPI.h>
#include <SD.h>

#define chipSelect 10

bool sdCardAvailable = false;


//Pin Definitions
int pin14[14] = {30, 32, 34, 36, 38, 40, 42, 43, 41, 39, 37, 35, 33, 31};
int pin16[16] = {30, 32, 34, 36, 38, 40, 42, 44, 45, 43, 41, 39, 37, 35, 33, 31};

//Database File name
#define fname "database.txt"

//Structure Definiton for IC
typedef struct {
  String num;
  String name;
} IC;

//Function Headers
boolean testIC(String buffer, int pins);
void autoSearchResult(int mode, String number = "", String name = "", int count = 0);
void manualSearchResult(String number, String name, int status);

int screenStatus = 0, lastStatus = 0;
int *pin, pinCount = 0;

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);

  delay( 1000 ); // power-up safety delay


  //TFT setup
  tft.fillScreen(BLACK);
  tft.setCursor(25, 40);
  tft.setTextColor(GREEN);  tft.setTextSize(5);
  tft.println("IC TESTER");
  tft.setCursor(150, 130);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("By");
  tft.setCursor(45, 160);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Prasun");
  tft.setCursor(20, 220);
  tft.setTextColor(RED);  tft.setTextSize(2);
  tft.println("Touch anywhere to START");
  tft_init();


  //SD Card Setup
  SD_init();

}
void loop() {
 
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    //Serial.println("Z: " + String(p.z) + " X: " + String(p.x) + " Y: " + String(p.y));
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());

    //Swapping for Set Rotation 3
    p.x = p.x + p.y;
    p.y = p.x - p.y;
    p.x = p.x - p.y;

    delay(10);
    Serial.println("(" +  String(p.x) + " , " + String(p.y) + " , " + String(p.z) + ")");

    if (screenStatus == 0)
      screenStatus = 1;

    else if (screenStatus == 1)
    {
      if (buttons[0].contains(p.x, p.y))
      {
        Serial.println("AUTO MODE");
        screenStatus = 2;
      }
      else if (buttons[1].contains(p.x, p.y))
      {
        Serial.println("MANUAL MODE");
        screenStatus = 3;
      }
    }
    else if (screenStatus == 2)
    {
      if (buttons[0].contains(p.x, p.y))
      {
        Serial.println("14 Pin Selected");
        screenStatus = 21;
        pinCount = 14;
      }
      else if (buttons[1].contains(p.x, p.y))
      {
        Serial.println("16 Pin Selected");
        screenStatus = 21;
        pinCount = 16;
      }
    }
    else if (screenStatus == 3)
    {
      if (buttons[0].contains(p.x, p.y))
      {
        Serial.println("Entering Keypad Mode");
        screenStatus = 30;
      }
    }
  }

  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);

  if (screenStatus != lastStatus)
  {
    switch (screenStatus)
    {
      case 0: startScreen();
        break;
      case 1: modeScreen();
        break;
      case 2: autoScreen();
        break;
      case 21: autoSearch(pinCount);
        break;
      case 3: manualScreen();
        break;
      case 30: String number = getIC();
        manualSearch(number);
        break;
    }
    lastStatus = screenStatus;
  }
  delay(5);
}

void getTouch()
{
  boolean status = false;
  while (1)
  {
    digitalWrite(13, HIGH);
    TSPoint q = ts.getPoint();
    digitalWrite(13, LOW);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (q.z > MINPRESSURE && q.z < MAXPRESSURE)
    {
      status = true;
      break;
    }
    delay(10);
  }

  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
}

