// #include "DirectionalLightSource.h"
// #include "RenderManager.h"
//
// DirectX::SimpleMath::Matrix DirectionalLightSource::calcViewProjForRenderable(BaseRenderable* r) {
// 	//TODO change for Actor.h
// 	const auto viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(
// 		DirectX::SimpleMath::Vector3(0, 100, 0),
// 		DirectX::SimpleMath::Vector3(0, 100, 0) + direction,
// 		DirectX::SimpleMath::Vector3::UnitY);
//
// 	const auto projMatrix = DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 30.0f);
//
// 	return viewMatrix * projMatrix;
// }
//
// void DirectionalLightSource::init(RenderManager* renderManager) {
// 	shadowMap.init(renderManager);
// }
//
// void DirectionalLightSource::pushShadowMapTexture(RenderManager* renderManager, uint slot = 0) {
// 	shadowMap.pushShadowMapTexture(renderManager, slot);
// }
