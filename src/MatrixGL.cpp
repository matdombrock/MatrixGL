#include "Arduino.h"
#include "MatrixGL.h"
#include <MD_MAX72xx.h>
// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI

int dfOSX = 0;
int dfOSY = 0;
bool inverted = false;

MatrixGL::MatrixGL(int CS_PIN, int MAX_DEVICES, int lengthX, int lengthY, int intensity)
{
  _lenX = lengthX;
  _lenY = lengthY;
  
  mx = new MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
  // Intialize the object:
  mx->begin();
  // Set the intensity (brightness) of the display (0-15):
  if(intensity>15){
    intensity = 15;
  }
  mx->control(MD_MAX72XX::INTENSITY, intensity);
  // Clear the display:
  mx->clear();
  _fr = 50;
}
// Move over functions
void MatrixGL::drawFrame(bool frame[], bool clearFirst){
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  if(clearFirst){
    mx->clear();
  }
  int pos[2] = {dfOSX,dfOSY};//x,y
  int frameLen = (_lenX * _lenY);
  // iterate through all pixels in frame
  for(int i = 0; i < frameLen; i++){
    // draw "pixel"
    bool pixel = pgm_read_byte_near(frame + i);
    if(inverted){
      pixel = !pixel;
    }
    if(pixel==1){
      //invert Y
      mx->setPoint(_lenY-1-pos[1], pos[0], true);
    }
    // change position
    pos[0]++;//x
    if(pos[0]>_lenX-1){
      pos[0] = 0;
      pos[1]++;//y
      if(pos[1]>_lenY-1){
        // done drawing frame
        mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
        return;
      }
    }
  }
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void MatrixGL::drawLine(int x1, int y1, int x2, int y2){
  //Digital differential analyzer
  //https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
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
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void MatrixGL::drawPath(int points[], int pointsLen){
  for(int i =0; i<pointsLen; i+=2){
    if(i+2 < pointsLen){
      drawLine(points[i], points[i+1], points[i+2], points[i+3]);
    }
  }
}

void MatrixGL::delayF(){
  delay(_fr);
}

void MatrixGL::clear(){
  mx->clear();
}

void MatrixGL::unlock(){
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void MatrixGL::lock(){
  mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
}