#include "RenderType.h"
#include "RenderManager.h"
#include "../Utils.h"
#include "../Game.h"
#include <iostream>

RenderType::RenderType(LPCWSTR shaderPath, VertexFormat& vertexFormat): shaderPath(shaderPath), vertexFormat(vertexFormat) {
}

void RenderType::render(RenderManager& renderManager, RenderableObject& object) {
	//ID3D11RasterizerState* oldState;
	//renderManager.getContext()->RSGetState(&oldState);
	//renderManager.getContext()->RSGetState(&oldState);
	pushShaders(renderManager);//TODO move outside to render many same-arch objects

	object.prepare(renderManager);

	object.vertexBuffer.push(renderManager);
	object.indexBuffer.push(renderManager);
	object.constantBuffer.push(renderManager);

	renderManager.getContext()->IASetPrimitiveTopology(vertexFormat.getTopology());
	renderManager.getContext()->DrawIndexed(object.indexBuffer.getSize(), 0, 0);
}

void RenderType::init(RenderManager& renderManager) {
	Utils::checkValid(compileVertexShader());
	Utils::checkValid(compilePixelShader());

	ID3D11Device* device = renderManager.getDevice();
	Utils::checkValid(createVertexShader(device));
	Utils::checkValid(createPixelShader(device));
	Utils::checkValid(createLayout(device));
}

void RenderType::pushShaders(RenderManager& renderManager) {
	ID3D11DeviceContext* ctx = renderManager.getContext();

	ctx->IASetInputLayout(layout.Get());
	ctx->IASetPrimitiveTopology(vertexFormat.getTopology());
	ctx->VSSetShader(vertexShader.Get(), nullptr, 0);
	ctx->PSSetShader(pixelShader.Get(), nullptr, 0);
}

HRESULT RenderType::compileVertexShader() {
	return compileShader(
		shaderPath,
		"VSMain",
		"vs_5_0",
		&vertexByteCode);
}

HRESULT RenderType::compilePixelShader() {
	return compileShader(
		shaderPath,
		"PSMain",
		"ps_5_0",
		&pixelByteCode);
}

HRESULT RenderType::compileShader(LPCWSTR path, LPCSTR entryPoint, LPCSTR target, ID3DBlob** byteCode) {
	ID3DBlob* errorCode = nullptr;
	HRESULT res = D3DCompileFromFile(path,
							 nullptr /*macros*/,
							 nullptr /*include*/,
							 entryPoint,
							 target,
							 D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
							 0,
							 byteCode,
							 &errorCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorCode) {
			char* compileErrors = (char*) (errorCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else {
			HWND hWnd = Game::getInstance()->getWindow().getHWnd();
			MessageBox(hWnd, path, L"Missing Shader File", MB_OK);
		}

		return res;
	}
}

HRESULT RenderType::createVertexShader(ID3D11Device* device) {
	return device->CreateVertexShader(
		vertexByteCode->GetBufferPointer(),
		vertexByteCode->GetBufferSize(),
		nullptr,
		&vertexShader);
}

HRESULT RenderType::createPixelShader(ID3D11Device* device) {
	return device->CreatePixelShader(
		pixelByteCode->GetBufferPointer(),
		pixelByteCode->GetBufferSize(),
		nullptr,
		&pixelShader);
}

HRESULT RenderType::createLayout(ID3D11Device* device) {
	return device->CreateInputLayout(
		&vertexFormat.getFront(),
		vertexFormat.getSize(),
		vertexByteCode->GetBufferPointer(),
		vertexByteCode->GetBufferSize(),
		&layout);
}
