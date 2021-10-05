#include "WrappedCubeScene.h"
#include "Rotation.h"
#include "TriangleRaster.h"

WrappedCubeScene::WrappedCubeScene(olc::PixelGameEngine* pge, const olc::Sprite* const texture) :
	texture{ texture },
	pubeScreenTransformer{ pge }
{
};

void WrappedCubeScene::Update(const olc::PixelGameEngine* const pge)
{
	controls.ChangeRoll(pge, olc::Q, roll);
	controls.ChangePitch(pge, olc::W, pitch);
	controls.ChangeYaw(pge, olc::E, yaw);
	controls.ChnageZOffset(pge, olc::UP, olc::DOWN, offset.z());
	ChangeWrap(pge, olc::Z, olc::X, 0.5f, wrapTimes);

	triangles = cube.GetTexturedTriangles();
	for (auto& vertex : triangles.vertices)
	{
		vertex.vertexPos = Rotation::Rotate(vertex.vertexPos, roll, pitch, yaw);
		vertex.vertexPos += offset;
	}

	for (size_t i = 0; i < triangles.indices.size() / 3; i++)
	{
		const Eigen::Vector3f& v0 = triangles.vertices[triangles.indices[i * 3 + 0]].vertexPos;
		const Eigen::Vector3f& v1 = triangles.vertices[triangles.indices[i * 3 + 1]].vertexPos;
		const Eigen::Vector3f& v2 = triangles.vertices[triangles.indices[i * 3 + 2]].vertexPos;
		triangles.cullFlags[i] = ((v1 - v0).cross(v2 - v1)).dot(v0) >= 0.0f;
	}

	for (auto& vertex : triangles.vertices)
	{
		vertex.vertexPos = pubeScreenTransformer.GetTrasformed(vertex.vertexPos);
	}
}

void WrappedCubeScene::Draw(olc::PixelGameEngine* pge) const
{
	pge->Clear(olc::BLACK);

	for (size_t i = 0; i < triangles.indices.size() / 3; i++)
	{
		if (!triangles.cullFlags[i])
		{
			TriangleRaster::DrawWrappedTexturedTriangle(pge,
				triangles.vertices[triangles.indices[i * 3 + 0]],
				triangles.vertices[triangles.indices[i * 3 + 1]],
				triangles.vertices[triangles.indices[i * 3 + 2]],
				texture, wrapTimes);
		}
	}

	pge->DrawString(10, 10, std::to_string(offset.z()));
}
