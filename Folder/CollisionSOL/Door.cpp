#include <string>
#include <iomanip>

#include "Door.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Door::Initialise(MeshManager& mgr)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	mCube.Initialise(*p);
	mCube.GetScale() = Vector3(0.2f, 0.3f, 0.1f);
	MaterialExt mat;
	mat.gfxData.Set(Vector4(1, 1, 0, 1), Vector4(1, 1, 0, 1), Vector4(1, 1, 0, 1));
	mat.flags &= ~MaterialExt::TFlags::LIT;
	mat.flags &= ~MaterialExt::TFlags::CCW_WINDING;
	mCube.SetOverrideMat(&mat);
}

void Door::Start(Vector3 startPos)
{
	mVel = Vector3(0, 0, 0) * -2;					//Middle value to 1 for moving door
	mGrav = Vector3(0, 0, 0);					//Middle value to -5.5f for moving door
	mAccel = Vector3(0, 0, 0);
	mCube.GetPosition() = startPos;
	hoverCentre = startPos.y;
	obtained = false;
}

void Door::Update(float dTime, PlayerControl& player)
{
	mCube.GetPosition() += mVel * dTime * SpeedLimiter;

	if (mCube.GetPosition().y <= hoverCentre) {
		mVel -= mGrav * dTime * SpeedLimiter;
		mVel -= mAccel * dTime * SpeedLimiter;
		mCube.GetScale() -= mAccel * 2000 * dTime * SpeedLimiter;
	}
	else {
		mVel += mGrav * dTime * SpeedLimiter;
		mVel += mAccel * dTime * SpeedLimiter;
		mCube.GetScale() += mAccel * 2000 * dTime * SpeedLimiter;
	}

	if (!obtained)
		obtained = CollisionCheck(player);
}

bool Door::CollisionCheck(PlayerControl& player)
{
	float player_Xmin = player.playerObject.GetPosition().x - player.playerObject.GetScale().x;
	float player_Xmax = player.playerObject.GetPosition().x + player.playerObject.GetScale().x;
	float player_Ymin = player.playerObject.GetPosition().y - player.playerObject.GetScale().y;
	float player_Ymax = player.playerObject.GetPosition().y + player.playerObject.GetScale().y;

	float cube_Xmin = mCube.GetPosition().x - mCube.GetScale().x;
	float cube_Xmax = mCube.GetPosition().x + mCube.GetScale().x;
	float cube_Ymin = mCube.GetPosition().y - mCube.GetScale().y;
	float cube_Ymax = mCube.GetPosition().y + mCube.GetScale().y;

	return (player_Xmin <= cube_Xmax && player_Xmax >= cube_Xmin) &&
		(player_Ymin <= cube_Ymax && player_Ymax >= cube_Ymin);
}

void Door::Render(FX::MyFX& fx)
{
	fx.Render(mCube, gd3dImmediateContext);
	FX::SetupPointLight(1, true, mCube.GetPosition(), Vector3(0, 0, 0.7f), Vector3(0, 0, 0), Vector3(0, 0, 1), 10, 0.1f);
}

