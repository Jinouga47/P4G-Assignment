#include <string>
#include <iomanip>

#include "LevelBuilder.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const int MAX_CUBES = 8;
const float CUBE_SCALE = 0.2f;


//void Initialise(MeshManager& mgr) {
//
//}
//void LevelBuilder::Initialise(MeshManager& mgr)
//{
//	Mesh *p = mgr.GetMesh("cube");
//	assert(p);
//	mCube.Initialise(*p);
//	cube test = { 0, 0, mCube };
//	vector<cube> cubes(3, test);
//	//mCubes.insert(mCubes.begin(), MAX_CUBES, mCube);
//
//	Start();
//}
//
//void Start()
//{
//
//}
//
//void LevelBuilder::Render(FX::MyFX& fx)
//{
//	for (int i = 0; i < 3; i++) {
//		mCubes.at(i).x = i;
//		mCubes.at(i).y = 1;
//		//mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
//		fx.Render(mCubes.at(i).model, gd3dImmediateContext);
//	}
//}