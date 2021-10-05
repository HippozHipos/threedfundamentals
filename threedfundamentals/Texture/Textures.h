#pragma once
#include "../src/olcPixelGameEngine.h"

class Textures
{
public:
	void Load() noexcept;
	const olc::Sprite* const GetMe() const noexcept;
	const olc::Sprite* const GetDirt() const noexcept;

private:
	std::unique_ptr<olc::Sprite> me = nullptr;
	std::unique_ptr<olc::Sprite> dirt = nullptr;
};

