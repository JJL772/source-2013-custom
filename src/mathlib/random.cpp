/*
 *
 * random.cpp
 *
 * Very fast random number generation
 *
 */
#include "mathlib/random.h"

#if defined(_x86_) && USE_STDC_FOR_SIMD == 0
#define USE_SSE
#endif

#if defined(_x86_) && defined(__GNUC__)
#include <xmmintrin.h>
#elif defined(_x86_) && defined(_MSC_VER)
#include <intrin.h>
#endif

int RandomIntFast(int iMin, int iMax)
{
#ifdef USE_SSE

#else

#endif
}

float RandomFloatFast(float flMin, float flMax)
{
#ifdef USE_SSE

#else

#endif
}

Vector RandomVectorFast(float flMin, float flMax)
{
#ifdef USE_SSE

#else

#endif
}

Vector2D RandomVector2DFast(float flMin, float flMax)
{
#ifdef USE_SSE

#else

#endif
}

Vector4D RandomVector4DFast(float flMin, float flMax)
{
#ifdef USE_SSE

#else

#endif
}

Vector RandomVectorInSphere(float flMinRadius, float flMaxRadius)
{
#ifdef USE_SSE

#else

#endif
}

Vector RandomVectorInDome(float flMinRadius, float flMaxRadius)
{
#ifdef USE_SSE

#else

#endif
}

Vector RandomVectorInCone(float flStartRadius, float flEndRadius, float flMinDist, float flMaxDist)
{
#ifdef USE_SSE

#else

#endif
}