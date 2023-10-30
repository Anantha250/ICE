

int state = 0;
int enA = 10;
int in1 = 9;
int in2 = 8;
int enB = 6;
int in3 = 5;
int in4 = 4;
int ldr = 1;

int ldrPin = A5 ;
int countBlink = 0 ;
unsigned long lastBlink = 0 ;
bool chkturn = false ;

bool spceial = false;

int sensorsValue[5] = {0,0,0,0,0};
int lightSensor;
int count_lightSensor = 0;

int motorSpeed;
int baseSpeed = 90;
int rightSpeed,leftSpeed;
int maxSpeed = 120;
int sum_error = 0;
unsigned long previousMillis = 0;
int checkpoint = 0;
unsigned long currentMillis1;

// PID
float error = 0;
int pre_error = 0;
int Kp = 20;
float Kd = 10;
int Ki = 0.2;

#define S0_W 500
#define S1_W 500
#define S2_W 400
#define S3_W 400
#define S4_W 350

#define S0_B 350  
#define S1_B 350
#define S2_B 200
#define S3_B 250
#define S4_B 250

void Play(){
      sensorsValue[0]=analogRead(A0);
  sensorsValue[1]=analogRead(A1);
  sensorsValue[2]=analogRead(A2);
  sensorsValue[3]=analogRead(A3);
  sensorsValue[4]=analogRead(A4);

    if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])<S4_B){ 
      error = 4;  
    }else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]<S3_B) && (sensorsValue[4])<S4_B){
      error = 3;
    }else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]<S3_B) && (sensorsValue[4])>=S4_W ){
      error = 2;
    }else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]<S2_B) && (sensorsValue[3]<S3_B) && (sensorsValue[4])>=S4_W ){
      error = 1;
    }else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]<S2_B) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])>=S4_W){
      error = 0;
    }else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]<S1_B) && (sensorsValue[2]<S2_B) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])>=S4_W){
      error = -1;
    }else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]<S1_B) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])>=S4_W ){
      error = -2;
    }else if( (sensorsValue[0]<S0_B) && (sensorsValue[1]<S1_B) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]>=S3_W) && (sensorsValue[4]>=S4_W) ){
      error = -3;
    }else if( (sensorsValue[0]<S0_B) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]>=S3_W) && (sensorsValue[4]>=S4_W) ){
        error = -4;
    }
    else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])>=S4_W){
        error = pre_error;
    }
    
    else if( (sensorsValue[0]<S0_B) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]<S2_B) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])>=S4_W){
        forward(300);
        turnRight(800);
    }
    else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]<S2_B) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])<S4_B){
        forward(300);
        turnLeft(700);
    }
//    else if( (sensorsValue[0]<=S0_B) && (sensorsValue[1]<=S1_B) && (sensorsValue[2]<S2_B) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])>=S4_W){
//        forward(300);
//        turnRight(450);
//    }
   else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]>=S1_W) && (sensorsValue[2]>=S2_W) && (sensorsValue[3]<S3_B) && (sensorsValue[4])<S4_B){
        forward(300);
        turnLeft(500);
    }

      else if( (sensorsValue[0]>=S0_W) && (sensorsValue[1]<S1_B) && (sensorsValue[2]<S2_B) && (sensorsValue[3]<S3_B) && (sensorsValue[4])<S4_B){
        forward(250);
        turnLeft(600);
    }

     else if( (sensorsValue[0]<=S0_B) && (sensorsValue[1]<=S1_B) && (sensorsValue[2]<S2_B) && (sensorsValue[3]>=S3_W) && (sensorsValue[4])>=S4_W){
      forward(10);
        turnRight(40);
      }
      else if(state == 0){
  if( (sensorsValue[0]<S0_B) && (sensorsValue[1]<S1_B) && (sensorsValue[2]<S2_B) && (sensorsValue[3]<S3_B) && (sensorsValue[4])<S4_B){
    spceial = true;
    breakr;
    while(spceial == true){
    analogWrite(enA, 0); // Speed Control
analogWrite(enB, 0); // Speed Control
       while (analogRead(ldrPin) < 500) {
        delay(1200);
    lastBlink = millis();
    countBlink = 1;
  }

  while(millis() - lastBlink <= 5000 && countBlink == 1) {
    if (analogRead(ldrPin) < 500) {
      countBlink = 2 ;
      break;
    }
  }

  if (countBlink != 0 && chkturn == false) {
    if (countBlink == 1) {
      forward(200);
      turnLeft(450); 
      chkturn = true;
      countBlink = 0 ;
       spceial = false;
       state = 1;
    }
    else if (countBlink == 2) {
      forward(200);
      turnRight(500); 
      forward(950);
      turnLeft(380);
      chkturn = true;
      countBlink = 0 ;
      spceial = false;
      state = 2;
    }
  }
  
  if (countBlink == 0) {
    chkturn = false;
  }

  }
}
      }

else if(state == 1){
  if( ((sensorsValue[1]<S1_B) && (sensorsValue[2]<S2_B) && (sensorsValue[3]<S3_B))){
    spceial = true;
    breakr;
    while(spceial == true){
    analogWrite(enA, 0); // Speed Control
analogWrite(enB, 0); // Speed Control
       while (analogRead(ldrPin) < 500) {
        delay(1200);
    lastBlink = millis();
    countBlink = 1;
  }


  while(millis() - lastBlink <= 5000 && countBlink == 1) {
    if (analogRead(ldrPin) < 500) {
      countBlink = 2 ;
      break;
    }
  }


  if (countBlink != 0 && chkturn == false) {
    if (countBlink == 1) {
      forward(200);
      turnLeft(450); 
      chkturn = true;
      countBlink = 0 ;
       spceial = false;
       state = 3;
    }



    
    else if (countBlink == 2) {
      forward(200);
      turnRight(450);
      chkturn = true;
      countBlink = 0 ;
      spceial = false;
      state = 3;
    }
  }
  
  if (countBlink == 0) {
    chkturn = false;
  }

  }
  }
}


