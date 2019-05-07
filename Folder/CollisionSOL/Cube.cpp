#include <string>
#include <iomanip>

#include "CubeClass.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void CubeClass::Initialise(Mesh& mesh, float x_, float y_)
{
	x = x_;
	y = y_;

	mCube.Initialise(mesh);

	mCube.GetPosition() = Vector3(x, y, 0);

	mCube.GetScale() = Vector3(0.25f, 0.25f, 0.25f);
}

Model CubeClass::GetCube() {
	return mCube;
}

bool CubeClass::CollisionCheck(PlayerControl& player)
{
	float player_Xmin = player.playerObject.GetPosition().x - player.playerObject.GetScale().x;
	float player_Xmax = player.playerObject.GetPosition().x + player.playerObject.GetScale().x;
	float player_Ymin = player.playerObject.GetPosition().y - player.playerObject.GetScale().y;
	float player_Ymax = player.playerObject.GetPosition().y + player.playerObject.GetScale().y;

	float cube_Xmin = x - mCube.GetScale().x;
	float cube_Xmax = x + mCube.GetScale().x;
	float cube_Ymin = y - mCube.GetScale().y;
	float cube_Ymax = y + mCube.GetScale().y;

	return (player_Xmin <= cube_Xmax && player_Xmax >= cube_Xmin) &&
		(player_Ymin <= cube_Ymax && player_Ymax >= cube_Ymin);
}


void CubeClass::CollisionManager(PlayerControl& player_)
{
	if (CollisionCheck(player_)) {
		Vector3 A, B, C, D;
		Model& player = player_.playerObject;
		float tempYBuffer = 0.07f;
		float tempXBuffer = 0.08f;
		float tempYScale = 0.05f;

		A = Vector3(x - mCube.GetScale().x, y + mCube.GetScale().y, 1); //Top Left
		B = Vector3(x - mCube.GetScale().x, y - mCube.GetScale().y, 1); //Bottom Left
		C = Vector3(x + mCube.GetScale().x, y - mCube.GetScale().y, 1); //Bottom Right
		D = Vector3(x + mCube.GetScale().x, y + mCube.GetScale().y, 1); //Top Right

		float player_Xmin = player.GetPosition().x - player.GetScale().x;
		float player_Xmax = player.GetPosition().x + player.GetScale().x;
		float player_Ymin = player.GetPosition().y - player.GetScale().y + tempYBuffer;
		float player_Ymax = player.GetPosition().y + player.GetScale().y - tempYBuffer;

		float cube_Xmin = x - mCube.GetScale().x;
		float cube_Xmax = x + mCube.GetScale().x;
		float cube_Ymin = y - mCube.GetScale().y;
		float cube_Ymax = y + mCube.GetScale().y;

		if (player_Xmax >= cube_Xmin && player_Ymin < cube_Ymax && player_Ymax > cube_Ymin && player_.Direction == 1) {
			player_.mVel.x = 0;
			player.GetPosition().x = mCube.GetPosition().x - mCube.GetScale().x - player.GetScale().x - tempXBuffer;
		}
		else if (player_Xmax >= cube_Xmin && player_Ymin < cube_Ymax && player_Ymax > cube_Ymin && player_.Direction == -1) {
			player_.mVel.x = 0;
			player.GetPosition().x = mCube.GetScale().x + mCube.GetPosition().x + player.GetScale().x + tempXBuffer;
		}
		else if ((player.GetPosition().y <= B.y) && (player.GetPosition().y <= C.y) && player_.Airborne) { //Wall fast fall issue on both sides but no corner glitch
			player_.mVel.y = -2;
			player_.mDblVel.y = -2;
		}
		else if (player_Ymin > cube_Ymax && player_Xmax > cube_Xmin && player_Xmin < cube_Xmax) {
			player.GetPosition().y = mCube.GetScale().y + mCube.GetPosition().y + player.GetScale().y + tempYScale;
			player_.Airborne = false;
			player_.SecondJump = false;
			player_.mDblVel = Vector3(0, 1, 0) * 5;
			player_.mVel = Vector3(0, 1, 0) * -5;
		}
	}
}