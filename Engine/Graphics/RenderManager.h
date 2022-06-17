#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <unordered_map>

#include "Camera.h"
#include "CameraHandler.h"
#include "Sampler.h"
#include "Window.h"
#include "Renderables/IRenderable.h"

namespace WRL = Microsoft::WRL;

class RenderManager {
private:
	Window& window;
	WRL::ComPtr<ID3D11Device> device = nullptr;
	WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	WRL::ComPtr<ID3D11DeviceContext> context = nullptr;

	WRL::ComPtr<ID3D11Texture2D> depthBuffer = nullptr;

	WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	WRL::ComPtr<ID3D11DepthStencilView> depthView = nullptr;

	WRL::ComPtr<ID3D11RasterizerState> rastState = nullptr;
	WRL::ComPtr<ID3D11DepthStencilState> depthState = nullptr;

	Camera* camera = nullptr;
	CameraHandler* cameraHandler = nullptr;
	std::vector<IRenderable*> renderObjects;
	std::unordered_map<std::string, IRenderable*> namedRenderObjects;

	Sampler sampler;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> testTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> testTextureView;

public:
	float fov;
	bool orthographic = false;

	RenderManager(Window& window);
	void init(Game* game);
	void render(float partialTick);
	int addRenderable(IRenderable* object);
	void addNamedRenderable(std::string name, IRenderable* object);
	void removeNamedRenderable(std::string name);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getContext();

	Camera* getCamera();
	CameraHandler* getCameraHandler();
private:
	HRESULT initSwapChain();
	HRESULT initDepthBuffer();
	HRESULT initDepthStencilView();
	HRESULT initDepthStencilState();
	HRESULT initRenderTarget();
	HRESULT initRasterizationState();

	void beginRender();
	void endRender();
};
