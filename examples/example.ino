/*
 * Matrix VCC - MC 5v
 * Matrix GND - MC GND
 * Matrix DIN - MC Pin 11 or MOSI
 * Matrix CS - MC Pin 10 or SS
 * Matrix CLK - MC Pin 13 or SCK
 */

#include <MatrixGL.h>

#define CLK_PIN   18  // or SCK//13
#define DATA_PIN  23  // or MOSI//11
#define CS_PIN 5 // or SS//10
#define MAX_DEVICES 4
#define LENGTHX 32
#define LENGTHY 8

MatrixGL matrix(CLK_PIN,DATA_PIN,CS_PIN,MAX_DEVICES);

// CUSTOM SPRITES
const bool sprite[] PROGMEM = {
  0,0,1,1,0,0,
  1,0,1,1,0,0,
  0,1,1,1,1,1,
  0,1,0,0,1,0,
  0,1,1,1,1,0,
  0,0,0,0,1,0
};
const bool sprite2[] PROGMEM = {
  0,0,1,1,0,0,
  0,0,1,1,0,1,
  1,1,1,1,1,0,
  0,1,0,0,1,0,
  0,1,1,1,1,0,
  0,1,0,0,0,0
};
const bool sprite3[] PROGMEM = {
  0,1,0,0,1,0,
  0,1,0,0,1,0,
  0,1,0,0,1,0,
  0,0,0,0,0,0,
  1,0,0,0,0,1,
  0,1,1,1,1,0
};
// CUSTOM FRAMES
const bool frame1[256] PROGMEM = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,
0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,1,1,1,1,
1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
const bool frame2[256] PROGMEM = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,
1,0,1,0,0,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,
0,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,0,1,1,1,0,1,1,1,
1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void setup() {
  // put your setup code here, to run once:
}

void demoLowLevel(){
  // Access the lower level MD_MAX72xx library
  matrix.mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  matrix.mx->clear();
  matrix.mx->setPoint(1, 1, true);
  matrix.mx->setPoint(2, 2, true);
  matrix.mx->setPoint(3, 3, true);
  matrix.mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  delay(100);
  matrix.mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  matrix.mx->clear();
  matrix.mx->setPoint(4, 4, true);
  matrix.mx->setPoint(5, 5, true);
  matrix.mx->setPoint(6, 6, true);
  matrix.mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  delay(100);
}

void demoPathRings(){
  // Use the `drawPath()` method to create a ring animation
  int X = matrix.lenX() - 1;
  int Y = matrix.lenY() - 1;
  int path[] = {0,0, X,0, X,Y, 0,Y, 0,0};
  matrix.drawPath(path, 10);
  matrix.delayF();
  X--;
  Y--;
  int path2[] = {1,1, X,1, X,Y, 1,Y, 1,1};
  matrix.drawPath(path2, 10);
  matrix.delayF();
  X--;
  Y--;
  int path3[] = {2,2, X,2, X,Y, 2,Y, 2,2};
  matrix.drawPath(path3, 10);
  matrix.delayF();
  X--;
  Y--;
  int path4[] = {3,3, X,3, X,Y, 3,Y, 3,3};
  matrix.drawPath(path4, 10);
  matrix.delayF();
  matrix.delayF();
  matrix.clear();
  matrix.lock();
  matrix.drawPath(path3, 10);
  matrix.drawPath(path2, 10);
  matrix.drawPath(path, 10);
  matrix.unlock();
  matrix.delayF();
  matrix.clear();
  matrix.lock();
  matrix.drawPath(path2, 10);
  matrix.drawPath(path, 10);
  matrix.unlock();
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path, 10);
  matrix.delayF();
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path, 10);
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path2, 10);
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path3, 10);
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path4, 10);
  matrix.delayF();
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path3, 10);
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path2, 10);
  matrix.delayF();
  matrix.clear();
  matrix.drawPath(path, 10);
  matrix.delayF();
  matrix.clear();
}

void demoLinesFill(){
  // Fill the screen with lines using the `drawLine()` method
  int X = matrix.lenX() - 1;
  int Y = matrix.lenY() - 1;
  for(int i = 0; i<=Y;i++){
    matrix.drawLine(0,0, X,i);
    matrix.delayF();
  }
  for(int i = 0; i<8;i++){
    matrix.drawLine(X,Y, 0,Y-i);
    matrix.delayF();
  }
  matrix.clear();
}
void demoIntensity(){
  // Use the `setIntensity()` method to make each line
  // brighter than the last until the max brightness is reached.
  int y = 0;
  int lenX = matrix.lenX()-1;
  for(int i = 0; i<=15;i++){
    matrix.drawLine(0,y, lenX,y);
    y++;
    if(y>7){
      y=0;
    }
    matrix.setIntensity(i);
    matrix.delayN(5);
    matrix.clear();
  }
}

void demoRandomLine(){
  // use the `drawLine()` method to draw a random line on the display
  int X = matrix.lenX();
  int Y = matrix.lenY();
  matrix.drawLine(random(X), random(Y), random(X), random(Y));
  matrix.delayF();
  matrix.clear();
}
void demoRandomLines(){
  // use the `drawLine()` method to draw 16 random lines on the display
  int X = matrix.lenX();
  int Y = matrix.lenY();
  for(int i = 0; i<16; i++){
    matrix.drawLine(random(X), random(Y), random(X), random(Y));
    matrix.delayF();
  }
  matrix.clear();
}

