#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace obj2D
{

	Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float lengthX, float lengthY, glm::vec3 color, bool fill = false);

	
}
