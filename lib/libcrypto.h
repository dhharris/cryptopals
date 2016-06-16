#ifndef LIBCRYPTO_H
#define LIBCRYPTO_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void print_byte_buffer(uint8_t *buf, size_t len, const char *name);
char *base64_encode(uint8_t *data, size_t len);
uint8_t nibble_from_char(char c);
uint8_t *hextobytes(char *inhex);
char *bytestohex(uint8_t *buf, size_t len);
uint8_t *xor_bytes(uint8_t *a, uint8_t *b, size_t len);
char *xor_hexstr(char *a, char *b, size_t len);
#endif
