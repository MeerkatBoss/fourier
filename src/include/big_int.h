/**
 * @file big_int.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * @brief Big integer support
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BIG_INT_H
#define BIG_INT_H

#include <stddef.h>

/**
 * @brief 
 * Big integer chunk type
 */
typedef unsigned long long int_chunk_t;

/**
 * @brief 
 * Big integer base
 */
const int_chunk_t BIGINT_BASE = 1e8;

/**
 * @brief 
 * Big integer default chunk count
 */
const size_t DEFAULT_CHUNKS = 16;

/**
 * @brief 
 * Big integer
 */
struct big_int
{
    /**
     * @brief 
     * Chunks of a number (digits in base `BIGINT_BASE`)
     */
    int_chunk_t *chunks;

    /**
     * @brief 
     * 1 if number is positive, -1 if negative, 0 if zero
     */
    signed char sign;
};

/**
 * @brief Construct big integer from its value
 * @param[in] value Big integer value
 * @return Constructed big integer
 */
[[nodiscard]]
big_int big_int_ctor(long long value = 0);

/**
 * @brief Destroy `big_int` instance. Free associated resources
 * @param[inout] number `big_int` instance
 */
void big_int_dtor(big_int *number);

/**
 * @brief Add two big integers
 * @param[in] a First summand
 * @param[in] b Second summand
 * @return Sum of big integers
 */
big_int big_int_add(const big_int* a, const big_int* b);

/**
 * @brief Subtract one big integer from another
 * @param[in] a Minuend
 * @param[in] b Subtrahend
 * @return Difference of big integers
 */
big_int big_int_sub(const big_int* a, const big_int* b);

/**
 * @brief Multiply big integers
 * @param[in] a First factor
 * @param[in] b Second factor
 * @return Product of big integers
 */
big_int big_int_mul(const big_int* a, const big_int* b);

/**
 * @brief Divide one big integer by another
 * @param[in] a Dividend
 * @param[in] b Divisor
 * @return Integer ratio of big integers
 * 
 * @warning Not Implemented
 * @todo Add implementation
 */
big_int big_int_div(const big_int* a, const big_int* b);

/**
 * @brief Get division remainder
 * @param[in] a Dividend
 * @param[in] b Divisor
 * @return Remainder modulo `b`
 * 
 * @warning Not Implemented
 * @todo Add implementation
 */
big_int big_int_mod(const big_int* a, const big_int* b);

#endif