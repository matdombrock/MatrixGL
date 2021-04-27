#include "Arduino.h"
#include "MatrixGL.h"
#include <MD_MAX72xx.h>
#include "Chars.h"
#include "findTools.h"
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

MatrixGL::MatrixGL(int CLK_PIN, int DATA_PIN, int CS_PIN, int MAX_DEVICES, int MDX, int MDY)
{
  _mdX = MDX;
  _mdY = MDY;
  if(MDX == NULL || MDY == NULL){
    _lenX = MAX_DEVICES * 8;
    _lenY = 8;
  }else{
    _lenX = MDX * 8;
    _lenY = MDY * 8;
  }
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

void MatrixGL::drawPoint(int x, int y, bool on){
  // Offset for custom configurations
  if(y>7 && _mdY > 1){
    // We are over low level height (not by mistake)
    // Move one _mdX to the right for each 8 pixels over 7
    int offset = y/8;
    x = x + ((_mdX*8)*offset);
    y = y - (offset*8);
  }
  mx->setPoint(y, x, on);
}

void MatrixGL::drawLine(int x1, int y1, int x2, int y2, bool on){
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
    drawPoint(pos[0], pos[1], on);
    pos[0] = pos[0] + d[0];
    pos[1] = pos[1] + d[1];
    i = i + 1;
  }
  drawPoint(x2, y2, on);// Set last point
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void MatrixGL::drawPath(int points[], int pointsLen, bool on){
  for(int i =0; i<pointsLen; i+=2){
    if(i+2 < pointsLen){
      drawLine(points[i], points[i+1], points[i+2], points[i+3], on);
    }
  }
}

void MatrixGL::drawSprite(const bool sprite[],int w, int h, int x, int y, bool inverted){
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
      drawPoint(pos[0]+x, lenY-1-pos[1]+y, true);
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

void MatrixGL::drawFrame(const bool frame[], bool clearFirst, bool inverted){
  if(clearFirst){
    mx->clear();
  }
  int pos[2] = {0,0};//x,y
  int frameLen = (_lenX * _lenY);
  drawSprite(frame, _lenX, _lenY, 0, 0, inverted);
}

void MatrixGL::drawChar(char c, int x, int y, bool inverted){
  const bool *frame;
  frame = findChar(c);
  drawSprite(frame,4,6,x,y, inverted);
}

void MatrixGL::drawNum(int n, int x, int y, bool inverted){
  const bool *frame;
  frame = findNum(n);
  drawSprite(frame,4,6,x,y, inverted);
}

void MatrixGL::drawString(String str, int length){
  char buf[length];
  str.toCharArray(buf, length+1);
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx->clear();
  //experimental
  int extraSpace = (_lenX-2) - (length*5);// There is a default padding of 1
  int padding = 1;
  if(extraSpace>2){//extraSpace<=2 does not need custom padding
    padding = extraSpace/2;
  }
  //
  for(int i = 0; i<length; i++){
    if(buf[i]==NULL){
      buf[i] = ' ';
    }
    drawChar(buf[i],padding+(i*5),1);//experimental: padding was 1  
  }
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
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


