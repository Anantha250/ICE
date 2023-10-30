#include "ST7735_TEE.h"

TEE_ST7735 lcd(9, 10, 11, 12, 13);

const byte PIN_MOVE = 0;
const byte PIN_SHOOT_BUTTON = 4;     
const byte PIN_BOOT = 3;
const byte PIN_BOOT2 = 2;
const byte PIN_PAUSE = 5;

const int characterWidth = 20;
const int characterHeight = 20;
const int enemyWidth = 10;
const int enemyHeight = 10;
const int screenWidth = 130;
const int screenHeight = 128;
int characterSpeed = 3;
const int bulletWidth = 3;
const int bulletHeight = 3;
const int bulletSpeed = 5;
int enemySpeed = 4;
const int maxBullets = 5;  
const int maxEnemyHealth = 3; 


int characterColor = GREEN;       
int boostedCharacterColor = BLUE;  
bool isBoosted = false;     
bool isBoostedEnemy = false;   

int enemyColor = RED;          
int damagedEnemyColor = YELLOW;  
int bulletColor = BLUE;

int characterX;
int bulletX[maxBullets], bulletY[maxBullets];
bool isShooting[maxBullets];
int enemyX, enemyY;
int enemyHealth = maxEnemyHealth; 
bool isEnemyActive = false;
bool gameStarted = false;

void setup() {
  
  lcd.init(lcd.VERTICAL);
  lcd.fillScreen(BLACK);
  Serial.begin(9600);
  pinMode(PIN_MOVE, INPUT_PULLUP);  
  pinMode(PIN_SHOOT_BUTTON, INPUT_PULLUP);     
   pinMode(PIN_BOOT, INPUT_PULLUP);  
   pinMode(PIN_BOOT,HIGH);
    pinMode(PIN_BOOT2, INPUT_PULLUP);  
   pinMode(PIN_BOOT2,HIGH);
  characterX = (screenWidth - characterWidth) / 2;
  for (int i = 0; i < maxBullets; i++) {
    isShooting[i] = false; 
  }
  spawnEnemy(); 


}

void drawCharacter(int x, int color) {
  lcd.fillRect(x, screenHeight - characterHeight, characterWidth, characterHeight, color);
}

void eraseCharacter(int x) {
  lcd.fillRect(x, screenHeight - characterHeight, characterWidth, characterHeight, BLACK);
}

void drawBullet(int x, int y,int color) {
  lcd.fillRect(x, y, bulletWidth, bulletHeight, color);
}

void eraseBullet(int x, int y) {
  lcd.fillRect(x, y, bulletWidth, bulletHeight, BLACK);
}

void drawEnemy(int x, int y,int color) {
  lcd.fillRect(x, y, enemyWidth, enemyHeight, color);
}

void eraseEnemy(int x, int y) {
  lcd.fillRect(x, y, enemyWidth, enemyHeight, BLACK);
}

void spawnEnemy() {
   enemyX = random(130 - enemyWidth);
  if (enemyX < 0) {
    enemyX = 0;
  }
  enemyY = 0;
  enemyHealth = maxEnemyHealth;
  isEnemyActive = true;
}

void GameOver() {
  lcd.drawString(10, 75, "Game Over", RED, 2);
}

void loop() {
  
  eraseCharacter(characterX);
   if (!gameStarted) {
    lcd.drawString(5, 30, "WELCOME TO", RED, 2);
    lcd.drawString(5, 70, "!FUN GAME!", BLUE, 2);
    lcd.drawString(25, 120, "MOVE TO START", GREEN, 1);
     lcd.drawString(30, 150, "By Group 18", MAGENTA, 1);
    if (digitalRead(PIN_SHOOT_BUTTON) == LOW || analogRead(PIN_MOVE) <= 100 || analogRead(PIN_MOVE) >= 400) {

      gameStarted = true;
      lcd.fillScreen(BLACK);
      spawnEnemy();
    }
  } else {
    lcd.drawRect(0, 0, 125, 135, RED);
 if (digitalRead(PIN_SHOOT_BUTTON) == LOW) {

    for (int i = 0; i < maxBullets; i++) {
      if (!isShooting[i]) {
        isShooting[i] = true;
        bulletX[i] = characterX + (characterWidth / 2);
        bulletY[i] = screenHeight - characterHeight;
        break; 
      }
    }
  }

  

    if (digitalRead(PIN_BOOT) == LOW) {
    
    characterSpeed = 6; 
  } else {
    characterSpeed = 3; 
  }



   if (digitalRead(PIN_BOOT2) == LOW) {
     isBoostedEnemy = true;
     enemyHealth = 1;
      enemyColor = damagedEnemyColor;
      bulletColor = YELLOW;
   }
     else{
       isBoostedEnemy = false;
    enemyColor = RED;
    bulletColor = BLUE;
     }

if (digitalRead(PIN_BOOT) == LOW) {

    isBoosted = true; 
    characterColor = boostedCharacterColor; 
  } else {
    isBoosted = false; 
    characterColor = GREEN; 
  }
  
  for (int i = 0; i < maxBullets; i++) {
    if (isShooting[i]) {
      eraseBullet(bulletX[i], bulletY[i]);
      bulletY[i] -= bulletSpeed;
      drawBullet(bulletX[i], bulletY[i],bulletColor);

      if (bulletY[i] < -10) {
        isShooting[i] = false;
      }
    }
  }


  if (analogRead(PIN_MOVE) <= 100) {
    characterX -= characterSpeed; 
  } else if (analogRead(PIN_MOVE) >=400) {
    characterX += characterSpeed; 
  }

  characterX = constrain(characterX, 0, screenWidth - characterWidth);

    drawCharacter(characterX, characterColor); // Change color naa kub!

  if (isEnemyActive) {
            //Move enemy na bro!
    eraseEnemy(enemyX, enemyY);
    enemyY += enemySpeed;
    drawEnemy(enemyX, enemyY,enemyColor);

    for (int i = 0; i < maxBullets; i++) {
      if (isShooting[i] && bulletX[i] + bulletWidth >= enemyX && bulletX[i] <= enemyX + enemyWidth &&
          bulletY[i] <= enemyY + enemyHeight) {
        // Bullet hit the enemy
        eraseBullet(bulletX[i], bulletY[i]);
        isShooting[i] = false;

        enemyHealth--;

        if (enemyHealth <= 0) {
          //spawn new enemy naa!
          eraseEnemy(enemyX, enemyY);
          isEnemyActive = false;
          spawnEnemy();
        }
      }
    }

 if (characterX + characterWidth >= enemyX && characterX <= enemyX + enemyWidth &&
        screenHeight - characterHeight <= enemyY + enemyHeight) {
      lcd.fillScreen(BLACK);
      GameOver();
      delay(4000);
      lcd.fillScreen(BLACK);
      gameStarted = false;
    }

    if (enemyY > 125) {
      isEnemyActive = false;
       lcd.fillScreen(BLACK);
      GameOver();
      delay(4000);
      lcd.fillScreen(BLACK);
      spawnEnemy();
      gameStarted = false;
    }
  }

  delay(10);
  }
 
}
