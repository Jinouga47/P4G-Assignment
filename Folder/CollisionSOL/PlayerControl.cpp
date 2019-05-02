#include <string>
#include <iomanip>

#include "PlayerControl.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const int MAX_CUBES = 8;
const float CUBE_SCALE = 0.2f;


void PlayerControl::Initialise(MeshManager& mgr)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	mBall.Initialise(*p);
	mBall.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	MaterialExt mat;
	mat.gfxData.Set(Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1));
	mat.flags &= ~MaterialExt::TFlags::LIT;
	mat.flags &= ~MaterialExt::TFlags::CCW_WINDING;
	mBall.SetOverrideMat(&mat);
	assert(p);
	mCube.Initialise(*p);

	Start();
}

void PlayerControl::Start()
{
	mBall.GetPosition() = Vector3(0, 4, 0);
	mVel = Vector3(0, 1, 0) * -4;
	mDblVel = Vector3(0, 1, 0) * 4;
	mGrav = Vector3(0, -9.81f, 0);
	mAccel = Vector3(0, 0, 0);
	mCOR = 1;
}

void PlayerControl::Input(std::unique_ptr<DirectX::Keyboard>& m_keyboard) {
	auto state = m_keyboard->GetState();
	tracker.Update(state);
	if (state.A)
	{
		mVel.x = -2;
		mDblVel.x = mVel.x;
		Direction = mVel.x/2;
	}
	else if (state.D)
	{
		mVel.x = 2;
		mDblVel.x = mVel.x;
		Direction = mVel.x/2;
	}
	else {
		mVel.x = 0;
		mDblVel.x = mVel.x;
		Direction = mVel.x;
	}
	if (tracker.pressed.W && !Airborne)
	{
		Airborne = true;
		SecondJump = true;
		//bounce up
		mVel.y *= -1;
		//lose energy
		mVel *= mCOR;
	}
	else if (tracker.pressed.W && Airborne && SecondJump)
	{
		//lose energy
		mDblVel *= mCOR;
		Airborne = true;
		SecondJump = false;
		//Reset the initial velocity
		mVel = Vector3(0, 1, 0) * 4;
	}
}

bool CollisionCheck(Model& player, /*LevelBuilder& level,*/ Model& cube)
{
	float player_Xmin = player.GetPosition().x - player.GetScale().x;
	float player_Xmax = player.GetPosition().x + player.GetScale().x;
	float player_Ymin = player.GetPosition().y - player.GetScale().y;
	float player_Ymax = player.GetPosition().y + player.GetScale().y;

	float cube_Xmin = cube.GetPosition().x - cube.GetScale().x;
	float cube_Xmax = cube.GetPosition().x + cube.GetScale().x;
	float cube_Ymin = cube.GetPosition().y - cube.GetScale().y;
	float cube_Ymax = cube.GetPosition().y + cube.GetScale().y;

	/*float cube_Xmin = level.GetCubes(i).GetPosition().x - level.GetCubes(i).GetScale().x;
	float cube_Xmax = level.GetCubes(i).GetPosition().x + level.GetCubes(i).GetScale().x;
	float cube_Ymin = level.GetCubes(i).GetPosition().y - level.GetCubes(i).GetScale().y;
	float cube_Ymax = level.GetCubes(i).GetPosition().y + level.GetCubes(i).GetScale().y;*/

	return (player_Xmin <= cube_Xmax && player_Xmax >= cube_Xmin) &&
		(player_Ymin <= cube_Ymax && player_Ymax >= cube_Ymin);
}

