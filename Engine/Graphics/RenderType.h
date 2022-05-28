#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "../Utils.h"
#include "VertexFormat.h"

class RenderManager;
class RenderableObject;

class RenderType {
private: 
	LPCWSTR shaderPath;
	VertexFormat vertexFormat;
	Microsoft::WRL::ComPtr<ID3DBlob> vertexByteCode;
	Microsoft::WRL::ComPtr<ID3DBlob> pixelByteCode;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
public:
	RenderType(LPCWSTR shaderPath, VertexFormat& vertexFormat);
	RenderType(RenderType&& other) noexcept = default;
	RenderType& operator=(RenderType&& other) noexcept = default;

	void render(RenderManager& renderManager, RenderableObject& object);
	void init(RenderManager& renderManager);
	void pushShaders(RenderManager& renderManager);
private:
	HRESULT compileVertexShader();
	HRESULT compilePixelShader();
	HRESULT createVertexShader(ID3D11Device* device);
	HRESULT createPixelShader(ID3D11Device* device);
	static HRESULT compileShader(LPCWSTR path, LPCSTR entryPoint, LPCSTR target, ID3DBlob** byteCode);
	HRESULT createLayout(ID3D11Device* device);
};

