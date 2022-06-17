#pragma once

#include <d3d11.h>
#include <DirectXTex.h>
#include <wrl/client.h>

class RenderManager;

class Texture {
	friend class TextureDefinition;
private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView = nullptr;
public:
	Texture() = default;
	Texture(Texture&& other) = default;
	Texture& operator=(Texture&& other) = default;

	void pushAsShaderResource(RenderManager& renderManager, int slot);
};

class TextureDefinition {
	friend class Texture;
private:
	DirectX::ScratchImage image;

public:
	explicit TextureDefinition(const wchar_t* path): image(load(path)){}

	Texture bake(RenderManager& renderManager);
private:
	static DirectX::ScratchImage load(const wchar_t* path);
};
