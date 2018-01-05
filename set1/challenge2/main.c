/*
 * Cryptopals - Challenge 2
 * Fixed XOR
 * Usage: challenge2 <input1> <input2>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char _hex2Dec(char hex) {
  if ('0' <= hex && hex <= '9') {
    return hex - '0';
  }
  if ('a' <= hex && hex <= 'f') {
    return hex - 'a' + 10;
  }
  if ('A' <= hex && hex <= 'F') {
    return hex - 'A' + 10;
  }

  printf("ERROR converting %c\n", hex);
  exit(-1);
}

unsigned char hex2Dec(char hex_1, char hex_2) {
  return _hex2Dec(hex_1) * 16 + _hex2Dec(hex_2);
}

void fixedXOR(unsigned char *input1, unsigned char *input2, 
              unsigned char *output, int nBytes) {
  for (int i = 0; i < nBytes; i++) {
    output[i] = input1[i] ^ input2[i];
  }
}

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Usage: challenge1 <input1> <input2>\n");
    exit(-1);
  }

  char* strHex1 = argv[1];
  char* strHex2 = argv[2];

  int strHexLen = strlen(strHex1);
  if (strHexLen % 2 != 0) {
    printf("Invalid Input!\n");
    exit(-1);
  }

  if (strHexLen != strlen(strHex2)) {
    printf("Inputs must be of equal length!\n");
    exit(-1);
  }

  int numBytes = strHexLen / 2;
  unsigned char byteArray1[numBytes];
  unsigned char byteArray2[numBytes];
  unsigned char output[numBytes];

  /* Read byte at a time */
  for (int i = 0; i <= strHexLen - 2; i += 2) {
    byteArray1[i / 2] = hex2Dec(strHex1[i], strHex1[i+1]);
    byteArray2[i / 2] = hex2Dec(strHex2[i], strHex2[i+1]);
  }

  fixedXOR(byteArray1, byteArray2, output, numBytes);

  /* Print out hex encoded output */
  char hexStr[strHexLen];
  for (int i = 0; i < numBytes; i++) {
    sprintf(hexStr + i * 2, "%02x", output[i]);
  }

  printf("RESULT: %s\n", hexStr);

  return 0;
}
