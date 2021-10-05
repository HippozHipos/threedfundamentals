#pragma once
#include "olcPixelGameEngine.h"

class Controls
{
public:
	Controls(float rotationSensitivity, float offsetSensitivity);

public:
	void ChangeRoll(const olc::PixelGameEngine* const pge, const olc::Key& key, float& roll);
	void ChangePitch(const olc::PixelGameEngine* const pge, const olc::Key&, float& pitch);
	void ChangeYaw(const olc::PixelGameEngine* const pge, const olc::Key&, float& yaw);
	void ChnageZOffset(const olc::PixelGameEngine* const pge, const olc::Key&, const olc::Key&, float& offset);

public:
	float rotationSensitivity = 1.0f;
	float offsetSensitivity = 1.0f;
};

void ChangeWrap(const olc::PixelGameEngine* const pge, olc::Key up, olc::Key down, float amount, float& times);