#include <string>
#include <iomanip>

#include "LevelBuilder.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//First Level
/*float cubeX[125] = {-3.5f, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 3.5f,
					3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 
					3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3, 2.5f, 2, 1.5f, 1, 0.5f, 0, -0.5f, -1, -1.5f, -2,
					-2.5f, -3, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, 
					-3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -2, -2, -2,
					-2, -2, -2, -1.5f, -1, -0.5f, 0, -1, -1, -1, -1, 1.5, 3, -1, -1, 2, 2, 2, 2, 2, 2,
					2, 2, 2, 2, 2, 2, 2, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1.5f, 2.5f, -3,
					-2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5, 3, -2.5f, 0, 0, 0, 0, 0};*/

/*float cubeY[125] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4,
					4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f, 10, 10, 10, 10, 10, 10, 10, 10, 
					10, 10, 10, 10, 10, 10, 10, 9.5f, 9, 8.5f, 8, 7.5f, 7, 6.5f, 6, 5.5f, 5, 4.5f, 4,
					3.5f, 3, 2.5f, 2, 1.5f, 1, 0.5f, 9.5f, 9, 8.5f, 8, 7.5f, 6, 6, 6, 6, 6, 6.5f, 7,
					7.5f, 8, 6, 6, 5, 4.5f, 8, 7.5f, 7, 6.5f, 6, 5.5f, 5, 4.5f, 4, 3.5f, 3, 2.5f, 2, 
					4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 9.5f, 9, 8.5f, 8, 7.5f};*/

float cubeX[143] = {0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f,		//Bottom of level
					0, 9.5f, 
					0, 9.5f,
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 7.5f, 9, 9.5f,									//First platform
					0, 7.5f, 9.5f,
					0, 7.5f, 9.5f,
					0, 7.5f, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 9.5f,				//Second platform
					0, 4.5f, 7.5f, 9.5f,
					0, 4.5f, 7.5f, 9.5f,
					0, 7.5f, 9.5f,
					0, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 6.5f, 7, 7.5f, 9, 9.5f,										//Third platform
					0, 3, 4, 7.5f, 9.5f,
					0, 2, 3, 4, 5, 7.5f, 9.5f,
					0, 2, 3, 5, 9.5f,
					0, 2, 4, 5, 9.5f,
					0, 2, 4, 5, 9.5f,
					0, 2, 4, 5, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f};		//Top of level

float cubeY[143] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,										//Bottom of level	
					0.5f, 0.5f,
					1, 1,
					1.5f, 1.5f,
					2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,														//First platform
					2.5f, 2.5f, 2.5f,
					3, 3, 3,
					3.5f, 3.5f, 3.5f,
					4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,											//Second platform
					4.5f, 4.5f, 4.5f, 4.5f,
					5, 5, 5, 5,
					5.5f, 5.5f, 5.5f,
					6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,															//Third platform
					6.5f, 6.5f, 6.5f, 6.5f, 6.5f,
					7, 7, 7, 7, 7, 7, 7,
					7.5f, 7.5f, 7.5f, 7.5f, 7.5f,
					8, 8, 8, 8, 8,
					8.5f, 8.5f, 8.5f, 8.5f, 8.5f,
					9, 9, 9, 9, 9,
					9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f};		//Top of level


//Second Level
//float cubeX2[61] = {-3.5f, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1, 1, 1, 1.5f, 2, 2.5f, 3, 3.5f,
//					1.5f, 2, 2.5f, -3.5f, -3, -2.5f, -2, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, 
//					-3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 
//					-2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f};

//float cubeY2[61] = {0, 0, 0, 0, 0, 0, 1.5f, 1.5f, 1.5f, 2.5f, 4.5f, 6.5f, 8.5f, 7, 5, 3, 0, 0, 1.5f,
//					1.5f, 1.5f, 2.5f, 2.5f, 2.5f, 2.5f, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f,
//					10, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f, 10, 4.5f, 5, 5.5f, 6, 6.5f, 7,
//					7.5f, 8, 8.5f, 9, 9.5f, 10};

float cubeX2[83] = {0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 7.5f, 8, 8.5f, 9, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 3.5f, 5, 6.5f, 8.5f, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 5, 7.5f, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 5, 6.5f, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 9.5f, 
					0, 9.5f,
					0, 9.5f,
					0, 9.5f, 
					0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f };
					

float cubeY2[83] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0.5f, 0.5f,
					1, 1,
					1.5f, 1.5f,
					2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
					2.5f, 2.5f,
					3, 3,
					3.5f, 3.5f,
					4, 4, 4, 4, 4, 4, 4,
					4.5f, 4.5f,
					5, 5,
					5.5f, 5.5f,
					6, 6, 6, 6,
					6.5f, 6.5f,
					7, 7,
					7.5f, 7.5f,
					8, 8,
					8.5f, 8.5f,
					9, 9,
					9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f};

//Third Level


void LevelBuilder::Initialise(MeshManager& mgr)//, int levelSize)
{
	p = mgr.GetMesh("cube");
	assert(p);
}

void LevelBuilder::Render(FX::MyFX& fx)
{
	for (int i = 0; i < size_; i++) {
		fx.Render(mCubes[i], gd3dImmediateContext);
	}
}

Model LevelBuilder::GetCubes(int i)
{
	return mCubes[i];
}

void LevelBuilder::LevelLoad(PlayerControl& player, Key& key, int level)
{
	switch (level) {
	case 1:
		for (int i = 0; i < 143; i++) {
			cubies.Initialise(*p, cubeX[i], cubeY[i]);

			cubiesArray[i] = cubies;
			mCubes[i] = cubies.GetCube();
			size_ = i + 1;
			//Puts the the cube in the array
		}
		player.Start(Vector3(4, 4, 0));
		key.Start(Vector3(1, 6, 0));
		break;
	case 2:
		for (int i = 0; i < 83; i++) {
			cubies.Initialise(*p, cubeX2[i], cubeY2[i]);

			cubiesArray[i] = cubies;
			mCubes[i] = cubies.GetCube();
			size_ = i + 1;
			//Puts the the cube in the array
		}
		player.Start(Vector3(3, 4, 0));
		key.Start(Vector3(8.5f, 1, 0));
		break;
	}

}

int LevelBuilder::Size()
{
	return size_;
}

void LevelBuilder::Collision(PlayerControl& player, Key& key)
{
	for (int i = 0; i < size_; i++)
	{
		cubiesArray[i].CollisionManager(player);
	}

	key.CollisionCheck(player);
}