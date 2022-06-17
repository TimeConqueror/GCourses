#include "Texture.h"
#include "RenderManager.h"

void Texture::pushAsShaderResource(RenderManager& renderManager, int slot) {
	renderManager.getContext()->PSSetShaderResources(slot, 1, textureView.GetAddressOf());
}

Texture TextureDefinition::bake(RenderManager& renderManager) {
	Texture texture;
	Utils::checkValid(CreateTextureEx(
		renderManager.getDevice(),
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET,
		0, 0, false,
		reinterpret_cast<ID3D11Resource**>(texture.texture.GetAddressOf())));

	renderManager.getDevice()->CreateShaderResourceView(texture.texture.Get(), nullptr, texture.textureView.GetAddressOf());

	this->image.Release();

	return std::move(texture);
}

DirectX::ScratchImage TextureDefinition::load(const wchar_t* path) {
	DirectX::ScratchImage image;
	Utils::checkValid(
		LoadFromWICFile(
			path,
			DirectX::WIC_FLAGS_NONE,
			nullptr,
			image)
	);
	return std::move(image);
}
