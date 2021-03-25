#include <FastLED.h>
#include <NintendoExtensionCtrl.h>
#include <string.h>
#include "letters.h"
#include "blocks.cpp"
#include "breakOutBlock.cpp"
#include "palettes.h"
#include "faces.h"

Nunchuk nchuk;

#define LED_PIN  D4
#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define BRIGHTNESS 150

// Params for width and height
const int width = 23;
const int height = 23;
#define NUM_LEDS (width * height)

CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);
//==============================================================================================================
//--------------------------------------------------BOARD SETUP-------------------------------------------------

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );

  Serial.begin(115200);
  nchuk.begin();

  while (!nchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }
}

//==============================================================================================================
//------------------------------------------------FUNCTIONS/METHODS---------------------------------------------

// input x and y coordinates, returns the led integer
int XY(int x, int y){
  if (y%2==0)
    return (y * 23) + x;
  else
    return ((y+1) * 23) - (x+1);
}

//draws the array shape or letter, given the x and y shift from 0,0, and the size of the array
void drawArray(int arr[][2], int x, int y, int arrSize, int color){
  int saturation = 255;
  if(color==-1) saturation=0;
  for (int i=0; i<arrSize; i++){
    if(arr[i][0]+x>-1 and arr[i][0]+x<23 and arr[i][1]+y>-1 and arr[i][1]+y<23)
      leds[XY(arr[i][0]+x,arr[i][1]+y)] = CHSV(color, saturation, 255);
  }
}

// scrolls array from right to left, given the x and y shift, size of array, and maximum width of array shape
void scrollArray(int arr[][2], int x, int y, int arrSize, int width, int color){
 
  for (int i=0; i<arrSize; i++)
    arr[i][0]+=22;
  for (int i=0; i<23+width; i++){
    clear();
    drawArray(arr, -i, y, arrSize, color);
    FastLED.show();
    delay(120);
  }
}

//draws both digits seperately, doesnt go over 99
void drawScore(int score){
  if (score>999){
//    scrollSentence("score is more than 1000", -1);
  }
  else{
    int d1 = (int)(score/100);
    int d2 = (int)((score/10) % 10);
    int d3 = score%10;
    int s = 0;
    if(d1!=0){
      if(d1==1) scr(num1,3); if(d1==2) scr(num2,3); if(d1==3) scr(num3,3); if(d1==4) scr(num4,3);
      if(d1==5) scr(num5,3); if(d1==6) scr(num6,3); if(d1==7) scr(num7,3); if(d1==8) scr(num8,3); if(d1==9) scr(num9,3);
      s = 3;
    }
    if(d2==0) scr(num0,6+s); if(d2==1) scr(num1,6+s); if(d2==2) scr(num2,6+s); if(d2==3) scr(num3,6+s); if(d2==4) scr(num4,6+s);
    if(d2==5) scr(num5,6+s); if(d2==6) scr(num6,6+s); if(d2==7) scr(num7,6+s); if(d2==8) scr(num8,6+s); if(d2==9) scr(num9,6+s);
   
    if(d3==0) scr(num0,12+s); if(d3==1) scr(num1,12+s); if(d3==2) scr(num2,12+s); if(d3==3) scr(num3,12+s); if(d3==4) scr(num4,12+s);
    if(d3==5) scr(num5,12+s); if(d3==6) scr(num6,12+s); if(d3==7) scr(num7,12+s); if(d3==8) scr(num8,12+s); if(d3==9) scr(num9,12+s);
  }
}
void scr(int arr[][2], int x){
  drawArray(arr,x,8,20,-1);
}

//clears and turns all lights off
void clear(){
  for(int i = 0; i < 529; i++)
    leds[i] = 0;
}
void fill(int color){
  for(int i = 0; i < 529; i++)
    leds[i] = CHSV(color, 255, 255);
}

//==============================================================================================================
//----------------------------------------------------MAIN LOOP-------------------------------------------------
int screenNum = 800;
int msIdle = millis();
int idleTime=15000;
boolean palettePlay = false;
void loop()
{
  boolean success = nchuk.update();  // Get new data from the controller

  if (!success)
  {
    Serial.println("Controller disconnected!");
    delay(1000);
  }
 
  else
  {
    // all nunchuk inputs
    int joyY = nchuk.joyY();
    int joyX = nchuk.joyX();

    boolean zButton = nchuk.buttonZ();
    if (zButton){
      delay(80);
      msIdle=millis();
    }
    boolean cButton = nchuk.buttonC();
    if (cButton){
      delay(80);
      msIdle=millis();
      face();
    }
   
    if (joyX>135){
      screenNum++;
      delay(80);
      msIdle=millis();
    }
    if (joyX<120){
      screenNum--;
      delay(80);
      msIdle=millis();
    }

    int currScreen=screenNum%8;
    if(currScreen == 0) snakeScreen();
    if(currScreen == 1) tetrisScreen();
    if(currScreen == 2) breakoutScreen();
    if(currScreen == 3) birdScreen();
    if(currScreen == 4) connect4Screen();
    if(currScreen == 5) rainbowScreen();
    if(currScreen == 6) fireFrame();
    if(currScreen == 7) vortexFrame();

    //select screen
    if (zButton){
      if(currScreen == 0) snake();
      if(currScreen == 1) tetris();
      if(currScreen == 2) breakout();
      if(currScreen == 3) flappyBird();
      if(currScreen == 4) connect4();
      if(currScreen == 5) rainbow();
    }

   
    msIdle=millis();
    FastLED.show();

    if (palettePlay)
      idleTime=3000;
     
    if (millis()-msIdle>idleTime) idleScreen();
   
    if(currScreen == 6){
      delay(30);
      msIdle=millis();
    }
    if(currScreen == 7){
      delay(0);
      msIdle=millis();
    }
    else
      delay(160);
  }
}

//==============================================================================================================
//-------------------------------------------------GAME SCREENS-------------------------------------------------


void snakeScreen(){
  fill(100);
  int S[][2]={14,7, 13,6, 12,6, 11,6, 10,6, 9,6, 8,7, 8,8, 8,9, 8,10, 9,11, 10,11, 11,11,
              12,11, 13,11, 14,12, 14,13, 14,14, 14,15, 13,16, 12,16, 11,16, 10,16, 9,16, 8,15};
  for(int i = 0; i < (sizeof S)/8; i++){
    leds[XY(S[i][0],S[i][1])] = CRGB(255, 255, 255);
  }
}

void tetrisScreen(){
  fill(55);
  for(int i = 7; i < 16; i++){
    leds[XY(i,6)] = CRGB(255, 255, 255);
  }
  for(int i = 6; i < 17; i++){
    leds[XY(11,i)] = CRGB(255, 255, 255);
  }
}

void breakoutScreen(){
  fill(240);
  int P[][2] = {9,6,9,7,9,8,9,9,9,10,9,11,9,12,9,13,9,14,9,15,9,16,
                  10,6,11,6,12,6,13,7,13,8,13,9,12,10,11,10,10,10};
  //for(int i = 0; i < (sizeof P)/8; i++){
  //  leds[XY(P[i][0],P[i][1])] = CRGB(255, 255, 255);
  //}
  drawArray(B,6,8,20,-1);
  drawArray(O,12,8,20,-1);
}

