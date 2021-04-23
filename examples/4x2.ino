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
#define MAX_DEVICES 8
#define MDX 4 //Amount of matrices on the X axis
#define MDY 2 //Amount of matrices on the Y axis

MatrixGL matrix(CLK_PIN,DATA_PIN,CS_PIN,MAX_DEVICES,MDX,MDY);

void setup(){

}

void loop(){
  for(int i = 0; i<matrix.lenX();i++){
    matrix.drawLine(matrix.lenX()-1-i,0, matrix.lenX(), matrix.lenY());
    matrix.delayF();
    matrix.clear();
  }
  for(int i = 0; i<matrix.lenY();i++){
    matrix.drawLine(0,matrix.lenY()-1-i, matrix.lenX(), matrix.lenY());
    matrix.delayF();
    matrix.clear();
  }
}