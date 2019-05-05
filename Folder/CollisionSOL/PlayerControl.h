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
	Model cube;
	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mDblVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);
	float mCOR = 1;
	int Direction = 0;
	bool Airborne = false, SecondJump = false;
	MouseAndKeys mMKInput;
	Gamepad mGamepad;
	DirectX::Keyboard::KeyboardStateTracker tracker;


	void Initialise(MeshManager& mgr);
	void Input(std::unique_ptr<DirectX::Keyboard>&);
	void Start(DirectX::SimpleMath::Vector3);

	void Update(float dTime, float dTime2, const DirectX::SimpleMath::Vector3& camPos, MouseAndKeys& input, std::unique_ptr<DirectX::Keyboard>&);
	void Render(FX::MyFX& fx, float dTime);
	void RenderText(DirectX::SpriteFont *pF, DirectX::SpriteBatch *pBatch);
private:

};

#endif
