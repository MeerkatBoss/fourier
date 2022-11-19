/**
 * @file fourier.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * @brief Fourier transform functions
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __FOURIER_H /* fourier.h */
#define __FOURIER_H

#include <stddef.h>
#include <complex.h>

/**
 * @brief 
 * Convert vector of polynomial coefficients to a vector
 * of polynomial function values at points, corresponding
 * to complex roots of 1.
 * 
 * @param[inout] coeffs Input and output coefficients
 * @param[in] size Length of `coeffs` array. Must be a power of 2.
 * 
 * @return 0 upon successful transform, -1 if size of `coeffs` array
 * is not a power of 2
 */
int fourier_transform(double _Complex coeffs[], size_t size);

/**
 * @brief 
 * Convert vector of polynomial function values at points,
 * corresponding to complex roots of 1 to vector of polynomial
 * coefficients.
 * 
 * @param[inout] coeffs Input and output coefficients
 * @param[in] size Length of `coeffs` array. Must be a power of 2.
 * 
 * @return 0 upon successful transform, -1 if size of `coeffs` array
 * is not a power of 2
 */
int inverse_fourier_transform(double _Complex coeffs[], size_t size);

#endif __FOURIER_H /* fourier.h */