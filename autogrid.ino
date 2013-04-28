#include <LiquidCrystal.h>


LiquidCrystal lcd(0,7,13,12,11,10,9);

char dir='N';
int td=1200;
int s0=500;
int s1=670;
int s2=631;
int s3=625;
int s4=438;
int pwm = 70;
int grid_x=4, grid_y=4;
int cx=0, cy=0;
int dx = 2, dy = 2;
int sharp = 0;
int a[5];
int sensorValue;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
    pinMode(13, OUTPUT);

}

int ReadSensor(uint8_t sensor, int x, int y)
{
  sensorValue = analogRead(sensor);
  lcd.setCursor(x,y);
  // set cursor to olumn 0, row 3
  lcd.print(sensorValue);
  return sensorValue;
  
}
void forward()
{
  digitalWrite(3, LOW); //Right
  digitalWrite(4, HIGH); //Right
  digitalWrite(1, LOW); //Left
  digitalWrite(2, HIGH); //Left
  analogWrite(5, pwm);
  analogWrite(6, pwm);
  //digitalWrite(5, HIGH); //En
  //digitalWrite(6, HIGH); //En
}
void backward()
{
  digitalWrite(4, LOW); //Right
  digitalWrite(3, HIGH); //Right
  digitalWrite(2, LOW); //Left
  digitalWrite(1, HIGH); //Left
  analogWrite(5, pwm);
  analogWrite(6, pwm);
 // digitalWrite(6, HIGH); //En
 // digitalWrite(5, HIGH); //En
}
void turn_left()
{
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);
  analogWrite(5, pwm);
  analogWrite(6, pwm);
  //digitalWrite(5, HIGH); //En
  //digitalWrite(6, HIGH); //En
}
void turn_right()
{
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  analogWrite(5, pwm);
  analogWrite(6, pwm);
 // digitalWrite(5, HIGH); //En
  //digitalWrite(6, HIGH); //En
}

void right_90()
{
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, LOW);
  analogWrite(5, pwm);
  analogWrite(6, pwm);
 // digitalWrite(5, HIGH); //En
  //digitalWrite(6, HIGH); //En
}  
void left_90()
{
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);
  analogWrite(5, pwm);
  analogWrite(6, pwm);
 // digitalWrite(5, HIGH); //En
 // digitalWrite(6, HIGH); //En
} 

void stopp()
{
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  analogWrite(5, pwm);
  analogWrite(6, pwm);
 // digitalWrite(5, HIGH); //En
  //digitalWrite(6, HIGH); //En
}

void uturn()
{
  grid_right();
  right_90();
  delay(td);
  //while(ReadSensor(A0, 0, 1)>=s0)
  //right_90();
  if(dir=='N')
  dir='E';
  else if(dir=='E')
  dir='S';
  else if(dir=='S')
  dir='W';
  else if(dir=='W')
  dir='N';
} 
void uturn_obs()
{
  right_90();
  delay(2000);
  while(ReadSensor(A0, 0, 1)>=s0)
  right_90();
   right_90();
  delay(2000);
  while(ReadSensor(A2, 0, 1)>=s2)
  right_90();
  if(dir=='N')
  dir='S';
  else if(dir=='E')
  dir='W';
  else if(dir=='S')
  dir='N';
  else if(dir=='W')
  dir='E';
} 

void line_follow()
{
  int exleft = ReadSensor(A0, 0, 0);
  int left = ReadSensor(A1, 4, 0);
  int middle = ReadSensor(A2, 8, 0);
  int right = ReadSensor(A3, 12, 0);
  
  int exright = ReadSensor(A4, 0, 1);

if(middle > s2 && left <s1 && right <s3)
{lcd.setCursor(4,1);
  lcd.print("Fo");
  forward();
  
}
else if(left > s1 && right < s2)
{lcd.setCursor(4,1);
 lcd.print("Le");
  turn_left();
}
else if(right > s3 && left < s1)
{lcd.setCursor(4,1);
  lcd.print("Ri");
  turn_right();
}
else if(exleft < s0)
{lcd.setCursor(4,1);
  lcd.print("eL");
  turn_left();
}
else if(exright<s4)
{
  lcd.setCursor(4,1);
  lcd.print("eR");
  turn_right();
}

}

int count = 0;

void grid_right()
{
 // forward();
  //delay(2000);
  right_90();
  delay(td);
  //stopp();
  //delay(1000);
  //return;
  while(ReadSensor(A1, 4, 0)<=s1 )
  right_90();
  //stopp();
  //delay(5000);
  if(dir=='N')
  dir='E';
  else if(dir=='E')
  dir='S';
  else if(dir=='S')
  dir='W';
  else if(dir=='W')
  dir='N';
  
 
}
void grid_left()
{
  
  left_90();
  delay(td);
  
  while(ReadSensor(A2, 8,0)<=s2)
  left_90();
  if(dir=='N')
  dir='W';
   else if(dir=='E')
  dir='N';
  else if(dir=='S')
  dir='E';
  else if(dir=='W')
  dir='S';
  
 
}


void grid_forward(int count)
{
  int temp=0; //make temp -1
int exleft = ReadSensor(A0, 0, 0);
  int exright = ReadSensor(A4, 0, 1);
if(exleft<s0 && exright <s4)
{
forward();
delay(800);
}
 
  while(1)
  {
  int exleft = ReadSensor(A0, 0, 0);
  int exright = ReadSensor(A4, 0, 1);
  if(exleft < s0 && exright < s4) //when either of the extreme sensors are on the line
    { 
       stopp();
       delay(500);
       temp++; //cant start bot at intersection
       
      
  if(temp==count)
  {
     stopp();
     return;
  }
else
{
  forward();
  delay(500);
}  
    }
  line_follow();
  }
}

