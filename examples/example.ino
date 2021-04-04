#include <MatrixGL.h>

#define CS_PIN 10
#define MAX_DEVICES 4
#define LENGTHX 32
#define LENGTHY 8
#define INTENSITY 0

MatrixGL matrix(CS_PIN,MAX_DEVICES, LENGTHX, LENGTHY, INTENSITY);
void setup() {
  // put your setup code here, to run once:
}

void demoLine(){
  for(int i = 0; i < LENGTHX; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,i,i/4);
  }
  for(int i = 0; i < 8; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,LENGTHX,7-i);
  }
  for(int i = 0; i < 8; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,LENGTHX,i);
  }
  for(int i = 0; i < LENGTHX; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,LENGTHX-1-i,7-i/4);
  }
  
  for(int i = 0; i < 8; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,8,i);
  }
  for(int i = 0; i < 8; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,8,7-i);
  }

  for(int i = 0; i < LENGTHX/2; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,LENGTHX/2,i);
  }
  for(int i = 0; i < LENGTHX/2; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,LENGTHX/2,7-i);
  }

  for(int i = 0; i < 24; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,24,i);
  }
  for(int i = 0; i < 24; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(0,0,24,7-i);
  }

  for(int i = 0; i < 16; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(i,i/2,i*2,1/4);
  }

  for(int i = 0; i < 16; i++){
    matrix.delayF();
    matrix.clear();
    matrix.drawLine(i,i/4,i*2,i/2);
  }
}

void demoLowLevel(){
  matrix.lock();
  matrix.clear();
  matrix.mx->setPoint(1, 1, true);
  matrix.mx->setPoint(2, 2, true);
  matrix.mx->setPoint(3, 3, true);
  matrix.unlock();
  matrix.delayF();
  matrix.lock();
  matrix.clear();
  matrix.mx->setPoint(4, 4, true);
  matrix.mx->setPoint(5, 5, true);
  matrix.mx->setPoint(6, 6, true);
  matrix.unlock();
  matrix.delayF();
}

void demoDrawPath(){
  int points[] = {0,0, 4,4, 7,6, 32,0};
  matrix.lock();
  matrix.clear();
  matrix.drawPath(points, 8);
  matrix.unlock();
}


void loop() {
  // put your main code here, to run repeatedly:
  //demoLowLevel();
  
  demoLine();
  //demoDrawPath();
  //delay(1000);
}