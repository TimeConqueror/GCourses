#include "Pong.h"

void Pong::init() {
	RenderManager& renderManager = getRenderManager();
	std::cout << "Initializing..." << std::endl;
	renderManager.addRenderable("left", leftBoard);
	renderManager.addRenderable("right", rightBoard);
}

void Pong::tick() {

}
