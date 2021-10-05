#pragma once
#include <vector>
#include "Eigen.h"

struct LineVertexObject
{
	std::vector<Eigen::Vector3f> vertices;
	std::vector<size_t> indices;
};

template<typename T>
struct VertexObject
{
	VertexObject() = default;

	VertexObject(std::vector<T> _vertices, std::vector<size_t> _indices) :
		vertices{ std::move(_vertices) },
		indices{ std::move(_indices) }
	{
		assert(vertices.size() > 2);
		assert(indices.size() % 3 == 0);
		cullFlags.resize(indices.size() / 3);
	}

	std::vector<T> vertices;
	std::vector<size_t> indices;
	std::vector<bool> cullFlags;
};
