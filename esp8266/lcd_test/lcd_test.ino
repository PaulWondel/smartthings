/*
 * https://circuits4you.com
 * I2C LCD Interfacing with ESP8266 and ESP32
 * 
 */
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void updateStats()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  lcd.setCursor(12, 0);
  lcd.print("NAN");
  lcd.setCursor(15, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity:");

  lcd.setCursor(12, 1);
  lcd.print("NAN");
  lcd.setCursor(15, 1);
  lcd.print("%");
}

void setup()
{

  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  lcd.begin(16, 2);
  lcd.init();

  // Turn on the backlight.
  lcd.backlight();

  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(0, 0);

  // Print HELLO to the screen, starting at 5,0.
  lcd.print("Weather Station");

  // Move the cursor to the next line and print
  // WORLD.
  lcd.setCursor(6, 1);
  lcd.print("Home");

  delay(400);
}

void loop()
{
  updateStats();
  delay(2000);
}

// int show=0;

// void setup()
// {
//   lcd.init();                      // initialize the lcd
//   // Print a message to the LCD.
//   lcd.backlight();
//   lcd.setCursor(3,0);
//   lcd.print("Hello, world!");
//   lcd.setCursor(0,1);
//   lcd.print("circuits4you.com");
// }

// void loop()
// {
//   if (show == 0) {
//     lcd.setBacklight(255);
//     lcd.home(); lcd.clear();
//     lcd.print("Hello LCD");
//     lcd.setCursor(0,1);
//     lcd.print("circuits4You.com");
//     delay(1000);

//     lcd.setBacklight(0);
//     delay(400);
//     lcd.setBacklight(255);

//   } else if (show == 1) {
//     lcd.clear();
//     lcd.print("Cursor On");
//     lcd.cursor();

//   } else if (show == 2) {
//     lcd.clear();
//     lcd.print("Cursor Blink");
//     lcd.blink();

//   } else if (show == 3) {
//     lcd.clear();
//     lcd.print("Cursor OFF");
//     lcd.noBlink();
//     lcd.noCursor();

//   } else if (show == 4) {
//     lcd.clear();
//     lcd.print("Display Off");
//     lcd.noDisplay();

//   } else if (show == 5) {
//     lcd.clear();
//     lcd.print("Display On");
//     lcd.display();

//   } else if (show == 7) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("*** first line.");
//     lcd.setCursor(0, 1);
//     lcd.print("*** second line.");

//   } else if (show == 8) {
//     lcd.scrollDisplayLeft();
//   } else if (show == 9) {
//     lcd.scrollDisplayLeft();
//   } else if (show == 10) {
//     lcd.scrollDisplayLeft();
//   } else if (show == 11) {
//     lcd.scrollDisplayRight();
//   }

//   delay(2000);
//   show = (show + 1) % 12;
// }