bool CollisionManager(Vector3& Vel, Vector3& DblVel, Vector3& pos, int dir, Model& player, Model& cube/*, LevelBuilder& level*/, bool airborne)
{
	//int counter = 0;
	//bool collide = false;
	//while (!collide && level.Size() >= counter) {
	//	if (CollisionCheck(player, level, level.GetCubes(counter)))
	//		collide = true;
	//	else {
	//		counter++;
	//	}
	//}
	////for (int i = 0; i < level.Size(); i++) {
	//if (CollisionCheck(player, level, level.GetCubes(counter))) {
	//	Vector3 A, B, C, D, Ap, Bp, Cp, Dp;
	//	//A = Vector3(cube.GetPosition().x - cube.GetScale().x, cube.GetPosition().y + cube.GetScale().y, 1); //Top Left
	//	//B = Vector3(cube.GetPosition().x - cube.GetScale().x, cube.GetPosition().y - cube.GetScale().y, 1); //Bottom Left
	//	//C = Vector3(cube.GetPosition().x + cube.GetScale().x, cube.GetPosition().y - cube.GetScale().y, 1); //Bottom Right
	//	//D = Vector3(cube.GetPosition().x + cube.GetScale().x, cube.GetPosition().y + cube.GetScale().y, 1); //Top Right

	//	A = Vector3(level.GetCubes(counter).GetPosition().x - level.GetCubes(counter).GetScale().x, level.GetCubes(counter).GetPosition().y + level.GetCubes(counter).GetScale().y, 1); //Top Left
	//	B = Vector3(level.GetCubes(counter).GetPosition().x - level.GetCubes(counter).GetScale().x, level.GetCubes(counter).GetPosition().y - level.GetCubes(counter).GetScale().y, 1); //Bottom Left
	//	C = Vector3(level.GetCubes(counter).GetPosition().x + level.GetCubes(counter).GetScale().x, level.GetCubes(counter).GetPosition().y - level.GetCubes(counter).GetScale().y, 1); //Bottom Right
	//	D = Vector3(level.GetCubes(counter).GetPosition().x + level.GetCubes(counter).GetScale().x, level.GetCubes(counter).GetPosition().y + level.GetCubes(counter).GetScale().y, 1); //Top Right

	//	Ap = Vector3(player.GetPosition().x - player.GetScale().x, player.GetPosition().y + player.GetScale().y, 1); //Top Left
	//	Bp = Vector3(player.GetPosition().x - player.GetScale().x, player.GetPosition().y - player.GetScale().y, 1); //Bottom Left
	//	Cp = Vector3(player.GetPosition().x + player.GetScale().x, player.GetPosition().y - player.GetScale().y, 1); //Bottom Right
	//	Dp = Vector3(player.GetPosition().x + player.GetScale().x, player.GetPosition().y + player.GetScale().y, 1); //Top Right

	//	float player_Xmin = player.GetPosition().x - player.GetScale().x;
	//	float player_Xmax = player.GetPosition().x + player.GetScale().x;
	//	float player_Ymin = player.GetPosition().y - player.GetScale().y + 0.1f;
	//	float player_Ymax = player.GetPosition().y + player.GetScale().y - 0.1f;

	//	/*float cube_Xmin = cube.GetPosition().x - cube.GetScale().x;
	//	float cube_Xmax = cube.GetPosition().x + cube.GetScale().x;
	//	float cube_Ymin = cube.GetPosition().y - cube.GetScale().y;
	//	float cube_Ymax = cube.GetPosition().y + cube.GetScale().y;*/

	//	cube = level.GetCubes(counter);

	//	float cube_Xmin = level.GetCubes(counter).GetPosition().x - level.GetCubes(counter).GetScale().x;
	//	float cube_Xmax = level.GetCubes(counter).GetPosition().x + level.GetCubes(counter).GetScale().x;
	//	float cube_Ymin = level.GetCubes(counter).GetPosition().y - level.GetCubes(counter).GetScale().y;
	//	float cube_Ymax = level.GetCubes(counter).GetPosition().y + level.GetCubes(counter).GetScale().y;

	//	if (player_Xmax >= cube_Xmin && player_Ymin < cube_Ymax && player_Ymax > cube_Ymin && dir != 0 && airborne)
	//		Vel.x = 0;
	//	else if ((pos.y <= B.y) && (pos.y <= C.y) && (pos.x + 0.1 >= B.x) && (pos.y - 0.1 <= C.x) && airborne) {
	//		Vel.y = -2;
	//		DblVel.y = -2;
	//	}
	//	else if (player_Ymin > cube_Ymax && player_Xmax > cube_Xmin && player_Xmin < cube_Xmax)
	//		return true;
	//	return false;
	//}
	//else
		return false;
	////}
	
}

