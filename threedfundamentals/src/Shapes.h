#pragma once
#include "VertexObject.h"
#include "TexturedVertex.h"

class Cube
{
public:
	Cube(float size);

public:
	VertexObject<Eigen::Vector3f> GetTriangles(const float size = 1.0f) const noexcept;
	VertexObject<TexturedVertex> GetTexturedTriangles(const float size = 1.0f) const noexcept;
	
private:
	std::vector<Eigen::Vector3f> vertices;
	std::vector<Eigen::Vector3f> tc;
};

