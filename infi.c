#include "infi.h"
#include <stdlib.h>
#include <assert.h>

#define MID(a, b) ((a + b) / 2.0)
#define DELTA(a, b, n) ((b - a) / n)

/**
 * This function will return the middle values of the x between [a,b].
 * @param a left x bound
 * @param n number of sums
 * @param dx the change in range [a,b]
 * @return pointer to the middle points of [a,b]
 */
double *getMidPoints(double a, unsigned int n, double dx)
{
    double *middles = (double *) calloc(n, sizeof(double));
    for (unsigned int i = 0; i < n; i++)
    {
        middles[i] = MID(a + i * dx, a + (i + 1) * dx);
    }
    return middles;
}

/**
 * This function will estimate the integral value of a function f using Riemann sums
 * @param f pointer to a function
 * @param a left bound for x
 * @param b right bound for x
 * @param n number of Riemann's sums
 * @return the estimated integral value
 */
double integration(RealFunction f, double a, double b, unsigned int n)
{
    assert(n > 0 && (double) (int) n == n);
    assert(a < b);
    double delta = DELTA(a, b, n);
    double sum = 0, singleVal = 0;
    double *midPoints = getMidPoints(a, n, delta);
    for (unsigned int i = 0; i < n; i++)
    {
        singleVal = f(midPoints[i]);
        assert(!isnan(singleVal));
        sum += delta * (singleVal);
    }
    free(midPoints);
    return sum;
}

/**
 * This function will estimate the slope (derivative) of a function f in the point x0.
 * @param f the given function
 * @param x0 the point
 * @param h the epsilon
 * @return the slope in x0
 */
double derivative(RealFunction f, double x0, double h)
{
    assert(h > 0);
    double leftVal = f(x0 + h), rightVal = f(x0 - h);
    assert(!isnan(leftVal));
    assert(!isnan(rightVal));
    return DELTA(rightVal, leftVal, (2 * h));
}