void PlayerControl::Update(float dTime, float dTime2, const Vector3& camPos, MouseAndKeys& input, /*LevelBuilder& level,*/ std::unique_ptr<DirectX::Keyboard>& m_keyboard)
//																								 ^^Pass in the cubes here^^
{
	//Input(m_keyboard);

	if (mVel.y > 4)
		mVel.y = 4;

	Vector3 pos = mBall.GetPosition();
	//CollisionManager(mVel, mDblVel, pos, Direction, mBall, mCube, /*level,*/ Airborne);
	//If the Player is Airborne and they haven't used their double jump, dTime2 is set to 0 so they're
	//still able to jump a second time.
	if (Airborne && SecondJump)
		dTime2 = 0;

	//If the Player is airborne and uses their second jump, their position is determined using dTime2 and mDblVel
	//instead of dTime and mVel. mDblVel and dTime2 are basically what mVel and dTime would be if the player was
	//on the ground, thus treating their airborne state as a psudeo grounded state in order for them to jump again.
	if (Airborne && !SecondJump)
		pos += mDblVel * dTime2;
	else
		pos += mVel * dTime;

	//Checks to see if the Player is beneath the floor. If they are their position is set so they are place
	//'on top' of it and the boolean states are set so the Player is treated as though they're on the ground.
	//if (pos.y < mBall.GetScale().y)
	//{
	//	pos.y = mBall.GetScale().y;
	//	Airborne = false;
	//	SecondJump = false;
	//	mDblVel = Vector3(0, 1, 0) * 4;
	//	mVel = Vector3(0, 1, 0) * -4;
	//}
	//else if (CollisionManager(mVel, mDblVel, pos, Direction, mBall, mCube, /*level,*/ Airborne)) {
	//	pos.y = mCube.GetScale().y + mCube.GetPosition().y + mBall.GetScale().y;
	//	Airborne = false;
	//	SecondJump = false;
	//	mDblVel = Vector3(0, 1, 0) * 4;
	//	mVel = Vector3(0, 1, 0) * -4;
	//}

	mBall.GetPosition() = pos;

	//Apply gravity
	//This applies the necessary accelerations in order for the Player to move (only mAccel is used currently).
	//If the Player has stopped moving, the accelerations are  set to 0,...
	if (mVel.LengthSquared() < 0.001f && fabsf(pos.y - mBall.GetScale().y) < 0.001f)
		mVel = Vector3(0, 0, 0);
	else if (mDblVel.LengthSquared() < 0.001f && fabsf(pos.y - mBall.GetScale().y) < 0.001f)
		mDblVel = Vector3(0, 0, 0);
	//but if they are still moving, depending on their state, the acceleration is multiplied by dTime and then
	//applied to their velocity.
	else
	{
		if (Airborne && !SecondJump) {
			mDblVel += mGrav * dTime2;
			mDblVel += mAccel * dTime2;
		}
		else {
			mVel += mGrav * dTime;
			mVel += mAccel * dTime;
		}
	}
}

void PlayerControl::Render(FX::MyFX& fx, float dTime)
{
	fx.Render(mBall, gd3dImmediateContext);
	FX::SetupPointLight(1, true, mBall.GetPosition(), Vector3(0, 0, 0.7f), Vector3(0, 0, 0), Vector3(0, 0, 1), 10, 0.1f);
	mCube.GetPosition() = Vector3(1, 1, 0);
	mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
	fx.Render(mCube, gd3dImmediateContext);
}

void PlayerControl::RenderText(SpriteFont *pF, SpriteBatch *pBatch)
{
	wstringstream ss;
	ss << std::setprecision(3);
	//LevelBuilder level;
	ss << L"Velocity 'x'=" << CollisionCheck(mBall, /*level,*/ mCube);
	pF->DrawString(pBatch, ss.str().c_str(), Vector2(10, 15), Colours::Blue, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

	wstringstream sq;
	sq << std::setprecision(3);
	sq << L"Velocity 'y'=" << mVel.y;
	pF->DrawString(pBatch, sq.str().c_str(), Vector2(10, 50), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

	/*wstringstream sw;
	sw << std::setprecision(3);
	sw << L"Double Velocity=" << mDblVel.y;
	pF->DrawString(pBatch, sw.str().c_str(), Vector2(10, 65), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));*/

	wstringstream sw;
	sw << std::setprecision(3);
	sw << L"Cube Position 'x'=" << mCube.GetPosition().x;
	pF->DrawString(pBatch, sw.str().c_str(), Vector2(10, 65), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

	wstringstream se;
	se << std::setprecision(3);
	se << L"Direction=" << Direction;
	pF->DrawString(pBatch, se.str().c_str(), Vector2(10, 80), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));
}

