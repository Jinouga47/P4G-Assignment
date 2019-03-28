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
}

void PlayerControl::Start()
{
	mBall.GetPosition() = Vector3(0, 0.1f, 0);
	mVel = Vector3(0, 1, 0) * 4;
	mDblVel = Vector3(0, 1, 0) * 4;
	mGrav = Vector3(0, -9.81f, 0);// *0.5f;
	mAccel = Vector3(0, 0, 0);
	mCOR = 1;
}

void PlayerControl::Input(MouseAndKeys& input) {
	if (input.IsPressed(VK_A))// || mGamepad.IsPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))
		mBall.GetPosition().x += Left;
	else if (input.IsPressed(VK_D))// || mGamepad.IsPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))
		mBall.GetPosition().x += Right;
	if (input.IsPressed(VK_W) && !Airborne)// && !Held)// || mGamepad.IsPressed(0, XINPUT_GAMEPAD_DPAD_UP))
	{
		//bounce up
		mVel.y *= -1;
		//lose energy
		mVel *= mCOR;
		Airborne = true;
		SecondJump = true;
	}
	if (input.IsPressed(VK_S) && Airborne && SecondJump)// && !Held)// || mGamepad.IsPressed(0, XINPUT_GAMEPAD_DPAD_UP))
	{
		//lose energy
		mDblVel *= mCOR;
		Airborne = true;
		SecondJump = false;
		//Reset the initial velocity
		mVel = Vector3(0, 1, 0) * 4;
	}
}

bool CollisionManager(const BoundingBox& box, const BoundingSphere& sphere, Vector3& vel, Vector3& pos, float COR, float dTime)
{
	Vector3 cn;
	if (SphereToSphere(sphere, BoundingSphere(box.Center, box.Extents.x*1.5f), cn))
	{
		//cube collision
		if (SphereToAABBox(box, sphere, cn))
		{
			//we're inside, but are we already trying to escape?
			//if we are not trying to escape then reflect our velocity and move away
			Vector3 d(vel);
			d.Normalize();
			float escaping = cn.Dot(d);
			if (escaping < 0)
			{
				//not an escape angle so reflect
				vel = Vector3::Reflect(vel, cn);
				vel *= COR;
				pos = sphere.Center;
				pos += vel * dTime;
			}
			return true;




		}
	}
	return false;
}

void PlayerControl::Update(float dTime, float dTime2, const Vector3& camPos, MouseAndKeys& input, Model& rock)
{
	Input(input);

	if (mVel.y > 4)
		mVel.y = 4;

	////Used to determine whether the button is still being pressed. This stops the If statements in Input
	////constantly being called, which messes with the velocity of the jumps.
	//if ((!Held && input.IsPressed(VK_W)) || (!Held && input.IsPressed(VK_S)))
	////if ((!Held && input.IsPressed(VK_S)) || (Held && input.IsPressed(VK_W)))//Test ver.
	//	Held = true;
	//else if ((Held && !input.IsPressed(VK_W)) || (Held && !input.IsPressed(VK_S)))
	////else if((Held && input.IsPressed(VK_W)) || (Held && !input.IsPressed(VK_S)))//Test ver.
	//	Held = false;

	//If the Player is not Airborne (meaning they're on the ground), dTime won't change. This stops
	//the player object from jumping as dTime is used for that.
	if (!Airborne) {
		dTime = 0;
		dTime2 = 0;
	}
	//If the Player is Airborne and they haven't used their double jump, dTime2 is set to 0 so they're
	//still able to jump a second time.
	else if (Airborne && SecondJump)
		dTime2 = 0;

	Vector3 pos = mBall.GetPosition();


	//If the Player is airborne and uses their second jump, their position is determined using dTime2 and mDblVel
	//instead of dTime and mVel. mDblVel and dTime2 are basically what mVel and dTime would be if the player was
	//on the ground, thus treating their airborne state as a psudeo grounded state in order for them to jump again.
	if(Airborne && !SecondJump)
		pos += mDblVel * dTime2;
	else
		pos += mVel * dTime;

	//Checks to see if the Player is beneath the floor. If they are their position is set so they are place
	//'on top' of it and the boolean states are set so the Player is treated as though they're on the ground.
	//#THIS WILL BE ALTERED WHEN COLLISION IS ADDED#
	if (pos.y < mRadius)
	{
		
		pos.y = mRadius;
		Airborne = false;
		SecondJump = false;
		mDblVel = Vector3(0, 1, 0) * 4;
	}
	CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f, 0.25f, 0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), mVel, pos, mCOR, dTime);
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
	wstring mssg;
	/*switch (mMode)
	{
	case Mode::WAITING:
		mssg = L"mode = Mode::WAITING";
		break;
	case Mode::LINEAR:
		mssg = L"mode = Mode::LINEAR, no gravity";
		break;
	case Mode::LINEAR_ACCEL:
		mssg = L"mode = Mode::LINEAR accel, no gravity";
		break;
	case Mode::BOUNCE_INF:
		mssg = L"mode = Bounce infinite";
		break;
	case Mode::BOUNCE:
		mssg = L"mode = Bounce";
		break;
	case Mode::CUBE:
		mssg = L"mode = Cube";
		break;
	case Mode::CUBE_MOUSE:
		mssg = L"mode = Cube - mouse control";
		break;
	case Mode::MULTI:
		mssg = L"mode = Cube - multi";
		break;
	}*/
	//pF->DrawString(pBatch, mssg.c_str(), Vector2(10, 10), Colours::White, 0, Vector2(0, 0));

	wstringstream ss;
	ss << std::setprecision(3);
	ss << L"Position=" << mBall.GetPosition().y;
	pF->DrawString(pBatch, ss.str().c_str(), Vector2(10, 15), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

	wstringstream sq;
	sq << std::setprecision(3);
	sq << L"Velocity=" << mVel.y;
	pF->DrawString(pBatch, sq.str().c_str(), Vector2(10, 30), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

	wstringstream sw;
	sw << std::setprecision(3);
	sw << L"Double Velocity=" << mDblVel.y;
	pF->DrawString(pBatch, sw.str().c_str(), Vector2(10, 45), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

	wstringstream se;
	se << std::setprecision(3);
	se << L"Held State=" << Held;
	pF->DrawString(pBatch, se.str().c_str(), Vector2(10, 60), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));
}

