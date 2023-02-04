#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
//#include <RGBmatrixPanel.h> 
//#include <Adafruit_TFTLCD.h>
#include <Fonts/CyberFont__1_8pt7b.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 12


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(0, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 255, 0), matrix.Color(0, 255, 0), matrix.Color(255, 0, 0)};

const uint16_t mapColor[8][32] = {
  {colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2]},
  {colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[0], colors[5], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[4], colors[0], colors[2]},
  {colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2]},
};



int walls[8][32] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

const uint16_t graphic1[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 255, 255), matrix.Color(255, 255, 255), matrix.Color(255, 255, 255), matrix.Color(255, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 255, 0), matrix.Color(185.4841, 0, 0), matrix.Color(185.4841, 0, 0), matrix.Color(185.4841, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 255, 255), matrix.Color(255, 0, 0), matrix.Color(255, 255, 255), matrix.Color(255, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 155.0668, 255), matrix.Color(255, 255, 0), matrix.Color(0, 155.0668, 255), matrix.Color(255, 255, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(255, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), },
{matrix.Color(0, 0, 0), matrix.Color(255, 255, 15.91163), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 255, 15.91163), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), },
{matrix.Color(0, 0, 0), matrix.Color(255, 255, 15.91163), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 255, 15.91163), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(131.9745, 91.67272, 0), matrix.Color(0, 0, 0), },
};

const uint16_t sword[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(91.49006, 138.1157, 133.9306), matrix.Color(91.49006, 138.1157, 133.9306), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(91.49006, 138.1157, 133.9306), matrix.Color(91.49006, 138.1157, 133.9306), matrix.Color(94.50335, 136.0686, 132.3377), matrix.Color(48.73258, 205.669, 191.5824), matrix.Color(94.50335, 136.0686, 132.3377), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(248.7519, 255, 254.4392), matrix.Color(48.73258, 205.669, 191.5824), matrix.Color(91.49006, 138.1157, 133.9306), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(248.7519, 255, 254.4392), matrix.Color(248.7519, 255, 254.4392), matrix.Color(248.7519, 255, 254.4392), matrix.Color(91.49006, 138.1157, 133.9306), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(248.7519, 255, 254.4392), matrix.Color(248.7519, 255, 254.4392), matrix.Color(248.7519, 255, 254.4392), matrix.Color(0, 0, 0), matrix.Color(94.50335, 136.0686, 132.3377), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(248.7519, 255, 254.4392), matrix.Color(248.7519, 255, 254.4392), matrix.Color(248.7519, 255, 254.4392), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(248.7519, 255, 254.4392), matrix.Color(248.7519, 255, 254.4392), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

uint16_t currentMap[8][32];
int playerPosition[] = {15, 4};
int yTextOffset = 7;
char defChar = '`';
String text = "";

int replicaCount = 0;
const String firstNPCtext[] = {"Hello!", "I'm here", "To find", "My roots", "Oh!", "Are you", "John69?"};
const uint16_t firstNPCcolor[] = {colors[1], colors[1], colors[1], colors[1], colors[4], colors[4], colors[4]};

int slayedEnemies = 0;

void setup() {
 Serial.begin(9600);
  SerialBT.begin(9600);
  SerialBT.begin("ESP32 Badge");
  Serial.println("The device started, now you can pair it with bluetooth!");
  matrix.begin();
  matrix.setTextWrap(true);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  Serial.begin(9600);
  //matrix.fillScreen(colors[0]);
  
  delay(3000);

  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
      currentMap[j][i] = mapColor[j][i];
    }
  }

  matrix.clear();
  matrix.setFont(&CyberFont__1_8pt7b);
  matrix.fillScreen(0);
  matrix.setCursor(0, yTextOffset);
  matrix.setTextColor(colors[2]);
  

  DrawLevel();
  //StartAttack();

  matrix.drawPixel(playerPosition[0], playerPosition[1], colors[1]);

  //matrix.
  uint32_t dim_color = matrix.getPixelColor(16)>>1;

  //Serial.print(dim_color);

  matrix.show();

 
#if defined (__AVR_ATmega32U4__) // Leonardo
  while (!Serial) {}
#elif defined(__PIC32MX__)
  delay(1000);
#endif

}

void LoadNewText() {
  char *arg = NULL;
  //arg = uduino.next();
  //char *arg[SerialBT.readStringUntil("`").length() + 1];// = NULL;
  //Until('`').toCharArray(arg, SerialBT.readStringUntil('`').length() + 1);
  
    matrix.clear();
    matrix.setTextWrap(true);
    matrix.fillScreen(0);
    matrix.setCursor(0, yTextOffset);
    
    //text = SerialBT.readStringUntil(defChar);
    text = SerialBT.readStringUntil(defChar);

    //matrix.setRotation(90);
    matrix.print(text);
    //Serial.println(SerialBT.readString());
    matrix.show();
    SerialBT.flush();
    //Display.displayClear();
    //Display.displayScroll("Aaaaa",PA_RIGHT,PA_SCROLL_LEFT,100);
    //replacechar(dupaText, '_', ' ');
    // for (size_t i = 0; i < TABLEN; i++)
    // {
    //   if(arg[i] == '`'){
    //     arg[i] = ' ';
    //   }
    // }
    // strncpy(dupaText,arg,TABLEN);
    // Display.displayScroll(dupaText, state, scrollState, scrollSpeed);
    
  
  //Display.displayScroll("Hello there", PA_RIGHT, PA_SCROLL_LEFT, 100);
}

