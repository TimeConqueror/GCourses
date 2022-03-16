#pragma once

#include <random>

class Rand {
	static std::mt19937 random;

public:
	static void init();
	static int upToIncluded(int bound);
	static float upToExcluded(float bound);
	static int inRangeIncluded(int start, int end);
};

