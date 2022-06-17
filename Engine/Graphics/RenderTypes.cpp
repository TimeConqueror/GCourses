#include "RenderTypes.h"

RenderType RenderTypes::LINELIST_POS_COLOR {
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

RenderType RenderTypes::TRIANGLELIST_POS_COLOR {
	L"../Shaders/MyVeryFirstShader.hlsl",
	VertexFormat(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	.add({
			"POSITION",
			DXGI_FORMAT_R32G32B32A32_FLOAT
		 })
	.add({
			"COLOR",
			DXGI_FORMAT_R32G32B32A32_FLOAT
		 })
};

RenderType RenderTypes::TRIANGLELIST_POS_UV{
	L"Assets/ModelShader.hlsl",
	VertexFormat(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	.add({
			"POSITION",
			DXGI_FORMAT_R32G32B32_FLOAT
		 })
	.add({
			"TEXCOORD",
			DXGI_FORMAT_R32G32_FLOAT
		 })
};

RenderType RenderTypes::TRIANGLESTRIP_POS_COLOR {
L"../Shaders/MyVeryFirstShader.hlsl",
VertexFormat(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)
.add({
		"POSITION",
		DXGI_FORMAT_R32G32B32A32_FLOAT
	 })
.add({
		"COLOR",
		DXGI_FORMAT_R32G32B32A32_FLOAT
	 })
};

void RenderTypes::init(RenderManager& renderManager) {
	LINELIST_POS_COLOR.init(renderManager);
	TRIANGLELIST_POS_COLOR.init(renderManager);
	TRIANGLESTRIP_POS_COLOR.init(renderManager);
	TRIANGLELIST_POS_UV.init(renderManager);
}
