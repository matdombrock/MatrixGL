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
    MatrixGL(int CLK_PIN, int DATA_PIN, int CS_PIN, int MAX_DEVICES=1, int MDX=NULL, int MDY=NULL);
    void drawPoint(int x, int y, bool on=true);
    void drawLine(int x1, int y1, int x2, int y2, bool on=true);
    void drawPath(int points[], int pointsLen, bool on=true);
    void drawSprite(const bool sprite[],int w, int h, int x, int y, bool inverted=false);
    void drawFrame(const bool frame[], bool clearFirst=true, bool inverted=false);
    void drawChar(char c, int x, int y, bool inverted=false);
    void drawNum(int n, int x, int y, bool inverted=false);
    void drawString(String str, int length=6);
    void setIntensity(int intensity);
    void setFrameRate(int fr);
    void delayF();
    void delayN(int n);
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
    int _mdX;
    int _mdY;
    bool _inverted;
};

#endif
