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
	float player_Xmin = player.mBall.GetPosition().x - player.mBall.GetScale().x;
	float player_Xmax = player.mBall.GetPosition().x + player.mBall.GetScale().x;
	float player_Ymin = player.mBall.GetPosition().y - player.mBall.GetScale().y;
	float player_Ymax = player.mBall.GetPosition().y + player.mBall.GetScale().y;

	float cube_Xmin = x - 0.25f;
	float cube_Xmax = x + 0.25f;
	float cube_Ymin = y - 0.25f;
	float cube_Ymax = y + 0.25f;

	return (player_Xmin <= cube_Xmax && player_Xmax >= cube_Xmin) &&
		(player_Ymin <= cube_Ymax && player_Ymax >= cube_Ymin);
}


void CubeClass::CollisionManager(PlayerControl& player_)
{
	if (CollisionCheck(player_)) {
		Vector3 A, B, C, D, Ap, Bp, Cp, Dp;
		Model& player = player_.mBall;

		A = Vector3(x - 0.25f, y + 0.25f, 1); //Top Left
		B = Vector3(x - 0.25f, y - 0.25f, 1); //Bottom Left
		C = Vector3(x + 0.25f, y - 0.25f, 1); //Bottom Right
		D = Vector3(x + 0.25f, y + 0.25f, 1); //Top Right

		Ap = Vector3(player.GetPosition().x - player.GetScale().x, player.GetPosition().y + player.GetScale().y, 1); //Top Left
		Bp = Vector3(player.GetPosition().x - player.GetScale().x, player.GetPosition().y - player.GetScale().y, 1); //Bottom Left
		Cp = Vector3(player.GetPosition().x + player.GetScale().x, player.GetPosition().y - player.GetScale().y, 1); //Bottom Right
		Dp = Vector3(player.GetPosition().x + player.GetScale().x, player.GetPosition().y + player.GetScale().y, 1); //Top Right

		float player_Xmin = player.GetPosition().x - player.GetScale().x/* + 0.1f*/;
		float player_Xmax = player.GetPosition().x + player.GetScale().x/* - 0.1f*/;
		float player_Ymin = player.GetPosition().y - player.GetScale().y + 0.07f;
		float player_Ymax = player.GetPosition().y + player.GetScale().y - 0.07f;

		float cube_Xmin = x - 0.25f;
		float cube_Xmax = x + 0.25f;
		float cube_Ymin = y - 0.25f;
		float cube_Ymax = y + 0.25f;

		if (player_Xmax >= cube_Xmin && player_Ymin < cube_Ymax && player_Ymax > cube_Ymin && player_.Direction == 1) {
			player_.mVel.x = 0;
			player.GetPosition().x = mCube.GetPosition().x - mCube.GetScale().x - player.GetScale().x - 0.08f;
			/*if (player.GetPosition().x < -3.5f)
				int i = 0;
				//Corner glitch test breakpoint*/
		}
		else if (player_Xmax >= cube_Xmin && player_Ymin < cube_Ymax && player_Ymax > cube_Ymin && player_.Direction == -1) {
			player_.mVel.x = 0;
			player.GetPosition().x = mCube.GetScale().x + mCube.GetPosition().x + player.GetScale().x + 0.08f;
		}
		else if ((player.GetPosition().y <= B.y) && (player.GetPosition().y <= C.y) && player_.Airborne) { //Wall fast fall issue on both sides but no corner glitch
		/*else if ((player_Ymax >= cube_Ymin && player_Xmin < cube_Xmax && player_Xmax > cube_Xmin) && player.GetPosition().y < y && player_.Airborne) { /*Fixes wall faast fall issue
																																						 for collision on the left of
																																						 the player but not the right.
																																						 Also, jumping into corners
																																						 above the player glitches
																																						 their posisition.*/
			player_.mVel.y = -2;
			player_.mDblVel.y = -2;
		}
		else if (player_Ymin > cube_Ymax && player_Xmax > cube_Xmin && player_Xmin < cube_Xmax) {
			player.GetPosition().y = mCube.GetScale().y + mCube.GetPosition().y + player.GetScale().y + 0.05f;
			player_.Airborne = false;
			player_.SecondJump = false;
			player_.mDblVel = Vector3(0, 1, 0) * 5;
			player_.mVel = Vector3(0, 1, 0) * -5;
		}
	}
}