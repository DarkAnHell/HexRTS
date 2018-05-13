// Fill out your copyright notice in the Description page of Project Settings.

#include "PerlinNoiseMatrix.h"

PerlinNoiseMatrix::PerlinNoiseMatrix(unsigned int seed) {
	p.resize(255);

	iota(p.begin(), p.end(), 0);

	default_random_engine engine(seed);

	shuffle(p.begin(), p.end(), engine);

	p.insert(p.end(), p.begin(), p.end());
}

PerlinNoiseMatrix::~PerlinNoiseMatrix()
{
}

float PerlinNoiseMatrix::noise(float x, float y, float z)
{
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;
	int Z = (int)floor(z) & 255;

	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	float u = fade(x);
	float v = fade(y);
	float w = fade(z);

	int A = p[X] + Y;
	int AA = p[A] + Z;
	int AB = p[A + 1] + Z;
	int B = p[X + 1] + Y;
	int BA = p[B] + Z;
	int BB = p[B + 1] + Z;

	float res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)), lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))), lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)), lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
	return (res + 1.0f)/2.0f;
}

float PerlinNoiseMatrix::octaveNoise(float x, float y, float z)
{
	float total = 0.0f;
	float frecuency = 4.0f;
	float amplitude = 128.0f;
	float maxValue = 0.0f;

	for (int i = 0; i < 6; i++) {
		total += noise(x*frecuency, y*frecuency, z*frecuency) * amplitude;

		maxValue += amplitude;

		amplitude /= 2;
		frecuency *= 2;
	}

	return total/maxValue;
}

float PerlinNoiseMatrix::fade(float t)
{
	return t * t * t  *(t * (t * 6 - 15) + 10);
}

float PerlinNoiseMatrix::lerp(float x, float a, float b)
{
	return a + x * (b - a);
}

float PerlinNoiseMatrix::grad(int hash, float x, float y, float z)
{
	int h = hash & 15;

	float u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