void demoSnow(){
  // Accumulate random "snow flakes" over time
  int X = matrix.lenX();
  int Y = matrix.lenY();
  for(int i = 0; i<256; i++){
    matrix.drawPoint(random(X), random(Y));
    matrix.delayF();
  }
  matrix.clear();
}

void demoRandomNoise(){
  // Generate random noise
  int X = matrix.lenX();
  int Y = matrix.lenY();
  matrix.lock();
  matrix.clear();
  for(int i = 0; i<(X*Y); i++){
    matrix.drawPoint(random(X), random(Y)); 
  }
  matrix.unlock();
  matrix.delayF();
}

void demoClock(){
  // A simple clock implementation that uses the `drawNum()` and `drawChar()` methods
  // DOES NOT TELL ACTUAL TIME (This moves very fast for demo purposes).
  int h1 = 0;
  int h2 = 1;
  int m1 = 0;
  int m2 = 1;
  for(int m = 1; m<=1440;m++){
    matrix.delayF();
    matrix.lock();
    matrix.clear();
    matrix.drawNum(h1, 6,1);
    matrix.drawNum(h2, 11,1);
    matrix.drawChar(':', 14,1);
    matrix.drawNum(m1, 18,1);
    matrix.drawNum(m2, 23,1);
    m2++;
    if(m2==10){// ten mins
      m2 = 0;
      m1++;
      if(m1==6){//1 hour
        m1=0;
        h2++;
        if(h2==10){// 10 hours
          h2 = 0;
          h1++;
        }
        if(h1==1 && h2 > 2){//12 hours
            h1 = 0;
            h2 = 1;
            m1 = 0;
            m2 = 1;
          }
      }
    }
    matrix.unlock();
  }
}
void demoShockBoy(){
  // Use a combination of the `drawSprite()` and `drawLine()` methods to 
  // generate a procedural animation of a person being perpetually shocked
  // WARNING: RUNS FOREVER
  int x = matrix.lenX()/2;
  int y = 0;
  while(true){
    x+=random(-1,2);
    if(x>23){
      x=22;
    }
    if(x<0){
      x=1;
    }
    matrix.setIntensity(0);
    matrix.drawSprite(sprite, 6,6,x,y);
    if(random(6)==5){
      matrix.setIntensity(5);
      matrix.drawLine(x+6,7, x+6+random(4), y);
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
    }
    if(random(8)==7){
      matrix.setIntensity(10);
      matrix.drawLine(x+6,7, x+6+random(4), y);
      matrix.drawLine(x+6,7, x+6+random(4), y);
      //
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
    }
    matrix.delayF();
    matrix.clear();
    matrix.drawSprite(sprite2, 6,6,x,y);
    if(random(6)==5){
      matrix.setIntensity(5);
      matrix.drawLine(x,7, x-random(4), y);
  
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
    }
    if(random(8)==7){
      matrix.setIntensity(10);
      matrix.drawLine(x+6,7, x+6+random(4), y);
      matrix.drawLine(x+6,7, x+6+random(4), y);
  
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
      matrix.drawLine(x+random(-20,20),7, x+6+random(4), 0);
    }
    matrix.delayF();
    matrix.clear();
  }
}


void demoDrawCustomSprite(){
  // Draw a custom sprite at position 1,1
  // Sprites at top of file
  matrix.drawSprite(sprite3, 6,6,1,1);
}

void demoDrawFrames(){
  // Draw a 2 frame animation using the `drawFrame()` method.
  // These frames are designed for a 4 unit wide matrix (32x8)
  // Frames at top of file
  matrix.drawFrame(frame1, true);
  matrix.delayN(5);
  matrix.drawFrame(frame2, true);
  matrix.delayN(5);
}

void demoInvertSprite(){
  matrix.drawSprite(sprite3, 6,6,1,1);
  matrix.delayN(2);
  matrix.clear();
  // invert
  matrix.drawSprite(sprite3, 6,6,1,1, true);
  matrix.delayN(2);
  matrix.clear();
}

void demoInvertFrames(){
  // Draw a 2 frame animation using the `drawFrame()` method.
  // These frames are designed for a 4 unit wide matrix (32x8)
  // Frames at top of file
  matrix.drawFrame(frame1, true);
  matrix.delayN(5);
  matrix.drawFrame(frame2, true);
  matrix.delayN(5);
  matrix.drawFrame(frame1, true, true);
  matrix.delayN(5);
  matrix.drawFrame(frame2, true, true);
  matrix.delayN(5);
}

void loop() {
  /*
   * Uncomment the demo you want to try
   */
  demoLowLevel();
  //demoPathRings();
  //demoLinesFill();
  //demoIntensity();
  //demoRandomNoise();
  //demoRandomLine();
  //demoRandomLines();
  //demoSnow();
  demoRandomNoise();
  //demoClock();
  //demoShockBoy();
  //demoDrawCustomSprite();
  //demoDrawFrames();
  //demoInvertSprite();
  //demoInvertFrames();
}