#include "Rand.h"

std::mt19937 Rand::random;

void Rand::init() {
	std::random_device rd;
	random = std::mt19937(rd());
}

int Rand::upToIncluded(int bound) {
	std::uniform_int_distribution<int> uniDistribution{0, bound};
	return uniDistribution(random);
}

float Rand::upToExcluded(float bound) {
	std::uniform_real_distribution<float> uniDistribution{0, bound};
	return uniDistribution(random);
}

int Rand::inRangeIncluded(int start, int end) {
	return start + upToIncluded(end - start);
}