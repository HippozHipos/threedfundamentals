#pragma once
#include "olcPixelGameEngine.h"

class Scene
{
public:
	virtual void Update(const olc::PixelGameEngine* const pge) = 0;
	virtual void Draw(olc::PixelGameEngine* pge) const = 0;
	virtual ~Scene() = default;
};

