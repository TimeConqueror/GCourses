#pragma once

#include "../Window.h"
#include "VertexBuffer.h"
#include "RenderableObject.h"
#include "RenderType.h"
#include <wrl.h>
#include <d3d.h>
#include <d3d11.h>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace WRL = Microsoft::WRL;

class RenderManager {
private:
	Window& window;
	WRL::ComPtr<ID3D11Device> device = nullptr;
	WRL::ComPtr<ID3D11DeviceContext> context = nullptr;
	WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	WRL::ComPtr<ID3D11RasterizerState> rastState = nullptr;

	std::unordered_map<std::string, RenderableObject&> renderObjects;
public:
	RenderManager(Window& window);
	void init();
	void render();
	void addRenderable(std::string name, RenderableObject& object);
	void removeRenderable(std::string name);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getContext();
private:
	HRESULT initSwapChain();
	HRESULT initRenderTarget();
	HRESULT initRasterizationState();

	void beginRender();
	void endRender();
};