// #include "ShadowMap.h"
//
// #include "RenderType.h"
// #include "RenderTypes.h"
// #include "Graphics/RenderManager.h"
// #include "Renderables/ModelBasedRenderable.h"
//
// void ShadowMap::init(RenderManager* renderManager) {
// 	this->width = renderManager->getWindow().getWidth();
// 	this->height = renderManager->getWindow().getHeight();
// 	initViewport();
// 	WRL::ComPtr<ID3D11Texture2D> depthMap;
//
// 	Utils::checkValid(initDepthMap(renderManager, depthMap.GetAddressOf()));
// 	Utils::checkValid(initDepthBuffer(renderManager, depthMap.Get()));
// 	Utils::checkValid(initShadowMap(renderManager, depthMap.Get()));
// 	Utils::checkValid(buffer.init(renderManager->getDevice()));
// }
//
// void ShadowMap::initViewport() {
// 	viewport.TopLeftX = 0.0f;
// 	viewport.TopLeftY = 0.0f;
// 	viewport.Width = static_cast<float>(width);
// 	viewport.Height = static_cast<float>(height);
// 	viewport.MinDepth = 0.0f;
// 	viewport.MaxDepth = 1.0f;
// }
//
// HRESULT ShadowMap::initDepthMap(RenderManager* renderManager, ID3D11Texture2D** depthMap) const {
// 	D3D11_TEXTURE2D_DESC depthMapDesc = {};
// 	depthMapDesc.Width = width;
// 	depthMapDesc.Height = height;
// 	depthMapDesc.MipLevels = 1;
// 	depthMapDesc.ArraySize = 1;
// 	depthMapDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
// 	depthMapDesc.SampleDesc.Count = 1;
// 	depthMapDesc.SampleDesc.Quality = 0;
// 	depthMapDesc.Usage = D3D11_USAGE_DEFAULT;
// 	depthMapDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
// 	depthMapDesc.CPUAccessFlags = 0;
// 	depthMapDesc.MiscFlags = 0;
//
// 	return renderManager->getDevice()->CreateTexture2D(&depthMapDesc, nullptr, depthMap);
// }
//
// HRESULT ShadowMap::initDepthBuffer(RenderManager* renderManager, ID3D11Texture2D* depthMap) {
// 	D3D11_DEPTH_STENCIL_VIEW_DESC depthBufferDesc = {};
// 	depthBufferDesc.Flags = 0;
// 	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
// 	depthBufferDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
// 	depthBufferDesc.Texture2D.MipSlice = 0;
//
// 	return renderManager->getDevice()->CreateDepthStencilView(
// 		depthMap, &depthBufferDesc, depthBuffer.GetAddressOf());
// }
//
// HRESULT ShadowMap::initShadowMap(RenderManager* renderManager, ID3D11Texture2D* depthMap) {
// 	D3D11_SHADER_RESOURCE_VIEW_DESC shadowMapDesc = {};
// 	shadowMapDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
// 	shadowMapDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
// 	shadowMapDesc.Texture2D.MipLevels = 1;
// 	shadowMapDesc.Texture2D.MostDetailedMip = 0;
//
// 	return renderManager->getDevice()->CreateShaderResourceView(
// 		depthMap, &shadowMapDesc, shadowMapView.GetAddressOf());
// }
//
// void ShadowMap::setCustomRenderTarget(RenderManager* renderManager) const {
// 	ID3D11RenderTargetView* renderTarget[1] = {nullptr};
// 	renderManager->getContext()->RSSetViewports(1, &viewport);
// 	renderManager->getContext()->OMSetRenderTargets(1, renderTarget, depthBuffer.Get());
// 	renderManager->getContext()->ClearDepthStencilView(depthBuffer.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
// }
//
// void ShadowMap::render(RenderManager* renderManager) {
// 	// setCustomRenderTarget(renderManager);
// 	// RenderTypes::SHADOW_MAP.pushShaders(*renderManager);
// 	//
// 	// buffer.pushForVertexShader(*renderManager, 0);
// 	// std::vector<IRenderable*>* renderables = renderManager->getRenderables();
// 	//
// 	// for (int i = 0; i < renderables->size(); i++) {
// 	// 	auto r = (*renderables)[i];
// 	//
// 	// 	auto modelBasedRenderable = dynamic_cast<ModelBasedRenderable*>(r);
// 	// 	if (modelBasedRenderable != nullptr) {
// 	// 		ShadowMapShaderTransform shadowMapShaderTransform = ShadowMapShaderTransform{ renderManager->getLightSource()->calcViewProjForRenderable(modelBasedRenderable) };
// 	// 		transform(renderManager, shadowMapShaderTransform);
// 	//
// 	// 		modelBasedRenderable->getTexture()->pushAsShaderResource(*renderManager, 0);
// 	// 		Model* model = modelBasedRenderable->getModel();
// 	// 		std::vector<VertexBuffer<PTVertex>>& vertexBuffers = model->getVertexBuffers();
// 	// 		std::vector<IndexBuffer>& indexBuffers = model->getIndexBuffers();
// 	// 		for (int j = 0; j < vertexBuffers.size(); ++j) {
// 	// 			vertexBuffers[j].push(*renderManager);
// 	// 			indexBuffers[j].push(*renderManager);
// 	// 			renderManager->getContext()->DrawIndexed(indexBuffers[j].getSize(), 0, 0);
// 	// 		}
// 	// 	}
// 	// }
// }
//
// void ShadowMap::transform(RenderManager* renderManager, ShadowMapShaderTransform& data) {
// 	buffer.update(*renderManager, &data);
// }
//
// void ShadowMap::pushShadowMapTexture(RenderManager* renderManager, int slot) {
// 	renderManager->getContext()->PSSetShaderResources(slot, 1, shadowMapView.GetAddressOf());
// }
