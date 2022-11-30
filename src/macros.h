#ifndef W65C02S_ANALYZER_MACROS_H
#define W65C02S_ANALYZER_MACROS_H

#define BAUD_RATE 9600
#define MP_READ_BUFF_SIZE 20

#define MP_W 0
#define MP_R 1

#define MP_RWB_PIN 2
#define MP_CLOCK_PIN 3

#define MP_A0_PIN 22
#define MP_A1_PIN 24
#define MP_A2_PIN 26
#define MP_A3_PIN 28
#define MP_A4_PIN 30
#define MP_A5_PIN 32
#define MP_A6_PIN 34
#define MP_A7_PIN 36
#define MP_A8_PIN 38
#define MP_A9_PIN 40
#define MP_A10_PIN 42
#define MP_A11_PIN 44
#define MP_A12_PIN 46
#define MP_A13_PIN 48
#define MP_A14_PIN 50
#define MP_A15_PIN 52

#define MP_D0_PIN 31
#define MP_D1_PIN 33
#define MP_D2_PIN 35
#define MP_D3_PIN 37
#define MP_D4_PIN 39
#define MP_D5_PIN 41
#define MP_D6_PIN 43
#define MP_D7_PIN 45

#define MP_RST_SEQ_ADDR 0xffff /*Received address indicating a reset sequence*/
#define MP_RST_LB_ADDR 0xfffc /*Received address indicating low byte  set*/
#define MP_RST_HB_ADDR 0xfffd /*Received address indicating high byte set*/
#define MP_RST_INST_COUNT 7 /*Total number of reset instructions*/

#define ADDR_VISUAL_MODE HEX /*Visualize the address in binary or hexadecimal*/
#define DATA_VISUAL_MODE HEX /*Visualize the data in binary or hexadecimal*/

#endif
