#include "Textures.h"
#include <assert.h>

void Textures::Load() noexcept
{
	me = std::make_unique<olc::Sprite>("C:\\Users\\rahul\\source\\repos\\threedfundamentals\\threedfundamentals\\Texture\\me.png");
	dirt = std::make_unique<olc::Sprite>("C:\\Users\\rahul\\source\\repos\\threedfundamentals\\threedfundamentals\\Texture\\dirt.png");

	/*me = std::make_unique<olc::Sprite>("me.png");
	dirt = std::make_unique<olc::Sprite>("dirt.png");*/
}

const olc::Sprite* const Textures::GetMe() const noexcept
{
	assert(me != nullptr);
	return me.get();
}

const olc::Sprite* const Textures::GetDirt() const noexcept
{
	assert(dirt != nullptr);
	return dirt.get();
}
