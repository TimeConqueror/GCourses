#pragma once

#include "Pong.h"
#include "../Engine/Graphics/VertexFormat.h"

class Main {
};

int main() {
	Pong g(800, 600);
	g.run();

	return 0;
}