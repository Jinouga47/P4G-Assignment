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
float cubeX2[61] = {-3.5f, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1, 1, 1, 1.5f, 2, 2.5f, 3, 3.5f,
					1.5f, 2, 2.5f, -3.5f, -3, -2.5f, -2, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, 
					-3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 
					-2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f, -2.5f};

float cubeY2[61] = {0, 0, 0, 0, 0, 0, 1.5f, 1.5f, 1.5f, 2.5f, 4.5f, 6.5f, 8.5f, 7, 5, 3, 0, 0, 1.5f,
					1.5f, 1.5f, 2.5f, 2.5f, 2.5f, 2.5f, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f,
					10, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f, 10, 4.5f, 5, 5.5f, 6, 6.5f, 7,
					7.5f, 8, 8.5f, 9, 9.5f, 10};

//Third Level


void LevelBuilder::Initialise(MeshManager& mgr)//, int levelSize)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	//cubies.Initialise(*p, 1, 1);

	int ii = sizeof(cubeX);

	//Sets up the array for the cubes that make up the level
	for (int i = 0; i < 150; i++) {
		cubies.Initialise(*p, cubeX[i], cubeY[i]);

		cubiesArray[i] = cubies;
		mCubes[i] = cubiesArray[i].GetCube();
		size_ = i + 1;
		//Puts the the cube in the array
	}
}

void LevelBuilder::Render(FX::MyFX& fx)
{
	for (int i = 0; i < 150; i++) {
		fx.Render(mCubes[i], gd3dImmediateContext);
	}
}

Model LevelBuilder::GetCubes(int i)
{
	return mCubes[i];
}

int LevelBuilder::Size()
{
	return size_;
}

void LevelBuilder::Collision(PlayerControl& player)
{
	for (int i = 0; i < size_; i++)
	{
		cubiesArray[i].CollisionManager(player);
	}
}