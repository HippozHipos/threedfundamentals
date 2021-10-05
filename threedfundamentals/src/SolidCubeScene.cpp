#include "SolidCubeScene.h"
#include "TriangleRaster.h"
#include "Rotation.h"

SolidSceneScene::SolidSceneScene(olc::PixelGameEngine* pge) :
	pubeScreenTransformer{ pge }
{
}

void SolidSceneScene::Update(const olc::PixelGameEngine* const pge)
{
	controls.ChangeRoll(pge, olc::Q, roll);
	controls.ChangePitch(pge, olc::W, pitch);
	controls.ChangeYaw(pge, olc::E, yaw);
	controls.ChnageZOffset(pge, olc::UP, olc::DOWN, offset.z());

	triangles = cube.GetTriangles();
	for (auto& vertex : triangles.vertices)
	{
		vertex = Rotation::Rotate(vertex, roll, pitch, yaw);
		vertex += offset;
	}

	for (size_t i = 0; i < triangles.indices.size() / 3; i++)
	{
		const Eigen::Vector3f& v0 = triangles.vertices[triangles.indices[i * 3 + 0]];
		const Eigen::Vector3f& v1 = triangles.vertices[triangles.indices[i * 3 + 1]];
		const Eigen::Vector3f& v2 = triangles.vertices[triangles.indices[i * 3 + 2]];
		triangles.cullFlags[i] = ((v1 - v0).cross(v2 - v1)).dot(v0) >= 0.0f;
	}

	for (auto& vertex : triangles.vertices)
	{
		vertex = pubeScreenTransformer.GetTrasformed(vertex);
	}
}

void SolidSceneScene::Draw(olc::PixelGameEngine* pge) const
{
	pge->Clear(olc::BLACK);

	for (size_t i = 0; i < triangles.indices.size() / 3; i++)
	{
		if (!triangles.cullFlags[i])
		{
			TriangleRaster::DrawTriangle(pge,
				triangles.vertices[triangles.indices[i * 3 + 0]],
				triangles.vertices[triangles.indices[i * 3 + 1]],
				triangles.vertices[triangles.indices[i * 3 + 2]],
				colorArray[i]);
		}
	}

	pge->DrawString(10, 10, std::to_string(offset.z()));
}
