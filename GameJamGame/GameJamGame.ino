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
  matrix.Color(0, 0, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 255, 0), matrix.Color(0, 255, 0), matrix.Color(255, 0, 0), matrix.Color(255, 128, 0), matrix.Color(255, 51, 255)};

uint16_t mapColor[8][32] = {
  {colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2]},
  {colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[2], colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[6], colors[0], colors[0], colors[0], colors[5], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[4], colors[0], colors[2]},
  {colors[6], colors[0], colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[2], colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[0], colors[2]},
  {colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2], colors[2]},
};

uint16_t level1[8][32] = {
  {matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), },
  {matrix.Color(0, 17.76037, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(255, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 255), },
  {matrix.Color(0, 17.76037, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 17.76037, 255), },
  {colors[6], matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(120.1115, 0, 0), },
  {colors[6], matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0),  matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(120.1115, 0, 0), },
  {matrix.Color(0, 17.76037, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(255, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), },
  {matrix.Color(0, 17.76037, 255), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(11.17019, 0, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 255), },
  {matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), matrix.Color(0, 0, 255), },
};

uint16_t finalLoc[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(127.8804, 85.76006, 8.742427), matrix.Color(127.8804, 85.76006, 8.742427), matrix.Color(255, 51, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(127.8804, 85.76006, 8.742427), matrix.Color(127.8804, 85.76006, 8.742427), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(127.8804, 85.76006, 8.742427), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 171.489, 0), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(121.7392, 81.29609, 7.345317), matrix.Color(0, 171.489, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
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

const uint16_t shield[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(76.31123, 142.4396, 136.8117), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(76.31123, 142.4396, 136.8117), matrix.Color(53.8583, 204.6203, 191.7895), matrix.Color(76.31123, 142.4396, 136.8117), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(76.31123, 142.4396, 136.8117), matrix.Color(53.8583, 204.6203, 191.7895), matrix.Color(76.31123, 142.4396, 136.8117), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(76.31123, 142.4396, 136.8117), matrix.Color(53.8583, 204.6203, 191.7895), matrix.Color(76.31123, 142.4396, 136.8117), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(143.7458, 160.728, 159.2827), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t torch[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(218.8692, 0, 0), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(142.4396, 82.92654, 2.758317), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(218.8692, 0, 0), matrix.Color(179.5016, 217.9397, 0), matrix.Color(179.5016, 217.9397, 0), matrix.Color(218.8692, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(218.8692, 0, 0), matrix.Color(218.8692, 0, 0), matrix.Color(179.5016, 217.9397, 0), matrix.Color(217.9397, 28.66906, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(218.8692, 0, 0), matrix.Color(218.8692, 0, 0), matrix.Color(217.9397, 28.66906, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t enemySword[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(160.728, 106.8583, 106.8583), matrix.Color(160.728, 106.8583, 106.8583), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(157.0703, 93.16157, 93.16157), matrix.Color(255, 0, 0), matrix.Color(160.728, 106.8583, 106.8583), matrix.Color(160.728, 106.8583, 106.8583), matrix.Color(160.728, 106.8583, 106.8583), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(160.728, 106.8583, 106.8583), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(160.728, 106.8583, 106.8583), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(157.0703, 93.16157, 93.16157), matrix.Color(0, 0, 0), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(244.8549, 176.8379, 176.8379), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t enemyShield[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(248.5126, 101.0575, 101.0575), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(248.5126, 101.0575, 101.0575), matrix.Color(248.5126, 101.0575, 101.0575), matrix.Color(248.5126, 101.0575, 101.0575), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(248.5126, 101.0575, 101.0575), matrix.Color(226.5665, 59.63476, 59.63476), matrix.Color(248.5126, 101.0575, 101.0575), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(226.5665, 59.63476, 59.63476), matrix.Color(226.5665, 59.63476, 59.63476), matrix.Color(226.5665, 59.63476, 59.63476), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(248.5126, 101.0575, 101.0575), matrix.Color(226.5665, 59.63476, 59.63476), matrix.Color(237.5395, 147.7039, 147.7039), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(189.9896, 137.2133, 137.2133), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t enemyTorch[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(112.9391, 124.1512, 0), matrix.Color(0, 193.3269, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 193.3269, 255), matrix.Color(253.9171, 255, 0), matrix.Color(253.9171, 255, 0), matrix.Color(0, 193.3269, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 193.3269, 255), matrix.Color(253.9171, 255, 0), matrix.Color(0, 193.3269, 255), matrix.Color(0, 193.3269, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 193.3269, 255), matrix.Color(0, 193.3269, 255), matrix.Color(0, 193.3269, 255), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};


///ANIMATIONS

const uint16_t rootFrame1[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t rootFrame2[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t rootFrame3[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t rootFrame4[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t rootFrame5[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t rootFrame6[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

const uint16_t rootFrame7[8][32] = {
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(205.6691, 103.2379, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(255, 128.0001, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(226.1398, 113.5134, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(193.3866, 97.07261, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(179.0571, 89.87976, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(166.7747, 84.05853, 0.6908485), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
{matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(148.3511, 74.46651, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), matrix.Color(0, 0, 0), },
};

uint16_t currentMap[8][32];
int playerPosition[] = {15, 4};
int yTextOffset = 7;
char defChar = '`';
String text = "";

int replicaCount = 0;
int replicaNumber = 0;
const String firstNPCtext[] = {"Hello!", "I'm here", "to find", "my", "roots", "Oh!", "I know", "you!", "son", "of the", "kings!", "You", "have", "to go", "further", "in the", "forest", "Thanks!", "Good", "Luck!"};
const uint16_t firstNPCcolor[] = {colors[1], colors[1], colors[1], colors[1], colors[1], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[1], colors[4], colors[4]};

const String finalNPCtext[] = {"Here's", "the", "tree", "which", "belongs", "to your", "family", "take a", "moment", "I will."};
const uint16_t finalNPCcolor[] = {colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[4], colors[1]};


int enemyPosition[] = {0, 0};
int playerWeapon = 0;
int enemyWeapon = 0;
int levelNumber = 0;

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
      if(currentMap[j][i] == colors[4])
        walls[j][i] = 2;
      else if(currentMap[j][i] == colors[5])
        walls[j][i] = 3;
      else if(currentMap[j][i] == colors[6])
        walls[j][i] = 4;
      else if(currentMap[j][i] == colors[7])
        walls[j][i] = 5;
      else if(currentMap[j][i] == colors[0])
        walls[j][i] = 0;
      else
        walls[j][i] = 1;
    }
  }
  matrix.drawPixel(playerPosition[0], playerPosition[1], colors[1]);
  matrix.show();
}

// void DrawCurrentLevel(){
//   for(int i = 0; i < matrix.width(); i++){
//     for(int j = 0; j < matrix.height(); j++){
//       matrix.drawPixel(i, j, currentMap[j][i]);
//     }
//   }
// }

void playRootAnim(){
  int wai = 1500;
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
        matrix.drawPixel(i, j, rootFrame1[j][i]);
    }
  }
  matrix.show();
  delay(wai);
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
        matrix.drawPixel(i, j, rootFrame2[j][i]);
    }
  }
  matrix.show();
  delay(wai);
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
        matrix.drawPixel(i, j, rootFrame3[j][i]);
    }
  }
  matrix.show();
  delay(wai);
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
        matrix.drawPixel(i, j, rootFrame4[j][i]);
    }
  }
  matrix.show();
  delay(wai);
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
        matrix.drawPixel(i, j, rootFrame5[j][i]);
    }
  }
  matrix.show();
  delay(wai);
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
        matrix.drawPixel(i, j, rootFrame6[j][i]);
    }
  }
  matrix.show();
  delay(wai);
  for(int i = 0; i < matrix.width(); i++){
    for(int j = 0; j < matrix.height(); j++){
        matrix.drawPixel(i, j, rootFrame7[j][i]);
    }
  }
  matrix.show();
  delay(wai*2);
  matrix.setRotation(90);
  matrix.clear();
  matrix.setTextWrap(true);
  matrix.fillScreen(0);
  matrix.setCursor(0, yTextOffset);
  matrix.print("Thank");
  matrix.show();
  delay(wai);
  matrix.setRotation(90);
  matrix.clear();
  matrix.setTextWrap(true);
  matrix.fillScreen(0);
  matrix.setCursor(0, yTextOffset);
  matrix.print("You");
  matrix.show();
  delay(wai);
  matrix.setRotation(90);
  matrix.clear();
  matrix.setTextWrap(true);
  matrix.fillScreen(0);
  matrix.setCursor(0, yTextOffset);
  matrix.print("for");
  matrix.show();
  delay(wai);
  matrix.setRotation(90);
  matrix.clear();
  matrix.setTextWrap(true);
  matrix.fillScreen(0);
  matrix.setCursor(0, yTextOffset);
  matrix.print("playing");
  matrix.show();
  delay(wai);
  matrix.setRotation(90);
  matrix.clear();
  matrix.setTextWrap(true);
  matrix.fillScreen(0);
  matrix.setCursor(0, yTextOffset);
  matrix.print("<3");
  matrix.show();
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
      replicaCount = 0;
      if(replicaNumber == 0)
        ContinueReplica();
      else if(replicaNumber == 1)
        ContinueReplicaFinal();
      SerialBT.println("medium");
    } else if(walls[playerPosition[1] + yDirection][playerPosition[0] + xDirection] == 3){ 
      SerialBT.println("high");
      enemyPosition[1] = playerPosition[1] + yDirection;
      enemyPosition[0] = playerPosition[0] + xDirection;

      StartAttack();
    } else if(walls[playerPosition[1] + yDirection][playerPosition[0] + xDirection] == 4){ 
      matrix.drawPixel(playerPosition[0], playerPosition[1], colors[0]);
      playerPosition[0] = 30;
      playerPosition[1] = 4;
      levelNumber++;
      ChangeLevel();
      DrawLevel();
      matrix.show();
    } else if(walls[playerPosition[1] + yDirection][playerPosition[0] + xDirection] == 5){ 
      playRootAnim();
    } 
    
    SerialBT.flush();
}

void ChangeLevel(){
  if(levelNumber == 0){
    for(int i = 0; i < matrix.width(); i++){
      for(int j = 0; j < matrix.height(); j++){
        currentMap[j][i] = mapColor[j][i];
      }
    }
  }
  if(levelNumber == 1){
    for(int i = 0; i < matrix.width(); i++){
      for(int j = 0; j < matrix.height(); j++){
        currentMap[j][i] = level1[j][i];
      }
    }
  }
  if(levelNumber == 2){
    for(int i = 0; i < matrix.width(); i++){
      for(int j = 0; j < matrix.height(); j++){
        currentMap[j][i] = finalLoc[j][i];
      }
    }
  }
  
}

void ContinueReplica(){
  
  if(replicaCount < 20){
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
    replicaNumber++;
    DrawLevel();
    matrix.drawPixel(playerPosition[0], playerPosition[1], colors[1]);
    matrix.show();
  }
  
  SerialBT.flush();
}

void ContinueReplicaFinal(){
  
  if(replicaCount < 10){
    matrix.setRotation(90);
    matrix.setTextWrap(true);
    matrix.fillScreen(0);
    matrix.setCursor(0, yTextOffset);
    matrix.clear();
    matrix.setTextColor(finalNPCcolor[replicaCount]);
    matrix.print(finalNPCtext[replicaCount]);
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
    replicaNumber++;
    DrawLevel();
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
  matrix.show();
  SerialBT.flush();
}

void PickWeapon(){
  playerWeapon = atoi(SerialBT.readStringUntil(defChar).c_str());
  
  if(playerWeapon == 0){
    for(int i = 18; i < 25; i++){
      for(int j = 0; j < 8; j++){
          matrix.drawPixel(i, j, sword[j][i]);
      }
    }
    
  }
  if(playerWeapon == 1){
    for(int i = 18; i < 25; i++){
      for(int j = 0; j < 8; j++){
          matrix.drawPixel(i, j, shield[j][i]);
      }
    }
  }
  if(playerWeapon == 2){
    for(int i = 18; i < 25; i++){
      for(int j = 0; j < 8; j++){
          matrix.drawPixel(i, j, torch[j][i]);
      }
    }
  }
  matrix.show();
}

void AttackEnemy(){
  EnemyRespond();
  SerialBT.flush();
}

void EnemyRespond(){
  enemyWeapon = random(3);

  if(enemyWeapon == 0){
    for(int i = 7; i < 15; i++){
      for(int j = 0; j < 8; j++){
          matrix.drawPixel(i, j, enemySword[j][i]);
      }
    }
    
  }
  if(enemyWeapon == 1){
    for(int i = 7; i < 15; i++){
      for(int j = 0; j < 8; j++){
          matrix.drawPixel(i, j, enemyShield[j][i]);
      }
    }
  }
  if(enemyWeapon == 2){
    for(int i = 7; i < 15; i++){
      for(int j = 0; j < 8; j++){
          matrix.drawPixel(i, j, enemyTorch[j][i]);
      }
    }
  }
  matrix.show();
  delay(1500);

  if((playerWeapon == 0 && enemyWeapon == 2) || (playerWeapon == 1 && enemyWeapon == 0) || (playerWeapon == 2 && enemyWeapon == 1)) currentMap[enemyPosition[1]][enemyPosition[0]] = colors[0];

  StopAttack();
}

void StopAttack(){
  matrix.clear(); 
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
  if(command == "cr") {
    if(replicaNumber == 0)
        ContinueReplica();
    else if(replicaNumber == 1)
        ContinueReplicaFinal();
  }
  if(command == "ae") AttackEnemy();

  //matrix.drawRGBBitmap(0, 0, "/Level1.bmp", 32, 8);
  //matrix.show();
  
}
