An Arduino Microcontroller Library For LED Dot Matrix Displays

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

Line drawing is preformed by a custom [digital differential analyzer (DDA)](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) implementation. 

## Setup

```c++
#include <MatrixGL.h>

#define CS_PIN 10 // The CS Pin for your device, may need changing
#define MAX_DEVICES 4 // How many matrix Blocks are connected?
#define LENGTHX 32 // How many LEDs on the X axis?
#define LENGTHY 8 // How many LEDs on the Y axis?

MatrixGL matrix(CS_PIN,MAX_DEVICES,LENGTHX,LENGTHY);
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
  matrix.lock();// Lock the display
  matrix.clear();// Clear the display
  matrix.drawPath(points, 8);// Draw a path from the given points
  matrix.unlock();// Unlock the display
}
```

## Animation Frames
The syntax for drawing frames is this:
```c++
drawFrame(bool frame[], bool clearFirst)
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
drawFrame(frameX,true);
```

You can more or less think of the frame data as being a direct representation of the pixel matrix (assuming you lay it out in the same manner). 

The first value represents the "pixel" 0,7 (This library uses zero-based counting). The second value represents pixel 1,7 and so on. The last value represents 32,0. 

While you do not have to write out your array to match the columns and rows of your screen, the array length must be equal to the area of your display. 

So, if your display is 32x8 your array MUST have a length of 256. If your display is 8x8 your array MUST have length of 16.

*Also notice that the array is being stored in program memory by the use of `PROGMEM` [More Info](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/). This is because frame data is much too large to store in RAM. While it would be technically possible to get away with storing a few frames of data in RAM, the `drawFrame()` method expects an array stored in program memory and will not work with an array stored in dynamic memory. Due to the fact that arrays MUST be stored in program memory, they are inherently immutable.*

