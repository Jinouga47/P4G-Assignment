#include <iomanip>

#include "Enemy.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Enemy::Initialise(MeshManager& mgr)
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
}

void Enemy::Start(int delayIn, vector<Vector3>* playerPosList)
{
	mBall.GetPosition() = Vector3(0.1f, 0.1f, 0);
	delay = delayIn;
	delayCounter = 0;
	playerPosList->clear();
}

void Enemy::Update(float dTime, const vector<Vector3>* playerPosList)
{

	if (delayCounter > delay)
	{
		mBall.GetPosition() = playerPosList->at(delayCounter - delay);
	}
	delayCounter++;
}

bool Enemy::CollisionCheck(PlayerControl& player)
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


void Enemy::Render(FX::MyFX& fx, float dTime)
{
	fx.Render(mBall, gd3dImmediateContext);
}