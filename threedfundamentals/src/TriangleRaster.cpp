#include "TriangleRaster.h"

void TriangleRaster::DrawFlatTopTriangle(olc::PixelGameEngine* pge, const Eigen::Vector3f& v0,
	const Eigen::Vector3f& v1, const Eigen::Vector3f& v2, olc::Pixel c)
{
	float v2v0Slope = (v2.x() - v0.x()) / (v2.y() - v0.y());
	float v2v1Slope = (v2.x() - v1.x()) / (v2.y() - v1.y());

	int startY = (int)std::ceil(v0.y() - 0.5f);
	int endY = (int)std::ceil(v2.y() - 0.5f);

	for (int y = startY; y < endY; y++)
	{
		float _startX = v2v0Slope * (y + 0.5f - v0.y()) + v0.x();
		float _endX = v2v1Slope * (y + 0.5f - v1.y()) + v1.x();

		int startX = (int)std::ceil(_startX - 0.5f);
		int endX = (int)std::ceil(_endX - 0.5f);

		for (int x = startX; x < endX; x++)
		{
			pge->Draw(x, y, c);
		}
	}
}

void TriangleRaster::DrawFlatBottomTriangle(olc::PixelGameEngine* pge, const Eigen::Vector3f& v0,
	const Eigen::Vector3f& v1, const Eigen::Vector3f& v2, olc::Pixel c)
{
	float v0v1Slope = (v0.x() - v1.x()) / (v0.y() - v1.y());
	float v0v2Slope = (v0.x() - v2.x()) / (v0.y() - v2.y());

	int startY = (int)std::ceil(v0.y() - 0.5f);
	int endY = (int)std::ceil(v2.y() - 0.5f);

	for (int y = startY; y < endY; y++)
	{
		float _startX = v0v1Slope * (y + 0.5f - v1.y()) + v1.x();
		float _endX = v0v2Slope * (y + 0.5f - v2.y()) + v2.x();

		int startX = (int)std::ceil(_startX - 0.5f);
		int endX = (int)std::ceil(_endX - 0.5f);

		for (int x = startX; x < endX; x++)
		{
			pge->Draw(x, y, c);
		}
	}
}

void TriangleRaster::DrawTriangle(olc::PixelGameEngine* pge, const Eigen::Vector3f& v0,
	const Eigen::Vector3f& v1, const Eigen::Vector3f& v2, olc::Pixel c)
{
	const Eigen::Vector3f* pv0 = &v0;
	const Eigen::Vector3f* pv1 = &v1;
	const Eigen::Vector3f* pv2 = &v2;

	if (pv1->y() < pv0->y()) std::swap(pv1, pv0);
	if (pv2->y() < pv1->y()) std::swap(pv2, pv1);
	if (pv1->y() < pv0->y()) std::swap(pv1, pv0);

	//float top
	if (pv0->y() == pv1->y())
	{
		if (pv0->x() > pv1->x()) std::swap(pv0, pv1);
		DrawFlatTopTriangle(pge, *pv0, *pv1, *pv2, c);
	}

	//float bottom
	else if (pv1->y() == pv2->y())
	{
		if (pv1->x() > pv2->x()) std::swap(pv1, pv2);
		DrawFlatBottomTriangle(pge, *pv0, *pv1, *pv2, c);
	}

	else
	{
		float alpha = (pv1->y() - pv0->y()) / (pv2->y() - pv0->y());
		Eigen::Vector3f split = *pv0 + (*pv2 - *pv0) * alpha;

		//major left
		if (split.x() < pv1->x())
		{
			DrawFlatTopTriangle(pge, split, *pv1, *pv2, c);
			DrawFlatBottomTriangle(pge, *pv0, split, *pv1, c);
		}
		else //major right
		{
			DrawFlatBottomTriangle(pge, *pv0, *pv1, split, c);
			DrawFlatTopTriangle(pge, *pv1, split, *pv2, c);
		}
	}
}

