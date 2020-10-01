/*
/ Every function in this file is to display tekst on the lcd
*/

#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initizialize display
void initDisplay()
{
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.display();
  lcd.printstr("Starting up.....");
}

// Update values on LCD screen
void updateStats(float temp, float hum)
{
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  lcd.setCursor(13, 0);
  lcd.print((int)temp);
  lcd.setCursor(15, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity:");

  lcd.setCursor(13, 1);
  lcd.print((int)hum);
  lcd.setCursor(15, 1);
  lcd.print("%");
  // delay(1000);
}

// Display search for wifi message
void searchMesg()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Searching for a");
  lcd.setCursor(0, 1);
  lcd.print("Wi-Fi Connection");
}

// Display reconnecting to wifi message
void reconnectMesg()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reconnecting");
  lcd.setCursor(0, 1);
  lcd.print("Wi-Fi Connection");
}

// Display error when wifi disconnected
void errorMesg()
{
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Wi-Fi");
  lcd.setCursor(2, 1);
  lcd.print("Disconnected");
  delay(2000);
  lcd.clear();
}

// Display error mesg when uploading data to website failed
void errorSiteMesg()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error uploading");
  lcd.setCursor(0, 1);
  lcd.print("to website");
  delay(10000);
  lcd.clear();
}

// Print a startup message with IP information on the lcd display
void startUpMesg(String ipAddress)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print(ipAddress);
  delay(3000);
  lcd.clear();
}

// Turn lcd display on or off
void powerDisplay(boolean choice)
{
  switch(choice)
  {
    case true:
      lcd.backlight();
      lcd.display();
      break;
    case false:
      lcd.noBacklight();
      lcd.noDisplay();
      break;
    default:
      break;
  }
}