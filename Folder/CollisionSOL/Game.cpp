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

	//wood floor
	mQuad.Initialise(BuildQuad(mMeshMgr));
	MaterialExt *pMat = &mQuad.GetMesh().GetSubMesh(0).material;
	pMat->gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0, 0, 0, 1));
	pMat->pTextureRV = mFX.mCache.LoadTexture("floor.dds", true, gd3dDevice);
	pMat->texture = "floor";
	mLoadData.loadedSoFar++;
	m_keyboard = std::make_unique<Keyboard>();

	//torch
	mTorch.Initialise(BuildSphere(mMeshMgr, 16,16));
	pMat = &mTorch.GetMesh().GetSubMesh(0).material;
	pMat->gfxData.Set(Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1));
	mTorch.GetScale() = Vector3(0.1f, 0.1f, 0.1f);// Vector3(0.2f, 0.1f, 0.1f);
	mTorch.GetPosition() = Vector3(0, 0.2f, 0);
	mLoadData.loadedSoFar++;

	mCube.Initialise(BuildCube(mMeshMgr));
	mLoadData.loadedSoFar++;

	mPlayer.Initialise(mMeshMgr);
	mBuilder.Initialise(mMeshMgr);
	mKey.Initialise(mMeshMgr);
	mBuilder.LevelLoad(mPlayer, mKey, 1);
	mEnemy.Initialise(mMeshMgr, 200);
	mEnemy2.Initialise(mMeshMgr, 400);
	mEnemy3.Initialise(mMeshMgr, 600);

}

void Game::LoadDisplay(float dTime)
{
	BeginRender(Colours::Black);

	mpSpriteBatch->Begin();

	static int pips = 0;
	static float elapsed = 0;
	elapsed += dTime;
	if (elapsed > 0.25f){
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

	EndRender();
}

void Game::Initialise()
{
	mFX.Init(gd3dDevice);


	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.8f,0.8f,0.8f), Vector3(0.15f,0.15f,0.15f), Vector3(0.25f,0.25f,0.25f));

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
	mGamepad.Update();

	const float camInc = 10.f * dTime;

	CubePos = mCube.GetPosition();

	float Left = -0.005f;
	float Right = 0.005f;

	mCube.GetScale() = Vector3(0.2f, 0.2f, 0.2f);


	mCamPos.x += mGamepad.GetState(0).leftStickX * dTime;
	mCamPos.z += mGamepad.GetState(0).leftStickY * dTime;
	mCamPos.y += mGamepad.GetState(0).rightStickY * dTime;



	//don't update anything that relies on loaded assets until they are loaded
	if (mLoadData.running)
		return;
	mPlayer.Input(m_keyboard);
	mBuilder.Collision(mPlayer, mKey);
	mPlayer.Update(dTime, dTime, mCamPos, mMKInput, m_keyboard);
	mKey.Update(dTime);
	playerPosList.push_back(mPlayer.playerObject.GetPosition());
	mEnemy.Update(dTime, &playerPosList);
	mEnemy2.Update(dTime, &playerPosList);
	mEnemy3.Update(dTime, &playerPosList);
	if (mEnemy.CollisionCheck(mPlayer) || mEnemy2.CollisionCheck(mPlayer) || mEnemy3.CollisionCheck(mPlayer) || mKey.CollisionCheck(mPlayer)){
		PostQuitMessage(0);
		return;
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

	BeginRender(Colours::Black);

	FX::SetPerFrameConsts(gd3dImmediateContext, mCamPos);

	CreateViewMatrix(FX::GetViewMatrix(), mCamPos, Vector3(5, 5, 0), Vector3(0, 1, 0));
	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 1, 1000.f);


	MaterialExt mat = MaterialExt::default;

	mPlayer.Render(mFX, dTime);

	mBuilder.Render(mFX);
	mEnemy.Render(mFX, dTime);
	mEnemy2.Render(mFX, dTime);
	mEnemy3.Render(mFX, dTime);
	mKey.Render(mFX);



	CommonStates state(gd3dDevice);
	mpSpriteBatch->Begin(SpriteSortMode_Deferred, state.NonPremultiplied());

	wstring mssg, mssg2;
	if (mMKInput.GetMouseButton(MouseAndKeys::LBUTTON))
	{
		//fire a ray from the camera to the point on the XY plane we mouse clicked on
		Ray ray;
		mMKInput.MousePosToWorldRay(FX::GetViewMatrix(), FX::GetProjectionMatrix(), mCamPos, ray);
		Plane p(Vector3(0, 0, 0), Vector3(0, 0, -1));
		float dist;
		ray.Intersects(p, dist);
		Vector3 pos(ray.position + ray.direction*dist);

		//show that we can generate 3D world space mouse click coordinates
		wstringstream sstr;
		sstr.precision(1);
		sstr << L"Mouse move 3D x=" << pos.x << L" y=" << pos.y << L" z=" << pos.z;
		mssg = sstr.str();
		mpFont->DrawString(mpSpriteBatch, mssg.c_str(), Vector2(10, 100), DirectX::Colors::White, 0, Vector2(0, 0), Vector2(1, 1));

		//display a saw blade on the mouse clicked XY plane to attack the rock with
		mat = MaterialExt::default;
		mat.pTextureRV = mFX.mCache.LoadTexture("saw2.dds", true, gd3dDevice);
		mat.flags |= MaterialExt::TFlags::ALPHA_TRANSPARENCY;
		mQuad.GetPosition() = pos;
		mQuad.GetRotation() = Vector3(-PI / 2, 0, GetClock() * 4);
		mQuad.GetScale() = Vector3(0.2f, 0.2f, 0.2f);
		mFX.Render(mQuad, gd3dImmediateContext, &mat);
	}



	//general messages
	wstringstream ss;
	if (dTime > 0)
		ss << L"FPS: " << (int)(1.f / dTime);
	else
		ss << L"FPS: 0";
	mpFont->DrawString(mpSpriteBatch, ss.str().c_str(), Vector2(10, 550), Colours::White, 0, Vector2(0, 0), Vector2(0.5f, 0.5f));

	mPlayer.RenderText(mpFont, mpSpriteBatch);

	mpSpriteBatch->End();


	EndRender();

	mMKInput.PostProcess();
}

LRESULT Game::WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const float camInc = 20.f * GetElapsedSec();
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		case 'x':
			mCamPos = Vector3(0, 0, -5);
			break;
		case ' ':
			mCamPos = mDefCamPos;
			break;
		}
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

