#ifndef ENEMY_H
#define ENEMY_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "PlayerControl.h"
#include <Keyboard.h>
#include <vector>
class Enemy
{
public:

	Model mBall;
	Model mCube;
	Model mCubes[100];
	Model cube;
	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mDblVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);

	enum class Mode { WAITING, LINEAR, LINEAR_ACCEL, BOUNCE_INF, BOUNCE, CUBE, CUBE_MOUSE, MULTI };
	Mode mMode, mLastMode;
	MouseAndKeys mMKInput;
	Gamepad mGamepad;
	PlayerControl Player;
	int delayCounter = 0;
	int delay;
	std::vector<DirectX::SimpleMath::Vector3> posList;
	void Initialise(MeshManager& mgr, int delay);

	void Start();

	void Update(float dTime, const std::vector<DirectX::SimpleMath::Vector3>* playerPosList);
	void Render(FX::MyFX& fx, float dTime);

private:



};

#endif // !ENEMY_H
