#pragma once
#include "Scene.h"
#include "Shapes.h"
#pragma warning(push)
#pragma warning(disable: 26812) 
#include "Controls.h"
#pragma warning(pop)
#include "ScreenTransformer.h"
#include "../Texture/Textures.h"

class WrappedCubeScene : public Scene
{
public:
	WrappedCubeScene(olc::PixelGameEngine* pge, const olc::Sprite* const texture);

public:
	virtual void Update(const olc::PixelGameEngine* const pge) override;
	virtual void Draw(olc::PixelGameEngine* pge) const override;

private:
	Cube cube{ 1.0f };
	PubeScreenTransformer pubeScreenTransformer;
	Controls controls{ 3.0f, 1.0f };

	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	Eigen::Vector3f offset = { 0.0f, 0.0f, 3.0f };
	VertexObject<TexturedVertex> triangles;
	const olc::Sprite* const texture = nullptr;

	float wrapTimes = 2.0f;
};
