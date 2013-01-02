#include <LiquidCrystal.h>

LiquidCrystal lcd(4,5,6,7,8,9);

const int pingPin  = 2;
const int echoPin  = 3;
const int warningPin = 10;
const int unwarningPin = 11;

void setup() {
  lcd.begin(16, 2);
  lcd.write("Starting Up...");
  delay(500);
  lcd.clear();
  
  pinMode(pingPin,      OUTPUT);
  pinMode(echoPin,      INPUT);
  pinMode(warningPin,   OUTPUT);
  pinMode(unwarningPin, OUTPUT);
  
  digitalWrite(pingPin, LOW);
  digitalWrite(warningPin, LOW);
  digitalWrite(unwarningPin, LOW);
}

// Ping (an 8 cycle sonic burst) is triggered by a short
// 10 microsecond HIGH pulse.  The return value is the
// time in microseconds for the round-trip.
long ping()
{
  // Short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void process_ping(long usec)
{
  long tenth_of_meters;
  long tenth_of_feet;
  
  tenth_of_meters = distance_in_tenth_of_meters(usec);
  tenth_of_feet   = distance_in_tenth_of_feet(usec);
  
  lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print(tenth_of_meters / 10);
  lcd.print(".");
  lcd.print(tenth_of_meters % 10);
  lcd.print(" meters");
  
  lcd.setCursor(0,1);
  
  lcd.print(tenth_of_feet / 10);
  lcd.print(".");
  lcd.print(tenth_of_feet % 10);
  lcd.print(" feet");
  
  if (tenth_of_feet <= 10)
  {
    digitalWrite(warningPin, HIGH);
    digitalWrite(unwarningPin, LOW);
    lcd.setCursor(15,0);
    lcd.write("*");
  }
  else
  {
    digitalWrite(warningPin, LOW);
    digitalWrite(unwarningPin, HIGH);
    lcd.setCursor(15,0);
    lcd.write(" ");
  }
}

void loop()
{  
  process_ping(ping());
  delay(60);             // 60ms delay
}

// Formula: uS / 58 = centimeters or uS / 148 =inch; or: the 
// range = high level time * velocity (340M/S) / 2; we suggest to use over 60ms 
// measurement cycle, in order to prevent trigger signal to the echo signal.

// The speed of sound is 340 m/s
// This is equivalent to 29.4 us/cm.
long distance_in_centimeters(long usec)
{
  return usec / 59;
}

long distance_in_tenth_of_meters(long usec)
{
  return usec / 588;
}

// The speed of sound is 340 m/s, 13385.8 in/s
// This is equivalent to 74.7 us/in
long distance_in_inches(long usec)
{
  return usec / 149;
}

// The speed of sound is 340 m/s, 13385.8 in/s
// This is equivalent to 89.6 us/in
long distance_in_tenth_of_feet(long usec)
{
  return usec / 170;
}


