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
	mCube.GetPosition() = startPos;
	obtained = false;
}

void Door::Update(float dTime, PlayerControl& player)
{
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
}

