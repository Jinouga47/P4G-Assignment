#include <string>
#include <iomanip>

#include "LevelBuilder.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

float cubeX[34] = { -3.5,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,3.5,3.5,3.5,3.5,3.5,3.5,0.5,0,-0.5,-1,-1.5,-2,-2.5,-3,-3.5,-3.5,-3.5,-3.5,-3.5,-3.5 };
float cubeY[34] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,1,1.5,2,2,2,2,2,2,2,2,2,2,2,2,2,1.5,1,0.5 };

void LevelBuilder::Initialise(MeshManager& mgr)//, int levelSize)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	mCube.Initialise(*p);

	//Sets up the array for the cubes that make up the level
	for (int i = 0; i < 34; i++) {

		mCube.GetPosition() = Vector3(cubeX[i], cubeY[i], 0);

		mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
		mCubes[i] = mCube;
		//Puts the the cube in the array
	}

}

void LevelBuilder::Render(FX::MyFX& fx)//, int levelSize)
{
	for (int i = 0; i < 34; i++) {
		fx.Render(mCubes[i], gd3dImmediateContext);
	}
}

Model LevelBuilder::GetCubes(int i) {
	return mCubes[i];
}