
#include <Servo.h>  //include servo.h library
Servo myservo;

int pos = 0;   
boolean fire = false;
int trigPin = 40;      // trig pin of HC-SR04
int echoPin = 41;     // Echo pin of HC-SR04
long duration, distance;

#define Left 9      // left sensor
#define Right 10    // right sensor
#define Forward 8   //front sensor

#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor
#define pump 6
#define buzzer 49

void setup()
{
delay(random(500,2000));   // delay for random time
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves

  
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(13);
  myservo.write(90);
}

void put_off_fire()
{
    delay (500);
    digitalWrite(buzzer, HIGH);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
   
   digitalWrite(pump, HIGH);
   delay(500);
   
    for (pos = 50; pos <= 150; pos += 1) {
    myservo.write(pos);
    delay(10); 
  }
  for (pos = 150; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
 
  digitalWrite(pump,LOW);
  digitalWrite(buzzer,LOW);
  myservo.write(90);
 
  fire=false;
}

void loop()
{
   myservo.write(90); //Sweep_Servo(); 

    if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1)
    {
   
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
   
    else if (digitalRead(Forward) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
    }
   
    else if (digitalRead(Left) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
   
    else if (digitalRead(Right) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
    
digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);
   
  if (distance < 19)
  {
  digitalWrite(buzzer, HIGH);   // turn the buzzer on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(buzzer, LOW);    // turn the buzzer off by making the voltage LOW
  delay(3);                       // wait for a second

    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
   
delay(300);//change this value to increase the distance

     while (fire == true)
     {
      put_off_fire();
     }
}
