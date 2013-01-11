#include "pitches.h"

const int pingPin  = 2;
const int echoPin  = 3;
const int tonePin  = 8;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

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
  long tenth_of_meters;
  long tenth_of_feet;
  
  //tenth_of_meters = distance_in_tenth_of_meters(usec);
  //tenth_of_feet   = distance_in_tenth_of_feet(usec);
  tone(tonePin, usec);
}

void loop()
{  
  process_ping(ping());
  delay(60);             // 60ms delay
}

// The speed of sound is 340 m/s, 13385.8 in/s
// This is equivalent to 74.7 us/in
long distance_in_inches(long usec)
{
  return usec / 149;
}
