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

	delay = delayIn;
	Start();

}

void Enemy::Start()
{
	mBall.GetPosition() = Vector3(0.1f, 0.1f, 0);
}

void Enemy::Update(float dTime, const std::vector<DirectX::SimpleMath::Vector3>* playerPosList)
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

	float cube_Xmin = mBall.GetPosition().x - 0.25f;
	float cube_Xmax = mBall.GetPosition().x + 0.25f;
	float cube_Ymin = mBall.GetPosition().y - 0.25f;
	float cube_Ymax = mBall.GetPosition().y + 0.25f;

	return (player_Xmin <= cube_Xmax && player_Xmax >= cube_Xmin) &&
		(player_Ymin <= cube_Ymax && player_Ymax >= cube_Ymin);
}


void Enemy::Render(FX::MyFX& fx, float dTime)
{
	fx.Render(mBall, gd3dImmediateContext);
	FX::SetupPointLight(2, true, mBall.GetPosition(), Vector3(0.7f, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1), 10, 0.1f);
}