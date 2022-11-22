#include <stdlib.h>
#include <string.h>

#include "fourier.h"
#include "big_int.h"

static void carry(big_int *num);
static void try_shrink(big_int *num);
static int is_zero(const big_int *num);

static inline size_t max(size_t a, size_t b) { return a > b ? a : b; }
static inline size_t min(size_t a, size_t b) { return a < b ? a : b; }

big_int big_int_ctor(long long value)
{
    int_chunk_t *chunks = (int_chunk_t*)calloc(DEFAULT_CHUNKS, sizeof(*chunks));
    signed char sign = 1;
    if (value == 0) sign = 0;
    if (value < 0)  sign = -1;

    int ptr = 0;
    /* no more than 3 chunks will be needed */
    while (value)
    {
        /* correct remainder from possibly negative number */
        chunks[ptr++] = (value % BIGINT_BASE) * sign;
        value /= BIGINT_BASE;
    }

    big_int result = {
        .chunks      = chunks,
        .chunk_count = DEFAULT_CHUNKS,
        .sign        = sign
    };

    return result;
}

void big_int_dtor(big_int * number)
{
    free(number->chunks);
    number->chunks = NULL;
    number->sign = 0;
}

big_int big_int_add(const big_int* a, const big_int* b)
{
    if (a->chunk_count < b->chunk_count)
    {
        const big_int *tmp = a;
        a = b;
        b = tmp;
    }
    size_t size = a->chunk_count;
    big_int result = {
        .chunks      = (int_chunk_t*) calloc(size, sizeof(int_chunk_t)),
        .chunk_count = size,
        .sign        = 0
    };
    for (size_t i = 0; i < b->chunk_count; i++)
        result.chunks[i] = a->sign * a->chunks[i] + b->sign * b->chunks[i];
    for (size_t i = b->chunk_count; i < a->chunk_count; i++)
        result.chunks[i] = a->sign * a->chunks[i];
    carry(&result);
    return result;
}

big_int big_int_sub(const big_int* a, const big_int* b)
{
    big_int *tmp = (big_int*) (b);
    tmp->sign *= (signed char)-1;
    big_int result = big_int_add(a, tmp);
    tmp->sign *= (signed char)-1;
    return result;
}

big_int big_int_mul(const big_int * a, const big_int * b)
{
    if (a->chunk_count < b->chunk_count)
    {
        const big_int *tmp = a;
        a = b;
        b = tmp;
    }
    size_t size = 1;
    while (size < a->chunk_count)
        size *= 2;
    size *= 2;
    double _Complex *a_cx   = (double _Complex *)calloc(size, sizeof(*a_cx));
    double _Complex *b_cx   = (double _Complex *)calloc(size, sizeof(*b_cx));
    double _Complex *res_cx = (double _Complex *)calloc(size, sizeof(*res_cx));

    for (size_t i = 0; i < a->chunk_count; i++) a_cx[i] = a->chunks[i];
    for (size_t i = 0; i < b->chunk_count; i++) b_cx[i] = b->chunks[i];

    fourier_transform(a_cx, size);
    fourier_transform(b_cx, size);

    for (size_t i = 0; i < size; i++)
        res_cx[i] = a_cx[i] * b_cx[i];

    inverse_fourier_transform(res_cx, size);

    big_int result = {
        .chunks      = (int_chunk_t*)calloc(size, sizeof(int_chunk_t)),
        .chunk_count = size,
        .sign        = 0
    };

    for (size_t i = 0; i < size; i++)
        result.chunks[i] = (int_chunk_t) round(creal(res_cx[i]));

    carry(&result);

    result.sign = a->sign * b->sign;

    return result;
}

big_int string_to_big_int(const char * str)
{
    size_t len = strlen(str);
    size_t size = 1;
    while (size < len / 7)
        size *= 2;
    
    if (size < DEFAULT_CHUNKS) size = DEFAULT_CHUNKS;
    big_int result = {
        .chunks      = (int_chunk_t*)calloc(size, sizeof(int_chunk_t)),
        .chunk_count = size,
        .sign        = 0
    };

    while (isspace(*str)) str++;
    if (*str == '-')
    {
        result.sign = -1;
        str++;
    }
    if (*str == '+')
        str++;

    size_t it = 0;
    int n_read = 0;
    unsigned number = 0;
    while (sscanf(str, "%7u%n", &number, &n_read) == 1) 
    {
        result.chunks[it++] = number;
        if (n_read < 7) break;
    }
    try_shrink(&result);
    if (is_zero(&result)) result.sign = 0;
    return result;
}

void big_int_to_string(const big_int* num, char strbuf[])
{
    long long it = (long long) num->chunk_count - 1;
    while (it > 0 && num->chunks[it] == 0)
        it--;
    int pos = 0;
    int n_write = 0;
    sprintf(strbuf, "%lld%n", num->chunks[it--], &n_write);
    pos += n_write;
    while(it >= 0)
    {
        sprintf(strbuf + pos, "%lld%n", num->chunks[it--], &n_write);
        pos += n_write;
    }
    return;
}

static void carry(big_int *num)
{
    int_chunk_t car = 0;
    for (size_t i = 0; i < num->chunk_count; i++)
    {
        num->chunks[i] += car;

        car = num->chunks[i] / BIGINT_BASE;
        num->chunks[i] %= car;

        /* Negative digits require extra carrying */
        if (num->chunks[i] < 0)
        {
            car -= 1;
            num->chunks[i] *= -1;
        }
    }
    
    if (car == 0)
    {
        num->sign = is_zero(num) ? 0 : 1;
        try_shrink(num);
        return;
    }

    num->chunks = (int_chunk_t*)reallocarray(num->chunks,
                                    2*num->chunk_count, sizeof(*num->chunks));
    memset(num->chunks + num->chunk_count, 0, num->chunk_count);
    num->chunks[num->chunk_count] = car;
    num->chunk_count *= 2;

    if (car < 0)
        for (size_t i = 0; i < num->chunk_count; i++)
            num->chunks[i] *= -1;
    
    carry(num);

    if (car < 0)
        num->sign = -1;
}

static void try_shrink(big_int * num)
{
    size_t front = num->chunk_count - 1;
    while (front > 0 && num->chunks[front] == 0)
        front--;

    size_t new_size = 1;
    while (new_size <= front)
        new_size *= 2;

    if (new_size < DEFAULT_CHUNKS) new_size = DEFAULT_CHUNKS;

    if (new_size >= num->chunk_count) return;

    num->chunks = (int_chunk_t*) reallocarray(num->chunks,
                                                new_size, sizeof(*num->chunks));
    num->chunk_count = new_size;
}

static int is_zero(const big_int * num)
{
    for (size_t i = 0; i < num->chunk_count; i++)
        if (num->chunks[i] != 0)
            return 0;
    return 1;
}
