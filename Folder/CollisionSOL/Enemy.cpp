#include <iomanip>

#include "Enemy.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const int MAX_CUBES = 8;
const float CUBE_SCALE = 0.2f;

void Enemy::Initialise(MeshManager& mgr, int delayIn)
{
	Mesh *p = mgr.GetMesh("sphere");
	assert(p);
	mBall.Initialise(*p);
	mBall.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	MaterialExt mat;
	mat.gfxData.Set(Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1));
	mat.flags &= ~MaterialExt::TFlags::LIT;
	mat.flags &= ~MaterialExt::TFlags::CCW_WINDING;
	mBall.SetOverrideMat(&mat);
	//mLastMode = mMode = Mode::WAITING;
	p = mgr.GetMesh("cube");
	assert(p);
	mCube.Initialise(*p);

	//mCubes.insert(mCubes.begin(), MAX_CUBES, mCube);
	delay = delayIn;
	Start();

}

void Enemy::Start()
{
	mBall.GetPosition() = Vector3(0.1f, 0.1f, 0);
}


bool CollisionManager(const BoundingBox& box, const BoundingSphere& sphere, Vector3& pos, int dir, Model& cube, bool& cling, bool& airborne)
{
	//Vector3 cn;
	//Vector3 A, B, C, D;
	//for (int i(0); i < 100; i++) {
	//	A = Vector3(cube.GetPosition().x - 0.3, cube.GetPosition().y + 0.3, 1); //Top Left
	//	B = Vector3(cube.GetPosition().x - 0.3, cube.GetPosition().y - 0.3, 1); //Bottom Left
	//	C = Vector3(cube.GetPosition().x + 0.3, cube.GetPosition().y - 0.3, 1); //Bottom Right
	//	D = Vector3(cube.GetPosition().x + 0.3, cube.GetPosition().y + 0.3, 1); //Top Right


	//																			//A = Vector3(level.GetCubes(i).GetPosition().x - 0.3, level.GetCubes(i).GetPosition().y + 0.3, 1); //Top Left
	//																			//B = Vector3(level.GetCubes(i).GetPosition().x - 0.3, level.GetCubes(i).GetPosition().y - 0.3, 1); //Bottom Left
	//																			//C = Vector3(level.GetCubes(i).GetPosition().x + 0.3, level.GetCubes(i).GetPosition().y - 0.3, 1); //Bottom Right
	//																			//D = Vector3(level.GetCubes(i).GetPosition().x + 0.3, level.GetCubes(i).GetPosition().y + 0.3, 1); //Top Right


	//	if (SphereToSphere(sphere, BoundingSphere(box.Center, box.Extents.x*1.5f), cn))
	//	{
	//		//cube collision
	//		if (SphereToAABBox(box, sphere, cn))
	//		{
	//			if ((pos.x <= A.x) && (pos.x <= B.x) && (pos.y + 0.1 <= A.y) && (pos.y - 0.1 >= B.y) && dir == 1) {
	//				pos.x -= 0.002f;
	//				/*if (airborne) {
	//				cling = true;
	//				airborne = false;
	//				}*/
	//			}
	//			else if ((pos.x >= D.x) && (pos.x >= C.x) && (pos.y + 0.1 <= D.y) && (pos.y - 0.1 >= C.y) && dir == -1)
	//				pos.x += 0.002f;
	//			else if ((pos.y <= B.y) && (pos.y <= C.y) && (pos.x + 0.1 >= B.x) && (pos.y - 0.1 <= C.x))
	//				pos.y -= 0.004f;
	//			else if ((pos.y >= A.y) && (pos.y >= D.y) && (pos.x + 0.1 >= A.x) && (pos.y - 0.1 <= D.x)) {
	//				pos.y = cube.GetPosition().x + cube.GetScale().x + 0.1;
	//				return true;
	//			}
	//			//else
	//			//cling = false;
	//		}
	//	}
	//	//cling = false;
	//}
	return false;
}

