#include <string>
#include <iomanip>

#include "LevelBuilder.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//First Level
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

//Fourth Level
float cubeX4[117] = {0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f,		//Bottom of level
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 9.5f,							//First platform
					0, 3.5f, 9.5f,
					0, 3.5f, 9.5f,
					0, 3.5f, 9.5f,
					0, 0.5f, 3.5f, 4, 4.5f, 5, 5.5f, 6, 9, 9.5f,													//Top of rectangle housing next level warp
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 1, 8.5f, 9.5f,																				//Two small platforms for reaching the top one
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 9.5f,							//Top platform
					0, 9.5f,
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f};		//Top of level


float cubeY4[117] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,									//Bottom of level
					0.5f, 0.5f,
					1, 1,
					1.5f, 1.5f,
					2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,													//First platform
					2.5f, 2.5f, 2.5f,
					3, 3, 3,
					3.5f, 3.5f, 3.5f,
					4, 4, 4, 4, 4, 4, 4, 4, 4, 4,																	//Top of rectangle housing next level warp	
					4.5f, 4.5f,
					5, 5,
					5.5f, 5.5f,
					6, 6, 6, 6,																						//Two small platforms for reaching the top one
					6.5f, 6.5f,
					7, 7,
					7.5f, 7.5f,
					8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,													//Top platform
					8.5f, 8.5f,
					9, 9,
					9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f};	//Top of level

//Fifth level
float cubeX5[81] = {0, 0.5f, 1, 1.5f, 2, 3, 5, 6.5f, 8.5f, 9, 9.5f,													//Bottom of level
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 9.5f,																			//Top of rectangle housing next level warp
					0, 9.5f, 
					0, 9.5f, 
					0, 9.5f, 
					0, 9.5f, 
					0, 9.5f, 
					0, 9.5f, 
					0, 3, 3.5f, 4, 4.5f, 5, 5.5f, 9.5f,																//Third platform (you start at the level top)
					0, 9.5f,
					0, 2, 2.5f, 9.5f,																				//Second platform
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 9.5f,																			//First platform
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f};		//Top of level


float cubeY5[81] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,																//Bottom of level
					0.5f, 0.5f,
					1, 1,
					1.5f, 1.5f,
					2, 2, 2, 2, 2,																					//Top of rectangle housing next level warp
					2.5f, 2.5f,
					3, 3,
					3.5f, 3.5f,
					4, 4,
					4.5f, 4.5f,
					5, 5,
					5.5f, 5.5f, 5.5f, 5.5f, 5.5f, 5.5f, 5.5f, 5.5f,													//Third platform (you start at the level top)
					6, 6,
					6.5f, 6.5f, 6.5f, 6.5f,																			//Second platform
					7, 7,
					7.5f, 7.5f, 7.5f, 7.5f, 7.5f,																	//First platform
					8, 8,
					8.5f, 8.5f,
					9, 9,
					9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f};	//Top of level


//Sixth level
float cubeX6[115] = {0, 0.5f, 1, 1.5f, 2, 2.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f,											//Bottom of level
					0, 9.5f,
					0, 9.5f,
					0, 1, 2, 3, 6.5f, 7.5f, 8, 9.5f,																//Beginning of rectangular box sections
					0, 2, 7.5f, 9.5f,
					0, 2, 3.5f, 4, 4.5f, 5, 5.5f, 6, 7.5f, 9.5f,
					0, 1.5f, 2, 7.5f, 9, 9.5f,
					0, 2, 7.5f, 9.5f,
					0, 0.5f, 2, 7.5f, 9.5f,
					0, 2, 7.5f, 8.5f, 9.5f,
					0, 2, 7.5f, 9.5f,
					0, 1, 1.5f, 2, 7.5f, 9.5f,
					0, 2, 7.5f, 8, 9.5f,
					0, 2, 9.5f,
					0, 2, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 7.5f, 8, 8.5f, 9, 9.5f,													//End of rectangular box sections
					0, 9.5f,
					0, 9.5f,
					0, 9.5f,
					0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f};		//Top of level


float cubeY6[115] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
					0.5f, 0.5f,
					1, 1,
					1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f,													//Beginning of rectangular box sections
					2, 2, 2, 2,
					2.5f, 2.5f, 2.5f, 2.5f, 2.5f, 2.5f, 2.5f, 2.5f, 2.5f, 2.5f,
					3, 3, 3, 3, 3, 3,
					3.5f, 3.5f, 3.5f, 3.5f,
					4, 4, 4, 4, 4,
					4.5f, 4.5f, 4.5f, 4.5f, 4.5f,
					5, 5, 5, 5,
					5.5f, 5.5f, 5.5f, 5.5f, 5.5f, 5.5f,
					6, 6, 6, 6, 6,
					6.5f, 6.5f, 6.5f,
					7, 7, 7,
					7.5f, 7.5f, 7.5f, 7.5f, 7.5f, 7.5f, 7.5f, 7.5f, 7.5f, 7.5f,										//End of rectangular box sections
					8, 8,
					8.5f, 8.5f,
					9, 9,
					9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f, 9.5f};	//Top of level

void LevelBuilder::Initialise(MeshManager& mgr)
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

void LevelBuilder::LevelLoad(PlayerControl& player, Key& key, Door& door, int level)
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
		door.Start(Vector3(2, 6, 0));
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
		door.Start(Vector3(1, 6, 0));
		break;
	case 3:
		for (int i = 0; i < 83; i++) {
			cubies.Initialise(*p, cubeX2[i], cubeY2[i]);

			cubiesArray[i] = cubies;
			mCubes[i] = cubies.GetCube();
			size_ = i + 1;
			//Puts the the cube in the array
		}
		player.Start(Vector3(3, 4, 0));
		key.Start(Vector3(8.5f, 1, 0));
		door.Start(Vector3(1, 6, 0));
		break;
	case 4:
		for (int i = 0; i < 117; i++) {
			cubies.Initialise(*p, cubeX4[i], cubeY4[i]);

			cubiesArray[i] = cubies;
			mCubes[i] = cubies.GetCube();
			size_ = i + 1;
			//Puts the the cube in the array
		}
		player.Start(Vector3(3, 4, 0));
		key.Start(Vector3(8.5f, 1, 0));
		door.Start(Vector3(1, 6, 0));
		break;
	case 5:
		for (int i = 0; i < 81; i++) {
			cubies.Initialise(*p, cubeX5[i], cubeY5[i]);

			cubiesArray[i] = cubies;
			mCubes[i] = cubies.GetCube();
			size_ = i + 1;
			//Puts the the cube in the array
		}
		player.Start(Vector3(3, 4, 0));
		key.Start(Vector3(8.5f, 1, 0));
		door.Start(Vector3(1, 6, 0));
		break;
	case 6:
		for (int i = 0; i < 116; i++) {
			cubies.Initialise(*p, cubeX6[i], cubeY6[i]);

			cubiesArray[i] = cubies;
			mCubes[i] = cubies.GetCube();
			size_ = i + 1;
			//Puts the the cube in the array
		}
		player.Start(Vector3(3, 4, 0));
		key.Start(Vector3(8.5f, 1, 0));
		door.Start(Vector3(1, 6, 0));
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
}