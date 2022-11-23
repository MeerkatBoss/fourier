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
typedef long long int_chunk_t;

/**
 * @brief 
 * Big integer base
 */
static const int_chunk_t BIGINT_BASE = 1e7;

/**
 * @brief 
 * Big integer default chunk count
 */
static const size_t DEFAULT_CHUNKS = 16;

/**
 * @brief 
 * Big integer
 */
typedef struct
{
    /**
     * @brief Chunks of a number (digits in base `BIGINT_BASE`)
     */
    int_chunk_t *chunks;

    /**
     * @brief Capacity of `chunks` array
     */
    size_t chunk_count;

    /**
     * @brief 1 if number is positive, -1 if negative, 0 if zero
     */
    signed char sign;
} big_int;

/**
 * @brief Construct big integer from its value
 * @param[in] value Big integer value
 * @return Constructed big integer
 */
big_int big_int_ctor(long long value);

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

/**
 * @brief Compare two big integers
 * @param[in] a `big_int` instance
 * @param[in] b `big_int` instance
 * @return -1 if a < b, 1 if a > b, 0 if a = b
 * 
 * @warning Not Implemented
 * @note Add implementation
 */
int big_int_cmp(const big_int* a, const big_int* b);

/**
 * @brief Read big integer from string
 * @param[in] str String representation of a number
 * @return Parsed big integer
 * 
 * @warning Not Implemented
 * @note Add implementation
 */
big_int string_to_big_int(const char *str);

/**
 * @brief Convert big integer to its string representation
 * @param[in] num `big_int` instance
 * @param[out] strbuf Output buffer
 */
void big_int_to_string(const big_int* num, char strbuf[]);

#endif