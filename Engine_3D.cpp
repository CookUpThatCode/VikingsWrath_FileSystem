#include "Engine.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "World.h"
#include "Assets.h"
#include "Object.h"

using namespace std;

array<Vec3Df, 8> Engine::createCube(const Vec3Di location, const float angle, const float pitch, const float scale,
	const Vec3Df& camera)
{
	auto& cell = world.getCell(location);

	// Unit Cube    x+: to the right;  y+: straight up;  z+: into the screen. Working with pixel space
	// This cube starts at the origin. Collection of 8 points.
	array<Vec3Df, 8> unitCube, rotCube, pitchCube, projCube;
	unitCube[0] = { 0.0f, 0.0f, 0.0f };
	unitCube[1] = { scale * cDims.x, 0.0f, 0.0f };
	unitCube[2] = { 0.0f, scale * cDims.y, 0.0f };
	unitCube[3] = { scale * cDims.x, scale * cDims.y, 0.0f };
	unitCube[4] = { 0.0f, 0.0f, scale * cDims.z };
	unitCube[5] = { scale * cDims.x, 0.0f, scale * cDims.z };
	unitCube[6] = { 0.0f, scale * cDims.y, scale * cDims.z };
	unitCube[7] = { scale * cDims.x, scale * cDims.y, scale * cDims.z };

	// Translate Cube in XZ Plane. Move cube over to its location in world pixel space. But the screen will
	// center around the camera location, so we make the camera the origin now by offsetting
	// So now we're in camera pixel space.
	for (int i = 0; i < 8; i++)
	{
		unitCube[i].x += location.x * scale * cDims.x - camera.x;
		unitCube[i].y += location.y * scale * cDims.y - camera.y;
		unitCube[i].z += location.z * scale * cDims.z - camera.z;
	}

	// Rotate Cube in Y-axis around origin using Orthogonal Matrix Transformations
	float s = sin(angle);
	float c = cos(angle);
	for (int i = 0; i < 8; i++)
	{
		rotCube[i].x = unitCube[i].x * c + unitCube[i].z * s;
		rotCube[i].y = unitCube[i].y;
		rotCube[i].z = -unitCube[i].x * s + unitCube[i].z * c;
	}

	// Rotate cube in X-axis around origin (tilting upwards)
	s = sin(pitch);
	c = cos(pitch);
	for (int i = 0; i < 8; i++)
	{
		pitchCube[i].x = rotCube[i].x;
		pitchCube[i].y = rotCube[i].y * c - rotCube[i].z * s;
		pitchCube[i].z = rotCube[i].y * s + rotCube[i].z * c;
	}

	// Defining all the cubes in this space would put the camera as the origin at the top left of the screen.
	// We want to move it center screen. When projected orthographically, the z coordinate is irrelevant,
	// But we will leave it in for future use.
	for (int i = 0; i < 8; i++)
	{
		projCube[i].x = pitchCube[i].x + ScreenWidth() * 0.5f;
		projCube[i].y = pitchCube[i].y + ScreenHeight() * 0.5f;
		projCube[i].z = pitchCube[i].z;
	}

	return projCube;
}

// Check once cube from the seen to set the flags for which faces are visible for the whole world since orthographic
	// projection has no vanishing points. Faces are defined by order of points given.
void Engine::calculateVisibleFaces(array<Vec3Df, 8>& cube)
{
	// checking 3 vertices in a counter-clockwise fashion to find the direction of the normal.
	// z component is ignored, everything treated in two dimensions since with orthographic projection
	// you can still see whether face is pointing towards you with only x and y. Cross product used
	auto checkNormal = [&](int v1, int v2, int v3)
	{
		olc::vf2d a = { cube[v1].x, cube[v1].y };
		olc::vf2d b = { cube[v2].x, cube[v2].y };
		olc::vf2d c = { cube[v3].x, cube[v3].y };
		return (b - a).cross(c - a) > 0;
	};
	visible[Floor] = checkNormal(1, 5, 4);
	visible[East] = checkNormal(5, 7, 3);
	visible[North] = checkNormal(4, 6, 7);
	visible[West] = checkNormal(0, 2, 6);
	visible[South] = checkNormal(1, 3, 2);
	visible[Top] = checkNormal(3, 7, 6);
}

void Engine::addQuadFaces(const Vec3Di location, const float angle, const float pitch, const float scale,
	const Vec3Df camera, vector<Quad>& drawList)
{
	array<Vec3Df, 8> projCube = createCube(location, angle, pitch, scale, camera);
	auto& cell = world.getCell(location);

	auto addFace = [&](int v1, int v2, int v3, int v4, Face f, olc::vi2d tileDims)
	{
		drawList.push_back({ projCube[v1], projCube[v2], projCube[v3], projCube[v4], cell.tiles[f], tileDims });
	};
	if (cell.placed)
	{
		//if(visible[Floor]) addFace(4, 0, 1, 5, Floor);
		if (visible[East]) addFace(3, 1, 5, 7, East, wallDims);
		if (visible[North]) addFace(7, 5, 4, 6, North, wallDims);
		if (visible[West]) addFace(6, 4, 0, 2, West, wallDims);
		if (visible[South]) addFace(2, 0, 1, 3, South, wallDims);
		if (visible[Top]) addFace(6, 2, 3, 7, Top, floorDims);
	}
}