void birdScreen(){
  fill(20);
  int B[28][2] = {{9,6},{9,7},{9,8},{9,9},{9,10},{9,11},{9,12},{9,13},{9,14},{9,15},{9,16},
                  {10,6},{11,6},{12,6},{13,7},{13,8},{13,9},{13,10},{12,11},{11,11},{10,11},
                  {13,12},{13,13},{13,14},{13,15},{12,16},{11,16},{10,16}};
  for(int i = 0; i < 28; i++){
    leds[XY(B[i][0],B[i][1])] = CRGB(255, 255, 255);
  }
}

void rainbowScreen(){
  for(int x = 0; x < 23; x++){
    for(int y = 0; y < 23; y++){
      leds[XY(x,y)] = CHSV(x*y*255/529, 255, 255);
    }
  }
}

void connect4Screen(){
  fill(140);
  drawArray(C,6,8,20,-1);
  drawArray(num4,12,8,20,-1);
}

void gameOverScreen(int score){
  fill(0);
  drawScore(score);
}

//==============================================================================================================
//-------------------------------------------------SNAKE GAME---------------------------------------------------
int snakeWall[60][2];
int snakeX[529];
int snakeY[529];
int snakeLength;
int appleX;
int appleY;
int snakeDirection; //snake direction has intger values of degrees in circle
boolean snakeGameOver;
int snakeDelay;
int snakeColor;
void snake()
{  
  snakeX[0]=5;
  snakeY[0]=5;
  snakeLength=5;
  appleX=15;
  appleY=15;
  snakeDirection=0;
  snakeGameOver=false;
  snakeDelay=100;
  snakeColor=100;
  srand(millis());
  while (not snakeGameOver){
   
    nchuk.update();
    int joyX = nchuk.joyX();
    int joyY = nchuk.joyY();
    boolean cButton = nchuk.buttonC();
   
    checkSnakeDirection(joyX, joyY);
   
    moveSnake();
    checkSnake();
    if (snakeGameOver or cButton){
      gameOverScreen(snakeLength-5);
      FastLED.show();
      delay(2000);
      msIdle=millis();
      break;
    }

    clear();
    //draw apple
    leds[XY(appleX,appleY)] = CHSV(255,255,255);
    //draw snake
    for (int i=0; i<snakeLength; i++){
      leds[XY(snakeX[i],snakeY[i])] = CHSV(snakeColor,255,255);
    }
    leds[XY(snakeX[0],snakeY[0])] = CRGB(255,255,255);
    //drawArray(snakeWall,0,0,60,-1);
    FastLED.show();
   
    if (snakeLength<8){
      snakeDelay=100;
      snakeColor=100;
    }
    else if (snakeLength<11){
      snakeDelay=90;
      snakeColor=120;
    }
    else if (snakeLength<14){
      snakeDelay=80;
      snakeColor=140;
    }
    else if (snakeLength<17){
      snakeDelay=70;
      snakeColor=160;
    }
    else if (snakeLength<20){
      snakeDelay=60;
      snakeColor=180;
    }
    else{
      snakeDelay=50;
      snakeColor+=20;
    }
    delay(snakeDelay);
  }
}

void checkSnakeDirection(int joyX, int joyY){
  if (joyX<110 and snakeDirection!=0)
    snakeDirection = 180;
  else if (joyX>145 and snakeDirection!=180)
    snakeDirection = 0;
  else if (joyY>145 and snakeDirection!=90)
    snakeDirection = 270;
  else if (joyY<110 and snakeDirection!=270)
    snakeDirection = 90;
}

