#include <iomanip>

#include "ScreenManager.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void ScreenManager::Initialise(MeshManager& mgr, int delayIn)
{
	Mesh *p = mgr.GetMesh("sphere");
	assert(p);
	mBall.Initialise(*p);
	mBall.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	MaterialExt mat;
	mat.gfxData.Set(Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1));
	mat.flags &= ~MaterialExt::TFlags::LIT;
	mat.flags &= ~MaterialExt::TFlags::CCW_WINDING;
	mBall.SetOverrideMat(&mat);

	delay = delayIn;
	Start();

}

void ScreenManager::Start()
{
	mBall.GetPosition() = Vector3(0.1f, 0.1f, 0);
}

void ScreenManager::Update(float dTime, const vector<Vector3>* playerPosList)
{

	if (delayCounter > delay)
	{
		mBall.GetPosition() = playerPosList->at(delayCounter - delay);
	}
	delayCounter++;
}

void ScreenManager::LoadScreen(int screen)
{
	
}


void ScreenManager::Render(FX::MyFX& fx, float dTime)
{
	fx.Render(mBall, gd3dImmediateContext);
	FX::SetupPointLight(2, true, mBall.GetPosition(), Vector3(0.7f, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1), 10, 0.1f);
}