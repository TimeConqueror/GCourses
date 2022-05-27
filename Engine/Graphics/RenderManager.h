#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <unordered_map>

#include "Camera.h"
#include "CameraHandler.h"
#include "RenderableObject.h"
#include "Window.h"

namespace WRL = Microsoft::WRL;

class RenderManager {
private:
	Window& window;
	WRL::ComPtr<ID3D11Device> device = nullptr;
	WRL::ComPtr<ID3D11DeviceContext> context = nullptr;
	WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	WRL::ComPtr<ID3D11RasterizerState> rastState = nullptr;

	Camera* camera = nullptr;
	CameraHandler* cameraHandler = nullptr;
	std::unordered_map<std::string, RenderableObject&> renderObjects;
public:
	RenderManager(Window& window);
	void init(Game* game);
	void render(float partialTick);
	void addRenderable(std::string name, RenderableObject& object);
	void removeRenderable(std::string name);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getContext();

	Camera* getCamera();
	CameraHandler* getCameraHandler();
private:
	HRESULT initSwapChain();
	HRESULT initRenderTarget();
	HRESULT initRasterizationState();

	void beginRender();
	void endRender();
};
