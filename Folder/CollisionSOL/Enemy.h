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
	PlayerControl Player;
	std::vector<DirectX::SimpleMath::Vector3> posList;

	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mDblVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);

	int delayCounter = 0;
	int delay;
	
	void Initialise(MeshManager& mgr);
	void Start(int delay, std::vector<DirectX::SimpleMath::Vector3>* playerPosList);
	void Update(float dTime, const std::vector<DirectX::SimpleMath::Vector3>* playerPosList);
	bool CollisionCheck(PlayerControl& player);
	void Render(FX::MyFX& fx, float dTime);

private:

};

#endif // !ENEMY_H
