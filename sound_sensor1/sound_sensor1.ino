void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT); // LED (PWM)
}

void loop ()
{
  int a = analogRead(0);
  int d = digitalRead(2);
  if (a > 100)
  { 
    
    analogWrite(3, (a - 100) * 60);
    Serial.print(a);
    Serial.println((a - 100) * 30);
  }
  else
  {
     analogWrite(3, 0);
  }
  //Serial.println(d);
}

