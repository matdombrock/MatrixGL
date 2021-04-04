#include <MatrixGL.h>

#define CS_PIN 10
#define MAX_DEVICES 4
#define LENGTHX 32
#define LENGTHY 8

MatrixGL matrix(CS_PIN,MAX_DEVICES);
void setup() {
  // put your setup code here, to run once:
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

void demoPathRings(){
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
  //
  //
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
  //
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

void demoRandomLines(){
  int X = matrix.lenX();
  int Y = matrix.lenY();
  matrix.drawLine(random(X), random(Y), random(X), random(Y));
  matrix.delayF();
  matrix.clear();
}
void demoRandomLines2(){
  int X = matrix.lenX();
  int Y = matrix.lenY();
  for(int i = 0; i<16; i++){
    matrix.drawLine(random(X), random(Y), random(X), random(Y));
    matrix.delayF();
  }
  matrix.clear();
}

void demoSnow(){
  int X = matrix.lenX();
  int Y = matrix.lenY();
  for(int i = 0; i<256; i++){
    matrix.mx->setPoint(random(Y), random(X), true);
    matrix.delayF();
  }
  matrix.clear();
}

void demoRandomNoise(){
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
void loop() {
  matrix.drawPoint(0,0);
  //demoRandomNoise();
}