void moveSnake(){

  //assign new snake segments
  for (int i=snakeLength; i>0; i--){
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  //move snake
  if (snakeDirection==180)
    snakeX[0]--;
  if (snakeDirection==0)
    snakeX[0]++;
  if (snakeDirection==90)
    snakeY[0]++;
  if (snakeDirection==270)
    snakeY[0]--;
}

void checkSnake(){
  // eats apple
  if(snakeX[0]==appleX and snakeY[0]==appleY){
    snakeLength++;

    boolean appleRespawn=true;
    while (appleRespawn){
      appleX = rand()%23;
      appleY = rand()%23;
      Serial.printf("%d, %d\n", appleX, appleY);
      appleRespawn=false;
      for (int i=0; i<snakeLength; i++){
        if (snakeX[i] == appleX and snakeY[i] == appleY)
        {
          Serial.println("APPLE IN SNAKE");
          appleRespawn=true;
        }
       
      }
    }
  }
//  //walls
//  for (int i=0; i<60; i++){
//    if (snakeWall[i][0]==snakeX[0] and snakeWall[i][1]==snakeY[0])
//      snakeGameOver=true;
//  }
  //teleport
  if (snakeX[0]<0)
    snakeX[0]=22;
  if (snakeY[0]<0)
    snakeY[0]=22;
  if (snakeX[0]>22)
    snakeX[0]=0;
  if (snakeY[0]>22)
    snakeY[0]=0;
  // bite itself
  for (int i=1; i<snakeLength; i++){
    if (snakeX[i] == snakeX[0] and snakeY[i] == snakeY[0]) snakeGameOver=true;
  }
}

//==============================================================================================================
//-------------------------------------------------TETRIS GAME--------------------------------------------------
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
const int gameWidthLeft = 9;
const int gameWidthRight = 21;
const int gameHeightTop = 5;
const int gameHeightBottom = 21;
int maxY, maxX = -1;
int minX, minY = 23;

Block *currentBlock;
Block *nextBlock;
Block *nextBlockTwo;
Block *nextBlockThree;

int savedBlocks[23][23];

int tetrisFrameCount;
boolean tetrisGameOver;
int tetrisScore;

void tetris()
{
  tetrisFrameCount=0;
  tetrisGameOver=false;
  tetrisScore=0;
  srand(millis());

  currentBlock = new Block(13, 5, rand()%7);
  nextBlock = new Block(4, 19, rand()%7);
  nextBlockTwo = new Block(4, 14, rand()%7);
  nextBlockThree = new Block(4, 9, rand()%7);

  memset(&savedBlocks, -1, sizeof(savedBlocks[0][0])*23*23);
 
  while (true){
    nchuk.update();
    int joyX = nchuk.joyX();
    int joyY = nchuk.joyY();
    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();
    if(tetrisGameOver or cButton){
      gameOverScreen((tetrisScore/4));
      FastLED.show();
      delay(2000);
      msIdle=millis();
      break;
    }

    clear();
   
    setMaxAndMins();
    tetrisCheckMovement(joyX, joyY);
    if(zButton)
    {
      rotateShape();
      delay(20);
    }
    if(tetrisFrameCount%4==0 or joyY<120)
      fall();
    deleteRow();
    loadBlocks();
    drawTetrisWalls();
    drawShape();

    FastLED.show();
    delay(110);
    tetrisFrameCount++;
  }
}

void tetrisCheckMovement(int joyX, int joyY){
  if (joyX<120 && minX>gameWidthLeft  && !checkMultiBlockCollision(currentBlock->x, currentBlock->y,0, -1))
    for(int i = 0; i < 4; i++) currentBlock->x[i]--;
  else if (joyX>135 && maxX<gameWidthRight  && !checkMultiBlockCollision(currentBlock->x, currentBlock->y, 0, 1))
    for(int i = 0; i < 4; i++) currentBlock->x[i]++;
}

void rotateShape(){
  int tempArrX[4];
  int tempArrY[4];

  for(int i = 3; i >= 0; i--){
    //Sets origin at initX and initY
    int tempX = currentBlock->x[i]-currentBlock->x[0];
    int tempY = currentBlock->y[i]-currentBlock->y[0];
    //Makes old y coord negative
    int temp = -tempY;
    //Flips x and y
    tempY = tempX;
    tempX = temp;

    //Adds initX and initY back
    tempArrX[i]=tempX+currentBlock->x[0];
    tempArrY[i]=tempY+currentBlock->y[0];  

    //Checks wall & block collision and shifts player block
    if( currentBlock->y[0]-minY==2 && (currentBlock->x[0]==gameWidthRight || checkSingleBlockCollision(currentBlock->x[0], currentBlock->y[0],0, 1) ) )
      tempArrX[i]-=2;
    else if( maxY-currentBlock->y[0]==2 && (currentBlock->x[0]==gameWidthLeft || checkSingleBlockCollision(currentBlock->x[0], currentBlock->y[0],0, -1) ) )
      tempArrX[i]+=2;
    else if ( (currentBlock->y[0]-minY==1 && (currentBlock->x[0]==gameWidthRight || checkSingleBlockCollision(currentBlock->x[0], currentBlock->y[0],0, 1) ) ) || (currentBlock->y[0]-minY==2 && (currentBlock->x[0]==gameWidthRight-1 || checkSingleBlockCollision(currentBlock->x[0], currentBlock->y[0],0, 2) ) ) )
      tempArrX[i]-=1;
    else if( (maxY-currentBlock->y[0]==1 && (currentBlock->x[0]==gameWidthLeft || checkSingleBlockCollision(currentBlock->x[0], currentBlock->y[0],0, -1) ) ) || (maxY-currentBlock->y[0]==2 && (currentBlock->x[0]==gameWidthLeft+1 || checkSingleBlockCollision(currentBlock->x[0], currentBlock->y[0],0, -2) ) ) )
      tempArrX[i]+=1;
  }
  //Double checks final rotated position after shifting x-positions
  if( !checkMultiBlockCollision(tempArrX, tempArrY,0, 0) && checkRotationInBounds(tempArrX, tempArrY) ){
    for(int i = 0; i < 4; i++){
      currentBlock->x[i]=tempArrX[i];
      currentBlock->y[i]=tempArrY[i];
    }
  }
}

void setMaxAndMins()
{
  maxX=-1;
  maxY=-1;
  minX=24;
  minY=24;
  for(int i = 0; i <4; i++){
     maxY = MAX(maxY,currentBlock->y[i]);
     minY = MIN(minY,currentBlock->y[i]);
     maxX = MAX(maxX,currentBlock->x[i]);
     minX = MIN(minX,currentBlock->x[i]);
  }
}

void fall(){
  if(maxY<gameHeightBottom && !checkMultiBlockCollision(currentBlock->x, currentBlock->y,1, 0))
    for(int i = 0; i <4; i++) currentBlock->y[i]++;
  else{
      saveBlock();
      drawShape();
      loadBlocks();

      delete currentBlock;
      currentBlock = new Block(13, 5, nextBlock->blockType);
      delete nextBlock;
      nextBlock = new Block(4, 19, nextBlockTwo->blockType);
      delete nextBlockTwo;
      nextBlockTwo = new Block(4, 14, nextBlockThree->blockType);
      delete nextBlockThree;
      nextBlockThree = new Block(4, 9, rand() % 7);
  }
}

//False if no blocks collide, true if at least one block will collide
boolean checkMultiBlockCollision(int mX[], int mY[], int y, int x){
  for(int i = 0; i < 4; i++)
    if(checkSingleBlockCollision(mX[i], mY[i], y, x)) return true;
  return false;
}

//False if no collision, true if there is a collision
boolean checkSingleBlockCollision(int sX, int sY, int y, int x){
  if(savedBlocks[sX+x][sY+y]!=-1)
    return true;
  return false;
}

boolean checkRotationInBounds(int x[], int y[]){
  for(int i = 0; i < 4; i++){
    if(x[i]<gameWidthLeft || x[i]>gameWidthRight || y[i]<gameHeightTop || y[i]>=gameHeightBottom)
      return false;
  }
  return true;
}

void deleteRow(){
  //Search each row
  for(int j = gameHeightBottom; j >= 0; j--){
    //Search each column
    for(int i = gameWidthLeft; i <= gameWidthRight; i++){
      //Break column search loop if there is an empty dot in the row
      if(savedBlocks[i][j]==-1)
        break;
      //If i reaches the end, then that means there is a full row
      else if(i==gameWidthRight){
        //Set the target row values to -1
        //tetrisScore++;
        for(int k = 0; k <= gameWidthRight; k++)
          savedBlocks[k][j] = -1;
        //Shift everything above down one
        for(int l = gameHeightBottom; l > 0; l--){
          if(l<j) for(int m = 0; m <= gameWidthRight; m++) savedBlocks[m][l+1] = savedBlocks[m][l];
        }
      }
    }
  }
}
void drawTetrisWalls(){
  for (int i=0; i<23; i++){
    leds[XY(i,0)] = CHSV(255,0,255);
    leds[XY(i,22)] = CHSV(255,0,255);
    leds[XY(0,i)] = CHSV(255,0,255);
    leds[XY(8,i)] = CHSV(255,0,255);
    leds[XY(22,i)] = CHSV(255,0,255);
  }
  for (int i=9; i<22; i++)
    leds[XY(i,5)] = CHSV(255,0,100);
}

void drawShape(){
  for (int i = 0; i<4; i++){
    leds[XY(currentBlock->x[i],currentBlock->y[i])] = CHSV(currentBlock->color,255,255);
    leds[XY(nextBlock->x[i],nextBlock->y[i])] = CHSV(nextBlock->color,255,255);
    leds[XY(nextBlockTwo->x[i],nextBlockTwo->y[i])] = CHSV(nextBlockTwo->color,255,255);
    leds[XY(nextBlockThree->x[i],nextBlockThree->y[i])] = CHSV(nextBlockThree->color,255,255);
  }
}

void loadBlocks(){
  for(int i = 0; i <= gameWidthRight; i++){
    for(int j = 0; j <= gameHeightBottom; j++){
      if(savedBlocks[i][j]!=-1)
        leds[XY(i,j)] = CHSV(savedBlocks[i][j], 255, 255);
    }
  }
}

void saveBlock(){
  for(int k = 0; k < 4; k++){
    for(int j = 0; j <= gameHeightBottom; j++){
      if(currentBlock->y[k] == j){
        for(int i = 0; i <= gameWidthRight; i++){
          if(currentBlock->x[k] == i){
            //Serial.println(tetrisScore);
            savedBlocks[i][j] = currentBlock->color;
            tetrisScore++;
            //Serial.println(tetrisScore);
          }
        }
      }
    }
    if(currentBlock->y[k] == gameHeightTop){
      //Serial.println(tetrisScore);
      tetrisGameOver=true;
      //Serial.println(tetrisScore);
    }
  }
}

//==============================================================================================================
//-----------------------------------------------BREAKOUT GAME--------------------------------------------------
int breakOutScore;
int breakOutFrame;

boolean breakOutGameOver;
breakOutBlock blockArray[21];

int ballX;
int ballY;
int balldx;
int balldy;

int pX[4] = {7, 8, 9, 10};
int pY = 20;
int checkUp;
int checkDown;
int checkLeft;
int checkRight;
int checkTopLeft;
int checkTopRight;
int checkBotLeft;
int checkBotRight;

int prevballX1;
int prevballY1;
int prevballX2;
int prevballY2;



void breakout()
{
  breakOutScore = 0;
  breakOutFrame = 0;
  breakOutGameOver = false;
  saveBreakOutBlocks();
  resetBreakOutBall();
 
  while(true)
  {
    nchuk.update();
    int joyY = nchuk.joyY();
    int joyX = nchuk.joyX();
    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();
    if (breakOutGameOver or cButton){
      gameOverScreen(breakOutScore);
      FastLED.show();
      delay(2000);
      msIdle=millis();
      break;
    }

    int breakOutDelay=0;
    if(breakOutScore>=10) breakOutDelay=1;
    if(breakOutScore>=20) breakOutDelay=2;
    if(breakOutScore>=30) breakOutDelay=3;
    if(breakOutScore>=40) breakOutDelay=4;
    //must be even and positive
    int breakOutFrameRate = 8-breakOutDelay;
    int breakOutFrameMod = breakOutFrame%breakOutFrameRate;
    int fade = breakOutFrameMod*255/breakOutFrameRate;

    if (breakOutFrame%(5)==0)
      movePaddle(joyX);
   
    //Set previous ball positions, check area around ball and change direction if need be, and move ball
    if (breakOutFrameMod==0){
      prevballX1 = ballX;
      prevballY1 = ballY;
      prevballX2 = prevballX1-balldx;
      prevballY2 = prevballY1+balldy;
     
      checkBreakOutBall(joyX);
      moveBreakOutBall();
    }

    //Draw ball
    leds[XY(prevballX2, prevballY2)] = CHSV(235, 255, 255-fade);
    leds[XY(prevballX1, prevballY1)] = CHSV(235, 255, 255);
    leds[XY(ballX, ballY)] = CHSV(235, 255, fade);

    drawPaddle();

    drawBreakOutWalls();

   
    loadBreakOutBlocks();
    checkBreakOutBlocksDestroyed();
    checkGameOver();

   


   
    FastLED.show();
    //delay((int)(5/breakOutFrameRate));
    delay(0);
    clear();
    breakOutFrame++;
  }
}

void movePaddle(int joyX){
  if (joyX<120 && pX[0]>1)
    for(int i = 0; i < 4; i++) pX[i]-=1;

  if (joyX>135 && pX[3]<21)
    for(int i = 0; i < 4; i++) pX[i]+=1;
}

void drawPaddle()
{
  for(int i = 0; i < 4; i++)
    leds[XY(pX[i], pY)] = (255, 255, 255);
}

void drawBreakOutWalls()
{
  for(int i = 0; i < 23; i ++){
    leds[XY(0,i)] = CHSV(255, 0, 255);
    leds[XY(22,i)] = CHSV(255, 0, 255);
    leds[XY(i,0)] = CHSV(255, 0, 255);
  }
}

void resetBreakOutBall()
{
  pX[0] = 7;
  pX[1] = 8;
  pX[2] = 9;
  pX[3] = 10;
  ballX=11;
  ballY=8;
  balldx = 0;
  balldy = -1;
}

void moveBreakOutBall()
{
  ballX+=balldx;
  ballY-=balldy;
}


void checkBreakOutBall(int joyX)
{
  //Checks up, down, left, and right to see if ball is hitting block
  checkUp = checkBreakOutBlock(0, -1);
  checkDown = checkBreakOutBlock(0, 1);
  checkLeft = checkBreakOutBlock(-1, 0);
  checkRight = checkBreakOutBlock(1, 0);
  checkTopLeft = checkBreakOutBlock(-1, -1);
  checkTopRight = checkBreakOutBlock(1, -1);
  checkBotLeft = checkBreakOutBlock(-1, 1);
  checkBotRight = checkBreakOutBlock(1, 1);
 
  //Detects if hitting paddle and change direction
 
  if(ballY==pY-1)
  {
    for(int i = 0; i < 4; i++){
      if (ballX==pX[i])
        balldy*=-1;
    }
    if (ballX==pX[0])
      balldx=-1;
    else if (ballX==pX[1]){
      if(joyX<120)balldx--;
      else if (balldx==0) balldx=-1;
    }
    else if (ballX==pX[2]){
      if(joyX>135) balldx++;
      else if (balldx==0) balldx=1;
    }
    else if (ballX==pX[3])
      balldx=1;
    else if ( (ballX==pX[0]-1 and balldx==1) or (ballX==pX[3]+1 and balldx==-1)){
      balldx*=-1;
      balldy*=-1;
    }

    if(balldx>1) balldx=1;
    if(balldx<-1) balldx=-1;
  }
 

  //Detect if hitting walls and change direction if so
  if( ballX >= 21 || ballX <= 1 )
    balldx *= -1;
  if( ballY >= 22 || ballY <= 1 )
    balldy *= -1;
 
  //Detect if hitting block and change direction if so
  if( checkUp != -1  && balldy>0)
  {
    changeBlockColor(checkUp);
    balldy*=-1;
  }
  if( checkDown != -1 && balldy<0)
  {
    changeBlockColor(checkDown);
    balldy*=-1;
  }
  if( checkLeft != -1 && balldx<0)
  {
    changeBlockColor(checkLeft);
    balldx*=-1;
  }
  if( checkRight != -1 && balldx>0)
  {
    changeBlockColor(checkRight);
    balldx*=-1;
  }
  else if( checkTopLeft != -1 && balldx<0 && balldy>0)
  {
    changeBlockColor(checkTopLeft);
    balldy*=-1;
    balldx*=-1;
  }
  else if( checkTopRight != -1 && balldx>0 && balldy>0 )
  {
    changeBlockColor(checkTopRight);
    balldy*=-1;
    balldx*=-1;    
  }
  else if( checkBotLeft != -1 && balldx<0 && balldy<0)
  {
    changeBlockColor(checkBotLeft);
    balldy*=-1;
    balldx*=-1;
  }
  else if( checkBotRight != -1 && balldx>0 && balldy<0)
  {
    changeBlockColor(checkBotRight);
    balldx*=-1;
    balldy*=-1;
  }
}

void saveBreakOutBlocks()
{
  int z = 0;
  int color = 0;
  for(int j = 1; j <= 5; j+=2)
  {
    switch(j)
    {
      case 3:
        color = 15;
        break;
      case 5:
        color = 50;
        break;
      default:
        break;
    }
    for(int i = 1; i <= 19; i+=3)
    {
      blockArray[z++].setXY(i, j, color);
    }
  }
}

void loadBreakOutBlocks()
{
  for(int z = 0; z < 21; z++)
  {
    if(blockArray[z].color!=-1)
    {
      for(int i = 0; i < 6; i++)
      {
        leds[ XY( blockArray[z].breakOutX[i], blockArray[z].breakOutY[i] ) ] = CHSV(blockArray[z].color, 255, 255);
      }
    }
  }
}

int checkBreakOutBlock(int bX, int bY)
{
  for(int z = 0; z < 21; z++)
  {
    for(int i = 0; i < 6; i++)
    {
      if( blockArray[z].color != -1 && blockArray[z].breakOutX[i] == ballX+bX && blockArray[z].breakOutY[i] == ballY+bY)
        return z;
    }
  }
  return -1;
}


boolean checkBreakOutBlocksDestroyed()
{
  for(int i = 0; i < 21; i++)
  {
    if(blockArray[i].color!=-1)
      return false;
  }
  saveBreakOutBlocks();
  resetBreakOutBall();
  return true;
}

void checkGameOver(){
  if(ballY==22)
    breakOutGameOver = true;
}

void changeBlockColor(int check)
{
  breakOutScore+=1;
  Serial.println(breakOutScore);
  switch(blockArray[check].color)
  {
    case 50:
      blockArray[check].color = -1;
      break;
    case 15:
      blockArray[check].color = 50;
      break;
    case 0:
      blockArray[check].color = 15;
      break;
    default:
      break;
  }
}

//==============================================================================================================
//---------------------------------------------------BIRD GAME--------------------------------------------------


int birdframe;
const int wallWidth=2;
const int wallGap=8;
const int wallSize = (23-wallGap)*wallWidth;

int wall[wallSize][2];
int topWallHeight;

int bird[12][2];
int startBird[12][2] = {{7,2},{6,1},{5,1},{5,2},{4,2},{3,2},{2,3},{3,4},{4,4},{5,4},{6,3}};

int birdFrameDelay;
boolean birdGameOver;

void flappyBird()
{
  for(int i=0; i<12; i++){
    bird[i][0]=startBird[i][0];
    bird[i][1]=startBird[i][1];
  }
  birdframe = 0;
  birdFrameDelay = 60;
  birdGameOver = false;
 
  while (not birdGameOver){
   
    nchuk.update();
    int joyY = nchuk.joyY();
    boolean cButton = nchuk.buttonC();
   
    //bird
    drawBird(joyY);

    //walls
    drawBirdWall();
     
    checkBird();
    if (birdGameOver or cButton){
      gameOverScreen((int)birdframe/((23+wallWidth-1)*2));
      FastLED.show();
      delay(2000);
      msIdle=millis();
      break;
    }
   
    FastLED.show();
    clear();

    if (birdFrameDelay>10)
      birdFrameDelay=(60-((int)birdframe/46)*7);
   
    delay(birdFrameDelay);
    birdframe++;
  }
}


void drawBird(int joyY){
  if (joyY>135 and bird[0][1]>2)
    for(int i=0; i<11; i++) bird[i][1]--;
  else if (joyY<120 and bird[0][1]<20)
    for(int i=0; i<11; i++) bird[i][1]++;

  int frameRate = 8;
  int frameMod = birdframe%frameRate;
  int fade = frameMod*255/frameRate;

  //wing flaps
  if (birdframe%2==0){
    bird[4][1]++;
    bird[5][1]++;
    leds[XY(bird[0][0]-2,bird[0][1]+1)] = CRGB(255, 30, 0);
  }
  else{
    bird[4][1]--;
    bird[5][1]--;
  }

  //bird eye
  leds[XY(bird[0][0]-1,bird[0][1])] = CRGB(255, 255, 0);

  for(int i=0; i<11; i++){
    leds[XY(bird[i][0],bird[i][1])] = CRGB(255, 70, 0);
  }
  leds[XY(bird[4][0],bird[4][1])] = CRGB(255, 30, 0);
  leds[XY(bird[5][0],bird[5][1])] = CRGB(255, 30, 0);
}

void drawBirdWall(){
  int wallRound = ((int)birdframe/2)%(23+wallWidth-1);
  if (wallRound==0)
      topWallHeight = rand()%14+1;

  for (int w=0; w<wallWidth; w++){
    //upper wall
    for (int i=0; i<topWallHeight; i++){
      wall[i+(w*(23-wallGap))][0]=22-wallRound+w;
      wall[i+(w*(23-wallGap))][1]=i;
    }
    //lower wall
    for (int i=topWallHeight; i<23-wallGap; i++){
      wall[i+(w*(23-wallGap))][0]=22-wallRound+w;
      wall[i+(w*(23-wallGap))][1]=i+8;
    }
  }
  //for(int i=0; i<wallSize; i++)
  //  leds[XY(wall[i][0], wall[i][1])] = CRGB(0,255,100);
  drawArray(wall,0,0,wallSize,120);
}

void checkBird(){
  for(int b=0; b<11; b++){
    for(int w=0; w<wallSize; w++){
      if( XY(bird[b][0],bird[b][1])==XY(wall[w][0],wall[w][1]))
        birdGameOver=true;
    }
  }
}

//==============================================================================================================
//---------------------------------------------------CONNECT4 GAME--------------------------------------------------

const int c4gameWidthLeft = 0;
const int c4gameWidthRight = 22;

const int c4gameHeightTop = 0;
const int c4gameHeightBottom = 22;

boolean c4gameOver;

int c4savedBlocks[23][23];

int c4color;
int c4winCount;
int cx[4] = {1, 1, 2, 2};
int cy[4] = {1, 2, 1, 2};
int offsetX;
int offsetY;
int c4frame;

void connect4()
{
  memset(&c4savedBlocks, -1, sizeof(c4savedBlocks[0][0])*23*23);  
  c4gameOver = false;
  c4color = 0;
  c4frame=0;

  delay(200);
 
  while (not c4gameOver){

    nchuk.update();
    int joyX = nchuk.joyX();
    int joyY = nchuk.joyY();
    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();

    Serial.println(joyX);

    if(cButton or c4gameOver){
      msIdle=millis();
      break;
    }
   
    clear();
    c4checkMovement(joyX, joyY);
    if(zButton and c4frame%2==0 and c4savedBlocks[ cx[1] ][ cy[1]+4 ]==-1)
      c4dropPixel();
    c4loadBlocks();
    c4drawShape();
    c4drawWalls();
   
    FastLED.show();
    delay(100);
    c4frame++;
  }
  fill(c4color);
  Serial.println("called");
  FastLED.show();
  delay(3000);
}


void c4eraseShape(){
  for(int i = 0; i < 4; i++)
    leds[XY(cx[i],cy[i])] = 0;
}

void c4drawShape(){
  for(int i = 0; i < 4; i++)
    leds[XY(cx[i],cy[i])] = CHSV(c4color,255,255);
}

void c4drawWalls(){
  for (int j=4; j<23; j++)
    for (int i=0; i<23; i+=3) leds[XY(i,j)] = CHSV(255,0,120);
 
  for (int j=4; j<23; j+=3)
    for (int i=0; i<22; i++) leds[XY(i,j)] = CHSV(255,0,120);
}

void c4checkMovement(int joyX, int joyY){
  if (joyX<120 && cx[0]-3>c4gameWidthLeft)
    for(int i = 0; i < 4; i++) cx[i]-=3;
  else if (joyX>135 && cx[3]+3<c4gameWidthRight)
    for(int i = 0; i < 4; i++) cx[i]+=3;
}

void c4dropPixel(){
  while(cy[1] < c4gameHeightBottom-1 && c4savedBlocks[ cx[1] ][ cy[1]+2 ]==-1)
  {
    c4eraseShape();
    c4loadBlocks();

    for(int i = 0; i < 4; i++)
      cy[i]+=1;
     
    c4drawShape();
    c4drawWalls();
    FastLED.show();
    delay(50);
  }
  c4saveBlock();
 
  if( ( checkWinCondition(3, 0) + checkWinCondition(-3, 0) )>=3 || ( checkWinCondition(0, 3) + checkWinCondition(0, -3) )>=3 || ( checkWinCondition(3, 3) + checkWinCondition(-3, -3) )>=3 || ( checkWinCondition(-3, 3) + checkWinCondition(3, -3) )>=3 )
    c4gameOver=true;
  else{
    if(c4color==0)
      c4color=140;
    else
      c4color=0;
  }
  c4resetBlock();
}

void c4saveBlock(){
  for(int k = 0; k < 4; k++){
    for(int j = 0; j <= c4gameHeightBottom; j++){
      if(cy[k] == j){
        for(int i = 0; i <= c4gameWidthRight; i++)
          if(cx[k] == i)  c4savedBlocks[i][j] = c4color;
      }
    }
  }
}

void c4resetBlock(){
  cy[0] = 1;
  cy[1] = 2;
  cy[2] = 1;
  cy[3] = 2;
}

void c4loadBlocks(){
  for(int i = 0; i <= c4gameWidthRight; i++){
    for(int j = 0; j <= c4gameHeightBottom; j++){
      if(c4savedBlocks[i][j]!=-1)
        leds[XY(i,j)] = CHSV(c4savedBlocks[i][j], 255, 255);
    }
  }
}

int checkWinCondition(int iX, int iY){
  c4winCount = 0;
  for(int i = 1; i < 4; i++)
  {
    offsetX = cx[0] + i*iX;
    offsetY = cy[0] + i*iY;
    if(  offsetX >= 0 &&  offsetX <= 23 &&  offsetY >= 0 && offsetY <= 23 && c4savedBlocks[offsetX][offsetY] == c4color)
      c4winCount++;
    else
      break;
  }
  return c4winCount;
}
//==============================================================================================================
//-----------------------------------------------RAINBOW PATTERN------------------------------------------------

void rainbow(){
  while (true){
    nchuk.update();
    boolean cButton = nchuk.buttonC();
    if(cButton)
      break;
   
    int ms = millis();
    int yHueDelta32 = ((int)cos16( ms * (27/1) ) * (350 / width));
    int xHueDelta32 = ((int)cos16( ms * (39/1) ) * (310 / height));
    rainbowFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
    FastLED.show();
    delay(10);
  }
}

void rainbowFrame(int startHue8, int yHueDelta8, int xHueDelta8){
  int lineStartHue = startHue8;
  for( int y = 0; y < height; y++) {
    lineStartHue += yHueDelta8;
    int pixelHue = lineStartHue;      
    for( int x = 0; x < width; x++) {
      pixelHue += xHueDelta8;
      leds[ XY(x, y)]  = CHSV(pixelHue, 255, 255);
    }
  }
}

//==============================================================================================================
//-----------------------------------------------Idle Patterns------------------------------------------------
#define MAX_DIMENSION ((width>height) ? width : height)

uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

static uint16_t xPalette = random16();
static uint16_t yPalette = random16();
static uint16_t zPalette = random16();

uint16_t speed = 20;
uint16_t scale = 30;
uint8_t colorLoop = 1;

CRGBPalette16 currentPalette(PartyColors_p);

void idleScreen(){
  while(true){
    nchuk.update();
    int joyX = nchuk.joyX();
    int joyY = nchuk.joyY();
    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();
    if(cButton or zButton or joyX<125 or joyX>129 or joyY<125 or joyY>129){
      delay(100);
      msIdle=millis();
      break;
    }

    ChangePaletteAndSettingsPeriodically();

    if (palettePlay){
      currentPalette = currPal_p;
      speed = speedPal;
      scale = scalePal;
      colorLoop = colorLoopPal;
    }
   

    fillnoise8();
    mapNoiseToLEDsUsingPalette();

    LEDS.show();
    delay(10);
  }
}


void fillnoise8() {
  uint8_t dataSmoothing = 0;
  if( speed < 50)
    dataSmoothing = 200 - (speed * 4);
 
  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
     
      uint8_t data = inoise8(xPalette + ioffset, yPalette + joffset, zPalette);

      data = qsub8(data,16);
      data = qadd8(data,scale8(data,39));

      if( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }
      noise[i][j] = data;
    }
  }
  zPalette += speed;
  xPalette += speed / 8;
  yPalette -= speed / 16;
}

