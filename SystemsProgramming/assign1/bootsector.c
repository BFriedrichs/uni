#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOV_TO_AH 0xB4
#define MOV_TO_AL 0xB0

#define MOV_TO_BH 0xB7
#define MOV_TO_BL 0xB3

#define MOV_TO_CH 0xB5
#define MOV_TO_CL 0xB1

#define MOV_TO_DH 0xB6
#define MOV_TO_DL 0xB2

int to_relative(int addr) {
  return addr >= 0x7C00 ? addr - 0x7C00 : 0;
};
/*
MOV_TO_AH;
0x09;  // interrupt function 0x09 "write Character and Attribute at Current Cursor Position"

MOV_TO_AL;
49;    // == '1'

MOV_TO_BH;
0x00;  // Page 0

MOV_TO_BL;
0x0F;  // Color

MOV_TO_CH;
0x00;  // Repeat factor high

MOV_TO_CL;
0x01;  // Repeat factor low

0x40;  // Op-Code -> Increment AX

0xCD;  // Trigger interrupt
0x10;  // Interrupt 0x10

0xE9;  // JMP relative
0xFD;  // jmp low
0xFF;  // jmp high
*/

uint8_t ops[] = {MOV_TO_AH, 0x09, MOV_TO_AL, 49, MOV_TO_BH, 0x00, MOV_TO_BL, 0x0F, MOV_TO_CH, 0x00, MOV_TO_CL, 0x01, 0x40, 0xCD, 0x10, 0xE9, 0xFD, 0xFF};

int main() {

  FILE *file;
  uint8_t *out = calloc(512, sizeof(uint8_t));

  for(int i = 0; i < sizeof(ops) / sizeof(uint8_t); i++) {
    out[i] = ops[i];
  }

  out[to_relative(0x7DFE)] = 0x55;  // i = 510
  out[to_relative(0x7DFF)] = 0xAA;  // i = 511

  file = fopen("boot.bin", "w+b");

  if(file != NULL) {
    fwrite(out, sizeof(uint8_t), 512, file);

    fclose(file);
  }

  return 0;
}