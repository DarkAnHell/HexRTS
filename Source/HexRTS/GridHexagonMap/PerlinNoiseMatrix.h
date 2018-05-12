// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

class HEXRTS_API PerlinNoiseMatrix
{
	vector<int> p;
public:
	PerlinNoiseMatrix(unsigned int seed);
	~PerlinNoiseMatrix();
	float noise(float x, float y, float z);

private:
	float fade(float t);
	float lerp(float x, float a, float b);
	float grad(int hash, float x, float y, float z);
};