void mapNoiseToLEDsUsingPalette(){
  static uint8_t ihue=0;
 
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {

      uint8_t index = noise[j][i];
      uint8_t bri = noise[i][j];

      if(colorLoop)
        index += ihue;

      if (bri > 127) bri = 255;
      else bri = dim8_raw(bri * 2);

      CRGB colorP = ColorFromPalette(currentPalette, index, bri);
      leds[XY(i,j)] = colorP;
    }
  }
  ihue+=1;
}

#define HOLD_PALETTES_X_TIMES_AS_LONG 1

void ChangePaletteAndSettingsPeriodically(){
  uint8_t secondHand = ((millis() / 1000) / HOLD_PALETTES_X_TIMES_AS_LONG) % 30;
  static uint8_t lastSecond = 99;
 
  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    if( secondHand ==  0)  { currentPalette = RainbowColors_p;         speed = 15; scale = 30; colorLoop = 1; }
    if( secondHand ==  5)  { currentPalette = PurpleAndGreen_p;        speed = 10; scale = 35; colorLoop = 1; }
    if( secondHand == 10)  { currentPalette = ForestColors_p;          speed =  8; scale = 12; colorLoop = 0; }
    if( secondHand == 15)  { currentPalette = CloudColors_p;           speed =  4; scale = 30; colorLoop = 0; }
    if( secondHand == 20)  { currentPalette = LavaColors_p;            speed =  8; scale = 50; colorLoop = 0; }
    if( secondHand == 25)  { currentPalette = OceanColors_p;           speed = 20; scale = 30; colorLoop = 0; }
  }
}


