#include "Shapes.h"

Cube::Cube(float size)
{

}


VertexObject<Eigen::Vector3f> Cube::GetTriangles(const float size) const noexcept
{
	const float side = size / 2.0f;

	std::vector<Eigen::Vector3f> vertices;

	vertices.emplace_back(-side, -side, -side); // 0
	vertices.emplace_back(side, -side, -side); // 1
	vertices.emplace_back(-side, side, -side); // 2
	vertices.emplace_back(side, side, -side); // 3
	vertices.emplace_back(-side, -side, side); // 4
	vertices.emplace_back(side, -side, side); // 5
	vertices.emplace_back(-side, side, side); // 6
	vertices.emplace_back(side, side, side); // 7

	std::vector<Eigen::Vector3f> verts(vertices.size());
	for (size_t i = 0; i < vertices.size(); i++)
	{
		verts[i] = vertices[i];
	}

	return
	{ std::move(vertices),
		{
			0, 2, 1,
			2, 3, 1,
			1, 3, 5,
			3, 7, 5,
			2, 6, 3,
			3, 6, 7,
			4, 5, 7,
			4, 7, 6,
			0, 4, 2,
			2, 4, 6,
			0, 1, 4,
			1, 5, 4
		}
	};
}

VertexObject<TexturedVertex> Cube::GetTexturedTriangles(const float size) const noexcept
{

	float side = size * 0.5f;
	std::vector<Eigen::Vector3f> vertices;
	std::vector<Eigen::Vector3f> tc;

	vertices.emplace_back(-side, -side, -side); // 0
	tc.emplace_back(1.0f, 0.0f, 1.0f);
	vertices.emplace_back(side, -side, -side); // 1
	tc.emplace_back(0.0f, 0.0f, 1.0f);
	vertices.emplace_back(-side, side, -side); // 2
	tc.emplace_back(1.0f, 1.0f, 1.0f);
	vertices.emplace_back(side, side, -side); // 3
	tc.emplace_back(0.0f, 1.0f, 1.0f);
	vertices.emplace_back(-side, -side, side); // 4
	tc.emplace_back(1.0f, 1.0f, 1.0f);
	vertices.emplace_back(side, -side, side); // 5
	tc.emplace_back(0.0f, 1.0f, 1.0f);
	vertices.emplace_back(-side, side, side); // 6
	tc.emplace_back(1.0f, 0.0f, 1.0f);
	vertices.emplace_back(side, side, side); // 7
	tc.emplace_back(0.0f, 0.0f, 1.0f);
	vertices.emplace_back(-side, -side, -side); // 8
	tc.emplace_back(1.0f, 0.0f, 1.0f);
	vertices.emplace_back(side, -side, -side); // 9
	tc.emplace_back(0.0f, 0.0f, 1.0f);
	vertices.emplace_back(-side, -side, -side); // 10
	tc.emplace_back(0.0f, 1.0f, 1.0f);
	vertices.emplace_back(-side, -side, side); // 11
	tc.emplace_back(0.0f, 0.0f, 1.0f);
	vertices.emplace_back(side, -side, -side); // 12
	tc.emplace_back(1.0f, 1.0f, 1.0f);
	vertices.emplace_back(side, -side, side); // 13
	tc.emplace_back(1.0f, 0.0f, 1.0f);

	std::vector<TexturedVertex> texturedVertices{ vertices.size() };
	assert(tc.size() == vertices.size());

	for (size_t i = 0; i < vertices.size(); i++)
	{
		texturedVertices[i].vertexPos = vertices[i];
		texturedVertices[i].texturePos = tc[i];
	}

	return
	{ std::move(texturedVertices),
		{
			0,2,1,   2,3,1,
			4,8,5,   5,8,9,
			2,6,3,   3,6,7,
			4,5,7,   4,7,6,
			2,10,11, 2,11,6,
			12,3,7,  12,7,13
	}
	};
}

