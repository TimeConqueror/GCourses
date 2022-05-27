#pragma once

#include "SolarDemo.h"
#include "../Engine/Graphics/VertexFormat.h"

class Main {
};

int main() {
	SolarDemo g(800, 600);
	g.run();

	return 0;
}