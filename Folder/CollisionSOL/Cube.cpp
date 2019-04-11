#include <string>
#include <iomanip>

#include "CubeClass.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//float cubeX[34] = { -3.5,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,3.5,3.5,3.5,3.5,3.5,3.5,0.5,0,-0.5,-1,-1.5,-2,-2.5,-3,-3.5,-3.5,-3.5,-3.5,-3.5,-3.5 };
//float cubeY[34] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.5,1,1.5,2,2,2,2,2,2,2,2,2,2,2,2,2,1.5,1,0.5 };

//void CubeClass::Initialise(MeshManager& mgr, int x, int y)
//{
//	Mesh *p = mgr.GetMesh("cube");
//	assert(p);
//	//mCube.Initialise(*p);
//	test(*p);
//
//	//Sets up the array for the cubes that make up the level
//
//	mCube.GetPosition() = Vector3(x, y, 0);
//
//	mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
//	//mCubes[i] = mCube;
//	//Puts the the cube in the array
//
//}

void CubeClass::Initialise(Mesh& mesh, float x, float y)
{
	mCube.Initialise(mesh);

	mCube.GetPosition() = Vector3(x, y, 0);

	mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
}

Model CubeClass::GetCube() {
	return mCube;
}