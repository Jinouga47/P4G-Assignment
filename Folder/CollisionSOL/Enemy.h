#ifndef ENEMY_H
#define ENEMY_H


#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"


class Enemy
{
public:
	Model mBall;
	Model mCube;
	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mDblVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);
	float mCOR = 1;
	float mRadius = 0.1f;
	float Left = -0.002f;
	float Right = 0.002f;
	bool Airborne = false, SecondJump = false, Held = false;
	enum class Mode { WAITING, LINEAR, LINEAR_ACCEL, BOUNCE_INF, BOUNCE, CUBE, CUBE_MOUSE, MULTI };
	Mode mMode, mLastMode;
	MouseAndKeys mMKInput;
	Gamepad mGamepad;

	void Initialise(MeshManager& mgr);
	void Input(MouseAndKeys&);
	void Start();

	void Update(float dTime, float dTime2, const DirectX::SimpleMath::Vector3& camPos, MouseAndKeys& input, Model& rock);
	void Render(FX::MyFX& fx, float dTime);
	void RenderText(DirectX::SpriteFont *pF, DirectX::SpriteBatch *pBatch);
private:
	std::vector<Model> mCubes;
};

#endif