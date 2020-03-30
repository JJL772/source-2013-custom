/*
 *
 * random.h
 *
 * Very fast random number generation
 *
 */
#pragma once

#include "mathlib/vector.h"
#include "mathlib/vector2d.h"
#include "mathlib/vector4d.h"

bool RandomBool();

int RandomIntFast(int iMin, int iMax);

float RandomFloatFast(float flMin, float flMax);

Vector RandomVectorFast(float flMin, float flMax);

Vector2D RandomVector2DFast(float flMin, float flMax);

Vector4D RandomVector4DFast(float flMin, float flMax);

Vector RandomVectorInSphere(float flMinRadius, float flMaxRadius);

Vector RandomVectorInDome(float flMinRadius, float flMaxRadius);

Vector RandomVectorInCone(float flStartRadius, float flEndRadius, float flMinDist, float flMaxDist);

