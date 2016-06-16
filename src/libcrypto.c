#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * Prints bytes from a buffer in hex format to stdout
 */
void print_byte_buffer(uint8_t *buf, size_t len, const char *name)
{
        size_t i;
        printf("Dumping %zu bytes from %s\n", len, name);
        for (i = 0; i < len; ++i) {
                if(i > 0 && !(i%8)) putchar(' ');
                if(i > 0 && !(i%64)) putchar('\n');
                printf("%02x", buf[i]);
        }
        putchar('\n');
}

static char encoding_table[] =
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'};
static size_t mod_table[] = {0, 2, 1};

char *base64_encode(uint8_t *data, size_t len)
{

        size_t outlen = 4 * (len + 2) / 3;
        char *encoded_data = malloc(outlen + 1);
        size_t i, j;

        if (!encoded_data)
                return NULL;
        for (i = 0, j = 0; i < len; ) {
                uint32_t octet_a = i < len ? data[i++] : 0;
                uint32_t octet_b = i < len ? data[i++] : 0;
                uint32_t octet_c = i < len ? data[i++] : 0;

                uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

                encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
                encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
                encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
                encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
        }

        for (i = 0; i < mod_table[len % 3]; i++)
                encoded_data[outlen - 1 - i] = '=';

        encoded_data[outlen] = 0;
        return encoded_data;
}

/*
 * Utility function to convert hex character representation to their
 * nibble (4 bit) values
 */
uint8_t nibble_from_char(char c)
{
        if(c >= '0' && c <= '9') return c - '0';
        if(c >= 'a' && c <= 'f') return c - 'a' + 10;
        if(c >= 'A' && c <= 'F') return c - 'A' + 10;
        return 255;
}

/*
 * Convert a string of characters representing a hex buffer into a series
 * of bytes of that real value
 */
uint8_t *hextobytes(char *inhex)
{
        uint8_t *bytes;
        uint8_t *p;
        int len, i;

        len = strlen(inhex) / 2;
        bytes = malloc(len + 1);
        for (i = 0, p = (uint8_t*)inhex; i < len; ++i) {
                bytes[i] =
                        (nibble_from_char(*p) << 4) | (nibble_from_char(*(p + 1)));
                p += 2;
        }
        bytes[len] = 0;
        return bytes;
}


