#include <string>
#include <iomanip>

#include "LevelBuilder.h"
#include "CubeClass.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//float cubeX[34] = {-3.5f, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 3.5f, 
					//3.5f, 3.5f, 3.5f, 3.5f, 0.5f, 0, -0.5f, -1, -1.5f, -2, -2.5f, -3, -3.5f, -3.5f,
					//-3.5f, -3.5f, -3.5f, -3.5f};
//float cubeY[34] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,1,1.5f,2,2,2,2,2,2,2,2,2,2,2,2,2,1.5f,1,0.5f };

float cubeX[200] = {-3.5f, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 3.5f,
					3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 
					3.5f, 3.5f, 3.5f, 3.5f, 3.5f, 3, 2.5f, 2, 1.5f, 1, 0.5f, 0, -0.5f, -1, -1.5f, -2,
					-2.5f, -3, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, 
					-3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -3.5f, -2, -2, -2,
					-2, -2, -2, -1.5f, -1, -0.5f, 0, -1, -1, -1, -1, 1.5, 3, -1, -1, 2, 2, 2, 2, 2, 2,
					2, 2, 2, 2, 2, 2, 2, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1.5f, 2.5f, -3,
					-2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5, 3};

float cubeY[200] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4,
					4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8, 8.5f, 9, 9.5f, 10, 10, 10, 10, 10, 10, 10, 10, 
					10, 10, 10, 10, 10, 10, 10, 9.5f, 9, 8.5f, 8, 7.5f, 7, 6.5f, 6, 5.5f, 5, 4.5f, 4,
					3.5f, 3, 2.5f, 2, 1.5f, 1, 0.5f, 9.5f, 9, 8.5f, 8, 7.5f, 6, 6, 6, 6, 6, 6.5f, 7,
					7.5f, 8, 6, 6, 5, 4.5f, 8, 7.5f, 7, 6.5f, 6, 5.5f, 5, 4.5f, 4, 3.5f, 3, 2.5f, 2, 
					4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2};

void LevelBuilder::Initialise(MeshManager& mgr)//, int levelSize)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	cubies.Initialise(*p, 1, 1);

	//Sets up the array for the cubes that make up the level
	for (int i = 0; i < 200; i++) {
		cubies.Initialise(*p, cubeX[i], cubeY[i]);
		mCubes[i] = cubies.GetCube();
		//Puts the the cube in the array
	}
}

void LevelBuilder::Render(FX::MyFX& fx)
{
	for (int i = 0; i < 200; i++) {
		fx.Render(mCubes[i], gd3dImmediateContext);
	}
}