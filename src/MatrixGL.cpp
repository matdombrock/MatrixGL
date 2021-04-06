#include "Arduino.h"
#include "MatrixGL.h"
#include <MD_MAX72xx.h>
// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI

// Built-in characters and methods to support looking them up
const bool f0[] PROGMEM = {
  1,1,1,
  1,0,1,
  1,0,1,
  1,0,1,
  1,1,1
};

const bool f1[] PROGMEM = {
  0,1,1,
  0,0,1,
  0,0,1,
  0,0,1,
  0,0,1
};

const bool f2[] PROGMEM = {
  1,1,1,
  0,0,1,
  0,1,1,
  1,0,0,
  1,1,1
};

const bool f3[] PROGMEM = {
  1,1,1,
  0,0,1,
  0,1,1,
  0,0,1,
  1,1,1
};

const bool f4[] PROGMEM = {
  1,0,1,
  1,0,1,
  1,1,1,
  0,0,1,
  0,0,1
};

const bool f5[] PROGMEM = {
  1,1,1,
  1,0,0,
  1,1,1,
  0,0,1,
  1,1,1
};

const bool f6[] PROGMEM = {
  1,1,1,
  1,0,0,
  1,1,1,
  1,0,1,
  1,1,1
};

const bool f7[] PROGMEM = {
  1,1,1,
  0,0,1,
  0,0,1,
  0,1,0,
  0,1,0
};

const bool f8[] PROGMEM = {
  1,1,1,
  1,0,1,
  1,1,1,
  1,0,1,
  1,1,1
};

const bool f9[] PROGMEM = {
  1,1,1,
  1,0,1,
  1,1,1,
  0,0,1,
  0,0,1
};

const bool fCol[] PROGMEM = {
  0,0,0,
  0,1,0,
  0,0,0,
  0,1,0,
  0,0,0
};

bool * findChar(char c){
  switch(c){
    case '0':
      return f0;
      break;
    case '1':
      return f1;
      break;
    case '2':
      return f2;
      break;
    case '3':
      return f3;
      break;
    case '4':
      return f4;
      break;
    case '5':
      return f5;
      break;
    case '6':
      return f6;
      break;
    case '7':
      return f7;
      break;
    case '8':
      return f8;
      break;
    case '9':
      return f9;
      break;
    case ':':
      return fCol;
      break;
    default:
      return f0;
      break;
  }
}

bool * findNum(int n){
  // Abstraction of `findChar()` that allows an int as an argument
  if(n>9){
    n=0;
  }
  char nS [] = {'0','1','2','3','4','5','6','7','8','9'}; 
  return findChar(nS[n]);
}
//

int dfOSX = 0;
int dfOSY = 0;
bool inverted = false;

MatrixGL::MatrixGL(int CS_PIN, int MAX_DEVICES)
{
  _lenX = MAX_DEVICES * 8;
  _lenY = 8;

  mx = new MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
  // Initialize the object:
  mx->begin();
  // Set the intensity (brightness) of the display (0-15):
  setIntensity(0);
  // Clear the display:
  mx->clear();
  _fDelay = 83;
}

void MatrixGL::drawPoint(int x, int y){
  mx->setPoint(y, x, true);
}

void MatrixGL::drawLine(int x1, int y1, int x2, int y2){
  // Digital differential analyzer
  // Doesn't handle offset yet
  float pos[2];//x,y
  float d[2];//x,y
  float step;
  int i;
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  d[0] = (x2 - x1);
  d[1] = (y2 - y1);
  
  if (abs(d[0]) >= abs(d[1]))
    step = abs(d[0]);
  else
    step = abs(d[1]);
  
  d[0] = d[0] / step;
  d[1] = d[1] / step;
  pos[0] = x1;
  pos[1] = y1;
  i = 1;
  while (i <= step) {
    mx->setPoint(pos[1], pos[0], true);
    pos[0] = pos[0] + d[0];
    pos[1] = pos[1] + d[1];
    i = i + 1;
  }
  mx->setPoint(y2, x2, true);// Set last point
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void MatrixGL::drawPath(int points[], int pointsLen){
  for(int i =0; i<pointsLen; i+=2){
    if(i+2 < pointsLen){
      drawLine(points[i], points[i+1], points[i+2], points[i+3]);
    }
  }
}

void MatrixGL::drawSprite(bool sprite[],int w, int h, int x, int y){
  // w=x h=y
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  int lenX = w;
  int lenY = h;
  int pos[2] = {0,0};//x,y
  int spriteLen = lenX * lenY;
  // iterate through all pixels in frame
  for(int i = 0; i < spriteLen; i++){
    // draw "pixel"
    bool pixel = pgm_read_byte_near(sprite + i);
    if(inverted){
      pixel = !pixel;
    }
    if(pixel==1){
      //invert Y
      drawPoint(pos[0]+x, lenY-1-pos[1]+y);
    }
    // change position
    pos[0]++;//x
    if(pos[0]>lenX-1){
      pos[0] = 0;
      pos[1]++;//y
      if(pos[1]>(lenY)-1){
        // done drawing frame
        mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
        return;
      }
    }
  }
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void MatrixGL::drawFrame(bool frame[], bool clearFirst){
  if(clearFirst){
    mx->clear();
  }
  int pos[2] = {dfOSX,dfOSY};//x,y
  int frameLen = (_lenX * _lenY);
  drawSprite(frame, _lenX, _lenY, 0, 0);
}

void MatrixGL::drawChar(char c, int x, int y){
  bool *frame;
  frame = findChar(c);
  drawSprite(frame,3,5,x,y);
}

void MatrixGL::drawNum(int n, int x, int y){
  bool *frame;
  frame = findNum(n);
  drawSprite(frame,3,5,x,y);
}

void MatrixGL::setIntensity(int intensity){
  if(intensity>15){
    intensity = 15;
  }
  mx->control(MD_MAX72XX::INTENSITY, intensity);
}

void MatrixGL::setFrameRate(int fr){
  _fDelay = 1000/fr;
}

void MatrixGL::delayF(){
  delay(_fDelay);
}

void MatrixGL::delayN(int n){
  for(int i = 0; i<=n;i++){
    delay(_fDelay);
  }
}

void MatrixGL::clear(){
  mx->clear();
}

void MatrixGL::lock(){
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
}

void MatrixGL::unlock(){
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

int MatrixGL::lenX(){
  return _lenX;
}
int MatrixGL::lenY(){
  return _lenY;
}


