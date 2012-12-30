
const int pingPin  = 2;
const int echoPin  = 3;
const int warningPin = 4;
const int unwarningPin = 5;

void setup() {
  //pinMode(powerPin, OUTPUT); // attach pin 2 to vcc
  //pinMode(5, OUTPUT); // attach pin 5 to GND
  pinMode(pingPin,      OUTPUT);
  pinMode(echoPin,      INPUT);
  pinMode(warningPin,   OUTPUT);
  pinMode(unwarningPin, OUTPUT);
  
  digitalWrite(pingPin, LOW);
  digitalWrite(warningPin, LOW);
  digitalWrite(unwarningPin, LOW);
  
  Serial.begin(9600);
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
  long centimeters;
  long inches;
  centimeters = distance_in_centimeters(usec);
  inches      = distance_in_inches(usec);
  if (inches < 24)
  {
    digitalWrite(warningPin, HIGH);
    digitalWrite(unwarningPin, LOW);
  }
  else
  {
    digitalWrite(warningPin, LOW);
    digitalWrite(unwarningPin, HIGH);
  }
  
  Serial.print(centimeters);
  Serial.print(" cm | ");
  Serial.print(inches);
  Serial.print(" in");
  Serial.println();
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

// The speed of sound is 340 m/s, 13385.8 in/s
// This is equivalent to 74.7 us/in
long distance_in_inches(long usec)
{
  return usec / 149;
}


