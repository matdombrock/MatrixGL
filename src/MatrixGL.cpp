#include "Arduino.h"
#include "MatrixGL.h"
#include <MD_MAX72xx.h>
// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define CLK_PIN   18  // or SCK//13
//#define DATA_PIN  23  // or MOSI//11

// Built-in characters and methods to support looking them up
const bool f0[] PROGMEM = {
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
};

const bool f1[] PROGMEM = {
  0,1,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,1,1,1,
};

const bool f2[] PROGMEM = {
  1,1,1,1,
  0,0,0,1,
  0,1,1,1,
  1,0,0,0,
  1,0,0,0,
  1,1,1,1,
};

const bool f3[] PROGMEM = {
  1,1,1,1,
  0,0,0,1,
  0,1,1,1,
  0,0,0,1,
  0,0,0,1,
  1,1,1,1,
};

const bool f4[] PROGMEM = {
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
};

const bool f5[] PROGMEM = {
  1,1,1,1,
  1,0,0,0,
  1,1,1,0,
  0,0,0,1,
  0,0,0,1,
  1,1,1,0,
};

const bool f6[] PROGMEM = {
  1,1,1,1,
  1,0,0,0,
  1,1,1,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
};

const bool f7[] PROGMEM = {
  1,1,1,1,
  0,0,0,1,
  0,0,1,1,
  0,1,0,0,
  0,1,0,0,
  0,1,0,0,
};

const bool f8[] PROGMEM = {
  0,1,1,0,
  1,0,0,1,
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
};

const bool f9[] PROGMEM = {
  1,1,1,1,
  1,0,0,1,
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
  0,0,0,1,
};

const bool fCol[] PROGMEM = {
  0,1,1,0,
  0,1,1,0,
  0,0,0,0,
  0,0,0,0,
  0,1,1,0,
  0,1,1,0,
};

const bool fBLANK[] PROGMEM = {
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
};

const bool fNULL[] PROGMEM = {
  1,0,1,0,
  0,1,0,1,
  1,0,1,0,
  0,1,0,1,
  1,0,1,0,
  0,1,0,1,
};

const bool fA[] PROGMEM = {
  0,1,1,0,
  1,0,0,1,
  1,1,1,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
};

const bool fB[] PROGMEM = {
  1,1,1,0,
  1,0,1,0,
  1,1,1,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
};

const bool fC[] PROGMEM = {
  1,1,1,1,
  1,0,0,0,
  1,0,0,0,
  1,0,0,0,
  1,0,0,0,
  1,1,1,1,
};

const bool fD[] PROGMEM = {
  1,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,0,
};

const bool fE[] PROGMEM = {
  1,1,1,1,
  1,0,0,0,
  1,1,1,0,
  1,0,0,0,
  1,0,0,0,
  1,1,1,1,
};

const bool fF[] PROGMEM = {
  1,1,1,1,
  1,0,0,0,
  1,1,1,0,
  1,0,0,0,
  1,0,0,0,
  1,0,0,0,
};

const bool fG[] PROGMEM = {
  1,1,1,1,
  1,0,0,0,
  1,0,1,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
};

const bool fH[] PROGMEM = {
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
};

const bool fI[] PROGMEM = {
  1,1,1,1,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  1,1,1,1,
};

const bool fJ[] PROGMEM = {
  1,1,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  1,0,1,0,
  0,1,1,0,
};

const bool fK[] PROGMEM = {
  1,0,0,1,
  1,0,1,0,
  1,1,0,0,
  1,1,1,0,
  1,0,0,1,
  1,0,0,1,
};

const bool fL[] PROGMEM = {
  1,0,0,0,
  1,0,0,0,
  1,0,0,0,
  1,0,0,0,
  1,0,0,0,
  1,1,1,1,
};

const bool fM[] PROGMEM = {
  1,0,0,1,
  1,1,1,1,
  1,1,1,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
};

const bool fN[] PROGMEM = {
  1,0,0,1,
  1,1,0,1,
  1,1,0,1,
  1,0,1,1,
  1,0,1,1,
  1,0,0,1,
};

