int right1 = 6;                //motor
int right2 = 7;
int left1 = 4;
int left2 = 5;
int rightSpeed = 10;           //PWM
int leftSpeed = 9;


int trigPin = 12;            //ultrasonic sensor
int echoPin = 13;

int buzz = 3;                //buzzer

void setup()
{
  pinMode(right1, OUTPUT);   //motor
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(rightSpeed, OUTPUT);
  pinMode(leftSpeed, OUTPUT);
  
  Serial.begin(9600);        //sensor
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);
  
  pinMode(buzz, OUTPUT);    //buzzer

  
}

long duration, distance;
int flag = 0;

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 58);
  
  if(flag==0)
  {
    analogWrite(rightSpeed, 255); //move forward at full speed
    analogWrite(leftSpeed, 255);
    digitalWrite(right1, LOW);
    digitalWrite(right2, HIGH);
    digitalWrite(left1, LOW);
    digitalWrite(left2, HIGH);
  }
  
  if(distance>70)
  {
    flag = 0;
    Serial.println(">70 cm");
    analogWrite(rightSpeed, 255); //move forward at full speed
    analogWrite(leftSpeed, 255);
    digitalWrite(right1, LOW);
    digitalWrite(right2, HIGH);
    digitalWrite(left1, LOW);
    digitalWrite(left2, HIGH);
  }

  else
    if(distance<=70 && distance>15)
    {
      flag = 1;
      
      analogWrite(rightSpeed, distance*3); //decrease motor speed
      analogWrite(leftSpeed, distance*3);
      digitalWrite(right1, LOW);
      digitalWrite(right2, HIGH);
      digitalWrite(left1, LOW);
      digitalWrite(left2, HIGH);
      
      digitalWrite(buzz, HIGH); 
      delay(distance*5);
      digitalWrite(buzz, LOW);
      delay(distance*5);
      
      Serial.print(distance);       //display distance
      Serial.println(" cm");
    }

    else
      if(distance<=15)
      {
        flag = 1;
        analogWrite(rightSpeed, 0);
        analogWrite(leftSpeed, 0);
        digitalWrite(right1, LOW);
        digitalWrite(right2, LOW);
        digitalWrite(left1, LOW);
        digitalWrite(left2, LOW);

        digitalWrite(buzz, HIGH); 
        delay(100);
        digitalWrite(buzz, LOW);
        delay(100);
      } 

}

