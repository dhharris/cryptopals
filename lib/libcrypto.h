#ifndef LIBCRYPTO_H
#define LIBCRYPTO_H

void print_byte_buffer(uint8_t *buf, size_t len, const char *name);
char *base64_encode(uint8_t *data, size_t len);
uint8_t nibble_from_char(char c);
uint8_t *hextobytes(char *inhex);

#endif
