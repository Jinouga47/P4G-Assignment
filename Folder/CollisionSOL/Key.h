#ifndef KEY_H
#define KEY_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "PlayerControl.h"

class Key
{
public:
	Model mBall;
	Model mCube;
	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);
	float mRadius = 0.1f;

	void Initialise(MeshManager& mgr);
	void Start(DirectX::SimpleMath::Vector3);
	bool CollisionCheck(PlayerControl&);
	void Update(float dTime);
	void Render(FX::MyFX& fx);
private:
	std::vector<Model> mCubes;
	int hoverCentre;
};

#endif