//==============================================================================================================
//==============================================================================================================
//scroll thingy

void scrollSentence(char sentence[], int color){
  int sentenceLength = strlen(sentence);
  int fullArr[20*sentenceLength][2];

  for (int i=0; i<sentenceLength; i++){
    for (int j=0; j<20; j++){
      if (sentence[i]=='a'){
        fullArr[i*20+j][0] = A[j][0]+i*6;
        fullArr[i*20+j][1] = A[j][1];
      }
      if (sentence[i]=='b'){
        fullArr[i*20+j][0] = B[j][0]+i*6;
        fullArr[i*20+j][1] = B[j][1];
      }
      if (sentence[i]=='c'){
        fullArr[i*20+j][0] = C[j][0]+i*6;
        fullArr[i*20+j][1] = C[j][1];
      }
      if (sentence[i]=='d'){
        fullArr[i*20+j][0] = D[j][0]+i*6;
        fullArr[i*20+j][1] = D[j][1];
      }
      if (sentence[i]=='e'){
        fullArr[i*20+j][0] = E[j][0]+i*6;
        fullArr[i*20+j][1] = E[j][1];
      }
      if (sentence[i]=='f'){
        fullArr[i*20+j][0] = F[j][0]+i*6;
        fullArr[i*20+j][1] = F[j][1];
      }
      if (sentence[i]=='g'){
        fullArr[i*20+j][0] = G[j][0]+i*6;
        fullArr[i*20+j][1] = G[j][1];
      }
      if (sentence[i]=='h'){
        fullArr[i*20+j][0] = H[j][0]+i*6;
        fullArr[i*20+j][1] = H[j][1];
      }
      if (sentence[i]=='i'){
        fullArr[i*20+j][0] = I[j][0]+i*6;
        fullArr[i*20+j][1] = I[j][1];
      }
      if (sentence[i]=='j'){
        fullArr[i*20+j][0] = J[j][0]+i*6;
        fullArr[i*20+j][1] = J[j][1];
      }
      if (sentence[i]=='k'){
        fullArr[i*20+j][0] = K[j][0]+i*6;
        fullArr[i*20+j][1] = K[j][1];
      }
      if (sentence[i]=='l'){
        fullArr[i*20+j][0] = L[j][0]+i*6;
        fullArr[i*20+j][1] = L[j][1];
      }
      if (sentence[i]=='m'){
        fullArr[i*20+j][0] = M[j][0]+i*6;
        fullArr[i*20+j][1] = M[j][1];
      }
      if (sentence[i]=='n'){
        fullArr[i*20+j][0] = N[j][0]+i*6;
        fullArr[i*20+j][1] = N[j][1];
      }
      if (sentence[i]=='o'){
        fullArr[i*20+j][0] = O[j][0]+i*6;
        fullArr[i*20+j][1] = O[j][1];
      }
      if (sentence[i]=='p'){
        fullArr[i*20+j][0] = P[j][0]+i*6;
        fullArr[i*20+j][1] = P[j][1];
      }
      if (sentence[i]=='q'){
        fullArr[i*20+j][0] = Q[j][0]+i*6;
        fullArr[i*20+j][1] = Q[j][1];
      }
      if (sentence[i]=='r'){
        fullArr[i*20+j][0] = R[j][0]+i*6;
        fullArr[i*20+j][1] = R[j][1];
      }
      if (sentence[i]=='s'){
        fullArr[i*20+j][0] = S[j][0]+i*6;
        fullArr[i*20+j][1] = S[j][1];
      }
      if (sentence[i]=='t'){
        fullArr[i*20+j][0] = T[j][0]+i*6;
        fullArr[i*20+j][1] = T[j][1];
      }
      if (sentence[i]=='u'){
        fullArr[i*20+j][0] = U[j][0]+i*6;
        fullArr[i*20+j][1] = U[j][1];
      }
      if (sentence[i]=='v'){
        fullArr[i*20+j][0] = V[j][0]+i*6;
        fullArr[i*20+j][1] = V[j][1];
      }
      if (sentence[i]=='w'){
        fullArr[i*20+j][0] = W[j][0]+i*6;
        fullArr[i*20+j][1] = W[j][1];
      }
      if (sentence[i]=='x'){
        fullArr[i*20+j][0] = X[j][0]+i*6;
        fullArr[i*20+j][1] = X[j][1];
      }
      if (sentence[i]=='y'){
        fullArr[i*20+j][0] = Y[j][0]+i*6;
        fullArr[i*20+j][1] = Y[j][1];
      }
      if (sentence[i]=='z'){
        fullArr[i*20+j][0] = Z[j][0]+i*6;
        fullArr[i*20+j][1] = Z[j][1];
      }
      if (sentence[i]=='1'){
        fullArr[i*20+j][0] = num1[j][0]+i*6;
        fullArr[i*20+j][1] = num1[j][1];
      }
      if (sentence[i]=='2'){
        fullArr[i*20+j][0] = num2[j][0]+i*6;
        fullArr[i*20+j][1] = num2[j][1];
      }
      if (sentence[i]=='3'){
        fullArr[i*20+j][0] = num3[j][0]+i*6;
        fullArr[i*20+j][1] = num3[j][1];
      }
      if (sentence[i]=='4'){
        fullArr[i*20+j][0] = num4[j][0]+i*6;
        fullArr[i*20+j][1] = num4[j][1];
      }
      if (sentence[i]=='5'){
        fullArr[i*20+j][0] = num5[j][0]+i*6;
        fullArr[i*20+j][1] = num5[j][1];
      }
      if (sentence[i]=='6'){
        fullArr[i*20+j][0] = num6[j][0]+i*6;
        fullArr[i*20+j][1] = num6[j][1];
      }
      if (sentence[i]=='7'){
        fullArr[i*20+j][0] = num7[j][0]+i*6;
        fullArr[i*20+j][1] = num7[j][1];
      }
      if (sentence[i]=='8'){
        fullArr[i*20+j][0] = num8[j][0]+i*6;
        fullArr[i*20+j][1] = num8[j][1];
      }
      if (sentence[i]=='9'){
        fullArr[i*20+j][0] = num9[j][0]+i*6;
        fullArr[i*20+j][1] = num9[j][1];
      }
      if (sentence[i]=='0'){
        fullArr[i*20+j][0] = num0[j][0]+i*6;
        fullArr[i*20+j][1] = num0[j][1];
      }
      if (sentence[i]==' '){
        fullArr[i*20+j][0] = space[j][0]+i*4;
        fullArr[i*20+j][1] = space[j][1];
      }
      if (sentence[i]=='.'){
        fullArr[i*20+j][0] = period[j][0]+i*4;
        fullArr[i*20+j][1] = period[j][1];
      }
      if (sentence[i]=='!'){
        fullArr[i*20+j][0] = exclamationPoint[j][0]+i*4;
        fullArr[i*20+j][1] = exclamationPoint[j][1];
      }
      if (sentence[i]=='?'){
        fullArr[i*20+j][0] = questionMark[j][0]+i*4;
        fullArr[i*20+j][1] = questionMark[j][1];
      }
      if (sentence[i]=='#'){
        fullArr[i*20+j][0] = hashtag[j][0]+i*6;
        fullArr[i*20+j][1] = hashtag[j][1];
      }
      if (sentence[i]=='_'){
        fullArr[i*20+j][0] = underscore[j][0]+i*6;
        fullArr[i*20+j][1] = underscore[j][1];
      }
    }
  }
  scrollArray(fullArr,0,6,sentenceLength*20,sentenceLength*6, color);
}

