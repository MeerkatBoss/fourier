#include "fourier.h"

/* Move even-numbered elements to the left*/
static void split_array(double _Complex array[], size_t size);


/* Previous element in cyclic permutation */
static inline size_t prev_in_cycle(size_t cur, size_t n) { return 2*cur % n + (2 * cur >= n); }

/* Next element in cyclic permutation */
static inline size_t next_in_cycle(size_t cur, size_t n) { return cur / 2 + (n / 2) * (cur % 2); }

static void split_array(double _Complex array[], size_t size)
{
    /*
        Because each permutation is composition of
        independent cyclic permutations, we can find
        those cycles and perform them in any particular
        order for any permutation.

        In this case, next and previous elements in cycles
        are calculated with `next_in_cycle` and `prev_in_cycle`.

        For n = 16 cycles are following:
            (1 8 4 2)(3 9 12 6)(5 10)(7 11 13 14)(0)(15)

        Note that all non-trivial cycles start from an odd number
        less than n/2. TODO: proof
    */
    for (size_t i = 1; i < size / 2; i += 2)
    {
        size_t cur = i;
        
        /*
            To perform cycle of size k, we need to swap first
            element in cycle with previous one k-1 times.

            (1842) = (8421) = (84)(42)(21)
            Note, that cycle composition is performed right to left.
        */

        while ((cur = prev_in_cycle(cur, size)) != i) /* while loop not closed*/
        {
            size_t prv = next_in_cycle(cur, size);

            /* swap elements */
            double _Complex tmp = array[cur];
            array[cur] = array[prv];
            array[prv] = tmp;
        }
    }
}
