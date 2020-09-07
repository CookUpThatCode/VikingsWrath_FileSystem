// --- Engine.cpp ---

#include "Engine.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "World.h"
#include "Assets.h"
#include "Object.h"

using namespace std;

void Engine::testUpdateMethod() {
	2 + 2;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
	testUpdateMethod();


	if (GetKey(olc::Key::O).bPressed) angleOut.close();
	float angleTarget;
	float pitchTarget;
	float zoomTarget;
	time += fElapsedTime;
	if (time > 0.25)
	{
		time -= 0.25;
		if (GetKey(olc::Key::U).bHeld)
			angleOut << cameraAngle << " " << cameraPitch << " " << cameraZoom << " ";
		if (GetKey(olc::Key::I).bHeld)
		{
			angleIn >> angleTarget;
			angleIn >> pitchTarget;
			angleIn >> zoomTarget;
			angleVel = (angleTarget - cameraAngle) / 0.25;
			pitchVel = (pitchTarget - cameraPitch) / 0.25;
			zoomVel = (zoomTarget - cameraZoom) / 0.25f;
		}
		if (!GetKey(olc::Key::I).bHeld)
		{
			angleVel = 0;
			pitchVel = 0;
			zoomVel = 0;
		}
		// record angle position. 
	}
	cameraAngle += angleVel * fElapsedTime;
	cameraPitch += pitchVel * fElapsedTime;
	cameraZoom += zoomVel * fElapsedTime;


	if (GetKey(olc::Key::ENTER).bPressed) saveLevel();

	// Grab mouse for convenience
	olc::vi2d mouseLoc = { GetMouseX(), GetMouseY() };

	// Edit mode - Selection from tile sprite sheet    **** ... ****

	// Q/A keys to tilt pitch of camera. Z/X keys for rotating angle
	if (GetKey(olc::Key::Q).bHeld) cameraPitch += 1.0f * fElapsedTime;
	if (GetKey(olc::Key::A).bHeld) cameraPitch -= 1.0f * fElapsedTime;
	if (GetKey(olc::Key::Z).bHeld) cameraAngle += 1.0 * fElapsedTime;
	if (GetKey(olc::Key::X).bHeld) cameraAngle -= 1.0 * fElapsedTime;
	// W/S keys for zoom. E/D keys for faster zoom
	if (GetKey(olc::Key::W).bHeld) cameraZoom += 1.0f * fElapsedTime;
	if (GetKey(olc::Key::S).bHeld) cameraZoom -= 1.0f * fElapsedTime;
	if (GetKey(olc::Key::E).bHeld) cameraZoom += 1.0 * fElapsedTime;
	if (GetKey(olc::Key::D).bHeld) cameraZoom -= 1.0 * fElapsedTime;

	// Rotating and zoom sequences, smooth transitions

	// Numeric keys apply selected tile to specific face

	// Arrow keys to move the selection cursor around map (boundary checked)
	if (GetKey(olc::Key::LEFT).bPressed) cursor.x--;
	if (GetKey(olc::Key::RIGHT).bPressed) cursor.x++;
	if (GetKey(olc::Key::UP).bPressed) cursor.y++;
	if (GetKey(olc::Key::DOWN).bPressed) cursor.y--;
	if (GetKey(olc::Key::NP_SUB).bPressed) cursor.z++;
	if (GetKey(olc::Key::NP_ADD).bPressed) cursor.z--;
	if (cursor.x < 0) cursor.x = 0;	if (cursor.x >= world.size.x) cursor.x = world.size.x - 1;
	if (cursor.y < 0) cursor.y = 0;	if (cursor.y >= world.size.y) cursor.y = world.size.y - 1;
	if (cursor.z < 0) cursor.z = 0;	if (cursor.z >= world.size.z) cursor.z = world.size.z - 1;

	// Place / unplace block with space bar
	if (GetKey(olc::Key::SPACE).bPressed) world.getCell(cursor).placed = !world.getCell(cursor).placed;

	// Position camera in pixel world space
	cameraPos = { cursor.x + 0.5f, cursor.y + 0.5f, cursor.z + 0.5f };
	cameraPos = { cameraPos.x * cameraZoom * cDims.x, cameraPos.y * cameraZoom * cDims.y, cameraPos.z * cameraZoom * cDims.z };

	// Rendering
	// 1) Create dummy cube to extract visible face information
	// Exclude faces that cannot be seen
	array<Vec3Df, 8> dummyCube = createCube({ 0,0,0 }, cameraAngle, cameraPitch, cameraZoom, cameraPos);
	calculateVisibleFaces(dummyCube);
	// 2) Get all visible sides of all visible "tile cubes"
	vector<Quad> drawList;
	for (int x = 0; x < world.size.x; x++)
		for (int y = 0; y < world.size.y; y++)
			for (int z = 0; z < world.size.z; z++)
				addQuadFaces({ x,y,z }, cameraAngle, cameraPitch, cameraZoom, cameraPos, drawList);
	// 3) sor in order of depth, from farthest away to closest
	sort(drawList.begin(), drawList.end(), [](const Quad& q1, const Quad& q2)
		{
			float zAvg1 = (q1.points[0].z + q1.points[1].z + q1.points[2].z + q1.points[3].z) * 0.25f;
			float zAvg2 = (q2.points[0].z + q2.points[1].z + q2.points[2].z + q2.points[3].z) * 0.25f;
			return zAvg1 > zAvg2;
		});                          // make sure front of list has largest z coordinate: farthest away
// 4) iterate through all "tile cubes" and draw ther visible faces
	Clear(olc::BLACK);
	for (auto& q : drawList)
		DrawPartialWarpedDecal
		(
			newTiles.decal,
			{ {q.points[0].x,-q.points[0].y + ScreenHeight()},{q.points[1].x,-q.points[1].y + ScreenHeight()},
			{q.points[2].x,-q.points[2].y + ScreenHeight()},{q.points[3].x,-q.points[3].y + ScreenHeight()} },
			q.tileSpr, q.tileDims
		);

	drawList.clear();


	if (test_time == 0.0f) {
		if (test_time_end >= 0.75) {
			test_time_end = 0.0f;
			test_time = 0.00001f;
			DrawPartialDecal({ 100, 100 }, a.testDragDeath.decal, { 7*112,0 }, { 112,80 });
		}
		else {
			test_time_end += fElapsedTime;
			DrawPartialDecal({ 100, 100 }, a.testDragDeath.decal, { 7*112,0 }, { 112,80 });
		}
	}
	else {
		test_time += fElapsedTime;
		if (test_time >= 8*.04) {
			test_time = 0.0;
		}
		float t = float(int(test_time / .04));
		DrawPartialDecal({ 100, 100 }, a.testDragDeath.decal, { t*112,0 }, { 112,80 });
	}
	

	


	return true;
}