void TriangleRaster::DrawTexturedFlatTopTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0, const TexturedVertex& v1, 
	const TexturedVertex& v2, const olc::Sprite* const texture)
{

	float v2v0Slope = (v2.vertexPos.x() - v0.vertexPos.x()) / (v2.vertexPos.y() - v0.vertexPos.y());
	float v2v1Slope = (v2.vertexPos.x() - v1.vertexPos.x()) / (v2.vertexPos.y() - v1.vertexPos.y());

	int startY = (int)std::ceil(v0.vertexPos.y() - 0.5f);
	int endY = (int)std::ceil(v2.vertexPos.y() - 0.5f);

	Eigen::Vector3f texStepRight = (v2.texturePos - v1.texturePos).array() / (v2.vertexPos.y() - v1.vertexPos.y());
	Eigen::Vector3f texStepLeft = (v2.texturePos - v0.texturePos).array() / (v2.vertexPos.y() - v0.vertexPos.y());

	Eigen::Vector3f texLeft = v0.texturePos;
	Eigen::Vector3f texRight = v1.texturePos;

	texLeft += texStepLeft *((float)startY + 0.5f - v0.vertexPos.y());
	texRight += texStepRight * ((float)startY + 0.5f - v1.vertexPos.y());

	Eigen::Vector3f texSize = { (float)texture->width, (float)texture->height, 1.0f };
	Eigen::Vector3f texClamp = { texSize.x() - 1.0f, texSize.y() - 1.0f, 1.0f };

	for (int y = startY; y < endY; 
		y++, texLeft += texStepLeft, texRight += texStepRight)
	{
		float _startX = v2v0Slope * (y + 0.5f - v0.vertexPos.y()) + v0.vertexPos.x();
		float _endX = v2v1Slope * (y + 0.5f - v1.vertexPos.y()) + v1.vertexPos.x();

		int startX = (int)std::ceil(_startX - 0.5f);
		int endX = (int)std::ceil(_endX - 0.5f);

		Eigen::Vector3f texStepX = (texRight - texLeft) / (_endX - _startX);
		Eigen::Vector3f texPos = texLeft + texStepX * ((float)startX + 0.5f - _startX);

		for (int x = startX; x < endX; x++, texPos += texStepX)
		{
			pge->Draw(x, y,
				texture->GetPixel(
					(uint32_t)std::min(texPos.x() * texture->width, texClamp.x()),
					(uint32_t)std::min(texPos.y() * texture->height, texClamp.y())
				));
		}
	}
}

void TriangleRaster::DrawTexturedFlatBottomTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0, const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture)
{
	float v0v1Slope = (v0.vertexPos.x() - v1.vertexPos.x()) / (v0.vertexPos.y() - v1.vertexPos.y());
	float v0v2Slope = (v0.vertexPos.x() - v2.vertexPos.x()) / (v0.vertexPos.y() - v2.vertexPos.y());

	int startY = (int)std::ceil(v0.vertexPos.y() - 0.5f);
	int endY = (int)std::ceil(v2.vertexPos.y() - 0.5f);

	Eigen::Vector3f texStepRight = (v2.texturePos - v0.texturePos).array() / (v2.vertexPos.y() - v0.vertexPos.y());
	Eigen::Vector3f texStepLeft = (v1.texturePos - v0.texturePos).array() / (v1.vertexPos.y() - v0.vertexPos.y());

	Eigen::Vector3f texLeft = v0.texturePos;
	Eigen::Vector3f texRight = v0.texturePos;

	texLeft += texStepLeft * ((float)startY + 0.5f - v0.vertexPos.y());
	texRight += texStepRight * ((float)startY + 0.5f - v0.vertexPos.y());

	Eigen::Vector3f texSize = { (float)texture->width, (float)texture->height, 1.0f };
	Eigen::Vector3f texClamp = { texSize.x() - 1.0f, texSize.y() - 1.0f, 1.0f };

	for (int y = startY; y < endY; 
		y++, texLeft += texStepLeft, texRight += texStepRight)
	{
		float _startX = v0v1Slope * (y + 0.5f - v1.vertexPos.y()) + v1.vertexPos.x();
		float _endX = v0v2Slope * (y + 0.5f - v2.vertexPos.y()) + v2.vertexPos.x();

		int startX = (int)std::ceil(_startX - 0.5f);
		int endX = (int)std::ceil(_endX - 0.5f);

		Eigen::Vector3f texStepX = (texRight - texLeft) / (_endX - _startX);
		Eigen::Vector3f texPos = texLeft + texStepX * ((float)startX + 0.5f - _startX);

		for (int x = startX; x < endX; x++, texPos += texStepX)
		{
			pge->Draw(x, y,
				texture->GetPixel(
					(uint32_t)std::min(texPos.x() * texture->width, texClamp.x()),
					(uint32_t)std::min(texPos.y() * texture->height, texClamp.y())
				));
		}
	}
}

