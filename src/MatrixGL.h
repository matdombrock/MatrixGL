/*
  MatrixGL.h, a light-weight graphics library for MAX7219 LED Dot Matrix.
  Created by Mathieu Dombrock, April, 2021.
  Released into the public domain.
*/
#ifndef MatrixGL_h
#define MatrixGL_h

#include "Arduino.h"
#include <MD_MAX72xx.h>
class MatrixGL
{
  public:
    MatrixGL(int CS_PIN, int MAX_DEVICES);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawPath(int points[], int pointsLen);
    void drawFrame(bool frame[], bool clearFirst);
    void setIntensity(int intensity);
    void setFrameRate(int fr);
    void delayF();
    void clear();
    void lock();
    void unlock();
    int lenX();
    int lenY();
    MD_MAX72XX* mx;
  private:
    int _fDelay;
    int _lenX;
    int _lenY;
};

#endif
