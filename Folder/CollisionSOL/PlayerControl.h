#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
//#include "LevelBuilder.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <Keyboard.h>
#include <vector>
class PlayerControl
{
public:
	Model mBall;
	Model mCube;
	//Model mCubes[100];
	Model cube;
	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mDblVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);
	float mCOR = 1;
	float mRadius = 0.1f;
	float Left = -0.002f;
	float Right = 0.002f;
	int Direction = 0;
	bool Airborne = false, SecondJump = false, Cling = false;
	enum class Mode { WAITING, LINEAR, LINEAR_ACCEL, BOUNCE_INF, BOUNCE, CUBE, CUBE_MOUSE, MULTI };
	Mode mMode, mLastMode;
	MouseAndKeys mMKInput;
	Gamepad mGamepad;
//	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	DirectX::Keyboard::KeyboardStateTracker tracker;


	void Initialise(MeshManager& mgr);
	void Input(std::unique_ptr<DirectX::Keyboard>&);
	void Start();

	//void Update(float dTime, float dTime2, const DirectX::SimpleMath::Vector3& camPos, MouseAndKeys& input, LevelBuilder& level, std::unique_ptr<DirectX::Keyboard>&);
	void Update(float dTime, float dTime2, const DirectX::SimpleMath::Vector3& camPos, MouseAndKeys& input, std::unique_ptr<DirectX::Keyboard>&);
	void Render(FX::MyFX& fx, float dTime);
	void RenderText(DirectX::SpriteFont *pF, DirectX::SpriteBatch *pBatch);
	void SetCube(Model&);
private:
	//std::vector<Model> mCubes;
};

#endif