void TriangleRaster::DrawTexturedTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0, const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture)
{
	const TexturedVertex* pv0 = &v0;
	const TexturedVertex* pv1 = &v1;
	const TexturedVertex* pv2 = &v2;

	if (pv1->vertexPos.y() < pv0->vertexPos.y()) std::swap(pv1, pv0);
	if (pv2->vertexPos.y() < pv1->vertexPos.y()) std::swap(pv2, pv1);
	if (pv1->vertexPos.y() < pv0->vertexPos.y()) std::swap(pv1, pv0);

	//float top
	if (pv0->vertexPos.y() == pv1->vertexPos.y())
	{
		if (pv0->vertexPos.y() > pv1->vertexPos.y()) std::swap(pv0, pv1);
		DrawTexturedFlatTopTriangle(pge, *pv0, *pv1, *pv2, texture);
	}

	//float bottom
	else if (pv1->vertexPos.y() == pv2->vertexPos.y())
	{
		if (pv1->vertexPos.y() > pv2->vertexPos.y()) std::swap(pv1, pv2);
		DrawTexturedFlatBottomTriangle(pge, *pv0, *pv1, *pv2, texture);
	}

	else
	{
		float alpha = (pv1->vertexPos.y() - pv0->vertexPos.y()) / (pv2->vertexPos.y() - pv0->vertexPos.y());
		TexturedVertex split = pv0->InterpolateTo(*pv2, alpha);

		//major left
		if (split.vertexPos.x() < pv1->vertexPos.x())
		{
			DrawTexturedFlatTopTriangle(pge, split, *pv1, *pv2, texture);
			DrawTexturedFlatBottomTriangle(pge, *pv0, split, *pv1, texture);
		}
		else //major right
		{
			DrawTexturedFlatBottomTriangle(pge, *pv0, *pv1, split, texture);
			DrawTexturedFlatTopTriangle(pge, *pv1, split, *pv2, texture);
		}
	}
}

void TriangleRaster::DrawWrappedTexturedFlatTopTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0, const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture, float wrap)
{
	float v2v0Slope = (v2.vertexPos.x() - v0.vertexPos.x()) / (v2.vertexPos.y() - v0.vertexPos.y());
	float v2v1Slope = (v2.vertexPos.x() - v1.vertexPos.x()) / (v2.vertexPos.y() - v1.vertexPos.y());

	int startY = (int)std::ceil(v0.vertexPos.y() - 0.5f);
	int endY = (int)std::ceil(v2.vertexPos.y() - 0.5f);

	Eigen::Vector3f texStepRight = (v2.texturePos - v1.texturePos).array() / (v2.vertexPos.y() - v1.vertexPos.y());
	Eigen::Vector3f texStepLeft = (v2.texturePos - v0.texturePos).array() / (v2.vertexPos.y() - v0.vertexPos.y());

	Eigen::Vector3f texLeft = v0.texturePos;
	Eigen::Vector3f texRight = v1.texturePos;

	texLeft += texStepLeft * ((float)startY + 0.5f - v0.vertexPos.y());
	texRight += texStepRight * ((float)startY + 0.5f - v1.vertexPos.y());

	Eigen::Vector3f texSize = { (float)texture->width, (float)texture->height, 1.0f };
	Eigen::Vector3f texClamp = { texSize.x() - 1.0f, texSize.y() - 1.0f, 1.0f };

	for (int y = startY; y < endY;
		y++, texLeft += texStepLeft, texRight += texStepRight)
	{
		float _startX = v2v0Slope * (y + 0.5f - v0.vertexPos.y()) + v0.vertexPos.x();
		float _endX = v2v1Slope * (y + 0.5f - v1.vertexPos.y()) + v1.vertexPos.x();

		int startX = (int)std::ceil(_startX - 0.5f);
		int endX = (int)std::ceil(_endX - 0.5f);

		Eigen::Vector3f texStepX = (texRight - texLeft) / (_endX - _startX);
		Eigen::Vector3f texPos = texLeft + texStepX * ((float)startX + 0.5f - _startX);

		for (int x = startX; x < endX; x++, texPos += texStepX)
		{
			pge->Draw(x, y,
				texture->GetPixel(
					(uint32_t)std::fmod(texPos.x() * texture->width * wrap, texClamp.x()),
					(uint32_t)std::fmod(texPos.y() * texture->height * wrap, texClamp.y())
				));
		}
	}
}

