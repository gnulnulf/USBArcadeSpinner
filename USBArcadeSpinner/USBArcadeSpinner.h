/*
 * USB Arcade Spinner for Arduino
 *
 *
 * Copyright 2020 by Arco van Geest <arco@appeltaart.mine.nu>
 *
 * 20200522 Initial version
 *
 * License: GPLv3. See license.txt
 */


#ifndef _USBARCADESPINNER_H
#define _USBARCADESPINNER_H

#define BVERSION "20200522"



// if mouse.h not found, probably no leonardo selected
#include <Mouse.h>

// EEprom for saving settings
#include <EEPROM.h>

// encoder from Paul Stoffregen
#include <Encoder.h>

// hardware defines pins
#include "hardware.h"

// serial menu
#include "SerialCommands.h"


// defaults
// everything above SPINNER_SLOW is just a single step
#define SPINNER_SLOW 32

//single step
#define MOUSE_STEP 1

#define SPINNER_ACCELERATION_LSR 1 

#define SPINNER_BUTTON1_ACTIVE LOW

#define CONFIGMAGIC 0x05b501e7

struct USBSpinner {
  long eepromMagic=CONFIGMAGIC;
  int spinnerSlow=SPINNER_SLOW;
  int mouseStep=MOUSE_STEP; 
  int spinnerLsr=SPINNER_ACCELERATION_LSR; 
};

extern int spinnerSlow;
extern int mouseStep; 
extern int spinnerLsr; 

#endif
