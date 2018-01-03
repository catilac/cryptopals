/*
 * Cryptopals - Challenge 1
 * Convert hex to base64
 * Usage: challenge1 [hex]
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

/*
 * bytesToBase64()
 * returns base64 encoded string
 */
char* bytesToBase64(unsigned char* bytes) {
  int outputLen = 8 * strlen((char *)bytes) / 6;
  char *output = (char *)malloc(outputLen + 2);
  char *base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  char bitMask6 = 0x3F; 
  char bitMask4 = 0xF;
  char bitMask2 = 0x3;

  /* Iterate 4 blocks at a time */
  for (int n = 0; n < outputLen / 4; n++) {
    int i = 3*n; // start index of hex values
    int j = 4*n; // start index of base64 values

    // Take first 6 bits
    char val = (bytes[i] >> 2) & bitMask6;
    output[j] = base64Table[val];

    // last 2 bits OR first 4 bits of next byte
    // 1 -> 1, 2
    val = (bytes[i] & bitMask2) << 4;
    val |= (bytes[i + 1] >> 4) & bitMask4;
    output[j + 1] = base64Table[val];

    // last 4 bits of next byte OR first 2 bits of next next byte
    // 2 -> 2, 3
    val = (bytes[i + 1] & bitMask4) << 2;
    val |= (bytes[i + 2] >> 6) & bitMask2;
    output[j + 2] = base64Table[val];

    // last 6 bits of last byte
    val = bytes[i + 2] & bitMask6;
    output[j + 3] = base64Table[val];
  }

  output[outputLen] = '\n';
  output[outputLen + 1] = '\0';

  return output;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: challenge1 [hex]\n");
    exit(-1);
  }

  char* strHex = argv[1];

  int strHexLen = strlen(strHex);
  if (strHexLen % 2 != 0) {
    printf("Invalid Input!\n");
    exit(-1);
  }

  /* Convert strHex to bytes */
  // Algorithm:
  // len(strHex)/2 == numBytes
  int numBytes = strHexLen / 2;
  unsigned char byteArray[numBytes + 1];

  /* Read byte at a time */
  for (int i = 0; i <= strHexLen - 2; i += 2) {
    byteArray[i / 2] = hex2Dec(strHex[i], strHex[i+1]);
  }
  byteArray[numBytes] = '\0';

  char *output = bytesToBase64(byteArray);
  /* Convert bytes to base16 */
  printf("Output: %s\n", output);
  free(output);
  output = NULL;

  return 0;
}
