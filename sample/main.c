#include <stdio.h>

#include "big_int.h"

int main()
{
    big_int a = big_int_ctor(123456789101112);
    char BUFFER[1024] = "";
    big_int_to_string(&a, BUFFER);
    printf("%s\n", BUFFER);
    big_int_dtor(&a);
    return 0;
}