void Enemy::Update(float dTime, const std::vector<DirectX::SimpleMath::Vector3>* playerPosList)
//																								 ^^Pass in the cubes here^^
{

	if (delayCounter > delay)
	{
		mBall.GetPosition() = playerPosList->at(delayCounter - delay);
	}
	delayCounter++;

	//Input();

	//if (mVel.y > 4)
	//	mVel.y = 4;

	//Vector3 pos = mBall.GetPosition();

	////If the Player is not Airborne (meaning they're on the ground), dTime won't change. This stops
	////the player object from jumping as dTime is used for that.
	////if (!Airborne) {
	//if (CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f, 0.25f, 0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), pos, Direction, mCube, Cling, Airborne)) {
	//	dTime = 0;
	//	dTime2 = 0;
	//}
	////If the Player is Airborne and they haven't used their double jump, dTime2 is set to 0 so they're
	////still able to jump a second time.
	//else if (Airborne && SecondJump)
	//	dTime2 = 0;

	////If the Player is airborne and uses their second jump, their position is determined using dTime2 and mDblVel
	////instead of dTime and mVel. mDblVel and dTime2 are basically what mVel and dTime would be if the player was
	////on the ground, thus treating their airborne state as a psudeo grounded state in order for them to jump again.
	//if (Airborne && !SecondJump)
	//	pos += mDblVel * dTime2;
	//else
	//	pos += mVel * dTime;

	////Checks to see if the Player is beneath the floor. If they are their position is set so they are place
	////'on top' of it and the boolean states are set so the Player is treated as though they're on the ground.
	//if (pos.y < mRadius)
	//{
	//	pos.y = mRadius;
	//	Airborne = false;
	//	SecondJump = false;
	//	//Cling = false;
	//	mDblVel = Vector3(0, 1, 0) * 4;
	//	mVel = Vector3(0, 1, 0) * -4;
	//}
	//else if (CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f, 0.25f, 0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), pos, Direction, mCube, Cling, Airborne))
	//{
	//	Airborne = false;
	//	SecondJump = false;
	//	//Cling = false;
	//	mDblVel = Vector3(0, 1, 0) * 4;
	//	mVel = Vector3(0, 1, 0) * -4;
	//}

	//CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f, 0.25f, 0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), pos, Direction, mCube, Cling, Airborne);
	//mBall.GetPosition() = pos;

	////apply accelerations unless we've come to a halt
	////Apply gravity
	////This applies the necessary accelerations in order for the Player to move (only mAccel is used currently).
	////If the Player has stopped moving, the accelerations are  set to 0,...
	//if (mVel.LengthSquared() < 0.001f && fabsf(pos.y - mRadius) < 0.001f)
	//	mVel = Vector3(0, 0, 0);
	//else if (mDblVel.LengthSquared() < 0.001f && fabsf(pos.y - mRadius) < 0.001f)
	//	mDblVel = Vector3(0, 0, 0);
	////but if they are still moving, depending on their state, the acceleration is multiplied by dTime and then
	////applied to their velocity.
	//else
	//{
	//	if (Airborne && !SecondJump) {
	//		mDblVel += mGrav * dTime2;
	//		mDblVel += mAccel * dTime2;
	//	}
	//	else {
	//		mVel += mGrav * dTime;
	//		mVel += mAccel * dTime;
	//	}
	//}
}

void Enemy::Render(FX::MyFX& fx, float dTime)
{
	fx.Render(mBall, gd3dImmediateContext);
	FX::SetupPointLight(2, true, mBall.GetPosition(), Vector3(0.7f, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1), 10, 0.1f);
	mCube.GetPosition() = Vector3(1, 1, 0);
	mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
	fx.Render(mCube, gd3dImmediateContext);

	/*switch (mMode)
	{
	case Mode::CUBE:
	case Mode::CUBE_MOUSE:
	mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
	fx.Render(mCube, gd3dImmediateContext);
	break;
	case Mode::MULTI:
	for (auto& c : mCubes)
	fx.Render(c, gd3dImmediateContext);
	}*/
}