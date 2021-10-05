#pragma once
#include "olcPixelGameEngine.h"
#include "Eigen.h"
#include "TexturedVertex.h"

class TriangleRaster
{
private:
	static void DrawFlatTopTriangle(olc::PixelGameEngine* pge, const Eigen::Vector3f& v0,
		const Eigen::Vector3f& v1, const Eigen::Vector3f& v2, olc::Pixel c);

	static void DrawFlatBottomTriangle(olc::PixelGameEngine* pge, const Eigen::Vector3f& v0,
		const Eigen::Vector3f& v1, const Eigen::Vector3f& v2, olc::Pixel c);
	
	static void DrawTexturedFlatTopTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0,
	const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture);

	static void DrawTexturedFlatBottomTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0,
		const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture);

	static void DrawWrappedTexturedFlatTopTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0,
		const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture, float wrap);

	static void DrawWrappedTexturedFlatBottomTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0,
		const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture, float wrap);

public:
	static void DrawTriangle(olc::PixelGameEngine* pge, const Eigen::Vector3f& v0,
		const Eigen::Vector3f& v1, const Eigen::Vector3f& v2, olc::Pixel c);

	static void DrawTexturedTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0,
		const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture);

	static void DrawWrappedTexturedTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0,
		const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture, float wrap);
};

