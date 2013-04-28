/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(0, INPUT);
}
void forward(){
  digitalWrite(1, 1);  
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  analogWrite(5, 90);
  analogWrite(6, 90);
  //digitalWrite(5, 1);
  //digitalWrite(6, 1); 
}
void right(){
  digitalWrite(1, 1);   //right motor
  digitalWrite(2, 0); //right motor
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  analogWrite(5, 90);
  analogWrite(6, 90);
 // digitalWrite(5, 1);
 // digitalWrite(6, 1); 
}
void left(){
  digitalWrite(1, 0);  
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  analogWrite(5, 90);
  analogWrite(6, 90);
  //digitalWrite(5, 1);
  //digitalWrite(6, 1); 
}
void stopp(){
  digitalWrite(1, 0);  
  digitalWrite(2, 0);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  analogWrite(5, 90);
  analogWrite(6, 90);
  //digitalWrite(5, 1);
  //digitalWrite(6, 1); 
}
int stopval = 0;
void loop() {
  int sensorValue = analogRead(A0);
  stopval = digitalRead(0);
  Serial.println(stopval);
  //Serial.println(sensorValue);
  
  delay(1);        // delay in between reads for stability
  if(stopval == 1)
  {
	if (sensorValue>=550)
	{
        right();
       // Serial.println("Right");
	}
	else if(sensorValue<=410)
        {
	left();
       // Serial.println("Left");
        }
	else 
        {
	forward();
       // Serial.println("Forward");
        }
  }
  else if(stopval == 0)
  {
    while(1)
    {
      stopp();
    }
  }
}
