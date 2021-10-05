#include "Controls.h"

Controls::Controls(float rotationSensitivity, float offsetSensitivity) :
	rotationSensitivity{ rotationSensitivity },
	offsetSensitivity { offsetSensitivity }
{
}

void Controls::ChangeRoll(const olc::PixelGameEngine* const pge, const olc::Key& key, float& roll)
{
	if (pge->GetKey(key).bHeld) 
		roll += rotationSensitivity * pge->GetElapsedTime();
}

void Controls::ChangePitch(const olc::PixelGameEngine* const pge, const olc::Key& key, float& pitch)
{
	if (pge->GetKey(key).bHeld) 
		pitch += rotationSensitivity * pge->GetElapsedTime();
}

void Controls::ChangeYaw(const olc::PixelGameEngine* const pge, const olc::Key& key, float& yaw)
{
	if (pge->GetKey(key).bHeld)
		yaw += rotationSensitivity * pge->GetElapsedTime();
}

void Controls::ChnageZOffset(const olc::PixelGameEngine* const pge, const olc::Key& key, const olc::Key& key1, float& offset)
{
	if (pge->GetKey(key).bHeld)
		offset += offsetSensitivity * pge->GetElapsedTime();
	if (pge->GetKey(key1).bHeld)
		offset -= offsetSensitivity * pge->GetElapsedTime();
}

void ChangeWrap(const olc::PixelGameEngine* const pge, olc::Key up, olc::Key down, float amount, float& times)
{
	if (pge->GetKey(up).bHeld)
		times += amount * pge->GetElapsedTime();

	if (pge->GetKey(down).bHeld)
		times -= amount * pge->GetElapsedTime();
}
