#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <Keyboard.h>
#include <vector>
class PlayerControl
{
public:
	int Direction = 0;
	bool Airborne = false, SecondJump = false;

	Model playerObject;
	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mDblVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::Keyboard::KeyboardStateTracker tracker;

	void Initialise(MeshManager& mgr);
	void Input(std::unique_ptr<DirectX::Keyboard>&);
	void Start(DirectX::SimpleMath::Vector3);
	void Update(float dTime, float dTime2, const DirectX::SimpleMath::Vector3& camPos, MouseAndKeys& input, std::unique_ptr<DirectX::Keyboard>&);
	void Render(FX::MyFX& fx, float dTime);
	void RenderText(DirectX::SpriteFont *pF, DirectX::SpriteBatch *pBatch);
private:
	float SpeedLimiter = 0.14f;
	float mCOR = 1;
};

#endif
