int redPin = 15;    // Red RGB pin -> D5 // keep low on startup and reset
int greenPin = 12; // Green RGB pin -> D6
int bluePin = 14;  // Blue RGB pin -> D8

int PWM_Value_Red;
int PWM_Value_Green;
int PWM_Value_Blue;

// Initializes variables and pins in setup() in main file
void initRGB()
{
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  PWM_Value_Red = 0;
  PWM_Value_Green = 0;
  PWM_Value_Blue = 0;

  digitalWrite(redPin, LOW);
}

// Writes Color to the LED
void setColor()
{
  analogWrite(redPin, PWM_Value_Red);
  analogWrite(greenPin, PWM_Value_Green);
  analogWrite(bluePin, PWM_Value_Blue);
}

// RGB Colors for the moods
void hot()
{
  PWM_Value_Red = 255;
  PWM_Value_Green = 9;
  PWM_Value_Blue = 0;
}
void warm()
{
  PWM_Value_Red = 120;
  PWM_Value_Green = 19;
  PWM_Value_Blue = 0;
}
void cool()
{
  PWM_Value_Red = 0;
  PWM_Value_Green = 132;
  PWM_Value_Blue = 122;
}
void chilly()
{
  PWM_Value_Red = 255;
  PWM_Value_Green = 51;
  PWM_Value_Blue = 51;
}
void cold()
{
  PWM_Value_Red = 139;
  PWM_Value_Green = 0;
  PWM_Value_Blue = 139;
}
void freeze()
{
  PWM_Value_Red = 51;
  PWM_Value_Green = 0;
  PWM_Value_Blue = 255;
}
void off()
{
  PWM_Value_Red = 0;
  PWM_Value_Green = 0;
  PWM_Value_Blue = 0;
}

// Picks color for the RGB LED
void pickColor(int celsius)
{
  if(celsius <= 33 && celsius > 25)
  {
    hot();
    // Serial.println("hot");
  }
  else if(celsius <= 25 && celsius > 20)
  {
    warm();
    // Serial.println("warm");
  }
  else if(celsius <= 20 && celsius > 17)
  {
    cool();
    // Serial.println("cool");
  }
  else if(celsius <= 17 && celsius > 12)
  {
    chilly();
    // Serial.println("chilly");
  }
  else if(celsius <= 12 && celsius > 6)
  {
    cold();
    // Serial.println("cold");
  }
  else if(celsius <= 6 && celsius > -3)
  {
    freeze();
    // Serial.println("freeze");
  }
  else if(celsius > 33)
  {
    // Serial.println("Too hot to measure");
  }
  else if(celsius <= -3)
  {
    freeze();
    // Serial.println("Too cold to measure");
  }
  setColor();
}