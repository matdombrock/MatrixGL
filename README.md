# MatrixGL

*An Arduino Microcontroller Graphics Library For LED Dot Matrix Displays*

---
---

## MD_MAX_72XX

Depends on: [MD_MAX_72XX](https://github.com/MajicDesigns/MD_MAX72XX)

The MD_MAX_72XX library provides a system for addressing the "pixels" on the matrix individually. 

> The library implements functions that allow the MAX72xx to be used for LED matrices (64 individual LEDs), allowing the programmer to use the LED matrix as a pixel device, displaying graphics elements much like any other pixel addressable display.

\- MAX72xx LED Matrix Display Library README

*Note: The `MD_MAX_72XX` library treats additional 8x8 matrices as adding to the Y axis. This library prefers treating them as the X axis. So the axes are inverted relative to the `MD_MAX_72XX` library.*

---
---

## Features
* Frame Based Animation
* Sprite Drawing
* Line Drawing
* Path Drawing
* Character Drawing (Numbers work but letters not implemented yet)

Line drawing is preformed by a custom [digital differential analyzer (DDA)](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) implementation. 

## Used On

### [jackmachiela/PhotoLife](https://github.com/jackmachiela/PhotoLife)

> This project creates an old retro-looking photo-frame with a Conway's Game of Life simulation running in it. It's designed to hang on the wall, and to work continuously without stabilising. To prevent the simulation stabilising, the frankenstein switch can be thrown to spark new life into the display - zzzap!
> 
### [matdombrock/WiFi-Clock](https://github.com/matdombrock/WIFI-Clock)

> A WIFI Clock + Temperature/Humidity System for ESP32 Dev Boards.
> 
> Displays on a 32x8 "pixel" LED Matrix.

## Setup
```c++
MatrixGL(int CLK_PIN, int DATA_PIN, int CS_PIN, int MAX_DEVICES=1, int MDX=NULL, int MDY=NULL);
```

```c++
#include <MatrixGL.h>

#define CS_PIN 10 // The CS Pin for your device, may need changing
#define CLK_PIN   18  // The SCK Pin for your device, may need changing
#define DATA_PIN  23  // The MOSI Pin for your device, may need changing
#define MAX_DEVICES 4 // How many matrix Blocks are connected?

MatrixGL matrix(CLK_PIN,DATA_PIN,CS_PIN,MAX_DEVICES);
```

## Basic Usage Example
```c++
void loop(){
  // Draw some line segments
  matrix.delayF();// Delay based on the desired frame rate
  matrix.clear();// Clear the display
  matrix.drawLine(0,0,4,4);// Draw a line from 0,0 to 4,4
  matrix.delayF();// Delay based on the desired frame rate
  matrix.clear();// Clear the display
  matrix.drawLine(4,4,8,8);// Draw a line from 4,4 to 8,8
  // Draw a path
  int points[] = {0,0, 4,4, 7,6, 8,0};// Defines the points on the path
  matrix.lock();// Lock the display (not required)
  matrix.clear();// Clear the display
  matrix.drawPath(points, 8);// Draw a path from the given points
  matrix.unlock();// Unlock the display (not required)
}
```

## Matrix Arrangement

By default, this library assumes that any additional matrices that you include will be added to the X axis. 

If desired, you can add optional arguments (MDX & MDY) to the library instantiation that allow you to define the amount of displays on your X and Y axes.

*Wiring Note: You will need to wire the matrices in order from bottom left (being the first) to top right (being the last).*

Once you have it setup like that you can go ahead and start setting points that have a Y value over 7 and the library will automatically handle the addressing abstraction.

So if you had a 2x2 display setup you could draw 2 points like:
```c++
matrix.drawPoint(0,0,true);
matrix.drawPoint(15,15,true);
```

This will draw a point in the bottom left corner and another in the top right. The first point is drawn on the first display and the last point is drawn on last display in order of how they are wired.

**NOTE: At this time, support for custom display configurations (additional matrices on the Y axis) is an experimental feature and may not play well with other features like sprite/character drawing. Please feel free to [post an issue](https://github.com/matdombrock/MatrixGL/issues/new/choose) if you encounter any.**

See [the 4x2 example](https://github.com/matdombrock/MatrixGL/blob/master/examples/4x2.ino) for more info.

## Notes & Caveats
* This library uses zero based numbering to describe coordinates.
* Unlike many graphics libraries, this one does not start counting the Y axis from the top. So point 0,0 is the bottom left corner (as you would expect on a graphing calculator).
* (Almost) Nothing will stop you from trying to draw outside the bounds of your matrix. Sometimes this results in overflow and sometimes wrap-around. It's up to you to avoid this.

## Drawing Points
```c++
void drawPoint(int x, int y, bool on=true);
```
Turn on an LED at point x,y. 

Setting `on` to false will turn off the LED at that point.

## Drawing Lines
```c++
void drawLine(int x1, int y1, int x2, int y2, bool on=true);
```
Draw a line from the point `x1,y1` to the point `x2,y2`.

Setting `on` to false will turn off the LEDs along the line.

Example:
```c++
matrix.drawLine(0, 0, 6, 8);
```

## Drawing Paths
```c++
void drawPath(int points[], int pointsLen, bool on=true);
```
Draw a path based on the given array of point coordinates. 

Setting `on` to false will turn off the LEDs along the path.

Example:
```c++
int points[] = {0,0, 4,4, 7,6, 0,0};
matrix.drawPath(points, 8);
```

*Note: The length of the `points` array should always be an even number. This is not currently enforced.*

## Drawing Sprites
```c++
void drawSprite(bool sprite[],int w, int h, int x, int y, inverted=false);
```
Draw a sprite with width `w` and heigh `h` at the point `x,y`.

* sprite - contains an array of boolean pixel values
* w - The width (x length) of the sprite
* h - The width (y length) of the sprite
* x - The x drawing offset
* y - The y drawing offset
* inverted - Invert the "pixel values"

*Note: The x and y offsets position the bottom "left" pixel of the sprite.

Example:
```c++
matrix.drawSprite(sprite1, 6,6, 0,0);
```

Defining a sprite works like this:
```c++
const bool sprite[] PROGMEM = {
  0,0,1,1,0,0,
  0,0,1,1,0,0,
  1,1,1,1,1,1,
  0,1,0,0,1,0,
  0,1,1,1,1,0,
  0,1,0,0,1,0
};
```
You can more or less think of the sprite data as being a direct representation of the pixel matrix (assuming you lay it out in the same manner, which you don't have to). As you might have assumed, a 1 represents an active "pixel" (LED ON) and and a 0 represents an inactive "pixel" (LED OFF).

Drawing a series of sprites (an animation) might look like:
```c++
matrix.clear();
matrix.drawSprite(sprite1, 6,6, 1,1);
matrix.delayF();
matrix.clear();
matrix.drawSprite(sprite2, 6,6, 1,1);
matrix.delayF();
matrix.clear();
matrix.drawSprite(sprite3, 6,6, 1,1);
matrix.delayF();
```

*Also notice that the array is being stored in program memory by the use of `PROGMEM` [More Info](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/). This is because sprite/frame data is much too large to store in RAM. While it would be technically possible to get away with storing a few frames/sprites of data in RAM, the `drawSprite()` method expects an array stored in program memory and will not work with an array stored in dynamic memory. Due to the fact that arrays MUST be stored in program memory, they are inherently immutable.*

## Drawing Frames
```c++
void drawFrame(bool frame[], bool clearFirst, bool inverted=false)
```
Drawing a frame works in much the same way as drawing a sprite but we can assume that the frame will take up the entire display. Because of this we do not need to provide an x or y value and we also don't need to describe the width or height. 

* frame - contains an array of boolean pixel values with a length equal to the area of your display (in "pixels")
* clearFirst - should the previous display buffer be cleared before drawing?
* inverted - Invert the "pixel values"

Defining a frame works like this:
```c++
const bool frameX[256] PROGMEM = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,
0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,1,1,1,1,
1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
```
Drawing the frame might look like this:
```c++
matrix.drawFrame(frameX,true);
```

Drawing a series of frames (an animation) might look like:
```c++
matrix.drawFrame(frame1,true);
matrix.delayF();
matrix.drawFrame(frame2,true);
matrix.delayF();
matrix.drawFrame(frame3,true);
matrix.delayF();
```

Once again, you can think of the frame data as being a direct representation of the pixel matrix (assuming you lay it out in the same manner). 

The first value represents the "pixel" 0,7 (This library uses zero-based counting). The second value represents pixel 1,7 and so on. The last value represents 32,0. 

While you do not have to write out your array to match the columns and rows of your screen, the array length must be equal to the area of your display. 

So, if your display is 32x8 your array MUST have a length of 256. If your display is 8x8 your array MUST have length of 16.

## Drawing A Character
```C++
void drawChar(char c, int x, int y, inverted=false);
```
* c - Character to draw (A->Z)
* x - X position to draw the number at
* y - y position to draw the number at
* inverted - Invert the "pixel values"

You can draw any capital (uppercase) letter between A and Z. You can also draw a colon. 

Example:
```c++
drawChar('A', 1, 1);
```

Characters are 4 "pixels" wide so if you want to space them out appropriately you should but a horizontal space of at least 5 "pixels" between each character. 

Example:
```c++
drawChar('A', 1, 1);
drawChar('B', 6, 1);
drawChar('C', 11, 1);
```

## Drawing A Number
```C++
void drawNum(int n, int x, int y, inverted=false);
```

* n - Number to draw (0->9)
* x - X position to draw the number at
* y - y position to draw the number at
* inverted - Invert the "pixel values"

This works much like drawing a sprite.  Just provide a number between 0 and 9 and tell it where to draw at. 

*Note: At this time all built-in number sprites are 4 "pixels" wide and 6 "pixels" high.*

## Drawing A String
```C++
void drawString(String str, int length=6);
```

Draw a string on the display. The length can be greater than your actual string length.  

*Note: At this time the string will be left justified. You can pad with spaces at the beginning if needed.*

## Setting LED Intensity (Brightness)
```C++
void setIntensity(int intensity);
```

The value of `intensity` should be 0 through 15.

*Note: The default value is 0 (zero).*

## Setting Frame Rate
```c++
void setFrameRate(int fr);
```

The argument given for `fr` is the frame rate in 'frames per second'. 

## Following A Frame Rate
```c++
void delayF();
```
Used to delay from some time between drawing of frames or other items. The time delayed is based on the frame rate set with `setFrameRate()`.

## Delaying Several Frames
```c++
void delayN(int n);
```
Used to delay for `n` frames. 

## Clearing The Display
```c++
void clear();
```
Removes everything from the display.

## Locking The Display
```c++
void lock();
```

When preforming a long series of draw operations you might wish to lock the display so that the updates are written to the display buffer but not displayed on the device. 

To use this method effectively you need to lock the display, then clear it, write to the display, then unlock it. 

Consider this example:
```c++
void randomNoise(){
  int X = matrix.lenX();
  int Y = matrix.lenY();
  matrix.lock();
  matrix.clear();
  for(int i = 0; i<(X*Y); i++){
    matrix.mx->setPoint(random(Y), random(X), true); 
  }
  matrix.unlock();
  matrix.delayF();
}
```
Without using the `lock()` method, you will probably have issues with the display flickering. 

## Unlocking The Display
```c++
void unlock();
```

Unlock the display after locking it.

## Getting Display X Length
```c++
int lenX();
```

Returns the X length of the display

## Getting Display Y Length
```c++
int lenY();
```

Returns the Y length of the display

## Lower Level Operations
If you wish to access the underlying `MD_MAX72xx` library directly, you can use the pointer `mx`.

Example:

```c++
#include <MatrixGL.h>

#define CS_PIN 10
#define MAX_DEVICES 4
#define LENGTHX 32
#define LENGTHY 8
#define INTENSITY 0

MatrixGL matrix(CS_PIN,MAX_DEVICES, LENGTHX, LENGTHY, INTENSITY);

void loop(){
  matrix.mx->setPoint(1, 1, true);
}
```