//==============================================================================================================
//==============================================================================================================
//face stuff

boolean lookFront=true;
boolean lookLeft=false;
boolean lookRight=false;
//boolean faceBlink=false;

void face(){
  int ms=millis();
  while (true){
    nchuk.update();
    int joyX = nchuk.joyX();
    int joyY = nchuk.joyY();
    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();
    if(cButton or zButton){
      delay(100);
      msIdle=millis();
      break;
    }

    //control looking
    if (joyX<120){
      lookFront=false;
      lookLeft=true;
      lookRight=false;
    }
    else if (joyX>135){
      lookFront=false;
      lookLeft=false;
      lookRight=true;
    }
    else if (joyY<120){
      lookFront=true;
      lookLeft=false;
      lookRight=false;
    }

    //random looking
    if (millis()-ms>4000){
      if(rand()%3==0){
        lookFront=true;
        lookLeft=false;
        lookRight=false;
      }
      else if(rand()%3==1){
        lookFront=false;
        lookLeft=true;
        lookRight=false;
      }
      else{
        lookFront=false;
        lookLeft=false;
        lookRight=true;
      }
      ms=millis();
    }

    //face
    if (lookFront) drawFace(frontFace);
    if (lookLeft) drawFace(leftFace);
    if (lookRight) drawFace(rightFace);

    //blink
    if(rand()%20>18){
      if (lookFront) drawFace(frontBlink);
      if (lookLeft) drawFace(leftBlink);
      if (lookRight) drawFace(rightBlink);
    }
   
    FastLED.show();
    delay(100);
  }
}

