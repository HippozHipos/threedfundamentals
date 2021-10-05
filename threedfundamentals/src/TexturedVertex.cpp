#include "TexturedVertex.h"

TexturedVertex::TexturedVertex(const Eigen::Vector3f& v, const Eigen::Vector3f& t) :
	vertexPos{ v },
	texturePos{ t }
{
}

TexturedVertex TexturedVertex::InterpolateTo(const TexturedVertex& tv, float alpha) const
{
	return
	{
		vertexPos + (tv.vertexPos - vertexPos) * alpha,
		texturePos + (tv.texturePos - texturePos) * alpha
	};
}
