#include <string>
#include <iomanip>

#include "BallSim.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const int MAX_CUBES = 8;
const float CUBE_SCALE = 0.2f;


void BallSim::Initialise(MeshManager& mgr)
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
	mLastMode = mMode = Mode::WAITING;
	p = mgr.GetMesh("cube");
	assert(p);
	mCube.Initialise(*p);

	mCubes.insert(mCubes.begin(), MAX_CUBES, mCube);

	Start();
}

void BallSim::Input(char key)
{
	Mode mode = mLastMode;
	switch (key)
	{
	case 'x':
		break;
	case '1':
		mode = Mode::WAITING;
		break;
	case '2':
		mode = Mode::LINEAR;
		break;
	case '3':
		mode = Mode::LINEAR_ACCEL;
		break;
	case '4':
		mode = Mode::BOUNCE_INF;
		break;
	case '5':
		mode = Mode::BOUNCE;
		break;
	case '6':
		mode = Mode::CUBE;
		break;
	case '7':
		mode = Mode::CUBE_MOUSE;
		break;
	case '8':
		mode = Mode::MULTI;
		break;
	case '0':
		return;
	default:
		return;
	}
	mLastMode = mMode;
	mMode = mode;
	Start();
}

void BallSim::Start()
{
	switch (mMode)
	{
	case Mode::WAITING:
		mBall.GetPosition() = Vector3(-2, 0.5f, 0);
		mVel = Vector3(0, 1, 0) * 3;
		mGrav = Vector3(0, -9.81f, 0) * 0.5f;
		mAccel = Vector3(0, 0, 0);
		mCOR = 1;
		break;
	case Mode::LINEAR:
		mBall.GetPosition() = Vector3(-2, 1, 0);
		mVel = Vector3(1, 0, 0) * 1;
		mGrav = Vector3(0, 0, 0);
		mAccel = Vector3(0, 0, 0);
		mCOR = 1;
		break;
	case Mode::LINEAR_ACCEL:
		mBall.GetPosition() = Vector3(-2, 1, 0);
		mVel = Vector3(1, 0, 0) * 1;
		mGrav = Vector3(0, 0, 0);
		mAccel = Vector3(10, 0, 0);
		mCOR = 1;
		break;
	case Mode::BOUNCE_INF:
		mBall.GetPosition() = Vector3(-2, 0.5f, 0);
		mVel = Vector3(0.25f, 0.9f, 0) * 3;
		mGrav = Vector3(0, -9.81f, 0) * 0.5f;
		mAccel = Vector3(0, 0, 0);
		mCOR = 1;
		break;
	case Mode::BOUNCE:
		mBall.GetPosition() = Vector3(-2, 0.5f, 0);
		mVel = Vector3(0.25f, 0.9f, 0) * 3.5f;
		mGrav = Vector3(0, -9.81f, 0) * 0.5f;
		mAccel = Vector3(0, 0, 0);
		mCOR = 0.8f;
		break;
	case Mode::CUBE:
		mBall.GetPosition() = Vector3(-2, 0.5f, 0);
		mVel = Vector3(0.25f, 0.9f, 0) * GetRandom(3.f, 4.f);
		mGrav = Vector3(0, -9.81f, 0) * 0.5f;
		mAccel = Vector3(0, 0, 0);
		mCOR = 0.8f;
		mCube.GetPosition() = Vector3(GetRandom(-0.5f, 0.5f), GetRandom(0.25f, 1.f), 0);
		break;
	case Mode::CUBE_MOUSE:
		mBall.GetPosition() = Vector3(-2, 0.5f, 0);
		mVel = Vector3(0.25f, 0.9f, 0) * 3.5f;
		mGrav = Vector3(0, -9.81f, 0) * 0.5f;
		mAccel = Vector3(0, 0, 0);
		mCOR = 0.8f;
		if (mMode != mLastMode)
			mCube.GetPosition() = Vector3(0, 0.25f, 0);
		break;
	case Mode::MULTI:
		mBall.GetPosition() = Vector3(-2, 0.5f, 0);
		mVel = Vector3(0.25f, 0.9f, 0) * 3.5f;
		mGrav = Vector3(0, -9.81f, 0) * 0.5f;
		mAccel = Vector3(0, 0, 0);
		mCOR = 0.8f;
		for (auto& c : mCubes)
		{
			c.GetPosition() = Vector3(GetRandom(-2.f, 2.f), GetRandom(0.f, 1.75f), 0);
			c.GetScale() = Vector3(CUBE_SCALE, CUBE_SCALE, CUBE_SCALE);
		}
		break;
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

void BallSim::Update(float dTime, const Vector3& camPos, MouseAndKeys& input, Model& rock)
{
	Vector3 pos = mBall.GetPosition();
	pos += mVel * dTime;


	switch (mMode)
	{
	case Mode::CUBE:
	case Mode::CUBE_MOUSE:
	case Mode::BOUNCE:
	case Mode::BOUNCE_INF:
	case Mode::MULTI:
		//rock collision
		BoundingSphere head(rock.GetPosition(), 0.5f);
		Vector3 cn;
		if (SphereToSphere(BoundingSphere(mBall.GetPosition(), mRadius), head, cn))
		{
			//we're inside, but are we already trying to escape?
			//if we are not trying to escape then reflect our velocity and move away
			Vector3 d(mVel), d2(mBall.GetPosition() - rock.GetPosition());
			d.Normalize();
			d2.Normalize();
			float escaping = d2.Dot(d);
			if (escaping < 0)
			{
				//not an escape angle so reflect
				mVel = Vector3::Reflect(mVel, cn);
				mVel *= mCOR;
				pos = mBall.GetPosition();
				pos += mVel * dTime;
			}
		}
		break;
	}

	switch (mMode)
	{
	case Mode::CUBE:
	case Mode::CUBE_MOUSE:
		{
			CollisionManager(BoundingBox(mCube.GetPosition(), Vector3(0.25f,0.25f,0.25f)), BoundingSphere(mBall.GetPosition(), mRadius), mVel, pos, mCOR, dTime);
			break;
		}
	case Mode::MULTI:
		{
		for(auto& c : mCubes)
			CollisionManager(BoundingBox(c.GetPosition(), Vector3(CUBE_SCALE,CUBE_SCALE,CUBE_SCALE)), BoundingSphere(mBall.GetPosition(), mRadius), mVel, pos, mCOR, dTime);
		break;
		}
	}

	//are we beneath the floor
	if (pos.y < mRadius)
	{
		//bounce up
		mVel.y *= -1;
		//lose energy
		mVel *= mCOR;
		//ensure we aren't left under the floor
		mBall.GetPosition().y = mRadius;
		pos = mBall.GetPosition();
	}
	mBall.GetPosition() = pos;

	//apply accelerations unless we've come to a halt
	if (mVel.LengthSquared() < 0.001f && fabsf(pos.y - mRadius) < 0.001f)
		mVel = Vector3(0, 0, 0);
	else
	{
		mVel += mGrav * dTime;
		mVel += mAccel * dTime;
	}

	switch (mMode)
	{
	case Mode::CUBE_MOUSE:

		if (input.GetMouseButton(MouseAndKeys::LBUTTON))
		{
			Ray ray;
			input.MousePosToWorldRay(FX::GetViewMatrix(), FX::GetProjectionMatrix(), camPos, ray);
			float dist;
			if (RayToSphere(mCube.GetPosition(), 1.f * mCube.GetScale().x, ray, dist))
			{
				if (RayToPlane(Plane(mCube.GetPosition(), FX::GetViewMatrix().Backward()), ray, dist))
				{
					Vector3 pos(ray.position + ray.direction * dist);
					mCube.GetPosition() = pos;
				}
			}
		}
	}
}

void BallSim::Render(FX::MyFX& fx, float dTime)
{
	fx.Render(mBall, gd3dImmediateContext);
	FX::SetupPointLight(1, true, mBall.GetPosition(), Vector3(0, 0, 0.7f), Vector3(0, 0, 0), Vector3(0, 0, 1), 10, 0.1f);

	switch (mMode)
	{
	case Mode::CUBE:
	case Mode::CUBE_MOUSE:
		mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
		fx.Render(mCube, gd3dImmediateContext);
		break;
	case Mode::MULTI:
		for (auto& c : mCubes)
			fx.Render(c, gd3dImmediateContext);
	}
}

void BallSim::RenderText(SpriteFont *pF, SpriteBatch *pBatch)
{
	wstring mssg;
	switch (mMode)
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
	}
	pF->DrawString(pBatch, mssg.c_str(), Vector2(10, 10), Colours::White, 0, Vector2(0, 0));

	mssg = L"Keys: x=restart, 1=Mode::WAITING, 2=Mode::LINEAR, 3=Mode::LINEAR accel, 4=bounce infinite, 5=bounce, 6=cube, 7=cube mouse, 8=multi";
	pF->DrawString(pBatch, mssg.c_str(), Vector2(10, 30), Colours::White, 0, Vector2(0, 0), Vector2(0.7f, 0.7f));

	wstringstream ss;
	ss << std::setprecision(3);
	ss << L"Velocity=" << mVel.x << L", " << mVel.y;
	pF->DrawString(pBatch, ss.str().c_str(), Vector2(10, 45), Colours::White, 0, Vector2(0, 0), Vector2(0.75f, 0.75f));
}

