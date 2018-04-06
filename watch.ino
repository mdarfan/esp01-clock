/* ************************************
 Read the time from RTC and display on OLED
 with an ESP8266<br> sda=0, scl=2
* *************************************/

// Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 // alias for `#include "SSD1306Wire.h"`
#include "RTClib.h" //  Lady Ada
//Object declarations
RTC_DS1307 rtc;            // RTC
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2//0x3C being the usual address of the OLED

//Month and Day Arrays. Put in Language of your choice, omitt the 'day' part of the weekdays
char *maand[] =
{
  "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};
char *dagen[] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SAUTURDAY" };


// date and time variables
byte m = 0;    // contains the minutes, refreshed each loop
byte h = 0;    // contains the hours, refreshed each loop
byte s = 0;    // contains the seconds, refreshed each loop
byte mo = 0;   // contains the month, refreshes each loop
int j = 0;     // contains the year, refreshed each loop
byte d = 0;    // contains the day (1-31)
byte dag = 0;  // contains day of week (0-6)

void setup() {
  Serial.begin(115200);
  Wire.pins(0, 2);// yes, see text
  Wire.begin(0,2);// 0=sda, 2=scl
  rtc.begin();

// reading of time here only necessary if you want to use it in setup
  DateTime now = rtc.now();
  dag = now.dayOfTheWeek();
  j = now.year();
  mo = now.month();
  d = now.day();
  h = now.hour();
  m = now.minute();
  s = now.second();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime())
  {
    Serial.print(F("Current time"));
    Serial.println(now.unixtime());
    Serial.print(F("Compiled time"));
    Serial.println(compiled.unixtime());
    Serial.println("RTC is older than compile time! Updating");
    // following line sets the RTC to the date & time this sketch was compiled<br>   // uncomment to set the time
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Initialise the display.
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(10);
 display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("MOHAMMED ARFAN");
   display.println("BRAINHACKERZ");
   display.println("     BMS");
   display.println("COLLEGE OF ENGINEERING");
  display.display();
   delay(100);
  display.clearDisplay();

}


void loop() {
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //display.display();


  DateTime now = rtc.now();
  dag = now.dayOfTheWeek();
  j = now.year();
  mo = now.month();
  d = now.day();
  h = now.hour();
  m = now.minute();
  s = now.second();

  
  String t = String(h) + ":" + String(m) + ":" + String(s);
  String t2 = String(d) + ":"  + String(mo) + ":" + String(j);
  Serial.println(t);
  Serial.println(t2);
  Serial.println(maand[mo - 1]);
  
  String d = dagen[dag];
  d = d + "";//adding the word 'dag' (=day)  to the names of the days
  Serial.println(d);
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("**** B-AUTOMATE ****");
  display.setTextSize(2);
  display.print(" ");
  display.println(t);
   display.setTextSize(1);
  display.print(t2);
  display.setTextSize(1.5);
  display.print("   ");
  display.println(d);
  display.display();
 
  delay(10);
  display.clearDisplay();
}
