#ifndef GAME_H
#define GAME_H

#include <vector>
#include <future>

#include "Mesh.h"
#include "Model.h"
#include "FX.h"
#include "SpriteFont.h"
#include "Input.h"
#include "Key.h"
#include "PlayerControl.h"
#include "LevelManager.h"
#include "Enemy.h"
#include "MenuManager.h"
#include "Door.h"


#include <Keyboard.h>
//wrap up comon behaviours, initialisation+shutdown
class Game
{
public:
	//start up and shut down
	Game() {}
	~Game() {
		Release();
	}
	//game logic, called constantly, elapsed time passed in
	void Update(float dTime);
	//render images, called constantly, elapsed time passed in
	void Render(float dTime);
	//called when ALT+ENTER or drag
	void OnResize(int screenWidth, int screenHeight);
	void Initialise();
	void Release();
	//message handling
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//camera
	const DirectX::SimpleMath::Vector3 mDefCamPos = DirectX::SimpleMath::Vector3(5, 5, -15);
	DirectX::SimpleMath::Vector3 mCamPos = DirectX::SimpleMath::Vector3(5, 5, -15);
	//ensure each mesh is loaded and release exactly once
	MeshManager mMeshMgr;
	//game models that reference meshes
	Model mSphere, mCube;
	//handy rendering state
	FX::MyFX mFX;

private:
	Game& operator=(const Game&) = delete;
	Game(const Game& m) = delete;

	//load meshes
	void Load();
	//display a message
	void LoadDisplay(float dTime);
	//light position
	DirectX::SimpleMath::Vector3 mLightPos = DirectX::SimpleMath::Vector3(0, 0, 0);
	//text
	DirectX::SpriteBatch *mpSpriteBatch = nullptr;
	DirectX::SpriteFont *mpFont = nullptr, *mpFont2 = nullptr;

	//loading handler
	struct LoadData
	{
		//second thread
		std::future<void> loader;
		//how many meshes to load
		int totalToLoad = 0;
		//tally
		int loadedSoFar = 0;
		//is the loader active
		bool running = false;
	};
	LoadData mLoadData;

	MouseAndKeys mMKInput;
	Gamepad mGamepad;

	Key mKey;
	PlayerControl mPlayer;
	LevelManager lvlManager;
	Enemy mEnemy, mEnemy2, mEnemy3;
	Door mDoor;
	MenuManager menus;
	std::vector<DirectX::SimpleMath::Vector3> playerPosList;

	enum class GameState { START, GAME, QUIT, RESULT };
	GameState gameState = GameState::START;
	int level = 1;
};

#endif




