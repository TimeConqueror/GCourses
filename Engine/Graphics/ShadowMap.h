// #pragma once
// #include <wrl/client.h>
//
// #include "ConstantBuffer.h"
// #include "Graphics/Shape.h"
// #include "Renderables/IRenderable.h"
//
// struct ShadowMapShaderTransform {
// 	DirectX::SimpleMath::Matrix worldXLightViewProj;
// };
//
// class ShadowMap {
// private:
// 	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shadowMapView;
// 	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthBuffer;
// 	D3D11_VIEWPORT viewport;
// 	uint width = -1;
// 	uint height = -1;
// 	ConstantBuffer<ShadowMapShaderTransform> buffer;
// public:
// 	ShadowMap(): shadowMapView(nullptr)
// 	             , depthBuffer(nullptr)
// 	             , viewport{} {
// 	}
//
// 	void init(RenderManager* renderManager);
// 	void pushShadowMapTexture(RenderManager* renderManager, int slot = 0);
// 	void render(RenderManager* renderManager);
// 	void transform(RenderManager* renderManager, ShadowMapShaderTransform& data);
// private:
// 	void initViewport();
//
// 	HRESULT initDepthMap(RenderManager* renderManager, ID3D11Texture2D** depthMap) const;
//
// 	HRESULT initDepthBuffer(RenderManager* renderManager, ID3D11Texture2D* depthMap);
//
// 	HRESULT initShadowMap(RenderManager* renderManager, ID3D11Texture2D* depthMap);
//
// 	void setCustomRenderTarget(RenderManager* renderManager) const;
// };
