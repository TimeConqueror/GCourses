#pragma once

#include "../Engine/Game.h"
#include "../Engine/Graphics/VertexFormat.h"

class Main {
};

void main() {
	Game g(L"Pong", 1080, 1024);
	g.init();
	g.run();
}