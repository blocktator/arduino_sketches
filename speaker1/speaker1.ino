#include "pitches.h"

const int pingPin  = 2;
const int echoPin  = 3;
const int tonePin  = 8;

void setup() {
  pinMode(pingPin,      OUTPUT);
  pinMode(echoPin,      INPUT);
  pinMode(tonePin,      OUTPUT);
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
  tone(tonePin, usec);
}

void loop()
{  
  process_ping(ping());
  delay(30);             // 60ms delay
}

