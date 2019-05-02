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

void CubeClass::Initialise(Mesh& mesh, float x_, float y_)
{
	x = x_;
	y = y_;

	mCube.Initialise(mesh);

	mCube.GetPosition() = Vector3(x, y, 0);

	mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
}

Model CubeClass::GetCube() {
	return mCube;
}

bool CubeClass::CollisionCheck(PlayerControl& player)
{
	float player_Xmin = player.mBall.GetPosition().x - player.mBall.GetScale().x;
	float player_Xmax = player.mBall.GetPosition().x + player.mBall.GetScale().x;
	float player_Ymin = player.mBall.GetPosition().y - player.mBall.GetScale().y;
	float player_Ymax = player.mBall.GetPosition().y + player.mBall.GetScale().y;

	float cube_Xmin = x - 0.25f;
	float cube_Xmax = x + 0.25f;
	float cube_Ymin = y - 0.25f;
	float cube_Ymax = y + 0.25f;

	/*float cube_Xmin = level.GetCubes(i).GetPosition().x - level.GetCubes(i).GetScale().x;
	float cube_Xmax = level.GetCubes(i).GetPosition().x + level.GetCubes(i).GetScale().x;
	float cube_Ymin = level.GetCubes(i).GetPosition().y - level.GetCubes(i).GetScale().y;
	float cube_Ymax = level.GetCubes(i).GetPosition().y + level.GetCubes(i).GetScale().y;*/

	return (player_Xmin <= cube_Xmax && player_Xmax >= cube_Xmin) &&
		(player_Ymin <= cube_Ymax && player_Ymax >= cube_Ymin);
}


bool CubeClass::CollisionManager(PlayerControl& player_)
{
	/*int counter = 0;
	bool collide = false;
	while (!collide && level.Size() >= counter) {
		if (CollisionCheck(player, level, level.GetCubes(counter)))
			collide = true;
		else {
			counter++;
		}
	}*/
	//for (int i = 0; i < level.Size(); i++) {
	if (CollisionCheck(player_)) {
		Vector3 A, B, C, D, Ap, Bp, Cp, Dp;
		Model& player = player_.mBall;

		A = Vector3(x - 0.25f, y + 0.25f, 1); //Top Left
		B = Vector3(x - 0.25f, y - 0.25f, 1); //Bottom Left
		C = Vector3(x + 0.25f, y - 0.25f, 1); //Bottom Right
		D = Vector3(x + 0.25f, y + 0.25f, 1); //Top Right

		Ap = Vector3(player.GetPosition().x - player.GetScale().x, player.GetPosition().y + player.GetScale().y, 1); //Top Left
		Bp = Vector3(player.GetPosition().x - player.GetScale().x, player.GetPosition().y - player.GetScale().y, 1); //Bottom Left
		Cp = Vector3(player.GetPosition().x + player.GetScale().x, player.GetPosition().y - player.GetScale().y, 1); //Bottom Right
		Dp = Vector3(player.GetPosition().x + player.GetScale().x, player.GetPosition().y + player.GetScale().y, 1); //Top Right

		float player_Xmin = player.GetPosition().x - player.GetScale().x;
		float player_Xmax = player.GetPosition().x + player.GetScale().x;
		float player_Ymin = player.GetPosition().y - player.GetScale().y + 0.1f;
		float player_Ymax = player.GetPosition().y + player.GetScale().y - 0.1f;

		float cube_Xmin = x - 0.25f;
		float cube_Xmax = x + 0.25f;
		float cube_Ymin = y - 0.25f;
		float cube_Ymax = y + 0.25f;

		if (player_Xmax >= cube_Xmin && player_Ymin < cube_Ymax && player_Ymax > cube_Ymin && player_.Direction == 1/* && player_.Airborne*/) {
			player_.mVel.x = 0;
			player.GetPosition().x = mCube.GetScale().x - mCube.GetPosition().x - player.GetScale().x - 0.08f;
		}
		else if (player_Xmax >= cube_Xmin && player_Ymin < cube_Ymax && player_Ymax > cube_Ymin && player_.Direction == -1/* && player_.Airborne*/) {
			player_.mVel.x = 0;
			player.GetPosition().x = mCube.GetScale().x + mCube.GetPosition().x + player.GetScale().x + 0.08f;
		}
		else if ((player.GetPosition().y <= B.y) && (player.GetPosition().y <= C.y) && (player.GetPosition().x + 0.1 >= B.x) && (player.GetPosition().y - 0.1 <= C.x) && player_.Airborne) {
			player_.mVel.y = -2;
			player_.mDblVel.y = -2;
		}
		else if (player_Ymin > cube_Ymax && player_Xmax > cube_Xmin && player_Xmin < cube_Xmax) {
			player.GetPosition().y = mCube.GetScale().y + mCube.GetPosition().y + player.GetScale().y + 0.05f;
			player_.Airborne = false;
			player_.SecondJump = false;
			player_.mDblVel = Vector3(0, 1, 0) * 4;
			player_.mVel = Vector3(0, 1, 0) * -4;
		}
		return false;
	}
	else
		return false;
	//}

}