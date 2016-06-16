#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../lib/libcrypto.h"

int main(int argc, char **argv)
{
        if (argc != 2) {
                fprintf(stderr, "%s <hex string>\n", *argv);
                return 1;
        }

        uint8_t *data = hextobytes(argv[1]);
        size_t len = strlen(argv[1]) / 2;
        print_byte_buffer(data, len, "data");

        puts("Converting to base 64:");
        char *str = base64_encode(data, len);
        puts(str);

        free(data);
        free(str);
        return 0;
}
