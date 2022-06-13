#include "RenderManager.h"

#include "RenderTypes.h"
#include "../Utils.h"

static RenderType TRIANGLE_POS_COLOR{
	L"../Shaders/MyVeryFirstShader.hlsl", 
	VertexFormat(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST)
	.add({
			"POSITION",
			DXGI_FORMAT_R32G32B32A32_FLOAT
		 })
	.add({
			"COLOR",
			DXGI_FORMAT_R32G32B32A32_FLOAT
		 })
};

RenderManager::RenderManager(Window& window): window(window) {
	fov = DirectX::XM_PIDIV2;
}

HRESULT RenderManager::initSwapChain() {
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = window.getWidth();
	swapDesc.BufferDesc.Height = window.getHeight();
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = window.getHWnd();
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevel[] = {D3D_FEATURE_LEVEL_11_1};
	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	return result;
}

HRESULT RenderManager::initDepthBuffer() {
	D3D11_TEXTURE2D_DESC depthTexDesc;
	depthTexDesc.Width = window.getWidth();
	depthTexDesc.Height = window.getHeight();
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;

	return device->CreateTexture2D(&depthTexDesc, nullptr, depthBuffer.GetAddressOf());
}

HRESULT RenderManager::initDepthStencilView() {
	// D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	// depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	// depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	// depthStencilViewDesc.Flags = 0;
	// return device->CreateDepthStencilView(depthBuffer.Get(), &depthStencilViewDesc, depthView.GetAddressOf());
	return device->CreateDepthStencilView(depthBuffer.Get(), nullptr, depthView.GetAddressOf());
}

HRESULT RenderManager::initDepthStencilState() {
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	return device->CreateDepthStencilState(&depthStencilDesc, depthState.GetAddressOf());
}

HRESULT RenderManager::initRenderTarget() {
	ID3D11Texture2D* backTex;
	HRESULT res = swapChain->GetBuffer(0, IID_ID3D11Texture2D, reinterpret_cast<void**>(&backTex));
	Utils::checkValid(res);

	return device->CreateRenderTargetView(backTex, nullptr, renderTargetView.GetAddressOf());
}

HRESULT RenderManager::initRasterizationState() {
	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	return device->CreateRasterizerState(&rastDesc, rastState.GetAddressOf());
}

uint width = 800;
uint height = 600;

void RenderManager::init(Game* game) {
	Utils::checkValid(initSwapChain());
	Utils::checkValid(initDepthBuffer());
	Utils::checkValid(initDepthStencilView());
	Utils::checkValid(initDepthStencilState());
	Utils::checkValid(initRenderTarget());
	Utils::checkValid(initRasterizationState());

	camera = new Camera(game);
	cameraHandler = new CameraHandler(game, camera);

	RenderTypes::init(*this);
}

int RenderManager::addRenderable(RenderableObject* object) {
	object->init(*this);
	renderObjects.push_back(object);

	std::cout << "Added render object, current size: " << renderObjects.size() << std::endl;

	return renderObjects.size();
}

void RenderManager::addNamedRenderable(std::string name, RenderableObject* object) {
	object->init(*this);
	namedRenderObjects.insert(std::pair(name, object));
	std::cout << "Added named render object: '" << name << "'" << std::endl;
}

void RenderManager::removeNamedRenderable(std::string name) {
	namedRenderObjects.erase(name);
}

ID3D11Device* RenderManager::getDevice() {
	return device.Get();
}

ID3D11DeviceContext* RenderManager::getContext() {
	return context.Get();
}

Camera* RenderManager::getCamera() {
	return camera;
}

CameraHandler* RenderManager::getCameraHandler() {
	return cameraHandler;
}

void RenderManager::beginRender() {
	context->ClearState();

	context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthView.Get());

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(window.getWidth());
	viewport.Height = static_cast<float>(window.getHeight());
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
	context->RSSetState(rastState.Get());

	float color[] = {0.0F, 0.0f, 0.0f, 1.0f};
	context->ClearRenderTargetView(renderTargetView.Get(), color);
	context->ClearDepthStencilView(depthView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0F, 0);
}

void RenderManager::render(float partialTick) {
	cameraHandler->update(partialTick);

	beginRender();

	for (auto& it : renderObjects) {
		it->getRenderType()->render(*this, *it);
	}

	for(const auto& it : namedRenderObjects) {
		//it.second->getRenderType()->render(*this, *it.second);
	}

	endRender();
}

void RenderManager::endRender() {
	context->OMSetRenderTargets(0, nullptr, nullptr);
	swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}
