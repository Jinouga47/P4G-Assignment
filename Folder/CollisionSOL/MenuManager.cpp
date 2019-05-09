#include <string>
#include <iomanip>

#include "MenuManager.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void MenuManager::Initialise(MeshManager& mgr)
{
	Mesh *p = mgr.GetMesh("cube");
	assert(p);
	mPlayGame.Initialise(*p);
	mQuit.Initialise(*p);

	MaterialExt mat;
	mat.gfxData.Set(Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1));
	mat.flags &= ~MaterialExt::TFlags::CCW_WINDING;
	mat.flags &= ~MaterialExt::TFlags::LIT;
	mPlayGame.SetOverrideMat(&mat);
	mQuit.SetOverrideMat(&mat);
	assert(p);
	Start();
}

void MenuManager::Start()
{
	float boxPosX(5), boxPosZ(0);
	Vector3 boxScale = Vector3(3, 0.4f, 0);

	mPlayGame.GetPosition() = Vector3(boxPosX, 6, boxPosZ);
	mQuit.GetPosition() = Vector3(boxPosX, 2, boxPosZ);

	mPlayGame.GetScale() = boxScale;
	mQuit.GetScale() = boxScale;
}

void MenuManager::Update(unique_ptr<DirectX::Keyboard>& m_keyboard, int gameState)
{
	this->gameState = gameState;
	auto state = m_keyboard->GetState();

	tracker.Update(state);
	if ((state.Enter || state.Space) && (gameState == 0 || gameState == 3))//If the start menu is on screen or rhe result screen is, the user can start the game
		this->gameState = 1;
	else if (state.Q && (gameState == 0 || gameState == 3))//If the main menu is up or on the result screen, the user can quit
		this->gameState = 2;
}

int MenuManager::getGameState()
{
	return gameState;
}

void MenuManager::Render(FX::MyFX& fx, float dTime)
{
	fx.Render(mPlayGame, gd3dImmediateContext);
	fx.Render(mQuit, gd3dImmediateContext);
}

void MenuManager::RenderText(SpriteFont *pF, SpriteBatch *pBatch, float timer)
{
	wstring mssg;
	if (gameState == 0) {
		mssg = L"Play Game (Enter)";
		pF->DrawString(pBatch, mssg.c_str(), Vector2(420, 305), Colours::White, 0, Vector2(0, 0));
		mssg = L"Quit (Q)";
		pF->DrawString(pBatch, mssg.c_str(), Vector2(480, 555), Colours::White, 0, Vector2(0, 0));
		mssg = L"SPOOKY BOY";
		pF->DrawString(pBatch, mssg.c_str(), Vector2(420, 200), Colours::Black, 0, Vector2(0, 0), 1.5f);
	}
	else if(gameState == 3 ){
		wstringstream se;
		se << std::setprecision(3);
		se << L"TIME: " << timer<< "seconds";
		pF->DrawString(pBatch, se.str().c_str(), Vector2(420, 200), Colours::Black, 0, Vector2(0, 0), 1.5f);

		mssg = L"Replay Game (Enter)";
		pF->DrawString(pBatch, mssg.c_str(), Vector2(420, 305), Colours::White, 0, Vector2(0, 0));

		mssg = L"Quit (Q)";
		pF->DrawString(pBatch, mssg.c_str(), Vector2(480, 555), Colours::White, 0, Vector2(0, 0));
	}

	//mssg = L"Keys: 1= MenuManager, 2= Options, 3= Play Game";
	//the screen space is (0-1000,0-745) fo ui text
	//pF->DrawString(pBatch, mssg.c_str(), Vector2(10, 745), Colours::White, 0, Vector2(0, 0), Vector2(0.75f, 0.75f));
}