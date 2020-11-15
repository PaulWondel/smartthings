/*
/ Every function in this file is to display tekst on the lcd
*/

#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Timer for displaying windspeed
unsigned long timerInterval_1 = 3000;
unsigned long timerInterval_2 = 5000;
unsigned long lastInterval_1 = 0;
unsigned long lastInterval_2 = 0;

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
void updateStats(float temp, float hum, float mps)
{
  unsigned long currentInterval = millis();

  if ((currentInterval - lastInterval_1 > timerInterval_1))
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
    lastInterval_1 = currentInterval;
  }

  if ((currentInterval - lastInterval_2 > timerInterval_2))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printstr("Wind Speed:");
    lcd.setCursor(0, 1);
    lcd.print(mps);
    lcd.setCursor(6, 1);
    lcd.printstr("m/s");    
    lastInterval_2 = currentInterval;
  }
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
  delay(5000);
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
  switch (choice)
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

// Turn display on and of if object is detected in front of weather station
void screen()
{
  long state = analogRead(ProxSensor);
  if (state > 100)
  {
    // Serial.println("Turn Display off");
    powerDisplay(false);
  }
  else
  {
    // Serial.println("Turn Display on");
    powerDisplay(true);
    delay(2000);
  }
}

// Turn display on and of if motion is detected near weather station
void PIRSensor()
{
  if (digitalRead(ProxSensor) == HIGH)
  {
    if (lockLow)
    {
      PIRValue = 1;
      lockLow = false;
      powerDisplay(true);
    }
    takeLowTime = true;
  }
  if (digitalRead(ProxSensor) == LOW)
  {
    if (takeLowTime)
    {
      lowIn = millis();
      takeLowTime = false;
    }
    if (!lockLow && millis() - lowIn > pause)
    {
      PIRValue = 0;
      lockLow = true;
      powerDisplay(false);
    }
  }
}