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

#ifndef _SERIAL_COMMANDS2_H
#define _SERIAL_COMMANDS2_H

#include <Arduino.h>

#include "USBArcadeSpinner.h"

//#include "commands.h"

void serialInit();
// serial

void func ( void (*f)(int ) );
extern String inputString;         // a string to hold incoming data
extern boolean stringComplete;  // whether the string is complete



void serialEvent();


// --------------------------------------------------------
// Standard Includes
// --------------------------------------------------------
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <inttypes.h>
//#include <String>
//
//#include <Wire.h>

typedef void (*voidFunction) (void);
typedef void (*functiontype)();
typedef void (*voidStringArrayFunction) (String param[],int paramCount);
typedef void (*voidStringFunction) (String param);
typedef int (*intStringFunction) (String param);
typedef void (*voidIntFunction) (int param);

typedef struct  {
  String name;
  voidStringFunction func;
  int arguments;
  String help;
} Command;

typedef struct  {
  String name;
  intStringFunction func;
  int arguments;
  String help;
} intCommand;

void parseCommand(String cmd, String param);

void help(String param );
void cmd_version(String param );
void cmd_startline(String param );
void ping(String param );

void cmd_setMouseStep(String param);
void cmd_setSpinnerSlow(String param);
void cmd_setSpinnerLsr(String param);
void cmd_defaults(String param);
void cmd_showconfig(String param);
void cmd_save(String param);
void cmd_corrupt(String param);
void cmd_load(String param);



/*

*/
#endif
