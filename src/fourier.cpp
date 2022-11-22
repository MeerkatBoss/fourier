#include <string.h>
#include <math.h>

#include "fourier.h"

/* 
 * Move even-numbered elements to the left
 * TODO: avoid buffer usage, restructure in-place
 */
static inline int split_array(
                            double _Complex array[],
                            size_t size,
                            double _Complex buffer[] = NULL);

/*
 * Butterfly-transform in FFT
 */
static inline int butterfly(double _Complex array[], size_t size, int inverse = 0);

/*
 * Fast Fourier-transform
 */
static int fft(
            double _Complex coeffs[],
            size_t size,
            int inverse = 0,
            double _Complex buffer[] = NULL);

int fourier_transform(double _Complex coeffs[], size_t size)
{
    return fft(coeffs, size, 0);
}

int inverse_fourier_transform(double _Complex coeffs[], size_t size)
{
    return fft(coeffs, size, 1);
}

static int fft(
            double _Complex coeffs[],
            size_t size,
            int inverse,
            double _Complex buffer[])
{
    if (size == 1) return 0; /* trivial case: nothing to be done */

    if (size & (size - 1))
        return -1;

    int allocated = 0;
    if (!buffer)
    {
        buffer = (double _Complex*) calloc(size / 2, sizeof(*buffer));
        allocated = 1;
    }

    split_array(coeffs, size, buffer);  /* Partition coefficient array */

    /* Recursively solve for n/2 */
    fft(coeffs,          size/2, inverse, buffer);
    fft(coeffs + size/2, size/2, inverse, buffer);

    /* Combine solutions for n/2 */
    butterfly(coeffs, size, inverse);

    if (allocated) free(buffer);

    return 0;
}

static inline int butterfly(double _Complex array[], size_t size, int inverse)
{
    if (size & (size - 1))
        return -1;

    double angle = 2 * M_PI / size;

    /* Rotate in opposite direction for inverse transform */
    if (inverse) angle *= -1;

    double _Complex ru = CMPLX(cos(angle), sin(angle)); /* first primitive root of unity */
    double _Complex twiddle = 1; /* twiddle factor */
    for (size_t i = 0; i < size / 2; i++)
    {
        double _Complex x0 = array[i];
        double _Complex x1 = array[size/2 + i];

        array[i]          = x0 + twiddle * x1;
        array[size/2 + i] = x0 - twiddle * x1;

        if (inverse)    /* Divide by 2 on each step for inverse transform */
        {
            array[i]          /= 2;
            array[size/2 + i] /= 2;
        }

        twiddle *= ru;      /* next root of unity */
    }

    return 0;
}

static inline int split_array(double _Complex array[], size_t size, double _Complex buffer[])
{
    if (size & (size - 1))
        return -1;

    int allocated = 0;
    if (!buffer)
    {
        buffer = (double _Complex*) calloc(size / 2, sizeof(*buffer));
        allocated = 1;
    }

    for (size_t i = 0; i < size; i += 2)
    {
        array [i/2] = array[i];
        buffer[i/2] = array[i + 1];
    }
    memcpy(array + size/2, buffer, size/2);

    if (allocated) free(buffer);

    return 0;
}