void drawFace(int arr[23][23]){
  for (int j=0; j<23; j++){
    for (int i=0; i<23; i++){
      if (arr[j][i]==0)
        leds[XY(i,j)] = CHSV(255, 255, 80);
      if (arr[j][i]==1)
        leds[XY(i,j)] = 0;
      if (arr[j][i]==2)
        leds[XY(i,j)] = CHSV(255, 255, 255);
      if (arr[j][i]==3)
        leds[XY(i,j)] = CHSV(240, 255, 255);
    }
  }
}


//===============================================================
//fire stuff

CRGBPalette16 gPal = HeatColors_p;
#define COOLING 100
#define SPARKING 60
#define FRAMES_PER_SECOND 30
boolean spark=false;

void fire(){
  FastLED.setBrightness(250);
  //clear();
  while (true){
    nchuk.update();
    int joyX = nchuk.joyX();
    int joyY = nchuk.joyY();
    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();
    if(cButton or zButton){
      delay(200);
      msIdle=millis();
      break;
    }

    fireFrame();
   
    FastLED.show();
    delay(1000 / FRAMES_PER_SECOND);
  }
}

void fireFrame(){
  static byte heat[529];
  random16_add_entropy(random8());
 
  for (int x = 0; x < 23; x++){
   
    for (int y = 0; y < 23; y++)
      heat[XY(x, y)] = qsub8(heat[XY(x, y)], random8(0, ((COOLING * 10) / 23) + 2));
 
    for (int y = 0; y < 23; y++)
      heat[XY(x, y)] = (heat[XY(x, y + 1)] + heat[XY(x, y + 2)] + heat[XY(x, y + 2)]) / 3;
   
    if(random8() < SPARKING)
      heat[XY(x, 22)] = qadd8(heat[XY(x, 22)], random8(160,255));

    for (int y = 0; y < 23; y++) {
      int xy = XY(x, y);
      byte colorindex = scale8(heat[xy], 240);
      leds[xy] = ColorFromPalette( gPal, colorindex);
    }
  }
}