void TriangleRaster::DrawWrappedTexturedFlatBottomTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0, const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture, float wrap)
{
	float v0v1Slope = (v0.vertexPos.x() - v1.vertexPos.x()) / (v0.vertexPos.y() - v1.vertexPos.y());
	float v0v2Slope = (v0.vertexPos.x() - v2.vertexPos.x()) / (v0.vertexPos.y() - v2.vertexPos.y());

	int startY = (int)std::ceil(v0.vertexPos.y() - 0.5f);
	int endY = (int)std::ceil(v2.vertexPos.y() - 0.5f);

	Eigen::Vector3f texStepRight = (v2.texturePos - v0.texturePos).array() / (v2.vertexPos.y() - v0.vertexPos.y());
	Eigen::Vector3f texStepLeft = (v1.texturePos - v0.texturePos).array() / (v1.vertexPos.y() - v0.vertexPos.y());

	Eigen::Vector3f texLeft = v0.texturePos;
	Eigen::Vector3f texRight = v0.texturePos;

	texLeft += texStepLeft * ((float)startY + 0.5f - v0.vertexPos.y());
	texRight += texStepRight * ((float)startY + 0.5f - v0.vertexPos.y());

	Eigen::Vector3f texSize = { (float)texture->width, (float)texture->height, 1.0f };
	Eigen::Vector3f texClamp = { texSize.x() - 1.0f, texSize.y() - 1.0f, 1.0f };

	for (int y = startY; y < endY;
		y++, texLeft += texStepLeft, texRight += texStepRight)
	{
		float _startX = v0v1Slope * (y + 0.5f - v1.vertexPos.y()) + v1.vertexPos.x();
		float _endX = v0v2Slope * (y + 0.5f - v2.vertexPos.y()) + v2.vertexPos.x();

		int startX = (int)std::ceil(_startX - 0.5f);
		int endX = (int)std::ceil(_endX - 0.5f);

		Eigen::Vector3f texStepX = (texRight - texLeft) / (_endX - _startX);
		Eigen::Vector3f texPos = texLeft + texStepX * ((float)startX + 0.5f - _startX);

		for (int x = startX; x < endX; x++, texPos += texStepX)
		{
			pge->Draw(x, y,
				texture->GetPixel(
					(uint32_t)std::fmod(texPos.x() * texture->width * wrap, texClamp.x()),
					(uint32_t)std::fmod(texPos.y() * texture->height * wrap, texClamp.y())
				));
		}
	}
}

void TriangleRaster::DrawWrappedTexturedTriangle(olc::PixelGameEngine* pge, const TexturedVertex& v0, const TexturedVertex& v1, const TexturedVertex& v2, const olc::Sprite* const texture, float wrap)
{
	const TexturedVertex* pv0 = &v0;
	const TexturedVertex* pv1 = &v1;
	const TexturedVertex* pv2 = &v2;

	if (pv1->vertexPos.y() < pv0->vertexPos.y()) std::swap(pv1, pv0);
	if (pv2->vertexPos.y() < pv1->vertexPos.y()) std::swap(pv2, pv1);
	if (pv1->vertexPos.y() < pv0->vertexPos.y()) std::swap(pv1, pv0);

	//float top
	if (pv0->vertexPos.y() == pv1->vertexPos.y())
	{
		if (pv0->vertexPos.y() > pv1->vertexPos.y()) std::swap(pv0, pv1);
		DrawWrappedTexturedFlatTopTriangle(pge, *pv0, *pv1, *pv2, texture, wrap);
	}

	//float bottom
	else if (pv1->vertexPos.y() == pv2->vertexPos.y())
	{
		if (pv1->vertexPos.y() > pv2->vertexPos.y()) std::swap(pv1, pv2);
		DrawWrappedTexturedFlatBottomTriangle(pge, *pv0, *pv1, *pv2, texture, wrap);
	}

	else
	{
		float alpha = (pv1->vertexPos.y() - pv0->vertexPos.y()) / (pv2->vertexPos.y() - pv0->vertexPos.y());
		TexturedVertex split = pv0->InterpolateTo(*pv2, alpha);

		//major left
		if (split.vertexPos.x() < pv1->vertexPos.x())
		{
			DrawWrappedTexturedFlatTopTriangle(pge, split, *pv1, *pv2, texture, wrap);
			DrawWrappedTexturedFlatBottomTriangle(pge, *pv0, split, *pv1, texture, wrap);
		}
		else //major right
		{
			DrawWrappedTexturedFlatBottomTriangle(pge, *pv0, *pv1, split, texture, wrap);
			DrawWrappedTexturedFlatTopTriangle(pge, *pv1, split, *pv2, texture, wrap);
		}
	}
}
