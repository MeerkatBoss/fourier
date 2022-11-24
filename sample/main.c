#include <stdio.h>
#include <stdlib.h>

#include "big_int.h"

int main()
{
    puts("Please enter two numbers to multiply:");
    char *a_str = NULL, *b_str = NULL;
    scanf(" %m[0-9] %m[0-9]", &a_str, &b_str);

    big_int a = string_to_big_int(a_str); free(a_str);
    big_int b = string_to_big_int(b_str); free(b_str);
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