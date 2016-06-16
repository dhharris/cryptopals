#include "../lib/libcrypto.h"

int main(int argc, char **argv)
{
        if (argc != 3) {
                fprintf(stderr, "%s <hex string a> <hex string b>\n", *argv);
                return 1;
        }

        char *res = xor_hexstr(argv[1], argv[2], strlen(argv[1]));
        printf("%s\n", res);
        free(res);

        return 0;
}
