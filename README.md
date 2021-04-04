An Arduino Microcontroller Graphics Library For LED Dot Matrix Displays

Depends on: [MD_MAX_72XX](https://github.com/MajicDesigns/MD_MAX72XX)

## Features
Implemented:
* Frame Based Animation
* Line Drawing
* Path Drawing

Planned:
* Arbitrary Shape Drawing (with fills)
* Display Inversion
* Scrolling & Draw Offsets
* Text Support(?)
* Matrix State Queries

Line drawing is preformed by a custom [digital differential analyzer (DDA)](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) implementation. 

## Setup

```c++
#include <MatrixGL.h>

#define CS_PIN 10 // The CS Pin for your device, may need changing
#define MAX_DEVICES 4 // How many matrix Blocks are connected?
#define LENGTHX 32 // How many LEDs on the X axis?
#define LENGTHY 8 // How many LEDs on the Y axis?

MatrixGL matrix(CS_PIN,MAX_DEVICES, LENGTHX, LENGTHY);
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

## Draw Line
```c++
void drawLine(int x1, int y1, int x2, int y2);
```
Draw a line from the point `x1,y1` to the point `x2,y2`.

Example:
```c++
matrix.drawLine(0, 0, 6, 8);
```

## Draw Path
```c++
void drawPath(int points[], int pointsLen);
```
Draw a path based on the given array of point coordinates. 

Example:
```c++
int points[] = {0,0, 4,4, 7,6, 0,0};
matrix.drawPath(points, 8);
```

*Note: The length of the `points` array should always be an even number. This is not currently enforced.*

## Animation Frames
```c++
void drawFrame(bool frame[], bool clearFirst)
```
* frame - contains an array of boolean pixel values
* clearFirst - should the previous display buffer be cleared before drawing?

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

You can more or less think of the frame data as being a direct representation of the pixel matrix (assuming you lay it out in the same manner). 

The first value represents the "pixel" 0,7 (This library uses zero-based counting). The second value represents pixel 1,7 and so on. The last value represents 32,0. 

While you do not have to write out your array to match the columns and rows of your screen, the array length must be equal to the area of your display. 

So, if your display is 32x8 your array MUST have a length of 256. If your display is 8x8 your array MUST have length of 16.

*Also notice that the array is being stored in program memory by the use of `PROGMEM` [More Info](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/). This is because frame data is much too large to store in RAM. While it would be technically possible to get away with storing a few frames of data in RAM, the `drawFrame()` method expects an array stored in program memory and will not work with an array stored in dynamic memory. Due to the fact that arrays MUST be stored in program memory, they are inherently immutable.*

## Set LED Intensity (Brightness)
```C++
void setIntensity(int intensity);
```

The value of `intensity` should be 0 through 15.

*Note: The default value is 0 (zero).*

## Set Frame Rate
```c++
void setFrameRate(int fr);
```

The argument given for `fr` is the frame rate in 'frames per second'. 

## Delay Frame
```c++
void delayF();
```
Used to delay from some time between drawing of frames or other items. The time delayed is based on the frame rate set with `setFrameRate()`.

## Clear Display
```c++
void clear();
```
Removes everything from the display

## Lock Display
```c++
void lock();
```

When preforming a long series of draw operations you might wish to lock the display so that the updates are written to the display buffer but not displayed on the device. 

## Unlock Display
```c++
void unlock();
```

Unlock the display after locking it.

## Get Display X Length
```c++
int lenX();
```

Returns the X length of the display

## Get Display Y Length
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