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
	Mesh *p = mgr.GetMesh("sphere");
	assert(p);
	mBall.Initialise(*p);
	mBall.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	MaterialExt mat;
	mat.gfxData.Set(Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1));
	mat.flags &= ~MaterialExt::TFlags::LIT;
	mat.flags &= ~MaterialExt::TFlags::CCW_WINDING;
	mBall.SetOverrideMat(&mat);
	//mLastMode = mMode = Mode::WAITING;
	p = mgr.GetMesh("cube");
	assert(p);
	mCube.Initialise(*p);

	mCubes.insert(mCubes.begin(), MAX_CUBES, mCube);

	Start();
	m_keyboard = std::make_unique<Keyboard>();
}

void PlayerControl::Start()
{
	mBall.GetPosition() = Vector3(0, 0.1f, 0);
	mVel = Vector3(0, 1, 0) * -4;
	mDblVel = Vector3(0, 1, 0) * 4;
	mGrav = Vector3(0, -9.81f, 0);// *0.5f;
	mAccel = Vector3(0, 0, 0);
	mCOR = 1;
}

void PlayerControl::Input(MouseAndKeys& input) {
	auto state = m_keyboard->GetState();
	tracker.Update(state);
	if (state.A/* && mVel.x == 0*/)// || mGamepad.IsPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))
	{
		mBall.GetPosition().x += Left;
		Direction = -1;
	}
	else if (state.D/* && mVel.x == 0*/)// || mGamepad.IsPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		mBall.GetPosition().x += Right;
		Direction = 1;
	}
	else
		Direction = 0;
	if (tracker.pressed.W && !Airborne)
	{
		/*if (Cling) {
			if (Direction = 1)
				mVel.x = -1;
			else if (Direction = -1)
				mVel.x = 1;
			Airborne = false;
			SecondJump = false;
		}
		else {*/
			Airborne = true;
			SecondJump = true;
		//}
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

//bool CollisionManager(const BoundingBox& box, const BoundingSphere& sphere, Vector3& vel, Vector3& pos, int dir, float COR, float dTime, Model& cube)
//{
//	Vector3 cn;
//	if (SphereToSphere(sphere, BoundingSphere(box.Center, box.Extents.x*1.5f), cn))
//	{
//		//cube collision
//		if (SphereToAABBox(box, sphere, cn))
//		{
//			//we're inside, but are we already trying to escape?
//			//if we are not trying to escape then reflect our velocity and move away
//			Vector3 d(vel);
//			d.Normalize();
//			float escaping = cn.Dot(d);
////			if (escaping < 0)
//			if (true)
//			{
//				if (cube.GetPosition().x > pos.x && dir == 1)
//					pos.x -= 0.002f;
//				else if (cube.GetPosition().x < pos.x && dir == -1)
//					pos.x += 0.002f;
//				else if (cube.GetPosition().y > pos.y)
//					pos.y -= 0.002f;
//				else if (cube.GetPosition().y < pos.y) {
//					pos.y += 0.002f;
//					return true;
//				}					
//				//not an escape angle so reflect
//				//vel = Vector3::Reflect(vel, cn);
//				//vel *= COR;
//				//pos = sphere.Center;
//				//pos += vel * dTime;
//			}
//			/*else
//				pos.y -= 0.02f;*/
//			return false;
//		}
//	}
//	return false;
//}

bool CollisionManager(const BoundingBox& box, const BoundingSphere& sphere, Vector3& pos, int dir, Model& cube, bool& cling, bool& airborne)
{
	Vector3 cn;
	Vector3 A, B, C, D;
	A = Vector3(cube.GetPosition().x - 0.3, cube.GetPosition().y + 0.3, 1); //Top Left
	B = Vector3(cube.GetPosition().x - 0.3, cube.GetPosition().y - 0.3, 1); //Bottom Left
	C = Vector3(cube.GetPosition().x + 0.3, cube.GetPosition().y - 0.3, 1); //Bottom Right
	D = Vector3(cube.GetPosition().x + 0.3, cube.GetPosition().y + 0.3, 1); //Top Right
	if (SphereToSphere(sphere, BoundingSphere(box.Center, box.Extents.x*1.5f), cn))
	{
		//cube collision
		if (SphereToAABBox(box, sphere, cn))
		{
			if ((pos.x <= A.x) && (pos.x <= B.x) && (pos.y + 0.1 <= A.y) && (pos.y - 0.1 >= B.y) && dir == 1) {
				pos.x -= 0.002f;
				/*if (airborne) {
					cling = true;
					airborne = false;
				}*/
			}
			else if ((pos.x >= D.x) && (pos.x >= C.x) && (pos.y + 0.1 <= D.y) && (pos.y - 0.1 >= C.y) && dir == -1)
				pos.x += 0.002f;
			else if ((pos.y <= B.y) && (pos.y <= C.y) && (pos.x + 0.1 >= B.x) && (pos.y - 0.1 <= C.x))
				pos.y -= 0.004f;
			else if ((pos.y >= A.y) && (pos.y >= D.y) && (pos.x + 0.1 >= A.x) && (pos.y - 0.1 <= D.x)) {
				pos.y = cube.GetPosition().x + cube.GetScale().x + 0.1;
				return true;
			}
			//else
				//cling = false;
		}
	}
	//cling = false;
	return false;
}

void PlayerControl::Update(float dTime, float dTime2, const Vector3& camPos, MouseAndKeys& input, Model& rock)
{
	Input(input);

	if (mVel.y > 4)
		mVel.y = 4;

	Vector3 pos = mBall.GetPosition();

	//If the Player is not Airborne (meaning they're on the ground), dTime won't change. This stops
	//the player object from jumping as dTime is used for that.
	//if (!Airborne) {
	if (CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f, 0.25f, 0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), pos, Direction, mCube, Cling, Airborne)) {
		dTime = 0;
		dTime2 = 0;
	}
	//If the Player is Airborne and they haven't used their double jump, dTime2 is set to 0 so they're
	//still able to jump a second time.
	else if (Airborne && SecondJump)
		dTime2 = 0;

	//If the Player is airborne and uses their second jump, their position is determined using dTime2 and mDblVel
	//instead of dTime and mVel. mDblVel and dTime2 are basically what mVel and dTime would be if the player was
	//on the ground, thus treating their airborne state as a psudeo grounded state in order for them to jump again.
	if(Airborne && !SecondJump)
		pos += mDblVel * dTime2;
	else
		pos += mVel * dTime;

	//Checks to see if the Player is beneath the floor. If they are their position is set so they are place
	//'on top' of it and the boolean states are set so the Player is treated as though they're on the ground.
	if (pos.y < mRadius)
	{
		pos.y = mRadius;
		Airborne = false;
		SecondJump = false;
		//Cling = false;
		mDblVel = Vector3(0, 1, 0) * 4;
		mVel = Vector3(0, 1, 0) * -4;
	}
	else if (CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f, 0.25f, 0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), pos, Direction, mCube, Cling, Airborne))
	{
		Airborne = false;
		SecondJump = false;
		//Cling = false;
		mDblVel = Vector3(0, 1, 0) * 4;
		mVel = Vector3(0, 1, 0) * -4;
	}

	CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f, 0.25f, 0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), pos, Direction, mCube, Cling, Airborne);
	mBall.GetPosition() = pos;

	//apply accelerations unless we've come to a halt
	//Apply gravity
	//This applies the necessary accelerations in order for the Player to move (only mAccel is used currently).
	//If the Player has stopped moving, the accelerations are  set to 0,...
	if (mVel.LengthSquared() < 0.001f && fabsf(pos.y - mRadius) < 0.001f)
		mVel = Vector3(0, 0, 0);
	else if (mDblVel.LengthSquared() < 0.001f && fabsf(pos.y - mRadius) < 0.001f)
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

void PlayerControl::RenderText(SpriteFont *pF, SpriteBatch *pBatch)
{
	wstringstream ss;
	ss << std::setprecision(3);
	ss << L"Velocity 'x'=" << mVel.x;
	pF->DrawString(pBatch, ss.str().c_str(), Vector2(10, 15), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

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

