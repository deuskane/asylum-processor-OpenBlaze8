/*
 * math.h - Basic Mathematical (decimal only) functions header file
 *
 * adopted for SDCC and picoBlaze port by Zbynek Krivka, 2010 <krivka @ fit.vutbr.cz>
 *
*/

#ifndef __MATH_H__
#define __MATH_H__

/*
#pragma library math

#include <sdcc-lib.h>

#define PI          3.1415926536
#define TWO_PI      6.2831853071
#define HALF_PI     1.5707963268
#define QUART_PI    0.7853981634
#define iPI         0.3183098862
#define iTWO_PI     0.1591549431
#define TWO_O_PI    0.6366197724

// EPS=B**(-t/2), where B is the radix of the floating-point representation
// and there are t base-B digits in the significand.  Therefore, for floats
// EPS=2**(-12).  Also define EPS2=EPS*EPS.
#define EPS 244.14062E-6
#define EPS2 59.6046E-9
#define XMAX 3.402823466E+38

union float_long
{
    float f;
    long l;
};
*/

/**********************************************
 * Prototypes for float ANSI C math functions *
 **********************************************/

/* Trigonometric functions */
/*
float sinf(const float x) _MATH_REENTRANT;
float cosf(const float x) _MATH_REENTRANT;
float tanf(const float x) _MATH_REENTRANT;
float cotf(const float x) _MATH_REENTRANT;
float asinf(const float x) _MATH_REENTRANT;
float acosf(const float x) _MATH_REENTRANT;
float atanf(const float x) _MATH_REENTRANT;
float atan2f(const float x, const float y);
*/
/* Hyperbolic functions */
/*
float sinhf(const float x) _MATH_REENTRANT;
float coshf(const float x) _MATH_REENTRANT;
float tanhf(const float x) _MATH_REENTRANT;

/* Exponential, logarithmic and power functions */
/*
float expf(const float x);
float logf(const float x) _MATH_REENTRANT;
float log10f(const float x) _MATH_REENTRANT;
float powf(const float x, const float y);
float sqrtf(const float a) _MATH_REENTRANT;
*/
/* Nearest integer, absolute value, and remainder functions */
/*
float fabsf(const float x) _MATH_REENTRANT;
float frexpf(const float x, int *pw2);
float ldexpf(const float x, const int pw2);
float ceilf(float x) _MATH_REENTRANT;
float floorf(float x) _MATH_REENTRANT;
float modff(float x, float * y);
*/

unsigned int pow(const unsigned int x, const unsigned int y);
unsigned int sqrt(const unsigned int a); //_MATH_REENTRANT;

#endif  /* __MATH_H */
