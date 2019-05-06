#include <string>
#include <iomanip>

#include "Key.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Key::Initialise(MeshManager& mgr)
{
	Mesh *p = mgr.GetMesh("sphere");
	assert(p);
	mBall.Initialise(*p);
	mBall.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	MaterialExt mat;
	mat.gfxData.Set(Vector4(1, 0, 1, 1), Vector4(1, 0, 1, 1), Vector4(1, 0, 1, 1));
	mat.flags &= ~MaterialExt::TFlags::LIT;
	mat.flags &= ~MaterialExt::TFlags::CCW_WINDING;
	mBall.SetOverrideMat(&mat);
}

void Key::Start(Vector3 startPos)
{
	mVel = Vector3(0, 1, 0) * -2;
	mGrav = Vector3(0, -5.5f, 0);
	mAccel = Vector3(0, 0, 0);
	mBall.GetPosition() = startPos;
	hoverCentre = startPos.y;
}

void Key::Update(float dTime)
{
	mBall.GetPosition() += mVel * dTime;

	if (mBall.GetPosition().y <= hoverCentre) {
		mVel -= mGrav * dTime;
		mVel -= mAccel * dTime;
		mBall.GetScale() -= mAccel * 2000 * dTime;
	}
	else {
		mVel += mGrav * dTime;
		mVel += mAccel * dTime;
		mBall.GetScale() += mAccel * 2000 * dTime;
	}
}


bool Key::CollisionCheck(PlayerControl& player)
{
	float player_Xmin = player.playerObject.GetPosition().x - player.playerObject.GetScale().x;
	float player_Xmax = player.playerObject.GetPosition().x + player.playerObject.GetScale().x;
	float player_Ymin = player.playerObject.GetPosition().y - player.playerObject.GetScale().y;
	float player_Ymax = player.playerObject.GetPosition().y + player.playerObject.GetScale().y;

	float cube_Xmin = mBall.GetPosition().x - mBall.GetScale().x;
	float cube_Xmax = mBall.GetPosition().x + mBall.GetScale().x;
	float cube_Ymin = mBall.GetPosition().y - mBall.GetScale().y;
	float cube_Ymax = mBall.GetPosition().y + mBall.GetScale().y;

	return (player_Xmin <= cube_Xmax && player_Xmax >= cube_Xmin) &&
		(player_Ymin <= cube_Ymax && player_Ymax >= cube_Ymin);
}

void Key::Render(FX::MyFX& fx)
{
	fx.Render(mBall, gd3dImmediateContext);
	FX::SetupPointLight(1, true, mBall.GetPosition(), Vector3(0, 0, 0.7f), Vector3(0, 0, 0), Vector3(0, 0, 1), 10, 0.1f);
}

