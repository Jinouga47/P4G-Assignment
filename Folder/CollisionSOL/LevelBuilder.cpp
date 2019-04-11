#include <string>
#include <iomanip>

#include "LevelBuilder.h"
#include "CubeClass.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

float cubeX[34] = {-3.5f, -3, -2.5f, -2, -1.5f, -1, -0.5f, 0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 3.5f, 
					3.5f, 3.5f, 3.5f, 3.5f, 0.5f, 0, -0.5f, -1, -1.5f, -2, -2.5f, -3, -3.5f, -3.5f,
					-3.5f, -3.5f, -3.5f, -3.5f};
float cubeY[34] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,1,1.5f,2,2,2,2,2,2,2,2,2,2,2,2,2,1.5f,1,0.5f };

void LevelBuilder::Initialise(MeshManager& mgr)//, int levelSize)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	cubies.Initialise(*p, 1, 1);

	//Sets up the array for the cubes that make up the level
	for (int i = 0; i < 34; i++) {
		cubies.Initialise(*p, cubeX[i], cubeY[i]);
		mCubes[i] = cubies.GetCube();
		//Puts the the cube in the array
	}
}

void LevelBuilder::Render(FX::MyFX& fx)
{
	for (int i = 0; i < 34; i++) {
		fx.Render(mCubes[i], gd3dImmediateContext);
	}
}