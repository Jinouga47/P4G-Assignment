#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <Keyboard.h>

class MenuManager
{
public:
	void Initialise(MeshManager& mgr);
	void Start();
	void Update(std::unique_ptr<DirectX::Keyboard>& keyboard, DirectX::SimpleMath::Vector3 mCamPos, int gameState);
	int getGameState();
	void Render(FX::MyFX& fx, float dTime);
	void RenderText(DirectX::SpriteFont *pF, DirectX::SpriteBatch *pBatch);
private:
	Model mPlayGame, mOptions, mQuit;
	int gameState;
	DirectX::SimpleMath::Vector3 mousePos;
	DirectX::Keyboard::KeyboardStateTracker tracker;
	
};

#endif