
//#include "SerialCommands.h"
//#include "tools.h"
#include "USBArcadeSpinner.h"

String inputString;     // a string to hold incoming data
boolean stringComplete; // whether the string is complete

Command commands[] = {
    {"help", &help, 0, "Show help commands"},
    {"version", &cmd_version, 0, "Show Version"},
    //    {"showradios", &cmd_showradios, 0, "Show configured radios"},

    {"defaults", &cmd_defaults, 0, "Set defaults"},
    {"showconfig", &cmd_showconfig, 0, "Show current settings"},
    {"setspinnerslow", &cmd_setSpinnerSlow, 1, "Set slow value. All slower result in single step (default 32ms)"},
    {"setmousestep", &cmd_setMouseStep, 1, "Set base step (default 1)"},
    {"setspinnerlsr", &cmd_setSpinnerLsr, 1, "Set spinnerlsr step ( time>> n)  (default 1)"},
    {"save", &cmd_save, 0, "save settings to eeprom"},
    {"load", &cmd_load, 0, "load settings from eeprom"},
    {"corrupt", &cmd_corrupt, 0, "corrupt settings to eeprom"},
    {"ping", &ping, 0, "Keep alive test"},
};

// serial
void serialInit()
{
    Serial.begin(57600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.flush();
    inputString = "";       // a string to hold incoming data
    stringComplete = false; // whether the string is complete
} //serialInit

void parseCommand(String cmd, String param)
{
    int found = 0;
    cmd.toLowerCase();
    for (int i = 0; i < (sizeof(commands) / sizeof(Command)); i++)
    {
        if (commands[i].name == cmd)
        {
            commands[i].func(param);
            found = 1;
        }
    }

    if (found == 0)
    {
        Serial.println("Command not found.");
    }

} //parseCommand

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent()
{
    //  while (Serial.available()) {
    if (Serial.available())
    {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        if (inChar == '\n')
        {
            stringComplete = true;
        }
        else
        {
            inputString += inChar;
        }
    }
    if (stringComplete)
    {
        Serial.print("INPUTSTRING:");
        Serial.println(inputString);

        String param = "";
        String cmd = "";
        // command with parameters
        if (inputString.indexOf(" ") > 0)
        {
            Serial.println("MULTICOMMAND");
            cmd = inputString.substring(0, inputString.indexOf(" "));
            param = inputString.substring(inputString.indexOf(" ") + 1);
        }
        else
        {
            cmd = inputString;
        }

        /*
Serial.print("SPLIT#");
Serial.print(cmd);
Serial.print("#");
Serial.print(param);
Serial.println("#");
  */
        parseCommand(cmd, param);
        // clear the string:
        inputString = "";
        stringComplete = false;
    }
}

void help(String param)
{
    Serial.println();
    Serial.println("Known commands");
    Serial.println("==============");
    for (int i = 0; i < (sizeof(commands) / sizeof(Command)); i++)
    {
        Serial.print(commands[i].name);
        Serial.print(" - ");
        Serial.println(commands[i].help);
    }
    Serial.println();
}

void cmd_version(String param)
{

    Serial.print(F("+USBARCADE:VERSION:"));
    Serial.print(BVERSION);
    Serial.println("#");
    //Serial.print("+");
}

void cmd_startline(String param)
{
    Serial.print(F("USB Arcade Spinner VERSION:"));
    Serial.print(BVERSION);
    Serial.println(" type help for list of commands.");
}


void ping(String param)
{
    Serial.println("pong");
}

//cmd_setSpinnerSlow

void cmd_setMouseStep(String param)
{
    int paramint = param.toInt();
    if ( paramint > 0 and paramint<512 ) {
      mouseStep = paramint;
      Serial.print("mousestep set to ");
      Serial.println(paramint);
      cmd_showconfig("");
    } else {
          Serial.println("mousestep error");
    }
}

void cmd_setSpinnerSlow(String param)
{
    int paramint = param.toInt();
    if ( paramint > 0 and paramint<512 ) {
      spinnerSlow = paramint;
      Serial.print("spinnerSlow set to ");
      Serial.println(paramint);
      cmd_showconfig("");
    } else {
          Serial.println("spinnerSlow error");
    }
}

void cmd_setSpinnerLsr(String param)
{
    int paramint = param.toInt();
    if ( paramint > 0 and (2^paramint)< (spinnerSlow+1)  ) {
      spinnerLsr = paramint;
      Serial.print("spinnerLsr set to ");
      Serial.println(paramint);
      cmd_showconfig("");
    } else {
          Serial.println("spinnerLsr error");
    }
}


void cmd_defaults(String param)
{
 spinnerSlow=SPINNER_SLOW;
 mouseStep = MOUSE_STEP; 
 spinnerLsr =SPINNER_ACCELERATION_LSR; 
    Serial.println("defaults set");
}


void cmd_showconfig(String param)
{
    Serial.println("Current settings");
    Serial.println("----------------");
    Serial.print("spinnerSlow: ");
    Serial.println(spinnerSlow);
    Serial.print("mouseStep: ");
    Serial.println(mouseStep);
    Serial.print("spinnerLsr: ");
    Serial.println(spinnerLsr);
}


void cmd_load(String param)
{
    USBSpinner spinnerconfig;
    EEPROM.get(0,spinnerconfig);
    if ( spinnerconfig.eepromMagic == CONFIGMAGIC ) {
    spinnerSlow = spinnerconfig.spinnerSlow;
    mouseStep = spinnerconfig.mouseStep;
    spinnerLsr = spinnerconfig.spinnerLsr;
      Serial.println("Loaded settings");
    } else {
      cmd_defaults("");
      Serial.println("No valid config, defaults loaded");
    }
}

void cmd_save(String param)
{
    USBSpinner spinnerconfig; 
    spinnerconfig.spinnerSlow = spinnerSlow;
    spinnerconfig.mouseStep = mouseStep;
    spinnerconfig.spinnerLsr = spinnerLsr;
    
    //One simple call, with the address first and the object second.
    EEPROM.put(0, spinnerconfig);
    Serial.println("saved settings");

}


void cmd_corrupt(String param)
{
    USBSpinner spinnerconfig; 
    spinnerconfig.eepromMagic = 0;
    spinnerconfig.spinnerSlow = 0;
    spinnerconfig.mouseStep = 0;
    spinnerconfig.spinnerLsr = 0;
    
    //One simple call, with the address first and the object second.
    EEPROM.put(0, spinnerconfig);
    Serial.println("corrupted settings");

}