const bool fO[] PROGMEM = {
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
};

const bool fP[] PROGMEM = {
  1,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,1,1,0,
  1,0,0,0,
  1,0,0,0,
};

const bool fQ[] PROGMEM = {
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
  0,0,1,1,
};

const bool fR[] PROGMEM = {
  1,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,1,1,0,
  1,0,0,1,
  1,0,0,1,
};

const bool fS[] PROGMEM = {
  0,1,1,1,
  1,0,0,0,
  0,1,1,0,
  0,0,0,1,
  1,0,0,1,
  0,1,1,0,
};

const bool fT[] PROGMEM = {
  1,1,1,1,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
};

const bool fU[] PROGMEM = {
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
};

const bool fV[] PROGMEM = {
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
  0,1,1,0,
};

const bool fW[] PROGMEM = {
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
  1,1,1,1,
  1,0,0,1,
};

const bool fX[] PROGMEM = {
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
};

const bool fY[] PROGMEM = {
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
  0,1,1,1,
};

const bool fZ[] PROGMEM = {
  1,1,1,1,
  0,0,0,1,
  0,1,1,0,
  1,0,0,0,
  1,0,0,0,
  1,1,1,1,
};

const bool * findChar(char c){
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
    case ' ':
      return fBLANK;
      break;

    case 'A':
      return fA;
      break;
    case 'B':
      return fB;
      break;
    case 'C':
      return fC;
      break;
    case 'D':
      return fD;
      break;
    case 'E':
      return fE;
      break;
    case 'F':
      return fF;
      break;
    case 'G':
      return fG;
      break;
    case 'H':
      return fH;
      break;
    case 'I':
      return fI;
      break;
    case 'J':
      return fJ;
      break;
    case 'K':
      return fK;
      break;
    case 'L':
      return fL;
      break;
    case 'M':
      return fM;
      break;
    case 'N':
      return fN;
      break;
    case 'O':
      return fO;
      break;
    case 'P':
      return fP;
      break;
    case 'Q':
      return fQ;
      break;
    case 'R':
      return fR;
      break;
    case 'S':
      return fS;
      break;
    case 'T':
      return fT;
      break;
    case 'U':
      return fU;
      break;
    case 'V':
      return fV;
      break;
    case 'W':
      return fW;
      break;
    case 'X':
      return fX;
      break;
    case 'Y':
      return fY;
      break;
    case 'Z':
      return fZ;
      break;

    default:
      return fNULL;
      break;
  }
}

const bool * findNum(int n){
  // Abstraction of `findChar()` that allows an int as an argument
  if(n>9){
    n=0;
  }
  char nS [] = {'0','1','2','3','4','5','6','7','8','9'}; 
  return findChar(nS[n]);
}

MatrixGL::MatrixGL(int CLK_PIN, int DATA_PIN, int CS_PIN, int MAX_DEVICES)
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
  _inverted = false;
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

void MatrixGL::drawSprite(const bool sprite[],int w, int h, int x, int y){
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
    if(_inverted){
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

void MatrixGL::drawFrame(const bool frame[], bool clearFirst){
  if(clearFirst){
    mx->clear();
  }
  int pos[2] = {0,0};//x,y
  int frameLen = (_lenX * _lenY);
  drawSprite(frame, _lenX, _lenY, 0, 0);
}

void MatrixGL::drawChar(char c, int x, int y){
  const bool *frame;
  frame = findChar(c);
  drawSprite(frame,4,6,x,y);
}

void MatrixGL::drawNum(int n, int x, int y){
  const bool *frame;
  frame = findNum(n);
  drawSprite(frame,4,6,x,y);
}

void MatrixGL::setIntensity(int intensity){
  if(intensity>15){
    intensity = 15;
  }
  mx->control(MD_MAX72XX::INTENSITY, intensity);
}

void MatrixGL::invertSprites(){
  _inverted = !_inverted;
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


