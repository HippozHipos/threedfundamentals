#define OLC_PGE_APPLICATION
#include "SolidCubeScene.h"
#include "TexturedCubeScene.h"
#include "WrappedCubeScene.h"
#include "TriangleRaster.h"
#include "../Texture/Textures.h"

class ThreeDFundamentals : public olc::PixelGameEngine
{
public:
	ThreeDFundamentals()
	{
		sAppName = "ThreeDFundamentals";
	}

public:
	bool OnUserCreate() override
	{
		textures.Load();
		scenes.push_back(std::make_unique<SolidSceneScene>( this ));
		scenes.push_back(std::make_unique<TexcuredCubeScene>(this, textures.GetDirt()));
		scenes.push_back(std::make_unique<TexcuredCubeScene>( this, textures.GetMe()));
		scenes.push_back(std::make_unique<WrappedCubeScene>(this, textures.GetMe()));
		currentScene = scenes.begin();
		return true;
	}

	bool OnUserUpdate(float elapsedTime) override
	{
		if (GetKey(olc::TAB).bReleased)
		{
			if (++currentScene == scenes.end())
			{
				currentScene = scenes.begin();
			}
		}

		(*currentScene)->Update(this);
		(*currentScene)->Draw(this);

		return true;
	}

private:
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<std::unique_ptr<Scene>>::iterator currentScene;
	Textures textures;
};

int main()
{
	ThreeDFundamentals threeDFundamentals;
	if (threeDFundamentals.Construct(600, 600, 1, 1))
		threeDFundamentals.Start();
}

