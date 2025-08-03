#include <Servo.h>
int Led_1 =2;
int Led_2 =4;
Servo myservo;
int gas = A0;
int buzz = 11;
float temp;
int tempPin= A1;
int trig_pin = 13;
int echo_pin = 12;


void setup() {
  Serial.begin(9600);
  myservo.attach(A2);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(Led_1, OUTPUT);
  pinMode(Led_2, OUTPUT);
  pinMode(gas, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(tempPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);


  duration = pulseIn(echo_pin, HIGH);
  distance = (duration/2) / 588.10;

  if(distance >35)
  {
    digitalWrite(Led_1, HIGH);
    digitalWrite(Led_2, LOW);
  }
 else
 {
    digitalWrite(Led_1, LOW);
    digitalWrite(Led_2, HIGH); 
 }
 Serial.print("jarak : ");
 Serial.print(distance);
 Serial.println("cm");
 delay(250);

 gas = analogRead(A0); 
 Serial.print(gas);
 if(gas == 1)
 {
  digitalWrite(Led_1, LOW);
  digitalWrite(Led_2, LOW);
  digitalWrite(11,  HIGH );
  }

  if(gas == 0)
{
  digitalWrite(Led_1, LOW);
  digitalWrite(Led_2, LOW);
  digitalWrite(11,  LOW );
  }

 temp = analogRead(tempPin);
 temp = temp*0.48828125;
 if(temp > 35)
 {
  myservo.write(90);
 }
 else{
  myservo.write(0);
 }
 Serial.print("Temperatur = ");
 Serial.print(temp);
 Serial.print(" C ");
 delay(100);
 
} 

  
