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

	static void init(RenderManager& renderManager);
};