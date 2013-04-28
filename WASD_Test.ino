#define PINL1 3
#define PINL2 4
#define PINR1 1
#define PINR2 2
#define ENABLE1 5
#define ENABLE2 6

void setup()
{
  pinMode(ENABLE1,OUTPUT);
  pinMode(ENABLE2,OUTPUT);
  digitalWrite(ENABLE1, HIGH);
  digitalWrite(ENABLE2, HIGH);
  
  pinMode(PINL1,OUTPUT);
  pinMode(PINL2,OUTPUT);
  pinMode(PINR1,OUTPUT);
  pinMode(PINR2,OUTPUT);
  Serial.begin(9600);  
}  

void backward()
{
  digitalWrite(PINL1,HIGH);
  digitalWrite(PINL2,LOW);
  digitalWrite(PINR1,HIGH);
  digitalWrite(PINR2,LOW);
}
void forward()
{
  digitalWrite(PINL1,LOW);
  digitalWrite(PINL2,HIGH);
  digitalWrite(PINR1,LOW);
  digitalWrite(PINR2,HIGH);
}
void left()
{
  digitalWrite(PINL1,LOW);
  digitalWrite(PINL2,HIGH);
  digitalWrite(PINR1,HIGH);
  digitalWrite(PINR2,LOW);
}
void right()
{
  digitalWrite(PINL1,HIGH);
  digitalWrite(PINL2,LOW);
  digitalWrite(PINR1,LOW);
  digitalWrite(PINR2,HIGH);
}
void pause()
{
  digitalWrite(PINL1,LOW);
  digitalWrite(PINL2,LOW);
  digitalWrite(PINR1,LOW);
  digitalWrite(PINR2,LOW);
}

void loop()
{
  if(Serial.available())
  {
    int c = Serial.read();
    switch(c)
    {
      case 'w': forward(); Serial.println('w'); break;
      case 's': backward(); Serial.println('s');  break;
      case 'a': left(); Serial.println('a'); break;
      case 'd': right(); Serial.println('d'); break;
      case 'o': pause(); Serial.println('o'); break;
      default: Serial.println("Invalid"); break;
    } 
  }
}
