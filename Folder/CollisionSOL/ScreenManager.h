#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "PlayerControl.h"
#include <Keyboard.h>
#include <vector>
class ScreenManager
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
	enum class GameState { START, GAME, GAMEOVER, RESULT, HIGHSCORE };
	GameState state = GameState::START;

	void Initialise(MeshManager& mgr, int delay);
	void Start();
	void Update(float dTime, const std::vector<DirectX::SimpleMath::Vector3>* playerPosList);
	void LoadScreen(int);
	void Render(FX::MyFX& fx, float dTime);

private:

};

#endif // !SCREENMANAGER_H