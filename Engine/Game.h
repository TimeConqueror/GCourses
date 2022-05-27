#pragma once
#include "Window.h"
#include "Timer.h"
#include "InputController.h"
#include <windows.h>

#include "Graphics/RenderManager.h"

class Game {
private:
	static Game* instance;

	const LPCWSTR name;	
	InputController inputController;
	Window window;
	RenderManager renderManager;
	Timer timer;
public:
	Game(LPCWSTR name, uint width, uint height, int ticksPerSecond = 60);

	static Game* getInstance();
	static bool isReady();
	void run();
	float getPartialTick();

	Window& getWindow();
	RenderManager& getRenderManager();
	InputController& getInputController();

	/**
     * Singletons should not be cloned.
     */
	Game(Game& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const Game&) = delete;

protected:
	virtual void init() = 0;
	virtual void tick() = 0;

private:
	static void setInstance(Game* game);
	void initInternals();
};
