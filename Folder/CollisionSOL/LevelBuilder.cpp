#include <string>
#include <iomanip>

#include "LevelBuilder.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const int MAX_CUBES = 8;
const float CUBE_SCALE = 0.2f;

float cubeX[10] = { 1,2,3,4,5,6,7,8,9,10 };
float cubeY[10] = { 1,1,1,1,1,1,1,1,1,1 };


//void Initialise(MeshManager& mgr) {
//
//}
void LevelBuilder::Initialise(MeshManager& mgr)//, int levelSize)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	mCube.Initialise(*p);

	//Sets up the array for the cubes that make up the level
	for (int i = 0; i < 10; i++) {
		//The '3' will be replaced with the size of the array in that will be used
		//to hold the coordinates of the cube.

		mCube.GetPosition() = Vector3(cubeX[i], cubeY[i], 0);
		//The 'i' and '1' will be replaced with the array positions of the
		//cubes 'x' and 'y' coordinates respectively

		mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
		mCubes[i] = mCube;
		//Puts the the cube in the array
	}

	//Start();
}

void Start()
{

}

void LevelBuilder::Render(FX::MyFX& fx)//, int levelSize)
{
	for (int i = 0; i < 10; i++) {
		fx.Render(mCubes[i], gd3dImmediateContext);
	}
}