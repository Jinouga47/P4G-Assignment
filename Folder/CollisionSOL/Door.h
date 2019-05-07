#ifndef DOOR_H
#define DOOR_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "PlayerControl.h"

class Door
{
public:
	Model mCube;
	DirectX::SimpleMath::Vector3 mVel = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mGrav = DirectX::SimpleMath::Vector3(0, 0, 0);
	DirectX::SimpleMath::Vector3 mAccel = DirectX::SimpleMath::Vector3(0, 0, 0);
	float mRadius = 0.1f;
	bool obtained;

	void Initialise(MeshManager& mgr);
	void Start(DirectX::SimpleMath::Vector3);
	void Update(float dTime, PlayerControl&);
	void Render(FX::MyFX& fx);
	bool CollisionCheck(PlayerControl&);

private:
	std::vector<Model> mCubes;
	int hoverCentre;
	float SpeedLimiter = 0.1f;
};

#endif