else if(state == 2){
  if( ((sensorsValue[4]<S4_B) && (sensorsValue[3]<S3_B) /*&& ((sensorsValue[0]<S0_B) || (sensorsValue[4]<S4_B))*/  )){
    spceial = true;
    breakr;
    while(spceial == true){
    analogWrite(enA, 0); // Speed Control
analogWrite(enB, 0); // Speed Control
       while (analogRead(ldrPin) < 500) {
        delay(1200);
    lastBlink = millis();
    countBlink = 1;
  }

  while(millis() - lastBlink <= 5000 && countBlink == 1) {
    if (analogRead(ldrPin) < 500) {
      countBlink = 2 ;
      break;
    }
  }

  if (countBlink != 0 && chkturn == false) {
    if (countBlink == 1) {
      forward(200);
      turnLeft(450); 
      chkturn = true;
      countBlink = 0 ;
       spceial = false;
       state++;
    }
    else if (countBlink == 2) {
      forward(200);
      turnRight(450); 
      chkturn = true;
      countBlink = 0 ;
      spceial = false;
      state++;
    }
  }
  
  if (countBlink == 0) {
    chkturn = false;
  }

  }
  }
}

else if(state == 3){
  if( (sensorsValue[0]<S0_B) && (sensorsValue[1]<S1_B) && (sensorsValue[2]<S2_B) && (sensorsValue[3]<S3_B) && (sensorsValue[4])<S4_B){
    spceial = true;
    breakr;
    while(spceial == true){
    analogWrite(enA, 0); // Speed Control
analogWrite(enB, 0); // Speed Control
       while (analogRead(ldrPin) < 500) {
        delay(1200);
    lastBlink = millis();
    countBlink = 1;
  }


  while(millis() - lastBlink <= 5000 && countBlink == 1) {
    if (analogRead(ldrPin) < 500) {
      countBlink = 2 ;
      break;
    }
  }

  if (countBlink != 0 && chkturn == false) {
    if (countBlink == 1) {
      forward(200);
      turnLeft(450); 
      chkturn = true;
      countBlink = 0 ;
       spceial = false;
       state++;
    }
    else if (countBlink == 2) {
      forward(200);
      turnRight(450); 
      chkturn = true;
      countBlink = 0 ;
      spceial = false;
      state++;
    }
  }
  
  if (countBlink == 0) {
    chkturn = false;
  }

  }
  }
}


        
   motorSpeed = Kp*error + Kd*(error - pre_error) + Ki*(sum_error);
   leftSpeed = baseSpeed + motorSpeed;
   rightSpeed = baseSpeed - motorSpeed;
   
   if(leftSpeed > maxSpeed) leftSpeed = maxSpeed;
   if(rightSpeed > maxSpeed) rightSpeed = maxSpeed;

   if(leftSpeed < -maxSpeed) leftSpeed = -maxSpeed;
   if(rightSpeed < -maxSpeed) rightSpeed = -maxSpeed;


 if(spceial == false){
   digitalWrite(in1,HIGH);
   digitalWrite(in2,LOW);
   digitalWrite(in3,HIGH);
   digitalWrite(in4,LOW);
   constrain(leftSpeed,0,255);
   constrain(rightSpeed,0,255);
   analogWrite(enA,leftSpeed);   //Left Motor Speed
   analogWrite(enB,rightSpeed);  //Right Motor Speed

 }
  pre_error = error;
   sum_error += error;

}

      





void setup()  
{
pinMode(enA, OUTPUT); //PWM Pin 1
 pinMode(enB, OUTPUT); //PWM Pin 2
pinMode(in1, OUTPUT); //Left Motor Pin 1
 pinMode(in2, OUTPUT); //Left Motor Pin 2
 pinMode(in3, OUTPUT); //Right Motor Pin 1
pinMode(in4, OUTPUT); //Right Motor Pin 2
 Serial.begin(9600); //Enable Serial Communications
}
void loop()
{
   Play();
}


void forward(int time)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  analogWrite(enA, 100); // Speed Control
//delay(2000);

digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);

analogWrite(enB, 140); // Speed Control

delay(time);
}

void breakr()
{
   digitalWrite(in2, LOW);
digitalWrite(in1, LOW);

analogWrite(enA, 0); // Speed Control
analogWrite(enB, 0); // Speed Control
digitalWrite(in4, LOW);
digitalWrite(in3, LOW);

delay(10000);
}

void turnLeft(int time)
{
  digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);

analogWrite(enA, 150); // Speed Control
//delay(2000);

digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);

analogWrite(enB, 75); // Speed Control
delay(time);
}

void turnRight(int time){
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);

analogWrite(enA, 100); // Speed Control
//delay(2000);

digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);

analogWrite(enB, 100); // Speed Control

delay(time);
}

void trLine(){
while(sensorsValue[3]>=S3_W){
  digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
delay(100);
  digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enA, 80);
analogWrite(enB, 80); 
}
}

void tlLine(){
  while(sensorsValue[1]>=S1_W){
   digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, 80); 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enB, 80); 
  }
}
