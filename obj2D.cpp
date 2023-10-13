#include "obj2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* obj2D::CreateSquare(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float lengthX,
	float lengthY,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(lengthX, 0, 0), color),
		VertexFormat(corner + glm::vec3(lengthX, lengthY, 0), color),
		VertexFormat(corner + glm::vec3(0, lengthY, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

