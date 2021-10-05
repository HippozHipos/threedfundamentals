#pragma once
#include "Scene.h"
#include "Shapes.h"
#pragma warning(push)
#pragma warning(disable: 26812) 
#include "Controls.h"
#pragma warning(pop)
#include "ScreenTransformer.h"

class SolidSceneScene : public Scene
{
public:
	SolidSceneScene(olc::PixelGameEngine* pge);

public:
	virtual void Update(const olc::PixelGameEngine* const pge) override;
	virtual void Draw(olc::PixelGameEngine* pge) const override;

private:

	Cube cube{ 1.0f };
	PubeScreenTransformer pubeScreenTransformer;
	Controls controls{ 3.0f, 1.0f };

	olc::Pixel colorArray[12] =
	{
		olc::RED,
		olc::RED,
		olc::GREEN,
		olc::GREEN,
		olc::CYAN,
		olc::CYAN,
		olc::YELLOW,
		olc::YELLOW,
		olc::MAGENTA,
		olc::MAGENTA,
		olc::BLUE,
		olc::BLUE
	};

	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	Eigen::Vector3f offset = { 0.0f, 0.0f, 3.0f };

	VertexObject<Eigen::Vector3f> triangles;
};

