int display[12][7] =
{
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
  {1, 0, 0, 0, 1, 1, 0}, 
  {0, 0, 0, 1, 1, 1, 0}  
}; 
 
int pinseg[7] = {5, 6, 7, 8, 9, 10, 11};
int dpPin = 12;
int buttonAPin = 3;
int buttonGPin = 2;
 
int currentNumber = 1;
int randomNum;
 
void setup()
{
  for (int i = 0; i < 7; i++)
    pinMode(pinseg[i], OUTPUT);
  
  pinMode(dpPin, OUTPUT);
  pinMode(buttonAPin, INPUT_PULLUP);
  pinMode(buttonGPin, INPUT_PULLUP);
  
  Serial.begin(9600);
  randomSeed(millis());
  randomNum = random(1, 10); 
  Serial.print("Random Number : ");
  Serial.println(randomNum);
}
 
void displaySegment(int segment[7]) 
{
  for (int i = 0; i < 7; i++) 
    digitalWrite(pinseg[i], !segment[i]);
  digitalWrite(dpPin, HIGH);
}
 
void loop() 
{ 
  displaySegment(display[currentNumber]);
    if (digitalRead(buttonAPin) == LOW) {
      currentNumber = (currentNumber + 1);
      if(currentNumber==10)
        currentNumber=1;
      delay(200);
    }
    if (digitalRead(buttonGPin) == LOW){
      if (currentNumber == randomNum) {
        displaySegment(display[0]);
        randomNum = random(1, 9); 
        currentNumber = 1;
        Serial.print("Random Number : ");
        Serial.println(randomNum);
      } 
      else if (currentNumber > randomNum)
        displaySegment(display[11]); 
      else 
        displaySegment(display[10]);
      delay(1000);  
    }
}
