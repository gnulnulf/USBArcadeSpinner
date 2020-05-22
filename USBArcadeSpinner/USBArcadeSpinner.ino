/*
 * USB Arcade Spinner v1.0 for Arduino
 *
 * 32u4 as USB HID with serial setup menu
 *
 * Copyright 2020 by Arco van Geest <arco@appeltaart.mine.nu>
 *
 * 20200522 Initial version
 *
 * License: GPLv3. See license.txt
 */

//#define NOMOUSE 1
//#define SERIALDEBUG 1


#include "USBArcadeSpinner.h"


int spinnerSlow;
int mouseStep; 
int spinnerLsr; 

// setup encoder
Encoder myEnc(  ROTARY_A_DT, ROTARY_A_CLK);

/*
 * Setup
 */
void setup() {
    #ifndef NOMOUSE
  Mouse.begin();
  #endif
  
  // initialize serial port
  serialInit();
  // show version
  cmd_startline("");
  cmd_load("");
  // initialize the buttons' inputs:
    pinMode(ROTARY_A_BUTTON1, INPUT_PULLUP);
    pinMode(CONFIG_ENABLE, INPUT_PULLUP);


  // initialize mouse control:

}


/*
 * LOOP
 */
long oldPosition  = -999;
long spinnermilis = millis();
int oldButton1 = 0;


void loop() {
  //button1
  int button1 = digitalRead(ROTARY_A_BUTTON1);
  if ( button1 != oldButton1 ) {
    #ifdef SERIALDEBUG
    Serial.print("button1: ");
    Serial.println( button1 );
    #endif
    oldButton1 = button1; 


    #ifndef NOMOUSE
      // if the mouse button is pressed:
  if (button1 == SPINNER_BUTTON1_ACTIVE ) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
  #endif
  }
  // movement
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    long time = millis() - spinnermilis;
    int step =0;
    int direction = -1;
    if ( newPosition > oldPosition ) {
      direction = 1;
    }
    
    oldPosition = newPosition;

    if ( time > spinnerSlow ) {
      step = mouseStep;
    } else {
      step = (( (spinnerSlow - time)>>spinnerLsr )+1) * mouseStep;
    }
    
#ifdef SERIALDEBUG
    Serial.print("POS: ");
    Serial.print(newPosition);
    Serial.print("  TIME: ");
    Serial.print(time);

    Serial.print("  STEP: ");
    Serial.println(step* direction);
    #endif

#ifndef NOMOUSE
    Mouse.move(step* direction, 0);

#endif
    
    spinnermilis = millis();
  }
  // Serial
  int configenable = digitalRead(CONFIG_ENABLE);
  if ( configenable == LOW ) {
    serialEvent(); //call the function
  }
} //loop
