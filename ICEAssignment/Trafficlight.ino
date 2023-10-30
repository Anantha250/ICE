#define BUTTON_NORTH 10 // North
#define LED_N_R 2
#define LED_N_Y 3
#define LED_N_G 4

#define BUTTON_EAST 12 // East
#define LED_E_R 7
#define LED_E_Y 8
#define LED_E_G 9

#define BUTTON_WALK 11 // Walk
#define LED_W_R 6
#define LED_W_G 5

#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
#define goW 4
#define off 5
#define on1 6
#define off1 7
#define on2 8
#define off2 9
#define on3 10
#define off3 11

struct State {
  unsigned long ST_Out; // 6-bit pattern to street output
  unsigned long Time; // delay in ms units
  unsigned long NextST[8];
}; 
typedef const struct State SType;
SType FSM[12] = {
  {B01111001, 3000, {goN, waitN, goN, waitN, waitN, waitN, waitN, waitN}}, // goN
  {B01110101, 500, {goE, goW, goE, goW, goE, goE, goE, goE}}, // waitN
  {B11001101, 3000, {goE, waitE, waitE, waitE, goE, waitE, waitE, waitE}}, // goE
  
  {B10101101, 500, {goW, goW, goN, goW, goW, goW, goN, goW}}, // waitE
  {B01101110, 3000, {goW, goW,off, off,off, off,off, off}}, // goW
  {B01101111, 300, {on1, on1,on1, on1,on1, on1,on1, on1}}, // off
  {B01101110, 300, {off1, off1,off1, off1,off1, off1,off1, off1}}, // on1
  {B01101111, 300, {on2, on2,on2, on2,on2, on2,on2, on2}}, // off1
  {B01101110, 300, {off2, off2,off2, off2,off2, off2,off2, off2}}, // on2
  {B01101111, 300, {on3, on3,on3, on3,on3, on3,on3, on3}}, // off2
  {B01101110, 300, {off3, off3,off3, off3,off3, off3,off3, off3}}, // on3
  {B01101111, 300, {goN, goN, goN, goN, goE, goE, goN, goN}} // off3
  };

unsigned long ST = 0; // index to the current state

void setup() {
  pinMode(LED_N_R, OUTPUT);
  pinMode(LED_N_Y, OUTPUT);
  pinMode(LED_N_G, OUTPUT);
  pinMode(BUTTON_NORTH, INPUT);
  pinMode(LED_E_R, OUTPUT);
  pinMode(LED_E_Y, OUTPUT);
  pinMode(LED_E_G, OUTPUT);
  pinMode(BUTTON_EAST, INPUT);
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_G, OUTPUT);
  pinMode(BUTTON_WALK, INPUT);
}
int input,input1, input2, input3;
void loop() {
  digitalWrite(LED_N_R, FSM[ST].ST_Out & B00010000);
  digitalWrite(LED_N_Y, FSM[ST].ST_Out & B00001000);
  digitalWrite(LED_N_G, FSM[ST].ST_Out & B00000100);
  digitalWrite(LED_E_R, FSM[ST].ST_Out & B10000000);
  digitalWrite(LED_E_Y, FSM[ST].ST_Out & B01000000);
  digitalWrite(LED_E_G, FSM[ST].ST_Out & B00100000);
  digitalWrite(LED_W_R, FSM[ST].ST_Out & B00000010);
  digitalWrite(LED_W_G, FSM[ST].ST_Out & B00000001);
  delay(FSM[ST].Time);
  input1 = digitalRead(BUTTON_NORTH); 
  input2 = digitalRead(BUTTON_EAST);
  input3 = digitalRead(BUTTON_WALK);
  input = input1*2 + input2*4 + input3;

  ST = FSM[ST].NextST[input];
}
