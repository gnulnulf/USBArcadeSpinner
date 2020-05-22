
#ifndef _HARDWARE_H
#define _HARDWARE_H

/*           -----------
 *          |o         o|-
 *         -|D13     D12|-
 * VCC ROT -|3V3     D11|-
 *         -|REF     D10|-
 *         -|A0       D9|-
 *         -|A1       D8|- 
 *         -|A2       D7|- ROT SW
 *         -|A3       D6|-
 *         -|A4       D5|-
 *         -|A5       D4|-
 *         -|NC       D3|- ROT CLK
 *         -|NC       D2|- ROT DT
 *         -|5V      GND|- 
 *         -|RST     RST|-
 * GND ROT -|GND     RX1|-
 *         -|VIN     TX1|-
 *         -|MISO     SS|-
 *         -|SCK    MOSI|- 
 *          |o         o|
 *           -----------
 */


#define ROTARY_A_CLK 3
#define ROTARY_A_DT 2
#define ROTARY_A_BUTTON1 7
//#define ROTARY_A_BUTTON2 8

#endif
