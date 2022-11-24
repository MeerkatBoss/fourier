#include <stdio.h>
#include <stdlib.h>

#include "big_int.h"

int main()
{
    big_int a = string_to_big_int("123456789101112131415161718");
    big_int b = string_to_big_int("181716151413121110987654321");
    big_int c = big_int_mul(&a, &b);
    char *buffer = (char*)calloc(7 * c.chunk_count, sizeof(*buffer));
    big_int_to_string(&a, buffer);
    printf("%s * ", buffer);
    big_int_to_string(&b, buffer);
    printf("%s = ", buffer);
    big_int_to_string(&c, buffer);
    printf("%s\n", buffer);
    big_int_dtor(&a);
    big_int_dtor(&b);
    big_int_dtor(&c);
    free(buffer);
    return 0;
}