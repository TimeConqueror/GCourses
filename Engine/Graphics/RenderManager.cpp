#include "RenderManager.h"
#include "../Utils.h"

static RenderType TRIANGLE_POS_COLOR{
	L"../Shaders/MyVeryFirstShader.hlsl", 
	VertexFormat(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	.add({
			"POSITION",
			DXGI_FORMAT_R32G32B32_FLOAT
		 })
	.add({
			"COLOR",
			DXGI_FORMAT_R32G32B32A32_FLOAT
		 })
};

RenderManager::RenderManager(Window& window): window(window) {

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
		D3D11_CREATE_DEVICE_DEBUG,
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

HRESULT RenderManager::initRenderTarget() {
	ID3D11Texture2D* backTex;
	HRESULT res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &backTex);	// __uuidof(ID3D11Texture2D)
	Utils::checkValid(res);

	return device->CreateRenderTargetView(backTex, nullptr, renderTargetView.GetAddressOf());
}

HRESULT RenderManager::initRasterizationState() {
	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	return device->CreateRasterizerState(&rastDesc, rastState.GetAddressOf());
}

uint width = 800;
uint height = 600;

std::vector<Vertex> points = {
		Vertex(0.5f, 0.5f, 1.0f),	
		Vertex(0.9f, 0.0f, 0.9f),
		Vertex(-1.0f, 1.0f, 1.0f)
};

std::vector<uint> indices = {1,2,0};
auto ro = RenderableObject(points, indices);


void RenderManager::init() {
	Utils::checkValid(initSwapChain());
	Utils::checkValid(initRenderTarget());
	Utils::checkValid(initRasterizationState());

	TRIANGLE_POS_COLOR.init(*this);	
	addRenderable("testo", ro);
}

void RenderManager::addRenderable(std::string name,RenderableObject& object) {
	object.init(*this);
	renderObjects.insert(std::pair<std::string, RenderableObject&>(name, object));
}

void RenderManager::removeRenderable(std::string name) {
	renderObjects.erase(name);
}

ID3D11Device* RenderManager::getDevice() {
	return device.Get();
}

ID3D11DeviceContext* RenderManager::getContext() {
	return context.Get();
}

void RenderManager::beginRender() {
	context->ClearState();
	context->RSSetState(rastState.Get());	

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(window.getWidth());
	viewport.Height = static_cast<float>(window.getHeight());
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
	context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

	float color[] = {1.0F, 1.0f, 1.0f, 1.0f};
	context->ClearRenderTargetView(renderTargetView.Get(), color);
}

void RenderManager::render() {
	beginRender();

	for (auto& it : renderObjects) {
		auto obj = it.second;
		auto data = ConstantBufferData(0.5F, 0.5F);
		obj.transform(*this, &data);
		TRIANGLE_POS_COLOR.render(*this, obj);
	}

	endRender();
}

void RenderManager::endRender() {
	context->OMSetRenderTargets(0, nullptr, nullptr);
	swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}
