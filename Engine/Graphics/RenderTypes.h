#pragma once

#include <vector>
#include "RenderType.h"

class RenderTypes {
	friend class RenderManager;
	static std::vector<RenderType> types;
public:
	static RenderType LINELIST_POS_COLOR;
	static RenderType TRIANGLELIST_POS_COLOR;
	static RenderType TRIANGLESTRIP_POS_COLOR;
	// static RenderType TRIANGLELIST_POS_UV;
	static RenderType TRIANGLELIST_POS_NORMAL_UV;
	static RenderType SHADOW_MAP;

	static void init(RenderManager& renderManager);
};