void SetTextColor(){
  int r = atoi(SerialBT.readStringUntil(defChar).c_str());
  int g = atoi(SerialBT.readStringUntil(defChar).c_str());
  int b = atoi(SerialBT.readStringUntil(defChar).c_str());
  matrix.setTextColor(matrix.Color(r, g, b));
  matrix.print(text);
  matrix.show();
  SerialBT.flush();
}

void PaintPixels(){
  paint:
  int xPosition = atoi(SerialBT.readStringUntil(defChar).c_str());
  int yPosition = atoi(SerialBT.readStringUntil(defChar).c_str());
  int r = atoi(SerialBT.readStringUntil(defChar).c_str());
  int g = atoi(SerialBT.readStringUntil(defChar).c_str());
  int b = atoi(SerialBT.readStringUntil(defChar).c_str());
  Serial.println(xPosition);
  Serial.println(yPosition);
  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
  matrix.drawPixel(xPosition, yPosition, matrix.Color(r, g, b)); 
  matrix.show();

  if(SerialBT.readStringUntil(defChar) == "pp") goto paint;

  
  else SerialBT.flush();
}

void ChangePower() {
    matrix.setBrightness(atoi(SerialBT.readStringUntil(defChar).c_str()));
    matrix.show();
    SerialBT.flush();
}

void DrawLevel(){
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
      matrix.drawPixel(i, j, currentMap[j][i]);
      if(currentMap[j][i] == colors[2])
        walls[j][i] = 1;
      else if(currentMap[j][i] == colors[4])
        walls[j][i] = 2;
      else if(currentMap[j][i] == colors[5])
        walls[j][i] = 3;
      else
        walls[j][i] = 0;
    }
  }
}

void DrawCurrentLevel(){
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
      matrix.drawPixel(i, j, currentMap[j][i]);
    }
  }
}

void DrawIgnoreBlack(){
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
      if(currentMap[j][i] != colors[0])
        matrix.drawPixel(i, j, currentMap[j][i]);
    }
  }
}

void MovePlayer() {
    int xDirection = atoi(SerialBT.readStringUntil(defChar).c_str());
    int yDirection = atoi(SerialBT.readStringUntil(defChar).c_str());

    if(walls[playerPosition[1] + yDirection][playerPosition[0] + xDirection] == 0){
      
      matrix.drawPixel(playerPosition[0], playerPosition[1], colors[0]);
      playerPosition[0] += xDirection;
      playerPosition[1] += yDirection;
      matrix.drawPixel(playerPosition[0], playerPosition[1], colors[1]);
      matrix.show();
    } else if(walls[playerPosition[1] + yDirection][playerPosition[0] + xDirection] == 2){ 
      ContinueReplica();
      SerialBT.println("medium");
    } else if(walls[playerPosition[1] + yDirection][playerPosition[0] + xDirection] == 3){ 
      SerialBT.println("high");
      
      StartAttack();
      MovePlayer();
    }
    
    SerialBT.flush();
}

void ContinueReplica(){
  if(replicaCount < 7){
    matrix.setRotation(90);
    matrix.setTextWrap(true);
    matrix.fillScreen(0);
    matrix.setCursor(0, yTextOffset);
    matrix.clear();
    matrix.setTextColor(firstNPCcolor[replicaCount]);
    matrix.print(firstNPCtext[replicaCount]);
    replicaCount++;
    matrix.show();
  } else {
    SerialBT.println("low");
    matrix.setRotation(0);
    matrix.setTextWrap(false);
    matrix.fillScreen(0);
    matrix.setCursor(0, yTextOffset);
    matrix.clear();
    replicaCount = 0;
    
    DrawCurrentLevel();
    matrix.drawPixel(playerPosition[0], playerPosition[1], colors[1]);
    matrix.show();
  }
  
  SerialBT.flush();
}

void StartAttack(){
  matrix.clear();
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
      if(graphic1[j][i] != colors[0])
        matrix.drawPixel(i, j, graphic1[j][i]);
    }
  }
  // delay(3000);
  // for(int i = 18; i < 25; i++){
  //     for(int j = 0; j < matrix.height(); j++){
  //       if(sword[j][i] != colors[0])
  //         matrix.drawPixel(i, j, sword[j][i]);
  //     }
  //   }
  SerialBT.flush();
}

void PickWeapon(){
  int weaponType = atoi(SerialBT.readStringUntil(defChar).c_str());
  matrix.flush();
  if(weaponType == 0){
    for(int i = 18; i < 25; i++){
      for(int j = 0; j < 8; j++){
        if(sword[j][i] != colors[0])
          matrix.drawPixel(i, j, sword[j][i]);
      }
    }
  }
  if(weaponType == 1);
  if(weaponType == 2);
  
}

void AttackEnemy(){
  StopAttack();
  SerialBT.flush();
}

void StopAttack(){
  matrix.clear(); 
  if(slayedEnemies == 0) currentMap[3][2] = colors[0];
  DrawLevel();
  matrix.drawPixel(playerPosition[0], playerPosition[1], colors[1]);
  matrix.show();
  SerialBT.println("low");
  SerialBT.flush();
}

void loop() {
  String command = "";
  command = SerialBT.readStringUntil(defChar);
  Serial.print(command);
  if(command == "lnt") LoadNewText();
  if(command == "cp") ChangePower();
  if(command == "pp") PaintPixels();
  if(command == "cl"){ matrix.clear(); matrix.show();}
  if(command == "stc") SetTextColor();
  if(command == "pw") PickWeapon();
  if(command == "mp") MovePlayer();
  if(command == "cr") ContinueReplica(); 
  if(command == "ae") AttackEnemy();

  //matrix.drawRGBBitmap(0, 0, "/Level1.bmp", 32, 8);
  //matrix.show();
  
}
