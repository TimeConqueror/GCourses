#pragma once

#include "Pong.h"
#include "../Engine/Graphics/VertexFormat.h"

class Main {
};

void main() {
	Pong g(800, 600);
	g.run();
}