#pragma once
#include "Eigen.h"

class TexturedVertex
{
public:
	TexturedVertex() = default; //remove later, just for testing
	TexturedVertex(const Eigen::Vector3f& v, const Eigen::Vector3f& t);
	TexturedVertex InterpolateTo(const TexturedVertex& v, float alpha) const;

public:
	Eigen::Vector3f vertexPos;
	Eigen::Vector3f texturePos;
};

