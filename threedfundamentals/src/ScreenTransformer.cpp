#include "ScreenTransformer.h"

PubeScreenTransformer::PubeScreenTransformer() = default;

PubeScreenTransformer::PubeScreenTransformer(const olc::PixelGameEngine* const pge) : 
	factor{ (float)pge->ScreenWidth() * 0.5f, (float)pge->ScreenHeight() * 0.5f }
{
}

Eigen::Vector3f PubeScreenTransformer::GetTrasformed(const Eigen::Vector3f& v)
{
	Eigen::Vector3f out;
	const float zInv = 1.0f / v.z();
	out.x() = (v.x() * zInv + 1.0f) * factor.x();
	out.y() = (-v.y() * zInv + 1.0f) * factor.y();
	return out;
}
