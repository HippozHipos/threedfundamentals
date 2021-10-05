#pragma once
#include "Eigen.h"
#include "olcPixelGameEngine.h"

class PubeScreenTransformer
{
public:
	PubeScreenTransformer();
	explicit PubeScreenTransformer(const olc::PixelGameEngine* const pge);

public:
	Eigen::Vector3f GetTrasformed(const Eigen::Vector3f& v);

private:
	Eigen::Vector2f factor;
};