//=====================================================================================
//vortex stuff

class Vortex 
{
    

  public:
  
    int Vx = 0;
    int Vy = 0;
    int Vright = 1;
    int Vup = 0;
    int Vw = 22;
    int Vh = 22;
    int Vmargin = 0;
    int Vhue;
    
    Vortex() {}

    void vortex() 
    {
      leds[ XY(Vx, Vy)]  = CHSV(Vhue, 255, 255);
      // End of Vright
      if ((Vx >= (Vw - Vmargin)) && (Vup == 0)) {
        Vup = 1;
        Vright = 0;
          //    vortexVhue += 15;
      }
      // End of Vup
      else if ((Vy >= (Vh - Vmargin)) && (Vup == 1)) {
        Vup = 0;
        Vright = -1;
        //    vortexVhue += 15;
      }
      // End of left
      else if ((Vx == (0 + Vmargin)) && (Vup == 0 && Vright == -1)) {
        Vup = -1;
        Vright = 0;
        //    vortexVhue += 15;
      }
      // End of down
      else if ((Vx == (0 + Vmargin) && Vy == (1 + Vmargin)) && (Vup == -1 && Vright == 0)) {
        Vy += Vup;
        Vup = 0;
        Vright = 1;
        Vhue += 15;
        Vmargin++;
        Vy++;
      }

      // Final LED
      if ( Vx==11 && Vy==11 /*Vright == 0 && Vup == -1 && Vmargin == ( (23 / 2))*/) 
      {
        //delay(5000);
        Vhue = random(0, 255);
        Vmargin = 0;
        Vx = -1;
        Vy = 0;
        Vright = 1;
        Vup = 0;
      }

     // Option toggle?
      //  fadeLightBy(leds, (23 * 23), 20);
      Vx += Vright;
      Vy += Vup;
    }
};



#define SNAKE_GAP 5
#define NUM_SNAKES ((529 / SNAKE_GAP) / 2)
Vortex vortexs[NUM_SNAKES];

int vortexsStarted = 1;
//int const vortexDelay = ((23 * 2) + (23 * 2) - 1);
int const vortexDelay = SNAKE_GAP * 2;
int vortexGap = 0;

void vortexFrame() {

  if (vortexsStarted < NUM_SNAKES) 
  {
    if (vortexGap == vortexDelay)  
    {
      vortexsStarted++;
      vortexGap = 0;
    }
    else
    {
      vortexGap++;
    }
  }

  for (int  i = 0; i < vortexsStarted; i++) 
  {
    vortexs[i].vortex();
    Serial.printf("%d\n", vortexs[0].Vmargin);
  }
  fadeToBlackBy(leds, (23 * 23), 55); // TWEAK ME
  //FastLED.delay(20);
  EVERY_N_SECONDS(10) {
    Serial.println(FastLED.getFPS());
  }
}
