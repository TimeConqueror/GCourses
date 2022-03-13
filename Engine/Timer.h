#pragma once
#include <chrono>
#include "Utils.h"
#include <iostream>

using namespace std::chrono;

class Timer {
private:
	milliseconds lastMs = milliseconds(0L);
	const float msPerTick = 0;
	float tickDelta = 0;
	float partialTick = 0;
public:
	inline Timer(float ticksPerSecond): msPerTick(1000.0F / ticksPerSecond) {};

	inline void start() {
		lastMs = millis();
	}

	inline int advanceTime() {
		auto curMillis = millis();

		tickDelta = (curMillis - lastMs).count() / msPerTick;
		lastMs = curMillis;
		partialTick += tickDelta;
		int i = (int) partialTick;
		this->partialTick -= i;
		return i;
	}

	inline float getPartialTick() {
		return partialTick;
	}

private:
	inline static milliseconds millis() {
		return duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
	}
};
