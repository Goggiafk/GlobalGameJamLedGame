// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#include <Uduino.h>
#include<Uduino_Wifi.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

//BluetoothSerial SerialBT;

BluetoothSerial mySerial; // RX, TX

#define PIN 12

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 255, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 255) };

char* data;
char* datasaved;
int data_length;
int i=0;
int timeout;
int highLow;
char* send_data;

void setup() {
  mySerial.begin(115200);
  mySerial.begin("ESP32 Badge");
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  Serial.begin(115200);
  //matrix.fillScreen(colors[0]);
  matrix.drawPixel(0, 0, colors[0]); 
  matrix.show();
  delay(3000);
  matrix.clear();
  matrix.fillScreen(0);
  matrix.setCursor(-24, 0);

  matrix.setTextColor(colors[1]);
 
}

void readBT()
{
  if(mySerial.available() >= 2)
  {
    timeout=0;
    data_length = 0;
    byte pre1 = mySerial.read();
    byte pre2 = mySerial.read();
    if(pre1 != 85 || pre2 != 85) return;
    while(mySerial.available() < 2) continue;
    byte x1 = mySerial.read();
    byte x2 = mySerial.read();

    data_length = x1 << 8 | x2;
    
    data = new char[data_length];
    i=0;
    while(i<data_length)
    {
        
      if(mySerial.available()==0){
        if(++timeout == 1000)
          goto FreeData;
        continue;
      }
      timeout=0;
      data[i++] = mySerial.read();
    }

    send_data = new char[data_length+1];
    send_data[0] = 'S';
    for(byte i=0; i<2;i++)
      send_data[i+1] = data[i];

    Serial.write(data);
    //Display.displayScroll(send_data, PA_CENTER, PA_SCROLL_LEFT, 100);

    sendBT(send_data, data_length+1);
    delete [] send_data;

    FreeData:
    delete[] data;
  }
}

int x    = matrix.width();
int pass = 0;

void loop() {
  

  //Serial.print(mySerial.readString());
  matrix.flush();
  matrix.print(mySerial.readString());
  mySerial.flush();
  matrix.show();
  
  // if(--x < -46) {
  //    x = matrix.width();
  //  }
  //    if(++pass >= 3) pass = 0;
  //    matrix.setTextColor(colors[pass]);
  // }
  // matrix.show();
  //readBT();
  //Serial.write(mySerial.read());

  //colorWipe(50);
  
  delay(150);
  // delay(1000);

  // drawLogo();
  // delay(2000);
}

void colorWipe(uint8_t wait) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 32; column++) {
      matrix.drawPixel(column, row, matrix.Color(255, 255, 255));
      matrix.show();
      delay(wait);
    }
  }
}

void fadePixel(int x, int y, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
     matrix.drawPixel(x, y, matrix.Color(255, 255, 255));
     matrix.show();
     delay(wait);
  }
}

void drawLogo() {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {  
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
  };

  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(logo[row][column] == 1) {
       fadePixel(column, row, 120, 0);
     }
   }
  }
}



void sendBT(const char * data, int l)
{
  // byte len[4];
  // len[0] = 85;//preamble
  // len[1] = 85;//preamble
  // len[2] = (l >> 8) & 0x000000FF;
  // len[3] = (l & 0x000000FF);
  // mySerial.write(len, 4);
  // mySerial.flush();
  // mySerial.write((const uint8_t*)data, l);
  // mySerial.flush();
}



// void loop() {
//   readBT();
// }



