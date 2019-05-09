#include <sstream>
#include <thread>
#include <iomanip>

#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include "GeometryBuilder.h"
#include "CommonStates.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Game::OnResize(int screenWidth, int screenHeight)
{
	OnResize_Default(screenWidth, screenHeight);
}

void Game::Load()
{
	m_keyboard = std::make_unique<Keyboard>();

	mSphere.Initialise(BuildSphere(mMeshMgr, 16, 16));

	mCube.Initialise(BuildCube(mMeshMgr));

	menus.Initialise(mMeshMgr);


	mPlayer.Initialise(mMeshMgr);
	lvlManager.Initialise(mMeshMgr);
	mKey.Initialise(mMeshMgr);
	mDoor.Initialise(mMeshMgr);
	
	mEnemy.Initialise(mMeshMgr);
	mEnemy2.Initialise(mMeshMgr);
	mEnemy3.Initialise(mMeshMgr);

	lvlManager.LevelLoad(mPlayer, mKey, mDoor, mEnemy, mEnemy2, mEnemy3, level, &playerPosList);
	mLoadData.loadedSoFar++;

}

void Game::LoadDisplay(float dTime)
{
	/*BeginRender(Colours::Black);

	mpSpriteBatch->Begin();

	static int pips = 0;
	static float elapsed = 0;
	elapsed += dTime;
	if (elapsed > 0.25f) {
		pips++;
		elapsed = 0;
	}
	if (pips > 10)
		pips = 0;
	wstringstream ss;
	ss << L"Loading meshes(" << (int)(((float)mLoadData.loadedSoFar / (float)mLoadData.totalToLoad)*100.f) << L"%) ";
	for (int i = 0; i < pips; ++i)
		ss << L'.';
	mpFont2->DrawString(mpSpriteBatch, ss.str().c_str(), Vector2(100, 200), Colours::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	ss.str(L"");
	ss << L"FPS:" << (int)(1.f / dTime);
	mpFont->DrawString(mpSpriteBatch, ss.str().c_str(), Vector2(10, 550), Colours::White, 0, Vector2(0, 0), Vector2(0.5f, 0.5f));

	mpSpriteBatch->End();

	EndRender();*/
}

void Game::Initialise()
{
	mFX.Init(gd3dDevice);


	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));

	mpSpriteBatch = new SpriteBatch(gd3dImmediateContext);
	assert(mpSpriteBatch);
	mpFont = new SpriteFont(gd3dDevice, L"../bin/data/comicSansMS.spritefont");
	assert(mpFont);

	mpFont2 = new SpriteFont(gd3dDevice, L"../bin/data/algerian.spritefont");
	assert(mpFont2);

	mLoadData.totalToLoad = 4;
	mLoadData.loadedSoFar = 0;
	mLoadData.running = true;
	mLoadData.loader = std::async(launch::async, &Game::Load, this);

	mMKInput.Initialise(GetMainWnd());
	mGamepad.Initialise();

}

void Game::Release()
{
	mFX.Release();
	mMeshMgr.Release();
	delete mpFont;
	mpFont = nullptr;
	delete mpSpriteBatch;
	mpSpriteBatch = nullptr;
	delete mpFont2;
	mpFont2 = nullptr;
}

void Game::Update(float dTime)
{
	//don't update anything that relies on loaded assets until they are loaded
	if (mLoadData.running)
		return;

	if(level == 0 && gameState == GameState::GAME)
		mPlayer.ResetTimer();

	switch (gameState)
	{
	case Game::GameState::START:
		menus.Update(m_keyboard, (int)gameState);
		gameState = (GameState)menus.getGameState();
		break;
	case Game::GameState::GAME:
		mPlayer.Input(m_keyboard);
		lvlManager.Update(mPlayer, mKey, mDoor, mEnemy, mEnemy2, mEnemy3, (int)gameState, &playerPosList);
		mPlayer.Update(dTime, dTime, mCamPos, mMKInput, m_keyboard);
		mKey.Update(dTime, mPlayer);
		mDoor.Update(dTime, mPlayer);
		playerPosList.push_back(mPlayer.playerObject.GetPosition());
		mEnemy.Update(dTime, &playerPosList);
		mEnemy2.Update(dTime, &playerPosList);
		mEnemy3.Update(dTime, &playerPosList);

		if (mKey.obtained && mDoor.CollisionCheck(mPlayer)) {
			level++;
			lvlManager.LevelLoad(mPlayer, mKey, mDoor, mEnemy, mEnemy2, mEnemy3, level, &playerPosList);
		}
		gameState = (GameState)lvlManager.GetGameState();
		break;
	case Game::GameState::QUIT:
		PostQuitMessage(0);
		return;
	default:
		menus.Update(m_keyboard, (int)gameState);
		gameState = (GameState)menus.getGameState();
		level = 0;
		break;
	}
}

void Game::Render(float dTime)
{
	if (mLoadData.running)
	{
		if (!mLoadData.loader._Is_ready())
		{
			LoadDisplay(dTime);
			return;
		}
		mLoadData.loader.get();
		mLoadData.running = false;
		return;
	}

	BeginRender(Colours::White);

	FX::SetPerFrameConsts(gd3dImmediateContext, mCamPos);

	CreateViewMatrix(FX::GetViewMatrix(), mCamPos, Vector3(5, 5, 0), Vector3(0, 1, 0));
	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 1, 1000.f);

	MaterialExt mat = MaterialExt::default;

	CommonStates state(gd3dDevice);
	mpSpriteBatch->Begin(SpriteSortMode_Deferred, state.NonPremultiplied());

	wstringstream ss;
	if (dTime > 0)
		ss << L"FPS: " << (int)(1.f / dTime);
	else
		ss << L"FPS: 0";
	mpFont->DrawString(mpSpriteBatch, ss.str().c_str(), Vector2(10, 550), Colours::Black, 0, Vector2(0, 0), Vector2(0.5f, 0.5f));

	switch (gameState)
	{
	case Game::GameState::START:
		menus.Render(mFX, dTime);
		menus.RenderText(mpFont, mpSpriteBatch, mPlayer.GetTimer());
		break;
	case Game::GameState::GAME:
		mPlayer.Render(mFX, dTime);
		mPlayer.RenderText(mpFont, mpSpriteBatch);
		lvlManager.Render(mFX);
		mEnemy.Render(mFX, dTime);
		mEnemy2.Render(mFX, dTime);
		mEnemy3.Render(mFX, dTime);
		if (!mKey.obtained)
			mKey.Render(mFX);
		else
			mDoor.Render(mFX);
		break;
	case Game::GameState::QUIT:
		PostQuitMessage(0);
		return;
	default:
		menus.Render(mFX, dTime);
		menus.RenderText(mpFont, mpSpriteBatch, mPlayer.GetTimer());
		break;
	}

	mpSpriteBatch->End();


	EndRender();

	mMKInput.PostProcess();
}

LRESULT Game::WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(msg, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(msg, wParam, lParam);
		break;

	}
	//default message handling (resize window, full screen, etc)
	return DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