void move_robot(int dx, int dy)
{
  if(dx-cx>0 && dy-cy==0)
  {
    if(dir=='N')
    {
      grid_right();
      grid_forward(dx-cx);
       }
    else if(dir=='E')
    {
      grid_forward(dx-cx);
    }
    else if(dir=='S')
    {
      grid_left();
      grid_forward(dx-cx);
    }
    else if(dir=='W')
    {
      uturn();
      grid_forward(dx-cx);
    }
    cx+=dx-cx;;  
    
 
  }
  
      
  if(dx-cx==0 && dy-cy>0)
  {
    
    if(dir=='N')
    {
      grid_forward(dy-cy);
    }
    else if(dir=='E')
    {
      grid_left();
      grid_forward(dy-cy);
    }
    else if(dir=='W')
    {
      grid_right();
      grid_forward(dy-cy);
    }
    else if(dir=='S')
    {
      uturn();
      grid_forward(dy-cy);
    }
    cy+=dy-cy;

 
  }
  if(dx-cx<0 && dy-cy==0)
  {
    
    if(dir=='N')
    {
      grid_left();
      grid_forward(cx-dx);
       }
    else if(dir=='S')
    {
      grid_right();
      grid_forward(cx-dx);
    }
    else if(dir=='W')
    {
      grid_forward(cx-dx);
    }
    else if(dir=='E')
    {
      uturn();
      grid_forward(cx-dx);
    }
    cx-=cx-dx;
    
 
  }
  if(dx-cx==0 && dy-cy<0)
  {
    
    if(dir=='W')
    {
      grid_left();
      grid_forward(cy-dy);
       }
    else if(dir=='E')
    {
      grid_right();
      grid_forward(cy-dy);
    }
    else if(dir=='S')
    {
      grid_forward(cy-dy);
    }
    else if(dir=='N')
    {
      uturn();
      grid_forward(cy-dy);
    }
   cy-=cy-dy;
  
 
  }
  return ;
}

void move_general(int gx, int gy)
{
  move_robot(gx, cy);
  move_robot(gx,gy);
  return;
}

int visited[5][5];
int obstacles[5][5];
int valid_coordinates(int x, int y)
{
  if(x>grid_x) return 0;
  if(y>grid_y) return 0;                                                                                                                                                                                                                                                                                          
  if(x<0) return 0;
  if(y<0) return 0;
  return 1;
}

int turn_detect(int dx, int dy)
{
   if(dx-cx>0 && dy-cy==0)
  {
    if(dir=='N')
    {
      grid_right();
      
      stopp();
      if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='E')
    {
       
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='S')
    {
      grid_left();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='W')
    {
      uturn();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    
 
  }
  
      
  if(dx-cx==0 && dy-cy>0)
  {
    
    if(dir=='N')
    {
       if(detect_obs() == 1) return 1; else return 0; 
    }
    else if(dir=='E')
    {
      grid_left();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='W')
    {
      grid_right();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='S')
    {
      uturn();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }

 
  }
  if(dx-cx<0 && dy-cy==0)
  {
    
    if(dir=='N')
    {
      //Move back
      backward();
      delay(2000);
      grid_left();
       stopp();
      if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='S')
    {
      grid_right();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='W')
    {
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='E')
    {
      uturn();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    
 
  }
  if(dx-cx==0 && dy-cy<0)
  {
    
    if(dir=='W')
    {
      grid_left();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='E')
    {
      //Move back
      backward();
      delay(2000);
      grid_right();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='S')
    {
       if(detect_obs() == 1) return 1; else return 0;
    }
    else if(dir=='N')
    {
      uturn();
       stopp();
       if(detect_obs() == 1) return 1; else return 0;
    }
  
 
  }
}
int detect_obs()
{
  
  sharp = ReadSensor(A5, 0, 0);
  if(sharp < 500)
  return 0;
  else 
  return 1; //obstacle
}
int vx=0, vy=0;

int Recurpath(int x, int y)
{
  if(valid_coordinates(x, y) == 0) return 0;
  //if(turn_detect(x, y) == 1){digitalWrite(13, HIGH); return 0;}
  if(visited[x][y] == 1) return 0;
  if(obstacles[x][y] == 1) return 0;
  if(x==dx && y==dy) 
  
  {
    move_general(x, y);
    return 1;
  }
  move_general(x, y);
  lcd.setCursor(11,1);
  lcd.print(x); 
  Serial.print(x);
  lcd.setCursor(12,1);
  lcd.print(y); 
  visited[x][y]=1; //vx++; vy++;
  if(Recurpath(x, y+1) == 1) 
  { 
  
    return 1;
  }
  if(Recurpath(x+1, y) == 1) {
   
    return 1;
    
  }
  if(Recurpath(x, y-1) == 1)
 {
   
   return 1;
 }
 if(Recurpath(x-1, y) == 1) 
  {
    return 1;
  }
  
  if(dir=='N')
  {
    visited[x][y-1] = 0;
    Recurpath(x, y-1);
  }
  else if(dir=='E')
  {
    visited[x-1][y] = 0;
    Recurpath(x-1, y);
  }
  else if(dir=='S')
  {
    visited[x][y+1] = 0;
    Recurpath(x, y+1);
  }
  else if(dir=='W')
  {
    visited[x+1][y] = 0;
    Recurpath(x+1, y);
  }
  
  return 0; 
}

void loop()
{
  obstacles[1][2] = 1;
  obstacles[3][2] = 1;
  obstacles[1][4] = 1;
  obstacles[3][4] = 1;

 
 int val = Recurpath(0,0);
 if(val == 1) 
 {
  while(1)
  {
    stopp();
     lcd.setCursor(10,1);
     lcd.print("End");
  }
   
 }
 

}
